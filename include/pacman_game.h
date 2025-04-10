#pragma once
#include <vector>
#include "include/entity.h"
class PacmanGame {
public:
    int board[28][36];
    std::vector<Entity*> entities;
    Entity* player;

    void tick();
    void render(SDL_Renderer* renderer);

    ~PacmanGame();
};