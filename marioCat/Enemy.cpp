#include "Enemy.h"

void Enemy::init(const char* texture, int x, int y, int w, int h)
{
	tex = TextureManager::LoadTexture(texture);
	transform = new TransformComponent(x, y, w, h, 4);
}

void Enemy::move(int &range)
{
	transform->speed = 7;
	if (range == 100)
		range = 0;
	if (range < 50)
	{
		if (!(Game::event.key.keysym.sym == SDLK_d))
			transform->velocity.x = -1;
		else
			range--;
	}
	if (range >= 50)
	{
		if (!(Game::event.key.keysym.sym == SDLK_a))
			transform->velocity.x = +1;
		else
			range--;
	}
	transform->update();
	transform->velocity.x = 0;
	transform->speed = 7;
}

void Enemy::render()
{ 
	TextureManager::Draw(tex, { transform->possition.x,transform->possition.y,
				transform->width,transform->height }, SDL_FLIP_NONE);
}
