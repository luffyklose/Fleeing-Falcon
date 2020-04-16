#pragma once
#include <vector>
#include "GameObject.h"
#include "AniManager.h"
#include "Bullet.h"

const int FALCONSPEED = 10;
const int BULLETCD = 10;

class Falcon:public GameObject
{
public:
	Falcon(const char* TextureSheet, int x, int y):GameObject(TextureSheet,x,y)
	{
		FalconSpeed = FALCONSPEED;
		FalconBulletCD = BULLETCD;
		FalconBulletInterval = 0;
		tag = "Falcon";
		HP = 3;
	}
	//~Falcon();

	void Update();

	int getBulletCD()
	{
		return FalconBulletCD;
	}

	int getFalconSpeed()
	{
		return FalconSpeed;
	}

	std::vector<Bullet*> PlayerBulletVec;

	int FalconBulletInterval;
private:
	int FalconSpeed;
	int FalconBulletCD;
	bool isActive;
};
