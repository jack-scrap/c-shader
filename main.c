#include <SDL2/SDL.h>
#include <stdbool.h>

#include "math.h"
#include "col.h"
#include "blit.h"
#include "shader.h"
#include "err.h"

const unsigned int res[2] = {
	800,
	600
};

int (*fn)() = solid;

int main() {
	SDL_Window* win = SDL_CreateWindow("Blit", 0, 0, res[X], res[Y], 0);
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, 0);

	SDL_Texture* tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, res[X], res[Y]);

	unsigned char data[res[Y]][res[X]][CHAN_NO];

	// Clear
	clear(data);

	SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(data, res[X], res[Y], CHAN_NO * 8, CHAN_NO * res[X], rmask, gmask, bmask, amask);

	const SDL_Rect rect = {
		0,
		0,
		res[X],
		res[Y]
	};
	
	// Draw
	bool open = true;
	SDL_Event e;
	unsigned int t = 0;
	while (open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				open = false;
			}
		}

		for (int j = 0; j < res[Y]; j++) {
			for (int i = 0; i < res[X]; i++) {
				Coord st = {
					i,
					j
				};

				if (solid()) {
					blitPix(data, st, white);
				}
			}
		}

		SDL_UpdateTexture(tex, &rect, surf->pixels, surf->pitch);

		SDL_RenderDrawRect(rend, &rect);

		SDL_RenderCopy(rend, tex, NULL, NULL);
		SDL_RenderPresent(rend);

		t++;
	}

	return 0;
}
