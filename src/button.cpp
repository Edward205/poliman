#include "include/button.h"
#include "SDL3/SDL_render.h"
#include "include/font_renderer.h"
#include <iostream>

Button::Button(SDL_Renderer *renderer, int x, int y, int w, int h, int max_chars)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->max_chars = max_chars;
    if(!init(renderer))
        std::cerr << "Error loading button." << std::endl;
}
bool Button::init(SDL_Renderer *renderer)
{
    fontRenderer = new FontRenderer(renderer, "res/monogram.bmp", x, y, 2, max_chars);
    return true;
}

Button::~Button()
{
    delete fontRenderer;
}