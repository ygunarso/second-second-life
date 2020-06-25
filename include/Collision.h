#pragma once

#include <SDL2/SDL.h>

class ColliderComponent;

enum dir {
	UP, RIGHT, DOWN, LEFT, NONE
};

class Collision {
public:
	static dir AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};
