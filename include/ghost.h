#pragma once

#include "SDL3/SDL_render.h"
#include "include/entity.h"
#include "include/player.h"
#include "ghost_type.h"
#include <vector>
class Ghost: public Entity 
{
public:
    Ghost(Player* player, int(*board)[BOARD_WIDTH], GhostType type);
    GhostType type;
    ~Ghost() override = default;
    int (*board)[BOARD_WIDTH];
    int desired_speed = 4;
    int desired_x = 0;
    int desired_y = 0;
    Player* player;
    std::vector<std::vector<int>> board_graph;
    void tick() override;
    void render(SDL_Renderer *renderer) override;
    int bfs(const std::vector<std::vector<int>>& graph, int start, int target);
private:
    int xyToIndex(int x, int y);
};