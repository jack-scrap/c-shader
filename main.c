#include <SDL2/SDL.h>
#include <stdbool.h>

const unsigned int res[2] = {
				800,
				600
};

enum {
				X,
				Y
};

uint32_t rmask = 0xff000000;
uint32_t gmask = 0x00ff0000;
uint32_t bmask = 0x0000ff00;
uint32_t amask = 0x000000ff;

int main() {
	SDL_Window* win = SDL_CreateWindow("asdf", 0, 0, res[X], res[Y], 0);
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, 0);

	SDL_Texture* tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, res[X], res[Y]);

	SDL_Rect rect = {
					0,
					0,
					res[X],
					res[Y]
	};

	unsigned char data[res[Y]][res[X]][3 + 1];
	for (int y = 0; y < res[Y]; y++) {
					for (int x = 0; x < res[X]; x++) {
									data[y][x][0] = 255;
									data[y][x][1] = 0;
									data[y][x][2] = 0;
									data[y][x][3] = 0;
					}
	}

	SDL_Surface* surf = SDL_CreateRGBSurfaceFrom((void*) data, res[X], res[Y], 32, 4 * res[X], rmask, gmask, bmask, amask);

	SDL_UpdateTexture(tex, &rect, surf->pixels, surf->pitch);

	bool open = true;
	SDL_Event e;
	while (open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				open = false;
			}
		}

		SDL_RenderDrawRect(rend, &rect);

		SDL_RenderCopy(rend, tex, NULL, NULL);
		SDL_RenderPresent(rend);
	}

	return 0;
}
