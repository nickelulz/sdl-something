#include <SDL2/SDL.h>
#include <stdlib.h>
#include "./include/state.h"

struct State *create_state(const char *title, uint16_t width, uint16_t height) 
{
	struct State *new_state = (struct State*) malloc(sizeof(struct State));
	new_state->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (new_state->window == NULL) {
		SDL_LogCritical(EXIT_FAILURE, "Could not create SDL_Window: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	new_state->renderer = SDL_CreateRenderer(new_state->window, -1, SDL_RENDERER_ACCELERATED);
	if (new_state->renderer == NULL) {
		SDL_LogCritical(EXIT_FAILURE, "Could not create SDL_Renderer: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	new_state->running = true;
	return new_state;
}

void destroy_state(struct State *state) {
	free(state);
}