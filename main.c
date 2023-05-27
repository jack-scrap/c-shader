#include <SDL2/SDL.h>
#include <stdbool.h>

#include "math.h"
#include "col.h"
#include "err.h"

const unsigned int res[2] = {
	800,
	600
};

unsigned int coordToIdx(Coord st, Coord bound) {
	return (st._y * bound._x) + st._x;
}

int blitPix(unsigned char data[res[Y]][res[X]][3 + 1], Coord st, Col col) {
	if (data == NULL) {
		err(ERR_NULL_PTR);

		return 1;
	}

	if (!(st._x <= res[X] && st._y <= res[Y])) {
		err(ERR_PIXEL_COORD_BOUND);

		return 1;
	}

	data[st._y][st._x][R] = col._r;
	data[st._y][st._x][G] = col._g;
	data[st._y][st._x][B] = col._b;
	data[st._y][st._x][A] = col._a;

	return 0;
}

int blitRect(unsigned char data[res[Y]][res[X]][3 + 1], Coord sz, Coord pos, Col col) {
	if (data == NULL) {
		err(ERR_NULL_PTR);

		return 1;
	}

	for (int y = 0; y < sz._y; y++) {
		for (int x = 0; x < sz._x; x++) {
			Coord st = {
				pos._x + x,
				pos._y + y
			};

			if (blitPix(data, st, col)) {
				err(ERR_BLIT_PIX);
			}
		}
	}

	return 0;
}

int clear(unsigned char data[res[Y]][res[X]][3 + 1]) {
	if (data == NULL) {
		err(ERR_NULL_PTR);

		return 1;
	}

	Coord origin = {
		0,
		0
	};

	Coord bound = {
		res[X],
		res[Y]
	};

	blitRect(data, bound, origin, black);

	return 0;
}

int main() {
	SDL_Window* win = SDL_CreateWindow("asdf", 0, 0, res[X], res[Y], 0);
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, 0);

	SDL_Texture* tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, res[X], res[Y]);

	unsigned char data[res[Y]][res[X]][3 + 1];

	// Clear
	clear(data);

	SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(data, res[X], res[Y], (3 + 1) * 8, (3 + 1) * res[X], rmask, gmask, bmask, amask);

	SDL_Rect rect = {
		0,
		0,
		res[X],
		res[Y]
	};

	SDL_UpdateTexture(tex, &rect, surf->pixels, surf->pitch);

	// Draw
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
