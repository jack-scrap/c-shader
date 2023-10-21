#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "math.h"
#include "col.h"
#include "blit.h"
#include "shader.h"
#include "util.h"
#include "err.h"

const unsigned int res[2] = {
	800,
	600
};

int (*fn)() = solid;

int scrShot(char* filepath, SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer) {
	SDL_Surface* saveSurface = NULL;
	SDL_Surface* infoSurface = SDL_GetWindowSurface(SDLWindow);

	if (infoSurface == NULL) {
		printf("%s%s\n", "Failed to create info surface from window in save(string), SDL_GetError() - ", SDL_GetError());
	} else {
		unsigned char pixels[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];

		if (!pixels) {
			printf("Unable to allocate memory for screenshot pixel data buffer!\n");

			return false;
		} else {
			if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
				printf("%s%s\n", "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - ", SDL_GetError());

				return false;
			} else {
				saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);

				if (saveSurface == NULL) {
					printf("%s%s\n", "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - ", SDL_GetError());

					return false;
				}

				IMG_SavePNG(saveSurface, filepath);
				SDL_FreeSurface(saveSurface);
				saveSurface = NULL;
			}
		}

		SDL_FreeSurface(infoSurface);
		infoSurface = NULL;
	}

	return true;
}

int main() {
	SDL_Window* win = SDL_CreateWindow("Blit", 0, 0, res[X], res[Y], 0);
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);

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
			
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_F12) {
					scrShot("o/scr.png", win, rend);
				}
			}
		}

		Coord bound = {
			res[X],
			res[Y]
		};

		for (int j = 0; j < res[Y]; j++) {
			for (int i = 0; i < res[X]; i += sizeof (int)) {
				for (int b = 0; b < sizeof (int); b++) {
					Coord st = {
						i + b,
						j
					};

					unsigned int val = coordToIdx(st, bound);

					if (((val & (1 << (b - 1))) ? 1 : 0)) {
						blitPix(data, st, white);
					}
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
