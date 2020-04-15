#pragma once
#include"Smoke.h"

class AniManager
{
private:
	AniManager() {};
	static AniManager* s_pInstance;

	AniManager(AniManager const&) {};				// copy constructor is private
	AniManager& operator=(AniManager const&) {};	// assignment operator is private

	Smoke s;
public:
	static void DrawFrame(SDL_Texture* Tex, SDL_Rect DestRect, int x, int y, int w, int h);
	void AddSmoke(SDL_Renderer* renderer, SDL_Rect DestRect);
	void AnimateSmoke();
	static AniManager* Instance();
};
