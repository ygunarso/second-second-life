#include "Collision.h"
#include "ECS/ColliderComponent.h"


dir Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (recA.x + recA.w >= recB.x &&
		recA.y + recA.h >= recB.y &&
		recB.x + recB.w >= recA.x &&
		recB.y + recB.h >= recA.y) {
		if (recA.x > recB.x) {
			return LEFT;
		}
		else if (recA.x < recB.x) {
			return RIGHT;
		}
		else if (recA.y > recB.y) {
			return UP;
		}
		else {
			return DOWN;
		}
	}
	return NONE;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB) {
	if (AABB(colA.collider, colB.collider)) {
		cout << colA.tag << " hit: " << colB.tag << endl;
		return true;
	}
	return false;
}