#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game();
	game->init("MarioCat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
	while (game->isRunning)
	{
		game->hundleEvents();
		game->update();
		game->render();
	}

	game->clear();
	return 0;
}