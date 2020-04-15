#include "Smoke.h"

const int SMOKEWIDTH = 32;
const int SMOKEHEIGHT = 32;
const int SMOKEFRAMENUMBER = 24;

Smoke::Smoke(SDL_Renderer* pRenderer,SDL_Rect DestRect)
{
	currentFrame = 0;
	renderer = pRenderer;
	this->DestRect = DestRect;
	pTex= TextureManager::LoadTexture("assest/smoke.png");

	SDL_QueryTexture(pTex, NULL, NULL, &SrcRect.w, &SrcRect.h);

	SrcRect.x = 0;
	SrcRect.y = 0;
	SrcRect.w = SMOKEWIDTH;
	SrcRect.h = SMOKEHEIGHT;

}

bool Smoke::SmokeAnimaRender()
{
	if (currentFrame == SMOKEFRAMENUMBER)
	{
		return false;
	}


	SrcRect.x = currentFrame  * SMOKEWIDTH;
	SrcRect.y = 0;

	SDL_RenderCopy(renderer, pTex, &SrcRect, &DestRect);

	//we skip 1 frame because the animation has a higher framerate (it appears too slow)
	currentFrame += 2;
	if (currentFrame == SMOKEFRAMENUMBER)
	{
		cleanup();
		return false;
	}

	return true;
}

void Smoke::cleanup()
{
	SDL_DestroyTexture(pTex);
}