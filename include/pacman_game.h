#pragma once
#include <vector>
#include "include/entity.h"
#include "include/player.h"
#include "include/defines.h"
#include "include/quiz.h"

class PacmanGame {
public:
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    int lives = 3;
    int max_points = 0;
    std::vector<Entity*> entities;
    Player* player;
    SDL_FRect tile = {BOARD_CENTER_OFFSET_X, BOARD_CENTER_OFFSET_Y, TILE_WIDTH, TILE_HEIGHT};
    bool paused = false;
    Quiz* quiz;

    void tick();
    void render(SDL_Renderer* renderer);

    ~PacmanGame();
};