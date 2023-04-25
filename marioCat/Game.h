#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include "TextureManager.h"
#include <vector>
#include "Collision.h"
#include "Player.h"
#include "TransformComponent.h"
#include "Map.h"
#include "Collider.h"
#include "ColliderMap.h"
#include "Enemy.h"

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
	void KeyBoardController();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;

	static std::vector<class Collider*> colliders;
	
private:
	SDL_Window* window;
	SDL_Texture* background;
};

