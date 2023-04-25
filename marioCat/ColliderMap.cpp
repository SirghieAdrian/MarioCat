#include "ColliderMap.h"
#include <fstream>
#include "Game.h"

void ColliderMap::LoadColliderMap(const char* path, int sizeX, int sizeY,int height)
{
	char c;
	std::ifstream mapFile;
	mapFile.open(path);

	for (int y = -1; y < sizeY; y++)
	{
		for (int x = -1; x < sizeX; x++)
		{
			mapFile >> c;
			std::cout << c << " ";
			if (atoi(&c) == 0)
			{
				Collider* collider = new Collider();
				collider->init("assets/collider.png", x * height,y*height,height,height);//
				Game::colliders.push_back(collider);
			}
			mapFile.ignore();
		}
		std::cout << std::endl;
	}
	mapFile.close();
}

void ColliderMap::DrawColliderMap()
{
	for (Collider* collider : Game::colliders)
	{
		collider->render();
	}
}
