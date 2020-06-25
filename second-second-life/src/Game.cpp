#include "Game.h"
#include "TextureManager.h" 
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

using namespace std;

Map* gameMap;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, 32*39, 32*14 };

//AssetManager* Game::assets = new AssetManager(&manager);

vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabel : size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

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
		cout << "Subsystems Initialized!" << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			cout << "Window created!" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created!" << endl;
		}

		isRunning = true;
	} else {
		isRunning = false;
	}

	//assets->addTexture("terrain", "assets/map.map");
	//assets->addTexture("player", "assets/dwight.png");

	gameMap = new Map();

	//ecs implementation

	Map::loadMap("assets/map.map", 34, 17);


	player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("assets/dwight.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);
}

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
	bool justHit = false;
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	Vector2D playerVel = player.getComponent<TransformComponent>().velocity;
	int playerW = player.getComponent<TransformComponent>().width;
	int playerH = player.getComponent<TransformComponent>().height;


	manager.refresh();
	manager.update();


	camera.x = player.getComponent<TransformComponent>().position.x - 32*34/2;
	camera.y = player.getComponent<TransformComponent>().position.y - 32*17/2;


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

	cout << camera.x << " " << camera.y << endl;
	cout << playerPos << endl;


	for (auto c : colliders) {
		SDL_Rect cCol = c->collider;
		dir whereCol = Collision::AABB(playerCol, cCol);
		if (whereCol != NONE /*||
			player.getComponent<TransformComponent>().position.x <= 0 ||
			player.getComponent<TransformComponent>().position.x + playerW >= 1540 ||
			player.getComponent<TransformComponent>().position.y <= 0 ||
			player.getComponent<TransformComponent>().position.y + playerH >= 1200*/) {
			Collision::AABB(*c, player.getComponent<ColliderComponent>());
			switch (whereCol) {
			case UP:
				playerPos.y++;
				break;
			case DOWN:
				playerPos.y--;
				break;
			case LEFT:
				playerPos.x += 1;
				break;
			case RIGHT:
				playerPos.x--;
				break;
			default:
				break;
			}
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}
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