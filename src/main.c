#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <stdlib.h>
#include <stdbool.h>

#include "./include/state.h"
#include "./include/render.h"

struct State *state;

TTF_Font *press_start_2P;
SDL_Texture *test_text;
SDL_Color WHITE;

void load() {
	press_start_2P = load_font_size("./res/PressStart2P-Regular.ttf", 30);
	test_text = load_text(state->renderer, "Hello, World!", press_start_2P, WHITE);
}

void render() {
	render_tex(state->renderer, test_text, true);
}

void main_loop() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			state->running = false;
		}
	}

	// Clear Frame
	SDL_SetRenderDrawColor(state->renderer, 90, 90, 90, 255);
	SDL_RenderClear(state->renderer);

	// Render
	render();

	// Display
	SDL_RenderPresent(state->renderer);
}

void initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_LogCritical(EXIT_FAILURE, "Could not initialize SDL: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if (TTF_Init() < 0) {
		SDL_LogCritical(EXIT_FAILURE, "Could not initialize SDL_ttf: %s", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	if (IMG_Init(IMG_INIT_PNG) < 0) {
		SDL_LogCritical(EXIT_FAILURE, "Could not initialize SDL_image: %s", IMG_GetError());
		exit(EXIT_FAILURE);
	}
}

int main(void) {
	initialize();
	state = create_state("Game", 500, 500);

	load();

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop, 0, 1);
#else
	while (state->running) {
    	main_loop();
    	SDL_Delay(16);
	}
#endif

	destroy_state(state);
	TTF_Quit();
	SDL_Quit();

	return 0;
}