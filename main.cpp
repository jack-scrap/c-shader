#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const static unsigned int ht = 32;

std::vector<SDL_Texture*> tex;
std::vector<SDL_Rect> rect;

void blit(SDL_Renderer* rend, int i, char* txt, TTF_Font* font) {
	SDL_Surface* surf = TTF_RenderText_Solid(font, txt, {
		255, 255, 255
	});
	tex[i] = SDL_CreateTextureFromSurface(rend, surf);

	rect[i].x = 0;
	rect[i].y = i * ht;
	rect[i].w = surf->w;
	rect[i].h = surf->h;
}

int main() {
	// window
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

	for (int i = 0; i < buff.size(); i++) {
		SDL_Texture* tmpTex;
		tex.push_back(tmpTex);

		SDL_Rect tmpRect;
		rect.push_back(tmpRect);
	}

	for (int i = 0; i < buff.size(); i++) {
		blit(rend, i, (char*) buff[i].c_str(), font);
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
