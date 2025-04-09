#pragma once

#include "SDL3/SDL_render.h"
class Entity {
public:
    int x = 0;
    int y = 0;
    int direction = 0;
private:
    virtual void tick();
    virtual void render(SDL_Renderer *renderer);
};