#include "include/button.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "include/font_renderer.h"
#include <iostream>

Button::Button(SDL_Renderer *renderer, int x, int y, int w, int h, int max_chars, std::string text)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->max_chars = max_chars;
    this->text = text;
    if(!init(renderer))
        std::cerr << "Error loading button." << std::endl;
}
bool Button::init(SDL_Renderer *renderer)
{
    fontRenderer = new FontRenderer(renderer, "../res/monogram.bmp", x, y, 2, max_chars);
    fontRenderer->text = text;
    return true;
}

void Button::handleInput(SDL_Event e)
{
    int relative_x = w / 2 + x, relative_y = h / 2 + y;

    switch (e.type) {
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            if(hovering)
                if (onPressed != nullptr)
                {
                    onPressed();
                }
            // break missing intentionally so that switch can fall to mousemotion

        case SDL_EVENT_MOUSE_MOTION:
            if (e.button.x > relative_x - w / 2 && e.button.x < relative_x + w / 2 && e.button.y > relative_y - h / 2 && e.button.y < relative_y + h / 2)
            {
                hovering = true;
            }
            else
            {
                hovering = false;
            }
            break;
    }
}
void Button::render(SDL_Renderer *renderer)
{
    fontRenderer->text = text;
    SDL_FRect background = SDL_FRect({(float) x-5, (float) y-5, (float) w+10, (float) h+10});
    
    if(hovering)
        SDL_SetRenderDrawColor(renderer, 100, 100, 125, 255);
    else
        SDL_SetRenderDrawColor(renderer, 75, 75, 100, 255);
    SDL_RenderFillRect(renderer, &background);

    fontRenderer->render(renderer);
}

Button::~Button()
{
    delete fontRenderer;
}