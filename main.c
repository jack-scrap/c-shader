#include <SDL2/SDL.h>
#include <stdbool.h>

#include "math.h"

enum {
	R,
	G,
	B,
	A
} chan_t;

typedef struct {
	unsigned int _r;
	unsigned int _g;
	unsigned int _b;
	unsigned int _a;
} Col;

uint32_t rmask = 0xff000000;
uint32_t gmask = 0x00ff0000;
uint32_t bmask = 0x0000ff00;
uint32_t amask = 0x000000ff;

Col black = {
	0,
	0,
	0,
	255
};

Col red = {
	255,
	0,
	0,
	255
};

const unsigned int res[2] = {
	800,
	600
};

void err(char* msg) {
	fprintf(stderr, "%s\n", msg);
}

unsigned int coordToIdx(Coord st, Coord bound) {
	return (st._y * bound._x) + st._x;
}

int blitPix(unsigned char data[res[Y]][res[X]][3 + 1], Coord st, Col col) {
	if (!(st._x <= res[X] && st._y <= res[Y])) {
		err("Pixel coordinate out of range");

		return 1;
	}

	data[st._y][st._x][R] = col._r;
	data[st._y][st._x][G] = col._g;
	data[st._y][st._x][B] = col._b;
	data[st._y][st._x][A] = col._a;

	return 0;
}

int blitRect(unsigned char data[res[Y]][res[X]][3 + 1], Coord bound, Col col) {
	for (int y = 0; y < bound._y; y++) {
		for (int x = 0; x < bound._x; x++) {
			Coord st = {
				x,
				y
			};

			unsigned int i = coordToIdx(st, bound) * (3 + 1);

			data[st._y][st._x][R] = col._r;
			data[st._y][st._x][G] = col._g;
			data[st._y][st._x][B] = col._b;
			data[st._y][st._x][A] = col._a;
		}
	}
}

int clear(unsigned char data[res[Y]][res[X]][3 + 1]) {
	Coord bound = {
		res[X],
		res[Y]
	};

	blitRect(data, bound, black);
}

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

	// Clear
	unsigned char data[res[Y]][res[X]][3 + 1];

	clear(data);

	for (int y = 0; y < res[Y]; y++) {
		for (int x = 0; x < res[X]; x++) {
			Coord st = {
				x,
				y
			};

			if (blitPix(data, st, red)) {
				err("Couldn't blit pixel");
			}
		}
	}

	SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(data, res[X], res[Y], (3 + 1) * 8, (3 + 1) * res[X], rmask, gmask, bmask, amask);

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
