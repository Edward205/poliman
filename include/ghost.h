#pragma once

#include "SDL3/SDL_render.h"
#include "include/entity.h"
#include "include/player.h"
#include "include/pacman_game.h"
#include <vector>
class Ghost: public Entity 
{
public:
    int (*board)[BOARD_WIDTH];
    Player* player;
    std::vector<std::vector<int>> board_graph;
    void tick();
    void render(SDL_Renderer *renderer);
private:
    int xyToIndex(int x, int y);
};