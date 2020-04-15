#include "AniManager.h"

AniManager* AniManager::s_pInstance = NULL;

AniManager* AniManager::Instance()
{
	if (s_pInstance == NULL)
	{
		s_pInstance = new AniManager();
	}

	return s_pInstance;
}

void AniManager::DrawFrame(SDL_Texture* Tex, SDL_Rect DestRect, int x, int y, int w, int h)
{
	SDL_Rect FrameSrcRect;
	FrameSrcRect.x = x;
	FrameSrcRect.y = y;
	FrameSrcRect.w = w;
	FrameSrcRect.h = h;
	SDL_RenderCopy(Game::pRenderer, Tex, &FrameSrcRect, &DestRect);
}

void AniManager::AddSmoke(SDL_Renderer* renderer, SDL_Rect DestRect)
{
	s = Smoke(renderer, DestRect);
}

void AniManager::AnimateSmoke()
{
	s.SmokeAnimaRender();
}


