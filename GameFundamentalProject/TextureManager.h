#pragma once
#include "Game.h"
#include "Smoke.h"

class TextureManager {
private:
	TextureManager() {};

public:
	static SDL_Texture* LoadTexture(const char* FileLoc);
	static void Draw(SDL_Texture* Tex, SDL_Rect SrcRect, SDL_Rect DestRect);
	static void Draw(SDL_Texture* Tex, SDL_Rect DestRect);
	static SDL_Texture* LoadTexture(SDL_Surface* tempSurface);
	void ClearRender();
	static void PresentRender();
};