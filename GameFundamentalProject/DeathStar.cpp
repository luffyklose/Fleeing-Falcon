#include "DeathStar.h"

#include <iostream>


const int DEATHSTARSPEEDX = 1;
const int DEATHSTARSPEEDY = 1;
const int STARBULLETSPEED = 5;
const int STARBULLETCD = 200;
const int BULLETPERIOD = 200;
bool DeathStarHorDirX = true;
bool DeathStarHorDirY = true;

DeathStar::DeathStar(const char* TextureSheet, int x, int y) :GameObject(TextureSheet, x, y)
{
	StarState = 1;
	BulletInterval = 0;
	tag = "DeathStar";
	HP = 100;
	BulletAngle = 0;
	
	SrcRect.w = 256;
	SrcRect.h = 256;
	SrcRect.x = 0;
	SrcRect.y = 0;

	DestRect.w = SrcRect.w;
	DestRect.h = SrcRect.h;

	std::cout << "Create a Death Star! HP:" << HP<<std::endl;
}


void DeathStar::Update()
{
	switch(StarState)
	{
	case 1:
		{
		BulletInterval++;
		//std::cout << BulletInterval << std::endl;

		//飞机碰到边缘改变飞行方向
		if (DestRect.x <= 128 || DestRect.x >= 544)
			{
				DeathStarHorDirX = !DeathStarHorDirX;
				//std::cout << "改变飞行方向!\n"<<DeathStarHorDir;
			}

		//根据飞行方向进行横向移动
		switch (DeathStarHorDirX)
			{
			case true:
				DestRect.x += DEATHSTARSPEEDX;
				//std::cout << "向右飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
				break;
			case false:
				DestRect.x -= DEATHSTARSPEEDX;
				//std::cout << "向左飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
				break;
			default:
				break;
			}
		if (BulletInterval >= STARBULLETCD && BulletInterval <= STARBULLETCD + BULLETPERIOD && ((BulletInterval - STARBULLETCD) % 20 == 0))
			{
				ShootBullet();
			}
		//std::cout << "Current Health: " << HP << std::endl;
		//std::cout << DestRect.x << " " << DestRect.y << std::endl;
		break;
		}
	case 2:
		{
		//飞机碰到边缘改变飞行方向
		if (DestRect.x <= 0 || DestRect.x >= 544)
			{
				DeathStarHorDirX = !DeathStarHorDirX;
				//std::cout << "改变横向飞行方向!\n"<<DeathStarHorDir;
			}
			if(DestRect.y<=0||DestRect.y>=384)
			{
				DeathStarHorDirY = !DeathStarHorDirY;
			}

		//根据飞行方向进行移动
		switch (DeathStarHorDirX)
			{
			case true:
				DestRect.x += DEATHSTARSPEEDX;
				//std::cout << "向右飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
				break;
			case false:
				DestRect.x -= DEATHSTARSPEEDX;
				//std::cout << "向左飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
				break;
			default:
				break;
			}
			
		switch (DeathStarHorDirY)
		{
		case true:
			DestRect.y -= DEATHSTARSPEEDY;
			//std::cout << "向上飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
			break;
		case false:
			DestRect.y += DEATHSTARSPEEDY;
			//std::cout << "向下飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
			break;
		default:
			break;
		}
		BulletInterval = 0;
		//std::cout << DestRect.x << " " << DestRect.y << std::endl;
		break;
		}
	case 3:
		{
			//将死星移到指定位置
			if(DestRect.x!=272)
			{
				if(DestRect.x>272)
				{
					DeathStarHorDirX = false;
					DestRect.x -= DEATHSTARSPEEDX;
				}
				else if(DestRect.x<272)
				{
					DeathStarHorDirX = true;
					DestRect.x += DEATHSTARSPEEDX;
				}
			}
			if(DestRect.y>0)
			{
				DestRect.y -= DEATHSTARSPEEDY;
			}

			BulletInterval++;
			if (BulletInterval >= STARBULLETCD && BulletInterval <= STARBULLETCD + BULLETPERIOD && ((BulletInterval - STARBULLETCD) % 20 == 0))
			{
				ShootCircleBullet(BulletAngle);
			}
			//std::cout << DestRect.x << " " << DestRect.y << std::endl;
			//std::cout << "Bullet CD: "<<BulletInterval << std::endl;
			break;
		}
	default:
		break;		
	}
	
}

void DeathStar::ShootBullet()
{
	BulletManager::Instance()->AddEnemyBullet("DeathStar", DestRect.x + 125, DestRect.y + 256, -STARBULLETSPEED, STARBULLETSPEED);
	BulletManager::Instance()->AddEnemyBullet("DeathStar", DestRect.x + 125, DestRect.y + 256, 0, STARBULLETSPEED);
	BulletManager::Instance()->AddEnemyBullet("DeathStar", DestRect.x + 125, DestRect.y + 256, STARBULLETSPEED, STARBULLETSPEED);
	//StarBulletVec.push_back(new Bullet("DeathStar", DestRect.x + 125, DestRect.y + 256,-STARBULLETSPEED, STARBULLETSPEED));
	//StarBulletVec.push_back(new Bullet("DeathStar", DestRect.x + 125, DestRect.y + 256, 0, STARBULLETSPEED));
	//StarBulletVec.push_back(new Bullet("DeathStar", DestRect.x + 125, DestRect.y + 256, STARBULLETSPEED, STARBULLETSPEED));
	//std::cout << (int)ComBulletVec.size() << std::endl;
	//SoundManager::Instance()->PlaySound("assest/DeathStarFire.wav", 0);
	if(BulletInterval-STARBULLETCD==100)
	{
		BulletInterval = 0;
	}
}

void DeathStar::ShootCircleBullet(double &Angle)
{
	Angle += 15;
	BulletManager::Instance()->AddEnemyBullet("DeathStar", DestRect.x + 125, DestRect.y + 256, (Angle*3.1415926/180));
	std::cout << "Angle: " <<Angle<< std::endl;
	//std::cout << "BI-BCD: " << BulletInterval - STARBULLETCD << std::endl;
	if (BulletInterval - STARBULLETCD == 200)
	{
		BulletInterval = 0;
	}
	if(Angle==165)
	{
		Angle = 0;
	}
}


void DeathStar::BulletUpdate(GameObject* PlayerFalcon)
{
	for (int i = 0; i < (int)StarBulletVec.size(); i++)
	{
		StarBulletVec[i]->ComUpdate();
		if (StarBulletVec[i]->isActive == false)
		{
			delete StarBulletVec[i];
			StarBulletVec[i] = nullptr;
		}
	}

	if (!StarBulletVec.empty())
	{
		StarBulletVec.erase(remove(StarBulletVec.begin(), StarBulletVec.end(), nullptr), StarBulletVec.end());
	}
	for (int i = 0; i < (int)StarBulletVec.size(); i++)
	{
		if (StarBulletVec[i]->isCollidingWith(*PlayerFalcon))
		{
			std::cout << "Falcon Crashed!" << std::endl;
			StarBulletVec[i]->isActive = false;
			PlayerFalcon->setActive(false);
			PlayerFalcon->Destroy();
			/*delete PlayerFalcon;
			PlayerFalcon = nullptr;*/
		}
	}
}
