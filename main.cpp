#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const static unsigned int ht = 32;

void getTxtAndRect(SDL_Renderer* rend, int i, char* txt, TTF_Font* font, SDL_Texture** tex, SDL_Rect* rect) {
	SDL_Surface* surf = TTF_RenderText_Solid(font, txt, {
		255, 255, 255
	});
	*tex = SDL_CreateTextureFromSurface(rend, surf);

	SDL_FreeSurface(surf);

	rect->x = 0;
	rect->y = i * ht;
	rect->w = surf->w;
	rect->h = surf->h;
}

int main() {
	// window
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* win;
	SDL_Renderer* rend;
	SDL_CreateWindowAndRenderer(800, 600, 0, &win, &rend);

	// text
	TTF_Init();

	TTF_Font* font = TTF_OpenFont("terminus.bdf", 24);

	std::vector<std::string> buff = {
		"asdf",
		"hjkl"
	};

	std::vector<SDL_Texture*> tex;
	std::vector<SDL_Rect> rect;
	for (int i = 0; i < buff.size(); i++) {
		SDL_Texture* tmpTex;
		tex.push_back(tmpTex);

		SDL_Rect tmpRect;
		rect.push_back(tmpRect);
	}

	for (int i = 0; i < buff.size(); i++) {
		getTxtAndRect(rend, i, (char*) buff[i].c_str(), font, &tex[i], &rect[i]);
	}

	SDL_RenderClear(rend);

	for (int i = 0; i < buff.size(); i++) {
		SDL_RenderCopy(rend, tex[i], NULL, &rect[i]);
	}

	bool open = true;
	SDL_Event e;
	while (open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				open = false;
			}
		}

		SDL_RenderPresent(rend);
	}

	return 0;
}
