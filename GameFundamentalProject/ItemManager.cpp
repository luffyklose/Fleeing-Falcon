#include "ItemManager.h"

ItemManager* ItemManager::s_pInstance = NULL;
const int AUTOCREATEPOSY = -200;
const int WINDOWWIDTH = 800;

ItemManager* ItemManager::Instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new ItemManager();
	}

	return s_pInstance;
}

ItemManager::ItemManager()
{

}

ItemManager::~ItemManager()
{

}

void ItemManager::CreateItem(ItemType type,SDL_Rect DestRect)
{
	switch (type)
	{
	case 1:
	{
		ScoreStar* TempItem = new ScoreStar("assest/star.png", DestRect.x+16, DestRect.y+16);
		ItemVec.push_back(TempItem);
		std::cout << "Star Created!" << std::endl;
		TempItem = nullptr;
	}
	break;
	}
}

void ItemManager::Destroy(GameObject* GameObject)
{
	SDL_DestroyTexture(GameObject->getObjTex());
	delete GameObject;
	GameObject = nullptr;
}

void ItemManager::Update()
{
	for(int i=0;i<(int)ItemVec.size();i++)
	{
		ItemVec[i]->Update();
		//std::cout << ItemVec[i]->getDestRect().w << " " << ItemVec[i]->getDestRect().h << std::endl;
		if (ItemVec[i]->getActive() == false)
		{
			delete ItemVec[i];
			ItemVec[i] = nullptr;
		}
	}

	if (!ItemVec.empty())
	{
		ItemVec.erase(remove(ItemVec.begin(), ItemVec.end(), nullptr), ItemVec.end());
	}
}

void ItemManager::Render()
{
	for (int i = 0; i < (int)ItemVec.size(); i++)
	{
		ItemVec[i]->Render();
	}
}
