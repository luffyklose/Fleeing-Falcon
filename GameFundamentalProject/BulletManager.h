#pragma once
#include <vector>

#include "Bullet.h"
#include"Falcon.h"

class BulletManager
{
public:
	BulletManager(){};
	~BulletManager(){};

	void AddPlayerBullet(int x,int y);
	void AddPlayerBullet(int x,int y,int speedX, int speedY);
	void AddEnemyBullet(std::string id,int x,int y);
	void AddEnemyBullet(std::string id, int x, int y,int speedX,int speedY);
	void AddEnemyBullet(std::string id, int x, int y,SDL_Rect DestRect);
	void AddEnemyBullet(std::string id, int x, int y,double angle);
	void AddEnemyTrackingBullet(std::string id, int x, int y);
	void CheckPlayerBulletsCollision(std::vector<GameObject*> EnemyList, int& playerScore);
	void CheckEnemyBulletsCollision(Falcon* falcon);
	void Update();
	void Render(SDL_Renderer* Renderer);
	void setPlayerRect(GameObject* Player);
	
	std::vector <Bullet*> PlayerBullets;
	std::vector <Bullet*> EnemyBullets;

	static BulletManager* Instance();	
private:
	static BulletManager* s_pInstance;
	SDL_Rect PlayerDestRect;
};

