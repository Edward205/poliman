#pragma once

#include "SDL3/SDL_render.h"
class Entity {
public:
    int x = 0;
    int y = 0;
    int direction = 0;
    virtual ~Entity() = default;
private:
    virtual void tick() = 0;
    virtual void render(SDL_Renderer *renderer) = 0;

};