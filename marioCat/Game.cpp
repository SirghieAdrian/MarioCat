#include "Game.h"
#include "TransformComponent.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;
std::vector<Collider*> Game::colliders;

int jumpCnt = 1;
int enemyRange = 0;

Player* cat = nullptr;
Map* map = nullptr;
ColliderMap* colliderMap = nullptr;
Enemy* enemy = nullptr;

Vector2D possitionCat, possitionMap,possitionEnemy;
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
	enemy = new Enemy();
	
	//colliders.push_back(coll1);
	colliderMap->LoadColliderMap("assets/colliderMap.txt",29,10,64);

	cat->init("assets/marioCAT.png",300,346,100,100);
	map->init("assets/mapMario.png", -320, 0, 2496, 640);
	enemy->init("assets/enemy.png", 700, 448, 64, 64);

	enemy->transform->possition.x = colliders[62]->transform->possition.x;
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
/// <summary>
/// mai adauga 4x64 stanga si dreapta la mapa
/// 62 - 68
/// </summary>
void Game::update()
{
	std::cout << enemy->transform->velocity.x << std::endl;
	//std::cout << colliders[64]->transform->possition.x << std::endl;

	if(!possitionColl.empty())
		possitionColl.clear();

	possitionCat = cat->transform->possition;

	possitionMap = map->transform->possition;
	for (Collider* colider : colliders)
		possitionColl.push_back(colider->transform->possition);
	//possitionEnemy = enemy->transform->possition;

	cat->transform->possition.y += 5;

	KeyBoardController();

	enemyRange++;
	//enemy->move(enemyRange); ///urmareste 2 collidere dupa index
	//enemy->transform->possition.x = colliders[62]->transform->possition.x;
	///////////////
	


	///////////
	if(jumpCnt==1)
		cat->transform->update();
	map->transform->update();
	for (Collider* colider : colliders)
	{
		colider->transform->update();
	}
	//enemy->transform->update();

	for (Collider* colider : colliders)
	{
		if (Collision::AABB(cat->getRect(), colider->getRect()))//collision up/down
		{
			cat->transform->possition = possitionCat;
			jumpCnt = 1;
			if (Collision::AABB(cat->getRect(), colider->getRect()))//collision left/right
			{
				map->transform->possition = possitionMap;
				//enemy->transform->possition = possitionEnemy;
				jumpCnt = 0;
				int i = 0;
				for (Collider* colider : colliders)
				{
					colider->transform->possition = possitionColl[i];
					i++;
					cat->transform->possition.y= possitionCat.y+2;
				}
			}
		}
	}

	if (enemy->transform->possition.x <= colliders[62]->transform->possition.x)
		enemy->transform->velocity.x = +1;
	if (enemy->transform->possition.x >= colliders[68]->transform->possition.x)
		enemy->transform->velocity.x = -1;
	enemy->transform->update();

	//std::cout << map->transform->possition.x << std::endl;

}

void Game::render()
{
	SDL_RenderClear(renderer);

	map->render();
	cat->render();
	colliderMap->DrawColliderMap();
	enemy->render();

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
			jumpCnt++;
			break;
		case SDLK_a:
				map->transform->velocity.x = +1;
				if (jumpCnt == 1)
					jumpCnt++;
				for (Collider* colider : colliders)
					colider->transform->velocity.x = +1;
				//enemy->transform->velocity.x = +1;
			//map->transform->update();
			break;
		case SDLK_d:
			map->transform->velocity.x = -1;
			if (jumpCnt == 1)
				jumpCnt++;
			for (Collider* colider : colliders)
				colider->transform->velocity.x = -1;
			//enemy->transform->velocity.x = -1;
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
			//enemy->transform->velocity.x = 0;
			//map->transform->update();
			break;
		case SDLK_d:
			map->transform->velocity.x = 0;
			for (Collider* colider : colliders)
				colider->transform->velocity.x = 0;
			//enemy->transform->velocity.x = 0;
			//map->transform->update();
			break;
		default:
			break;
		}
	}
}