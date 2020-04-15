#include "BulletManager.h"

#include "ItemManager.h"
#include "SoundManager.h"

BulletManager* BulletManager::s_pInstance = NULL;

BulletManager* BulletManager::Instance()
{
	if (s_pInstance == NULL)
	{
		s_pInstance = new BulletManager();
	}

	return s_pInstance;
}

void BulletManager::AddPlayerBullet(int x, int y)
{
	PlayerBullets.push_back(new Bullet("player",x,y));
	SoundManager::Instance()->PlaySound("assest/FalconFire.wav", 0);
}

void BulletManager::AddPlayerBullet(int x,int y,int speedX,int speedY)
{
	PlayerBullets.push_back(new Bullet("player", x, y,speedX,speedY));
	SoundManager::Instance()->PlaySound("assest/FalconFire.wav", 0);
}

void BulletManager::AddEnemyBullet(std::string id, int x, int y)
{
	EnemyBullets.push_back(new Bullet(id, x, y));
	SoundManager::Instance()->PlaySound("assest/FighterFire.wav", 0);
}

void BulletManager::AddEnemyBullet(std::string id, int x, int y, int speedX, int speedY)
{
	EnemyBullets.push_back(new Bullet(id, x, y,speedX,speedY));
	SoundManager::Instance()->PlaySound("assest/FighterFire.wav", 0);
}

void BulletManager::AddEnemyBullet(std::string id, int x, int y, double angle)
{
	EnemyBullets.push_back(new Bullet(id, x, y,angle));
	SoundManager::Instance()->PlaySound("assest/FighterFire.wav", 0);
}

void BulletManager::AddEnemyBullet(std::string id, int x, int y, SDL_Rect DestRect)
{
	EnemyBullets.push_back(new Bullet(id, x, y,DestRect));
	SoundManager::Instance()->PlaySound("assest/FighterFire.wav", 0);
}

void BulletManager::AddEnemyTrackingBullet(std::string id, int x, int y)
{
	EnemyBullets.push_back(new Bullet(id, x, y, PlayerDestRect));
	SoundManager::Instance()->PlaySound("assest/FighterFire.wav", 0);
}


void BulletManager::CheckEnemyBulletsCollision(Falcon* falcon)
{
	for(int i=0;i<(int)EnemyBullets.size();i++)
	{
		if (EnemyBullets[i]->isCollidingWith(*falcon))
		{
			std::cout << "Falcon Crashed!" << std::endl;
			EnemyBullets[i]->isActive = false;
			falcon->setActive(false);
		}
	}
}

void BulletManager::CheckPlayerBulletsCollision(std::vector<GameObject*> EnemyList,int& playerScore)
{
	for (int i=0; i < (int)PlayerBullets.size();i++)
	{
		for(int j=0;j<(int)EnemyList.size();j++)
		{
			if(EnemyList[j]->tag.compare("Fighter") == 0&&PlayerBullets[i]->isCollidingWith(*EnemyList[j]))
			{
				PlayerBullets[i]->isActive = false;
				std::cout << "Fighter Crashed!" << std::endl;
				EnemyList[j]->setActive(false);
				playerScore++;
				std::cout << "start creating star!" << std::endl;
				SDL_Rect TempRect = EnemyList[j]->getDestRect();
				ItemManager::Instance()->CreateItem(Score_Star, TempRect);
			}
			if (EnemyList[j]->tag.compare("DeathStar") == 0 && PlayerBullets[i]->isCollidingWith(*EnemyList[j]))
			{
				EnemyList[j]->DecHP();
				std::cout << EnemyList[j]->getHP() << std::endl;
				PlayerBullets[i]->isActive = false;
				std::cout << "Death Star has been hit!" << std::endl;
				if (EnemyList[j]->getHP() == 0)
				{
					std::cout << "Death Star has been crashed!" << std::endl;
					EnemyList[j]->setActive(false);
					playerScore += 100;
				}
			}
		}
	}
}

void BulletManager::Update()
{
	//��������ӵ�״̬�����������Ч�ӵ�
	for (int i = 0; i < (int)PlayerBullets.size(); i++)
	{
		PlayerBullets[i]->PlayerUpdate();
		
		if (PlayerBullets[i]->isActive == false)
		{
			delete PlayerBullets[i];
			PlayerBullets[i] = nullptr;
		}
	}
	if (!PlayerBullets.empty())
	{
		PlayerBullets.erase(remove(PlayerBullets.begin(), PlayerBullets.end(), nullptr), PlayerBullets.end());
	}

	//���µл��ӵ�״̬�����ٵл��ӵ�
	for (int i = 0; i < (int)EnemyBullets.size(); i++)
	{
		EnemyBullets[i]->ComUpdate();
		
		if (EnemyBullets[i]->isActive == false)
		{
			delete EnemyBullets[i];
			EnemyBullets[i] = nullptr;
		}
	}
	if (!EnemyBullets.empty())
	{
		EnemyBullets.erase(remove(EnemyBullets.begin(), EnemyBullets.end(), nullptr), EnemyBullets.end());
	}
}

void BulletManager::Render(SDL_Renderer* Renderer)
{
	//��Ⱦ��ҷ�����ӵ�
	SDL_SetRenderDrawColor(Renderer, 255, 255, 0, 0);
	for (int i = 0; i < (int)PlayerBullets.size(); i++)
	{
		SDL_RenderFillRect(Renderer, &PlayerBullets[i]->DestRect);
	}

	//��Ⱦ�л�������ӵ�
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 0);
	for (int i = 0; i < (int)EnemyBullets.size(); i++)
	{
		SDL_RenderFillRect(Renderer, &EnemyBullets[i]->DestRect);
	}
}

void BulletManager::setPlayerRect(GameObject* Player)
{
	PlayerDestRect = Player->getDestRect();
}