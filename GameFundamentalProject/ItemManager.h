#pragma once
#include <vector>
#include"ScoreStar.h"

enum ItemType
{
	Score_Star=1
};

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	void CreateItem(ItemType type,SDL_Rect DestRect);
	void Destroy(GameObject* GameObject);
	void Update();
	void Render();
	
	static ItemManager* Instance();

	std::vector<GameObject*> ItemVec;
	const int FIGHTERCREATECD = 400;
private:
	static ItemManager* s_pInstance;
	
};
