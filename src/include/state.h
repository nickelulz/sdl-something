#pragma once

#include <stdint.h>
#include <stdbool.h>

struct State {
	SDL_Window *window;
	SDL_Renderer *renderer;
	uint32_t window_width, window_height;
	bool running;
} State;

extern struct State *state;

// Upkeep
struct State *create_state(const char *title, uint16_t width, uint16_t height);
void destroy_state(struct State *state);