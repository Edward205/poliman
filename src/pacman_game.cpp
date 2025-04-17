#include "include/pacman_game.h"

void PacmanGame::tick()
{
    // tick the player first
    player->tick();

    // tick all entities in the game
    for(auto entity : entities)
    {
        entity->tick();
    }
}

void PacmanGame::render(SDL_Renderer* renderer)
{
    // render the tile grid
    for(int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for(int j = 0; j < BOARD_WIDTH; ++j)
        {
            if(board[i][j] == 1)
            {
                SDL_FRect tile_c = tile;
                SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
                tile_c.x = tile.x + (tile.w) * j;
                tile_c.y = tile.y + (tile.h) * i;
                SDL_RenderRect(renderer, &tile_c);
            }
        }
    }

    // render the player first
    player->render(renderer);

    // render all entities in the game
    for(auto entity : entities)
    {
        entity->render(renderer);
    }
}

PacmanGame::~PacmanGame()
{
    // destructor
    // free entities/players spirtes ...
}