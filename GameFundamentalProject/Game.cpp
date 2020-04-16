#include<iostream>
#include<vector>
#include <algorithm>
#include<string.h>

#include"Game.h"
#include "AniManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Bullet.h"
#include "DeathStar.h"
#include "Falcon.h"
#include "Fighter.h"
#include "Smoke.h"
#include "SoundManager.h"
#include "EnemyManager.h"
#include"TextManager.h"
#include"BulletManager.h"
#include"ItemManager.h"

Falcon* PlayerFalcon;
Map* map;
DeathStar* deathStar = nullptr;

SDL_Renderer* Game::pRenderer = nullptr;

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(const char* WindowTitle, int xpos, int ypos, int width, int height, bool isFullScreen)
{
	int flags = 0;
	if (isFullScreen == 1)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "INIT SUCCESS!" << std::endl;
		pWindow = SDL_CreateWindow(WindowTitle, xpos, ypos, width, height, flags);
		if (pWindow)
		{
			pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
		}
		if (pWindow && pRenderer)
		{
			std::cout << "Window and Renderer create successfully!" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
		std::cout << "INIT FAILED!" << std::endl;
	}
	TextManager::Instance()->InitTTF();
}
	

void Game::Prepare()
{
	PlayerFalcon = new Falcon("assest/Falcon.png", 400, 500);
	map = new Map();

	EnemyManager::Instance()->CreateEnemy(X_Wing);
	std::cout << "Fighter Created!" << EnemyManager::Instance()->FighterVec.size() << std::endl;

	SoundManager::Instance()->InitAll();
	SoundManager::Instance()->PlayMusic("assest/Battle_BGM.wav", -1);
}


void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:isRunning = false;
		break;
	default:break;
	}
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		//控制飞船移动及发射子弹
		case(SDLK_SPACE):
		{
			if(PlayerFalcon==nullptr)
			{
				break;
			}
			if(PlayerFalcon->FalconBulletInterval<PlayerFalcon->getBulletCD())
			{
				break;
			}
			else
			{
				BulletManager::Instance()->AddPlayerBullet(PlayerFalcon->getDestRect().x + 32, PlayerFalcon->getDestRect().y);
				PlayerFalcon->FalconBulletInterval = 0;
				break;
			}			
		}
		case(SDLK_LEFT):
		{
			if (PlayerFalcon == nullptr)
			{
				break;
			}
			if(PlayerFalcon->getDestRect().x<=0)
			{
				break;
			}
			PlayerFalcon->Move(-PlayerFalcon->getFalconSpeed(),0);
			break;
		}
		case(SDLK_RIGHT):
		{
			if (PlayerFalcon == nullptr)
			{
				break;
			}
			if (PlayerFalcon->getDestRect().x >= 736)
			{
				break;
			}
			PlayerFalcon->Move(PlayerFalcon->getFalconSpeed(), 0);
			break;
		}
		case(SDLK_UP):
		{
			if (PlayerFalcon == nullptr)
			{
				break;
			}
			if (PlayerFalcon->getDestRect().y <= 0)
			{
				break;
			}
			PlayerFalcon->Move(0,-PlayerFalcon->getFalconSpeed());
			break;
		}
		case(SDLK_DOWN):
		{
			if (PlayerFalcon == nullptr)
			{
				break;
			}
			if (PlayerFalcon->getDestRect().y >= 576)
			{
				break;
			}
			PlayerFalcon->Move(0, PlayerFalcon->getFalconSpeed());
			break;
		}

		//控制音量增减	
		case(SDLK_KP_PLUS):
		{
			SoundManager::Instance()->TurnUpVolume();
			break;
		}
		case(SDLK_KP_MINUS):
		{
			SoundManager::Instance()->TurnDownVolume();
			break;
		}

		//控制游戏退出	
		case(SDLK_ESCAPE):
		{
			isRunning=false;
			break;
		}
		}
	}
}

void Game::Input()
{

}

