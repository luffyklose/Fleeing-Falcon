#pragma once
#include <SDL.h>
#include "TextureManager.h"

class Smoke
{
public:
	Smoke() { };
	Smoke(SDL_Renderer* pRenderer,SDL_Rect DestRect);
	~Smoke(){}

	bool SmokeAnimaRender();
	void cleanup();	
private:
	static int SmokeLife;
	int currentFrame;
	SDL_Rect DestRect,SrcRect;
	SDL_Texture* pTex = nullptr;
	SDL_Renderer* renderer;
};
