#pragma once
#include "Game.h"
#include "TransformComponent.h"

class Map
{
public:
	SDL_Texture* tex;
	TransformComponent* transform;
	Map() {}
	~Map() {}
	void init(const char* texture, int x, int y, int w, int h);
	void render();
};