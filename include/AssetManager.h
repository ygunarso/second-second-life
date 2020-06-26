#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"

class AssetManager {
public:
	AssetManager(Manager* man);
	~AssetManager();

	// Game Objects
	void createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

	//Texture Management
	void addTexture(std::string id, const char* path);
	SDL_Texture* getTexture(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;

};
