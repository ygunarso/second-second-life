#include "Game.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	640

Game *game = nullptr;

int main(int argc, char* argv[]) {

	(void) argc;
	(void) argv;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// Initialize Game
	game = new Game();
	game->init("(Second) Second Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}
