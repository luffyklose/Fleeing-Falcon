#pragma once
#include "Game.h"


class Map
{
public:
	Map();
	~Map();;

	void LoadMap(int arr[20][25]);
	void DrawMap();
	void ChangeMap();

	const int SCROLLCD = 100;
	int TimeCount;
private:
	SDL_Rect SrcRect, DestRect;

	SDL_Texture* space1;
	SDL_Texture* space2;
	SDL_Texture* space3;

	int map[20][25];
};