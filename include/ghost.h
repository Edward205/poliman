#pragma once

#include "SDL3/SDL_render.h"
#include "include/entity.h"
#include "include/player.h"
#include <vector>
class Ghost: public Entity {
public:
    Ghost(Player* player, int (*)[BOARD_HEIGHT][BOARD_WIDTH]);
    Ghost(int x, int y, int grid_x, int grid_y, int type, Player* player, int (*)[BOARD_HEIGHT][BOARD_WIDTH]);
    int (*board)[BOARD_HEIGHT][BOARD_WIDTH];
    int desired_speed = 5;
    int desired_x = 0;
    int desired_y = 0;
    int type;
    Player* player;
    std::vector<std::vector<int>> board_graph;
    void tick();
    void render(SDL_Renderer *renderer);
    int bfs(const std::vector<std::vector<int>>& graph, int start, int target);
    ~Ghost();
    bool loadSprite(SDL_Renderer *renderer, const char* sprite);
private:
    int xyToIndex(int x, int y);

    SDL_Texture* texture;
    SDL_Surface* surface;

    int current_animation_frame = 0;
    int ticks_per_animation_frame = 4;
    int elapsed_since_animation_frame = 0;
};