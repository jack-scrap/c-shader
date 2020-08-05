#include <stdlib.h>
#include <vector>
#include <string>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int
	wd = 800,
	ht = 600;

std::vector<SDL_Texture*> texture;
std::vector<SDL_Rect> rectangle;

std::vector<std::string> rd(std::string name) {
	std::ifstream f(name);
	std::string l;

	std::vector<std::string> word;

	while (std::getline(f, l)) {
		word.push_back(l);
	}

	return word;
}

void get_txt_and_rect(SDL_Renderer* rend, int x, int y, char* txt, TTF_Font* font, SDL_Texture** tex, SDL_Rect* rect) {
	int
		txt_wd,
		txt_ht;

	SDL_Surface* surface;
	SDL_Color txtCol = {255, 255, 255, 0};

	surface = TTF_RenderText_Solid(font, txt, txtCol);
	*tex = SDL_CreateTextureFromSurface(rend, surface);

	txt_wd = surface->w;
	txt_ht = surface->h;

	SDL_FreeSurface(surface);

	rect->x = x;
	rect->y = y;
	rect->w = txt_wd;
	rect->h = txt_ht;
}

int main() {
	std::vector<std::string> word = rd("intro");

	SDL_Renderer* rend;

	for (int i = 0; i < 3; i++) {
		SDL_Texture* theTexture;
		texture.push_back(theTexture);

		SDL_Rect theRect;
		rectangle.push_back(theRect);
	}

	// window
	SDL_Window* win;

	char* name = "terminus.bdf";

	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(wd, ht, 0, &win, &rend);

	// text
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(name, 24);

	for (int i = 0; i < word.size(); i++) {
		get_txt_and_rect(rend, 0, i * 32, (char*) word[i].c_str(), font, &texture[i], &rectangle[i]);
	}

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);

	int open = true;
	SDL_Event e;
	while (open) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				open = false;
			}
		}

		SDL_RenderClear(rend);

		for (int i = 0; i < word.size(); i++) {
			SDL_RenderCopy(rend, texture[i], NULL, &rectangle[i]);
		}

		SDL_RenderPresent(rend);
	}

	for (int i = 0; i < 3; i++) {
		SDL_DestroyTexture(texture[i]);
	}

	return 0;
}
