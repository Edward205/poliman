#pragma once
#include <vector>
#include "include/entity.h"

#define BOARD_HEIGHT 28
#define BOARD_WIDTH 36

class PacmanGame {
public:
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    std::vector<Entity*> entities;
    Entity* player;
    SDL_FRect tile = {0, 0, 800 / BOARD_WIDTH, 600 / BOARD_HEIGHT};

    void tick();
    void render(SDL_Renderer* renderer);

    ~PacmanGame();
};