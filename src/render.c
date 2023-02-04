#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./include/render.h"

SDL_Texture *load_image(SDL_Renderer *renderer, const char *filepath)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, filepath);

	if (texture == NULL)
		SDL_LogError(-2, "Failed to load texture. Error: %s", SDL_GetError());

	return texture;
}

SDL_Texture *load_text(SDL_Renderer *renderer, const char *message, TTF_Font *font, SDL_Color color)
{
	SDL_Surface *surface = TTF_RenderText_Blended(font, message, color);
	if (!surface) {
		SDL_LogCritical(EXIT_FAILURE, "Cannot render text to SDL_Surface: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_LogCritical(EXIT_FAILURE, "Cannot render text from SDL_Surface to SDL_Texture: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_FreeSurface(surface);
	return texture;
}

const uint8_t DEFAULT_FONT_SIZE = 30;

TTF_Font *load_font_size(const char *filepath, const uint8_t size)
{
	TTF_Font *font = TTF_OpenFont(filepath, size);
	if (!font) {
		SDL_LogCritical(EXIT_FAILURE, "Cannot open font file \"%s\": %s\n", filepath, TTF_GetError());
		exit(EXIT_FAILURE);
	}
	return font;
}

TTF_Font *load_font(const char *filepath) {
	return load_font_size(filepath, DEFAULT_FONT_SIZE);
}

void render_tex_at(SDL_Renderer *renderer, SDL_Texture* texture, SDL_Point position) {
	SDL_Rect bounds = { position.x, position.y, 0, 0 };
	SDL_QueryTexture(texture, NULL, NULL, &bounds.w, &bounds.h);
	SDL_RenderCopy(renderer, texture, NULL, &bounds);
}

void render_tex(SDL_Renderer *renderer, SDL_Texture* texture, bool center) {
	SDL_Rect bounds;
	SDL_QueryTexture(texture, NULL, NULL, &bounds.w, &bounds.h);
	if (center) {
		int32_t window_width, window_height;
		SDL_GetRendererOutputSize(renderer, &window_width, &window_height);

		bounds.x = (window_width - bounds.w)/2;
		bounds.y = (window_height - bounds.h)/2;
	}
	render_tex_at(renderer, texture, (SDL_Point) { bounds.x, bounds.y });
}