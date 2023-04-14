#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include "TextureManager.h"
#include <vector>
class Game
{
public:
	Game(){}
	~Game(){}
	void init(const char* title, int xpos, int ypos, int width, int hight, bool fullScreen);
	void hundleEvents();
	void update();
	void render();
	void clear();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;

private:
	SDL_Window* window;
	SDL_Texture* character;
	std::vector<SDL_Texture*> grass;
};

