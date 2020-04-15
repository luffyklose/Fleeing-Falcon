#include "EnemyManager.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

EnemyManager* EnemyManager::s_pInstance = NULL;
const int AUTOCREATEPOSY = -200;
const int WINDOWWIDTH = 800;

EnemyManager* EnemyManager::Instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new EnemyManager();
	}

	return s_pInstance;
}

EnemyManager::EnemyManager()
{
	
}

EnemyManager::~EnemyManager()
{
	
}

void EnemyManager::CreateEnemy(EnemyType type)
{
	switch (type)
	{
	case 1:
		{
		Fighter* TempEnemy = new Fighter("assest/X_Wing.png", getRanPos()[0], getRanPos()[1]);		
		FighterVec.push_back(TempEnemy);
		TempEnemy = nullptr;
		LastFighterCreateTime = 0;
		}
		break;
	case 2:
		DeathStar* TempEnemy= new DeathStar("assest/DeathStar.png", 400, 0);
		FighterVec.push_back(TempEnemy);
		TempEnemy = nullptr;
		break;
	}
}

void EnemyManager::Destroy(GameObject* GameObject)
{
	SDL_DestroyTexture(GameObject->getObjTex());
	delete GameObject;
	GameObject = nullptr;
}

int* EnemyManager::getRanPos()
{
	int RanPos[2];
	RanPos[1] = AUTOCREATEPOSY;
	srand((unsigned)time(NULL));
	RanPos[0] = (rand() % (WINDOWWIDTH-100))+50;
	return RanPos;
}


