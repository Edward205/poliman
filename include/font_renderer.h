#pragma once

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"

#include <string>

class FontRenderer {
public:
    FontRenderer(SDL_Renderer *renderer, const char *path, int x, int y, float scale, int max_chars);
    std::string text;
    float x, y;
    float scale;
    int max_chars;
    bool loadFont(SDL_Renderer *renderer, const char* path);
    void render(SDL_Renderer *renderer);
    ~FontRenderer();
private:
    SDL_Texture* font_texture;
    SDL_Surface* font_surface;
};