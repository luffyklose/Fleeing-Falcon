#pragma once
#include <vector>

#include "GameObject.h"
#include "Bullet.h"
#include "SoundManager.h"
#include"BulletManager.h"

class DeathStar:public GameObject
{
public:
	DeathStar();
	DeathStar(const char* TextureSheet, int x, int y);
	//~DeathStar();

	void Update();
	//void Render();
	//void Destroy();
	void ShootBullet();
	void ShootCircleBullet(double &Angle);
	void BulletUpdate(GameObject* PlayerFalcon);
	void setState(int x) { StarState = x; }

	std::vector<Bullet*> StarBulletVec;
private:

	int BulletInterval;
	int StarState;
	int HP;
	double BulletAngle;
};
