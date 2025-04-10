#include "include/pacman_game.h"

void PacmanGame::tick()
{
    player->tick();
    for(auto entity : entities)
    {
        entity->tick();
    }
}

void PacmanGame::render(SDL_Renderer* renderer)
{
    for(int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for(int j = 0; j < BOARD_WIDTH; ++j)
        {
            SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
            tile.x = (tile.w) * j;
            tile.y = (tile.h) * i;
            SDL_RenderRect(renderer, &tile);
        }
    }
    player->render(renderer);
    for(auto entity : entities)
    {
        entity->render(renderer);
    }
}

PacmanGame::~PacmanGame()
{

}