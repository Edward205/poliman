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
    player->render(renderer);
    for(auto entity : entities)
    {
        entity->render(renderer);
    }
}

PacmanGame::~PacmanGame()
{

}