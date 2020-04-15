#include "Fighter.h"

#include <iostream>


const int FIGHTERSPEEDX = 1;
const int FIGHTERSPEEDY = 1;
bool FighterHorDir = true;

void Fighter::Update()
{
	SrcRect.w = 64;
	SrcRect.h = 64;
	SrcRect.x = 0;
	SrcRect.y = 0;

	DestRect.w = SrcRect.w;
	DestRect.h = SrcRect.h;

	BulletInterval++;
	//std::cout << BulletInterval << std::endl;

	//飞机碰到边缘改变飞行方向
	if(DestRect.x<=0||DestRect.x>=736)
	{
		FighterHorDir = !FighterHorDir;
		//std::cout << "改变飞行方向!\n"<<FighterHorDir;
	}
	
	//根据飞行方向进行横向移动
	switch (FighterHorDir)
	{
	case true:
		DestRect.x +=FIGHTERSPEEDX;
		DestRect.y += FIGHTERSPEEDY;
		//std::cout << "向右飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
		break;
	case false:
		DestRect.x -= FIGHTERSPEEDX;
		DestRect.y += FIGHTERSPEEDY;
		//std::cout << "向左飞了。\n" << DestRect.x << " " << DestRect.y << std::endl;
		break;
	default:
		break;
	}

	//每隔一段时间发射子弹
	if(BulletInterval>=FIGHTBULLETCD)
	{
		//ShootBullet(PlayerFalcon);
		//BulletManager::Instance()->AddEnemyBullet("fighter", DestRect.x + 32, DestRect.y + 70, PlayerFalcon->getDestRect());
		BulletManager::Instance()->AddEnemyTrackingBullet("fighter", DestRect.x + 32, DestRect.y + 70);
		BulletInterval = 0;
	}

	//销毁飞出屏幕的敌机
	if(DestRect.y>=600)
	{
		isActive = false;
	}
}
