#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define CELL_SIZE 30
#define ROWS 8
#define COLS 8

#define WEIGHT COLS * CELL_SIZE
#define HEIGHT ROWS * CELL_SIZE

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool InitWindow() {
	if (SDL_Init(SDL_INIT_EVERYTHING != 0)) {
		fprintf(stderr, "Error: Initialzing SDL\n");
		return false;
	}

	window = SDL_CreateWindow(
		"Chess", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		WEIGHT, 
		HEIGHT, 
		0
	);

	if (!window) {
		fprintf(stderr, "Error: Creatign SDL window\n");
		return false;
	}
		
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		fprintf(stderr, "Error: Creating SDL Rnderer\n");
		return false;
	}

	return true;
}

int main() {
	bool running = InitWindow();
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
			}
		}
	}

	return 0;
}
