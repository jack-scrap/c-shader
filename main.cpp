#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

std::vector<SDL_Texture*> tex;
std::vector<SDL_Rect> rect;

void getTxtAndRect(SDL_Renderer* rend, int x, int y, char* txt, TTF_Font* font, SDL_Texture** tex, SDL_Rect* rect) {
	SDL_Surface* surf;

	surf = TTF_RenderText_Solid(font, txt, {255, 255, 255, 0});
	*tex = SDL_CreateTextureFromSurface(rend, surf);

	SDL_FreeSurface(surf);

	rect->x = x;
	rect->y = y;
	rect->w = surf->w;
	rect->h = surf->h;
}

int main() {
	SDL_Renderer* rend;

	for (int i = 0; i < 3; i++) {
		SDL_Texture* tmpTex;
		tex.push_back(tmpTex);

		SDL_Rect tmpRect;
		rect.push_back(tmpRect);
	}

	// window
	SDL_Window* win;

	char* name = "terminus.bdf";

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(800, 600, 0, &win, &rend);

	// text
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(name, 24);

	std::vector<std::string> word = {
		"asdf",
		"hjkl"
	};
	for (int i = 0; i < word.size(); i++) {
		getTxtAndRect(rend, 0, i * 32, (char*) word[i].c_str(), font, &tex[i], &rect[i]);
	}

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);

	SDL_RenderClear(rend);

	for (int i = 0; i < word.size(); i++) {
		SDL_RenderCopy(rend, tex[i], NULL, &rect[i]);
	}

	int open = true;
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
