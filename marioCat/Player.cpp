#include "Player.h"

Player::Player(){}

void Player::init(const char* texture, int x, int y, int w, int h)
{
	tex = TextureManager::LoadTexture(texture);
	transform = new TransformComponent(x,y,w,h,14);
}

void Player::render()
{
	TextureManager::Draw(tex, { transform->possition.x,transform->possition.y,
				transform->width,transform->height }, SDL_FLIP_HORIZONTAL);
}

