#include "Game.h"

Game* game = nullptr;

const int FPS = 60;
const int frameDelay = 1000 / FPS;

Uint32 frameStart;
int frameTime;

int main(int argc, char* argv[])
{
	game = new Game();
	game->init("MarioCat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
	while (game->isRunning)
	{
		frameStart = SDL_GetTicks();

		game->hundleEvents();
		if(game->getPause()==0)
			game->update();
			game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clear();
	return 0;
}