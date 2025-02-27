#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

#define WEIGHT 800
#define HEIGHT 600

#define CELL_SIZE 15
#define ROWS 30
#define COLS 30

bool init_window() {
	if (SDL_Init(SDL_INIT_EVERYTHING != 0)) {
		fprintf(stderr, "Error initializing SDL\n");
		return false;
	}

	window = SDL_CreateWindow(
		"MoveBlock", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		WEIGHT, 
		HEIGHT,
		0
	);

	if (!window) {
		fprintf(stderr, "Error creating SDL window\n");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		fprintf(stderr, "Error creating SDL Renderer\n");
		return false;
	}

	return true;
}

void ClearWindow() {
	SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Present() {
	SDL_RenderPresent(renderer);
}

SDL_Rect InitApple() {
	int x = rand() % WEIGHT + 1;
	int y = rand() % HEIGHT + 1;
	SDL_Rect apple = {x, y, 10, 10};

	return apple;
}

int main() {
	srand(time(0));
	bool running = init_window();
	SDL_Event event;

	int direction = 0;
	SDL_Rect body = {WEIGHT >> 1, HEIGHT >> 1, 10, 10};
	SDL_Rect apple = InitApple();

	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_UP && direction != DOWN)
						direction = UP;
					if (event.key.keysym.sym == SDLK_DOWN && direction != UP)
						direction = DOWN;
					if (event.key.keysym.sym == SDLK_LEFT && direction != RIGHT)
						direction = LEFT;
					if (event.key.keysym.sym == SDLK_RIGHT && direction != LEFT)
						direction = RIGHT;
					break;
				default:
					break;
			}
		}

		switch (direction) {
			case UP:
				body.y -= 10;
				break;	
			case DOWN:
				body.y += 10;
				break;
			case LEFT:
				body.x -= 10;
				break;
			case RIGHT:
				body.x += 10;
				break;
		}

		ClearWindow();

		// Draw a rectangular
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &body);

		SDL_SetRenderDrawColor(renderer, 180, 0, 0, 255);
		SDL_RenderFillRect(renderer, &apple);

		Present();
		
		SDL_Delay(25);
	}
	return 0;
}
