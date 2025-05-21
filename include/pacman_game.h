#pragma once
#include <vector>
#include "include/ghost.h"
#include "include/player.h"
#include "include/defines.h"
#include "include/quiz.h"

class PacmanGame {
public:
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    int lives = 3;
    int max_points = 0;
    std::vector<Ghost*> entities;
    Player* player;
    SDL_FRect tile = {BOARD_CENTER_OFFSET_X, BOARD_CENTER_OFFSET_Y, TILE_WIDTH, TILE_HEIGHT};
    bool paused = false;
    Quiz* quiz;

    void tick();
    void render(SDL_Renderer* renderer);
    bool loadSprites(SDL_Renderer *renderer, const char* air_sprite, const char* wall_sprite, const char* point_sprite);

    ~PacmanGame();
private:
    SDL_Surface* surface;
    
    SDL_Texture* air_texture;
    SDL_Texture* wall_texture;
    SDL_Texture* point_texture;
};