void Game::Update()
{
	//更新玩家及子弹状态，如果击毁敌机，更新敌机状态
	if(PlayerFalcon!=nullptr)
	{
	PlayerFalcon->Update();
	BulletManager::Instance()->setPlayerRect(PlayerFalcon);
	}

	//更新每架敌机的状态，如果击毁玩家，更新玩家飞机状态
	for(int i = 0; i < (int)EnemyManager::Instance()->FighterVec.size(); i++)
	{
		if(EnemyManager::Instance()->FighterVec[i]!=nullptr)
		{
			EnemyManager::Instance()->FighterVec[i]->Update();
		}	
	}
	
	//判定玩家是否与敌机相撞
	if(PlayerFalcon!=nullptr)
	{
		if(PlayerFalcon->getActive()==true)
		{
			for (int i = 0; i < (int)EnemyManager::Instance()->FighterVec.size(); i++)
			{
				if (EnemyManager::Instance()->FighterVec[i]->isCollidingWith(*PlayerFalcon)&& EnemyManager::Instance()->FighterVec[i]->tag.compare("DeathStar") != 0)
				{
				std::cout << "BOOM!" << std::endl;
				PlayerFalcon->setActive(false);
				EnemyManager::Instance()->FighterVec[i]->setActive(false);
				}
			}
			if(deathStar!=nullptr)
			{
				if(deathStar->isCollidingWith(*PlayerFalcon))
				{
					std::cout << "BOOM!" << std::endl;
					PlayerFalcon->setActive(false);
				}
			}
			
			for(int i=0;i<(int)ItemManager::Instance()->ItemVec.size();i++)
			{
				if (ItemManager::Instance()->ItemVec[i]->isCollidingWith(*PlayerFalcon))
				{
					std::cout << "Ding!" << std::endl;
					SoundManager::Instance()->PlaySound("assest/Ding.wav", 0);
					PLayerScore++;
					ItemManager::Instance()->ItemVec[i]->setActive(false);
				}
			}
		}
	}

	//更新游戏对象状态
	BulletManager::Instance()->Update();
	ItemManager::Instance()->Update();

	//所有子弹进行碰撞检测
	BulletManager::Instance()->CheckPlayerBulletsCollision(EnemyManager::Instance()->FighterVec, PLayerScore);
	if(PlayerFalcon!=nullptr)
	{
		BulletManager::Instance()->CheckEnemyBulletsCollision(PlayerFalcon);
	}
	
	//销毁不处于活跃状态的游戏对象
	Destroy();
	
	//每隔一定时间自动在屏幕上方生成敌机
	if(GameState==Normal)
	{
		EnemyManager::Instance()->TimeIncrease();
		if(EnemyManager::Instance()->getLastCreateTime()>= EnemyManager::Instance()->FIGHTERCREATECD)
		{
			EnemyManager::Instance()->CreateEnemy(X_Wing);
			std::cout << "Fighter Created!" << EnemyManager::Instance()->FighterVec.size() << std::endl;
		}	
	}
	
	
	//每隔2s地图滚动一次
	map->TimeCount++;
	//std::cout << map->TimeCount << std::endl;
	if(map->TimeCount >=map->SCROLLCD)
	{
		map->ChangeMap();
		//std::cout << "Map Changed!" << std::endl;
	}

	//切换游戏状态
	ChangeState();
}

void Game::Render()
{
	SDL_RenderClear(pRenderer);
	map->DrawMap();

	//渲染千年隼及敌机
	if(PlayerFalcon!=nullptr)
	{
		PlayerFalcon->Render();
	}

	for (int i = 0; i < (int)EnemyManager::Instance()->FighterVec.size(); i++)
	{
			EnemyManager::Instance()->FighterVec[i]->Render();
	}

	BulletManager::Instance()->Render(pRenderer);
	ItemManager::Instance()->Render();

	//显示玩家分数
	std::string Score= std::to_string(PLayerScore);
	Score = "Score: " + Score;
	const char* tmpText1 = Score.c_str();
	TextManager::Instance()->LoadText(tmpText1, 0, 0, 80, 30);

	
	AniManager::Instance()->AnimateSmoke();
	SDL_RenderPresent(pRenderer);

	if(PlayerFalcon==nullptr)
	{
		std::string GameOver = "GAME OVER";
		const char* tmpText2 = GameOver.c_str();
		TextManager::Instance()->LoadText(tmpText2, 150, 160, 500, 300);
	}
	if (GameState==StarDead)
	{
		std::string Win = "YOU WIN";
		const char* tmpText3 = Win.c_str();
		TextManager::Instance()->LoadText(tmpText3, 200, 160, 400, 300);
	}
}

