#pragma once

#include "include/entity.h"
#include "include/pacman_game.h"
#include <vector>
class Ghost: public Entity 
{
public:
    int (*board)[BOARD_WIDTH];
    std::vector<std::vector<int>> board_graph;
    void tick();
};