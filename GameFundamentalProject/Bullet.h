#pragma once
#include <string>

#include "GameObject.h"


const int BULLETSPEED = 5;

class Bullet
{
public:
	bool isActive;
	SDL_Rect DestRect;
	static const int BulletSpeed = BULLETSPEED;

	Bullet(std::string shooter,int x,int y);
	Bullet(std::string shooter, int x, int y,int speedX,int speedY);
	Bullet(std::string shooter, int x, int y,double angle);
	Bullet(std::string shooter,int x, int y, SDL_Rect TargetRect);

	//~Bullet();

	void PlayerUpdate();
	void ComUpdate();

	bool isCollidingWith(const GameObject& other);

private:
	int TargetX,
	TargetY,
	InitX,
	InitY;
	int SpeedX, SpeedY;
	double Distance;
};
