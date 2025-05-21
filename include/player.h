#pragma once

#include "SDL3/SDL_render.h"
#include "include/entity.h"
#include "include/defines.h"

class Player: public Entity {
public:
    Player(int x, int y, int grid_x, int grid_y, int (*)[BOARD_HEIGHT][BOARD_WIDTH]);
    Player();
    int (*board)[BOARD_HEIGHT][BOARD_WIDTH], points = 0;
    void tick();
    void handleInput();
    void render(SDL_Renderer *renderer);
    bool loadSprite(SDL_Renderer *renderer, const char* sprite);
    ~Player();
private:
    int desired_speed = 4;
    bool isValidDirection(int direction);
    SDL_Texture* texture;
    SDL_Surface* surface;

    int current_animation_frame = 0;
    int ticks_per_animation_frame = 4;
    int elapsed_since_animation_frame = 0;
};