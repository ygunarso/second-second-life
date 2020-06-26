#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	int count = 50;
	int delay = 50;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w: // move up
				transform->velocity.y = -1;
				sprite->play("Walk");
				break;
			case SDLK_a: // move left
				transform->velocity.x = -1;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d: // move right
				transform->velocity.x = 1;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_s: // move down
				transform->velocity.y = 1;
				sprite->play("Walk");
				break;
			case SDLK_UP: // shoot up
				if (count >= delay) {
					Game::assets->createProjectile(Vector2D(transform->position.x+transform->width/2, transform->position.y-32), Vector2D(0,-2), 200, 2, "projectile");
					count = 0;
				}
				break;
			case SDLK_LEFT: // shoot left
				if (count >= delay) {
					Game::assets->createProjectile(Vector2D(transform->position.x-32, transform->position.y+transform->height/2), Vector2D(-2,0), 200, 2, "projectile");
					count = 0;
				}
				break;
			case SDLK_RIGHT: // shoot right
				if (count >= delay) {
					Game::assets->createProjectile(Vector2D(transform->position.x+transform->width+64, transform->position.y+transform->height/2), Vector2D(2,0), 200, 2, "projectile");
					count = 0;
				}
				break;
			case SDLK_DOWN: // shoot down
				if (count >= delay) {
					Game::assets->createProjectile(Vector2D(transform->position.x+transform->width/2, transform->position.y+transform->height+96), Vector2D(0,2), 200, 2, "projectile");
					count = 0;
				}
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w: // move up
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;
			case SDLK_a: // move left
				transform->velocity.x = 0;
				sprite->play("Idle");
				//sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d: // move right
				transform->velocity.x = 0;
				sprite->play("Idle");
				break;
			case SDLK_s: // move down
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;
			default:
				break;
			}
		}
		count++;
	}
};
