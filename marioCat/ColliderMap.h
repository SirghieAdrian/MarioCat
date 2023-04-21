#pragma once
#include "Game.h"
#include "Collider.h"
class ColliderMap
{
public:
	void LoadColliderMap(const char* path, int sizeX, int sizeY,int height);
	void DrawColliderMap();
};