void Game::Clean()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}

void Game::Quit()
{

}

void Game::Destroy()
{
	if(PlayerFalcon!=nullptr)
	{
		if(PlayerFalcon->getActive()==false)
		{
			PlayerFalcon->Destroy();
			delete PlayerFalcon;
			PlayerFalcon = nullptr;
		}
	}

	if(deathStar!=nullptr)
	{
		if (deathStar->getActive() == false)
		{
			deathStar->Destroy();
			delete deathStar;
			deathStar = nullptr;
		}
	}

	//销毁无效的敌机，若敌机是被击毁的，生成加分道具
	for(int i=0;i< EnemyManager::Instance()->FighterVec.size();i++)
	{
		if(EnemyManager::Instance()->FighterVec[i]->getActive()==false)
		{
			/*if(!EnemyManager::Instance()->FighterVec[i]->isAtScreen())
			{
				std::cout << "start creating star!" << std::endl;
				SDL_Rect TempRect = EnemyManager::Instance()->FighterVec[i]->getDestRect();
				ItemManager::Instance()->CreateItem(Score_Star, TempRect);
			}*/
			EnemyManager::Instance()->FighterVec[i]->Destroy();
			delete EnemyManager::Instance()->FighterVec[i];
			EnemyManager::Instance()->FighterVec[i] = nullptr;
		}
	}
	if (!EnemyManager::Instance()->FighterVec.empty())
	{
		EnemyManager::Instance()->FighterVec.erase(remove(EnemyManager::Instance()->FighterVec.begin(), EnemyManager::Instance()->FighterVec.end(), nullptr), EnemyManager::Instance()->FighterVec.end());
	}

	//销毁无效的物品
	for (int i = 0; i < ItemManager::Instance()->ItemVec.size(); i++)
	{
		if (ItemManager::Instance()->ItemVec[i]->getActive() == false)
		{
			ItemManager::Instance()->ItemVec[i]->Destroy();
			delete ItemManager::Instance()->ItemVec[i];
			ItemManager::Instance()->ItemVec[i] = nullptr;
		}
	}
	if (!ItemManager::Instance()->ItemVec.empty())
	{
		ItemManager::Instance()->ItemVec.erase(remove(ItemManager::Instance()->ItemVec.begin(), ItemManager::Instance()->ItemVec.end(), nullptr), ItemManager::Instance()->ItemVec.end());
	}
	
}

void Game::ChangeState()
{
	if (PLayerScore >= 10 && GameState == Normal)
	{
		GameState = StarShoot;
		deathStar = new DeathStar("assest/DeathStar.png", 400, 0);
		std::cout << deathStar->getHP() << std::endl;
		EnemyManager::Instance()->FighterVec.push_back(deathStar);
		deathStar->setHP(100);
		
		if(deathStar!=nullptr)
		{
			std::cout << "Death Star Created!" << std::endl;
		}
		for(int i=0;i< (int)EnemyManager::Instance()->FighterVec.size();i++)
		{
			if(EnemyManager::Instance()->FighterVec[i]->tag.compare("Fighter") == 0)
			{
				EnemyManager::Instance()->FighterVec[i]->setActive(false);
			}
		}
		std::cout << "Current State: " << GameState << std::endl;
	}
	if(GameState!=Normal)
	{
		if (deathStar->getHP() <= 70 && GameState == StarShoot)
		{
			GameState = StarCrash;
			deathStar->setState(2);
			std::cout << "Current State: " << GameState << std::endl;
		}
		if (deathStar->getHP() <= 50 && GameState == StarCrash)
		{
			GameState = StarCircle;
			deathStar->setState(3);
			std::cout << "Current State: " << GameState << std::endl;
		}
		if(deathStar->getHP()<=0&&GameState==StarCircle)
		{
			GameState = StarDead;
			deathStar->setActive(false);
			std::cout << "Current State: " << GameState << std::endl;
		}
	}
}