#include "Game.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;

void Game::init(const char* title, int xpos, int ypos, int width, int hight, bool fullScreen)
{
	int flags = 0;
	if (fullScreen)
		flags = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem Initialised..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, hight, flags);
		if (window)
		{
			std::cout << "Window created..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255,255,255,255);
			std::cout << "Renderer created..." << std::endl;
			isRunning = true;
		}
		else
		{
			isRunning = false;
		}
	}

	character = TextureManager::LoadTexture("assets/marioCAT.png", Game::renderer);
}

void Game::hundleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{

}

void Game::render()
{
	SDL_RenderClear(renderer);

	TextureManager::Draw(character, { 0,0,100,100 }, SDL_FLIP_HORIZONTAL);

	SDL_RenderPresent(renderer);
}

void Game::clear()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleanned..." << std::endl;
}