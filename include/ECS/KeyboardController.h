#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	bool toggle = true;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP: // up
				transform->velocity.y = -1;
				sprite->play("Walk");
				break;
			case SDLK_LEFT: // left
				transform->velocity.x = -1;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_RIGHT: // right
				transform->velocity.x = 1;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_DOWN: // down
				transform->velocity.y = 1;
				sprite->play("Walk");
				break;
			case SDLK_SPACE: // space
				toggle = !toggle;
				if (toggle) {
					sprite->setTex("assets/dwight.png");
				}
				else {
					sprite->setTex("assets/michael.png");
				}
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP: // up
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;
			case SDLK_LEFT: // left
				transform->velocity.x = 0;
				sprite->play("Idle");
				//sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_RIGHT: // right
				transform->velocity.x = 0;
				sprite->play("Idle");
				break;
			case SDLK_DOWN: // down
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;
			default:
				break;
			}
		}
	}
};