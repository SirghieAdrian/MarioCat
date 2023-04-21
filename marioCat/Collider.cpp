#include "Collider.h"
#include "Game.h"
void Collider::init(const char* texture, int x, int y, int w, int h)
{
	tex = TextureManager::LoadTexture(texture);
	transform = new TransformComponent(x, y, w, h, 7);
}

void Collider::render()
{
	TextureManager::Draw(tex, { transform->possition.x,transform->possition.y,transform->width,transform->height }, SDL_FLIP_HORIZONTAL);
}
