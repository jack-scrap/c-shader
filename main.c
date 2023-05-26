#include <SDL2/SDL.h>
#include <stdbool.h>

enum {
	X,
	Y
};

enum {
	R,
	G,
	B,
	A
};

typedef struct {
	unsigned int _x;
	unsigned int _y;
} Coord;

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

const unsigned int res[2] = {
	800,
	600
};

int blitPix(unsigned char data[res[Y]][res[X]][3 + 1], Coord st, Col col) {
	if (!(st._x <= res[X] && st._y <= res[Y])) {
		printf("Error\n");

		return 1;
	}

	data[st._y][st._x][R] = col._r;
	data[st._y][st._x][G] = col._g;
	data[st._y][st._x][B] = col._b;
	data[st._y][st._x][A] = col._a;

	return 0;
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
	Col black = {
		0,
		0,
		0,
		255
	};

	unsigned char data[res[Y]][res[X]][3 + 1];
	for (int y = 0; y < res[Y]; y++) {
		for (int x = 0; x < res[X]; x++) {
			data[y][x][R] = black._r;
			data[y][x][G] = black._g;
			data[y][x][B] = black._b;
			data[y][x][A] = black._a;
		}
	}

	Col red = {
		255,
		0,
		0,
		255
	};

	for (int y = 0; y < res[Y]; y++) {
		for (int x = 0; x < res[X]; x++) {
			Coord st = {
				x,
				y
			};

			if (blitPix(data, st, red)) {
				printf("Error\n");
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
