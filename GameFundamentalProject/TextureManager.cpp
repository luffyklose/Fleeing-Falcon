#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* FileLoc) {
	SDL_Surface* tempSurface = IMG_Load(FileLoc);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

SDL_Texture* TextureManager::LoadTexture(SDL_Surface* tempSurface) {
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* Tex, SDL_Rect SrcRect, SDL_Rect DestRect)
{
	SDL_RenderCopy(Game::pRenderer, Tex, &SrcRect, &DestRect);	
}

void TextureManager::Draw(SDL_Texture* Tex, SDL_Rect DestRect)
{
	SDL_RenderCopy(Game::pRenderer, Tex, NULL, &DestRect);

}

void TextureManager::ClearRender()
{
	SDL_RenderClear(Game::pRenderer);
}

void TextureManager::PresentRender()
{
	SDL_RenderPresent(Game::pRenderer);
}