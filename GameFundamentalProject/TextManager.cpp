#include "TextManager.h"
#include"TextureManager.h"

#include <iostream>

TextManager* TextManager::s_pInstance = NULL;

TextManager* TextManager::Instance()
{
	if (s_pInstance == NULL)
	{
		s_pInstance = new TextManager();
	}

	return s_pInstance;
}

void TextManager::InitTTF()
{
	TTF_Init();
	ArialFont= TTF_OpenFont("arial.ttf", 30);
	if(!ArialFont)
		{
			std::cout << "Font Initialization Failed!" << std::endl;
		}
}

void TextManager::QuitTTF()
{
	TTF_Quit();
	TTF_CloseFont(ArialFont);
}

void TextManager::LoadText(const char* content, int x, int y, int width, int height)
{
	SDL_Surface* surface = TTF_RenderText_Solid(ArialFont,content, Yellow);
	SDL_Texture* texture = TextureManager::LoadTexture(surface);
	SDL_Rect DestRect = { x, y, width, height };
	//SDL_Rect SrcRect = {0,0,0,0};
	TextureManager::Draw(texture, DestRect);
	TextureManager::PresentRender();
	//SDL_RenderCopy(pTRenderer, texture, NULL, &dstrect);
	//SDL_RenderPresent(pTRenderer);
	//std::cout << "Text Loaded!" << std::endl;
}
