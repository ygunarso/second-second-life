#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

Map* gameMap;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, 32*39, 32*14 };

AssetManager* Game::assets = new AssetManager(&manager);

vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());


Game::Game() {
}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	} else {
		isRunning = false;
	}

	assets->addTexture("terrain", "assets/map.map");
	assets->addTexture("player", "assets/dwight.png");
	assets->addTexture("wall", "assets/dirt.png");
	assets->addTexture("projectile", "assets/snowball.png");

	gameMap = new Map();

	//ecs implementation

	Map::loadMap("assets/map.map", 34, 17);


	player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	// wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	// wall.addComponent<SpriteComponent>("wall");
	// wall.addComponent<ColliderComponent>("wall");
	// wall.addGroup(groupMap);

	assets->createProjectile(Vector2D(50, 300), Vector2D(2,0), 200, 2, "projectile");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents() {
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}


void Game::update() {
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	// Vector2D playerPos = player.getComponent<TransformComponent>().position;
	// int playerW = player.getComponent<TransformComponent>().width;
	// int playerH = player.getComponent<TransformComponent>().height;


	manager.refresh();
	manager.update();

	for (auto& p : projectiles) {
		std::cout << playerCol.x << ", " << playerCol.y << std::endl;
		std::cout << p->getComponent<ColliderComponent>().collider.x << ", " << p->getComponent<ColliderComponent>().collider.y << std::endl;
		std::cout << p->getComponent<ColliderComponent>().collider.w << ", " << p->getComponent<ColliderComponent>().collider.h << std::endl;


 		if(Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider) != NONE) {
			std::cout << "Hit player!" << std::endl;
			p->destroy();
		}
	}


	camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 32*34/2);
	camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 32*17/2);


	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	if (camera.x > camera.w) {
		camera.x = camera.w;
	}
	if (camera.y > camera.h) {
		camera.y = camera.h;
	}

	// cout << camera.x << " " << camera.y << endl;
	// cout << playerPos << endl;

	// for (auto c : colliders) {
	// 	SDL_Rect cCol = c->collider;
	// 	dir whereCol = Collision::AABB(playerCol, cCol);
	// 	if (whereCol != NONE /*||
	// 		player.getComponent<TransformComponent>().position.x <= 0 ||
	// 		player.getComponent<TransformComponent>().position.x + playerW >= 1540 ||
	// 		player.getComponent<TransformComponent>().position.y <= 0 ||
	// 		player.getComponent<TransformComponent>().position.y + playerH >= 1200*/) {
	// 		Collision::AABB(*c, player.getComponent<ColliderComponent>());
	// 		switch (whereCol) {
	// 		case UP:
	// 			playerPos.y++;
	// 			break;
	// 		case DOWN:
	// 			playerPos.y--;
	// 			break;
	// 		case LEFT:
	// 			playerPos.x += 1;
	// 			break;
	// 		case RIGHT:
	// 			playerPos.x--;
	// 			break;
	// 		default:
	// 			break;
	// 		}
	// 		player.getComponent<TransformComponent>().position = playerPos;
	// 	}
	// }

}


void Game::render() {
	SDL_RenderClear(renderer);

	// this is where we would add stuff to render
	for (auto& t : tiles) {
		t->draw();
	}

	for (auto& p : players) {
		p->draw();
	}

	for (auto& e : enemies) {
		e->draw();
	}

	for (auto& p : projectiles) {
		p->draw();
	}

	SDL_RenderPresent(renderer);

}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game cleaned" << endl;
}

void Game::addTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 64, 64, id);
	tile.addGroup(groupMap);
}
