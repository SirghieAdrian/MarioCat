#include "Game.h"
#include "TransformComponent.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;
std::vector<Collider*> Game::colliders;

Player* cat = nullptr;
Map* map = nullptr;
ColliderMap* colliderMap = nullptr;
Vector2D possitionCat, possitionMap;
std::vector<Vector2D> possitionColl;

SDL_Rect destBG = { 0,0,800,640 };
SDL_Rect srcBG = { 0,0,1664,640 };

void Game::init(const char* title, int xpos, int ypos, int width, int hight, bool fullScreen)
{
	int flags = 0;
	if (fullScreen)
		flags = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem Initialised..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, hight, flags);
		if (window)
		{
			std::cout << "Window created..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255,255,255,255);
			std::cout << "Renderer created..." << std::endl;
			isRunning = true;
		}
		else
		{
			isRunning = false;
		}
	}
	cat = new Player();
	map = new Map();
	colliderMap = new ColliderMap();
	
	//colliders.push_back(coll1);
	colliderMap->LoadColliderMap("assets/colliderMap.txt",27,11,64);

	cat->init("assets/marioCAT.png",100,346,100,100);
	map->init("assets/mapmario.png", 0, 0, 1664, 640);
}

void Game::hundleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	if(!possitionColl.empty())
		possitionColl.clear();

	possitionCat = cat->transform->possition;
	possitionMap = map->transform->possition;
	for (Collider* colider : colliders)
		possitionColl.push_back(colider->transform->possition);
	cat->transform->possition.y += 5;

	KeyBoardController();

	cat->transform->update();
	map->transform->update();
	for (Collider* colider : colliders)
	{
		colider->transform->update();
	}

	for (Collider* colider : colliders)
	{
		if (Collision::AABB(cat->getRect(), colider->getRect()))
		{
			cat->transform->possition = possitionCat;
			if (Collision::AABB(cat->getRect(), colider->getRect()))
			{
				std::cout << "hit" << std::endl;
				map->transform->possition = possitionMap;
				int i = 0;
				for (Collider* colider : colliders)
				{
					colider->transform->possition = possitionColl[i];
					i++;
				}
			}
		}
	}
	possitionCat.y += 2;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	map->render();
	cat->render();
	colliderMap->DrawColliderMap();

	SDL_RenderPresent(renderer);
}

void Game::clear()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleanned..." << std::endl;
}

void Game::KeyBoardController()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_w:
			cat->transform->velocity.y = -1;
			//cat->transform->update();
			cat->transform->jumpCnt++;
			//std::cout << cat->transform->jumpCnt++ << std::endl;
			break;
		case SDLK_a:
			map->transform->velocity.x = +1;
			for (Collider* colider : colliders)
				colider->transform->velocity.x = +1;
			//map->transform->update();
			break;
		case SDLK_d:
			map->transform->velocity.x = -1;
			for (Collider* colider : colliders)
				colider->transform->velocity.x = -1;
			//map->transform->update();
			break;
		default:
			break;
		}
	}
	if (Game::event.type == SDL_KEYUP)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_w:
			cat->transform->velocity.y =0;
			//cat->transform->update();
			break;
		case SDLK_a:
			map->transform->velocity.x = 0;
			for (Collider* colider : colliders)
				colider->transform->velocity.x = 0;
			//map->transform->update();
			break;
		case SDLK_d:
			map->transform->velocity.x = 0;
			for (Collider* colider : colliders)
				colider->transform->velocity.x = 0;
			//map->transform->update();
			break;
		default:
			break;
		}
	}
}