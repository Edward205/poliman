#pragma once

#include "SDL3/SDL_render.h"
#include "include/entity.h"
#include "include/pacman_game.h"

class Player: public Entity {
public:
    Player(int x, int y, int grid_x, int grid_y, int (*board)[BOARD_WIDTH]);
    int (*board)[BOARD_WIDTH];
    void tick();
    void handleInput();
    void render(SDL_Renderer *renderer);
    ~Player();
private:
    int desired_speed = 4;
    bool isValidDirection(int direction);
};