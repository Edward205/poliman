#pragma once

#include "SDL3/SDL_render.h"
#include "font_renderer.h"
class Button {
public:
    Button(SDL_Renderer *renderer, int x, int y, int w, int h, int max_chars);
    int x, y, w, h, max_chars;
    bool init(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer);
    ~Button();
private:
    FontRenderer *fontRenderer;
};