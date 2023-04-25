#pragma once
#include "Game.h"

class Enemy
{
public:
	SDL_Texture* tex;
	TransformComponent* transform;

	void init(const char* texture, int x, int y, int w, int h);
	SDL_Rect getRect() { return { transform->possition.x,transform->possition.y,transform->width,transform->height }; }
	void move(int &range);
	void render();
};

