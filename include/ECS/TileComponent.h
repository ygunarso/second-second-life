#pragma once

#include "ECS.h"
#include "SDL2/SDL.h"

class TileComponent : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect src;

	Vector2D pos;
	SDL_Rect tile;
	int tileID;
	const char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int h, int w, int id) {
		pos.x = x;
		pos.y = y;

		tile.x = x;
		tile.y = y;
		tile.w = w;
		tile.h = h;
		tileID = id;

		src.x = 0;
		src.y = 0;
		src.w = src.h = 32;

		switch (tileID) {
		case 0:
			path = "assets/floor.png";
			break;
		case 1:
			path = "assets/dirt.png";
			break;
		case 2:
			path = "assets/grass.png";
			break;
		case 3:
			path = "assets/water.png";
			break;
		default:
			break;
		}

		texture = TextureManager::loadTexture(path);
	}

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	void draw() override {
		TextureManager::draw(texture, src, tile, SDL_FLIP_NONE);
	}

	void update() override {
		tile.x = pos.x - Game::camera.x;
		tile.y = pos.y - Game::camera.y;

	}
};
