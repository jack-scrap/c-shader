#include <SDL2/SDL.h>

int main() {
	SDL_Window* win = SDL_CreateWindow("asdf", 0, 0, 800, 600, 0);

	bool open = true;
	SDL_Event e;
	while (open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				open = false;
			}
		}
	}

	return 0;
}
