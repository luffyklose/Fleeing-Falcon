#include <iostream>
#include"Game.h"

const int WINDOWWIDTH = 800;
const int WINDOWHEIGHT = 640;

Game *myGame=nullptr;

// Main function.
int main(int argc, char* args[]) // Main MUST have these parameters for SDL.
{
	const int FPS = 60;
	const int FrameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	
	myGame = new Game();
	myGame->Init("Fleeing Falcon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWWIDTH, WINDOWHEIGHT, 0);
	myGame->Prepare();

	while (myGame->running())
	{
		frameStart = SDL_GetTicks();

		myGame->HandleEvents();
		myGame->Update();
				
		myGame->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if(FrameDelay>frameTime)
		{
 			SDL_Delay(FrameDelay - frameTime);
		}
	}

	myGame->Clean();

	return 0;
}