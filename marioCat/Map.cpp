#include "Map.h"

void Map::init(const char* texture, int x, int y, int w, int h)
{
	tex = TextureManager::LoadTexture(texture);
	transform = new TransformComponent(x, y, w, h, 7);
}

void Map::render()
{
	TextureManager::Draw(tex, { transform->possition.x,0,transform->width,transform->height }, SDL_FLIP_NONE);
}