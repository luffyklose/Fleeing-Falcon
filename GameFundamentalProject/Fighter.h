#pragma once
#include <vector>

#include "GameObject.h"
#include "AniManager.h"
#include "Bullet.h"
#include "SoundManager.h"
#include "BulletManager.h"


class Fighter: public GameObject
{
public:
	//Fighter();
	Fighter(const char* TextureSheet, int x, int y):GameObject(TextureSheet,x,y)
	{
		BulletInterval = 0;
		tag = "Fighter";
	}
	//~Fighter();
	
	void Update();

	std::vector<Bullet*> ComBulletVec;
private:
	
	int BulletInterval;
	const int FIGHTBULLETCD=200;
};
