#pragma once
#include <SDL_ttf.h>
#include <string>

class TextManager
{
public:
	static TextManager* Instance();
	void InitTTF();
	void LoadText(const char* content, int x, int y, int width, int height);
	void QuitTTF();
	
	TTF_Font* ArialFont;
	SDL_Color Yellow = { 255, 255, 255 };
private:
	static TextManager* s_pInstance;
	SDL_Renderer* pTRenderer=NULL;
};
