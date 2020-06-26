#pragma once

#include "Components.h"
#include "SDL2/SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"

class SpriteComponent : public Component {
public:
	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(std::string id) {
		setTex(id);
	}

	SpriteComponent(std::string id, bool isAnimated) {
		animated = isAnimated;

		Animation idle = Animation(0, 3, 100);
		Animation walk = Animation(1, 6, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		play("Idle");
		setTex(id);
	}

	~SpriteComponent() {
	}

	void setTex(std::string id) {
		texture = Game::assets->getTexture(id);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		src.x = src.y = 0;
		src.w = transform->width;
		src.h = transform->height;
	}

	void update() override {
		if (animated) {
			src.x = src.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		src.y = animIndex * transform->height;

		dest.x = static_cast<int>(transform->position.x - Game::camera.x);
		dest.y = static_cast<int>(transform->position.y - Game::camera.y);
		dest.w = transform->width * transform->scale;
		dest.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::draw(texture, src, dest, spriteFlip);
	}

	void play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect src, dest;

	bool animated = false;
	int frames = 0;
	int speed = 100;
};
