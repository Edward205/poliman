#pragma once

#include "SDL3/SDL_render.h"
#include "include/entity.h"
#include "include/player.h"
#include <vector>
class Ghost: public Entity 
{
public:
    Ghost(Player* player, int (*)[BOARD_HEIGHT][BOARD_WIDTH]);
    Ghost(int x, int y, int grid_x, int grid_y, Player* player, int (*)[BOARD_HEIGHT][BOARD_WIDTH]);
    int (*board)[BOARD_HEIGHT][BOARD_WIDTH];
    int desired_speed = 4;
    int desired_x = 0;
    int desired_y = 0;
    Player* player;
    std::vector<std::vector<int>> board_graph;
    void tick();
    void render(SDL_Renderer *renderer);
    int bfs(const std::vector<std::vector<int>>& graph, int start, int target);
private:
    int xyToIndex(int x, int y);
};