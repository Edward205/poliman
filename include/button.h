#pragma once

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include "font_renderer.h"
#include <functional>
class Button {
public:
    Button(SDL_Renderer *renderer, int x, int y, int w, int h, int max_chars, std::string text);
    int x, y, w, h, max_chars;
    std::string text;
    std::function<void()> onPressed;

    bool init(SDL_Renderer *renderer);
    void handleInput(SDL_Event e);
    void render(SDL_Renderer *renderer);
    ~Button();
private:
    FontRenderer *fontRenderer;
    bool hovering;
};