#pragma once
#include <vector>
#include "Fighter.h"
#include "DeathStar.h"

enum EnemyType
{
	X_Wing=1,
	Death_Star
};

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void CreateEnemy(EnemyType type);
	void Destroy(GameObject* GameObject);
	static EnemyManager* Instance();
	int* getRanPos();
	void TimeIncrease() { LastFighterCreateTime++; }
	int getLastCreateTime() const { return LastFighterCreateTime; }
	

	std::vector<GameObject*> FighterVec;

	const int FIGHTERCREATECD = 400;
private:
	static EnemyManager* s_pInstance;

	int LastFighterCreateTime=0;

};
