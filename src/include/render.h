#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>

// Load
SDL_Texture *load_image(SDL_Renderer *renderer, const char *filepath);
SDL_Texture *load_text(SDL_Renderer *renderer, const char *message, TTF_Font *font, SDL_Color color);

extern const uint8_t DEFAULT_FONT_SIZE;
TTF_Font *load_font_size(const char *filepath, const uint8_t size);
TTF_Font *load_font(const char *filepath);

// Render
void render_tex_at(SDL_Renderer *renderer, SDL_Texture* texture, SDL_Point pos);
void render_tex(SDL_Renderer *renderer, SDL_Texture* texture, bool center);