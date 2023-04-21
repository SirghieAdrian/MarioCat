#pragma once
#include "Game.h"

struct Vector2D
{
	int x, y;
};
class TransformComponent
{
public:
	Vector2D possition;
	Vector2D velocity = { 0,0 };
	int speed;
	int width;
	int height;
	bool jump;
	int jumpCnt;

	TransformComponent(int x, int y, int w, int h, int sp)
	{
		possition.x = x;
		possition.y = y;
		height = h;
		width = w;
		speed = sp;
	}
	void update()
	{
		possition.x += velocity.x * speed;
		possition.y += velocity.y * speed;
	}
};

