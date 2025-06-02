#pragma once

#include "SDL3/SDL_render.h"
class Entity {
public:
    int x = 0;
    int y = 0;
    int grid_x = 0;
    int grid_y = 0;
    int desired_x = 0; // for smooth movment
    int desired_y = 0;
    int direction = 1; // rotation in clockwise order (0 = up, 1 = right, 2 = down, 3 = left)
    int init_grid_x = 0, init_grid_y = 0;
    SDL_FRect sprite;
    virtual ~Entity() = default;
    virtual void tick() = 0;
    virtual void render(SDL_Renderer *renderer) = 0;
private:

};