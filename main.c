#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "math.h"
#include "col.h"
#include "blit.h"
#include "shader.h"
#include "err.h"

const unsigned int res[2] = {
	184,
	184
};

int (*fn)() = solid;

bool scrShot(char* filepath, SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer) {
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
	SDL_Window* win = SDL_CreateWindow("asdf", 0, 0, res[X], res[Y], 0);
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
	
	for (int j = 0; j < res[Y]; j++) {
		for (int i = 0; i < res[X]; i++) {
			Coord st = {
				i,
				j
			};

			Coord start = {
				30,
				70
			};

			if (fn(st)) {
				blitPix(data, st, white);
			}
		}
	}

	SDL_UpdateTexture(tex, &rect, surf->pixels, surf->pitch);

	// Draw
	bool open = true;
	SDL_Event e;
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

		SDL_RenderDrawRect(rend, &rect);

		SDL_RenderCopy(rend, tex, NULL, NULL);
		SDL_RenderPresent(rend);
	}

	return 0;
}
