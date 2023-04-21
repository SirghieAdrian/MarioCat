#pragma once
#include "Game.h"
#include "TransformComponent.h"
class Collider
{
public:
	SDL_Texture* tex;
	TransformComponent* transform;

	void init(const char* texture, int x, int y, int w, int h);
	void render();
	SDL_Rect getRect() { return { transform->possition.x,transform->possition.y,transform->width,transform->height }; }
};

