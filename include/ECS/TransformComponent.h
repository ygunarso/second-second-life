#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;

	int height = 30;
	int width = 20;
	int scale = 1;

	int speed = 5;

	TransformComponent() {
		position.zero();
	}

	TransformComponent(int s) {
		position.x = 400;
		position.y = 320;
		scale = s;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int s) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = s;
	}

	void init() override {
		velocity.zero();
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};