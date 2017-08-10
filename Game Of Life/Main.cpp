#include <SDL.h>
#include <stdio.h>
#include <amp.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Cell.h"
#include <iostream>
#include <time.h>  

SDL_Window* window;
SDL_Surface* surface;
SDL_Surface* pixelSpace;
SDL_Renderer* renderer;
SDL_Texture* texture;

Uint32* pixels;

const int width = 640;
const int height = 480;

vector<Cell> cells;

using namespace concurrency;
using namespace std;

int Init() {
	window = NULL;
	surface = NULL;
	renderer = NULL;
	texture = NULL;
	pixelSpace = NULL;

	window = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	pixelSpace = SDL_CreateRGBSurface(0, width, height, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	pixels = (Uint32 *)pixelSpace->pixels;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);

	return 0;
}

void cleanUp() {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Uint32* drawPixel(int x, int y, int c[], SDL_Surface *pixelSurface) {
	Uint32 * pixels = (Uint32 *)pixelSurface->pixels;
	pixels[y * width + x] = SDL_MapRGB(pixelSurface->format, c[2], c[1], c[0]);
	return pixels;
}

void Draw() {
	int black[3] = { 0, 0, 0 };
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			drawPixel(j, i, black, pixelSpace);
		}	
	}
	for (int i = 0; i < cells.size(); i++) {
		int r = cells[i].c[0];
		int g = cells[i].c[1];
		int b = cells[i].c[2];
		int color[3] = { r, g, b };
		drawPixel(cells[i].x, cells[i].y, color, pixelSpace);
	}
}

void updateCells() {
	int size = cells.size();
	array_view<Cell, 1> source(size, cells);

	parallel_for_each(
		source.extent,
		[=](index<1> idx) restrict(amp) {

	});
}

void updateScreen() {
	updateCells();
	Draw();
	
	SDL_UpdateTexture(texture, NULL, pixelSpace->pixels, pixelSpace->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer
	);
}

int main(int argc, char *argv[]) {	
	bool quit = false;

	SDL_Event event;

	Init();

	Cell test;
	test.x = 20;
	test.y = 20;
	test.c[0] = 100;
	test.c[1] = 100;
	test.c[2] = 100;
	test.state = true;
	cells.push_back(test);;

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			}
		}
		updateScreen();
	}
	cleanUp();
	return 0;
}