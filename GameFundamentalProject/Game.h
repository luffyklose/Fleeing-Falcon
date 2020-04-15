#pragma once
#include<SDL.h>
#include "SDL_image.h"

//class GameObject;
enum GameState
{
	Normal = 1,
	StarShoot,
	StarCrash,
	StarCircle,
	StarDead
};

class Game {
private:
	bool isRunning;
	int PLayerScore=0;
	int GameState = Normal;
	
	SDL_Window *pWindow;
	
public:

	static SDL_Renderer* pRenderer;
	
	Game();
	~Game();

	void Init(const char *WindowTitle, int xpos, int ypos, int width, int height, bool isFullScreen);

	void Prepare();
	void HandleEvents();
	void Input();
	void Update();
	void Render();
	void Clean();
	void Quit();
	void Destroy();
	void ChangeState();

	bool running()
	{
		return isRunning;
	}
};
