#pragma once
#include <iostream>
#include <SDL.h>
#include <string>

#include "AniManager.h"

class GameObject
{
public:
	GameObject(const char* TextureSheet,int x,int y);
	~GameObject();

	GameObject(GameObject const&) {};
	GameObject& operator=(GameObject const&) {};
	
	virtual void Update()=0;
	void Render();
	void Move(int x,int y);
	void Destroy();
	void setActive(bool NewStatus);
	bool getActive() { return isActive; }
	bool isCollidingWith(const GameObject& other);
	void DecHP()
	{
		HP--;
		std::cout << "Current HP: " << HP << std::endl;
	}
	int getHP() { return HP; }
	void setHP(int x) { HP = x; }
	bool isAtScreen() const;

	SDL_Rect getSrcRect() const
	{
		return SrcRect;
	}

	SDL_Rect getDestRect() const
	{
   		return DestRect;
	}

	SDL_Texture* getObjTex() { return ObjTexture; }

	std::string tag;
	
protected:
	int xpos;
	int ypos;
	bool isActive;
	int HP;

	SDL_Texture* ObjTexture;
	SDL_Rect SrcRect, DestRect;
};
