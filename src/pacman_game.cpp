#include "include/pacman_game.h"

void PacmanGame::tick()
{
    // check player collisions
    if(!paused)
    {
        for(auto entity : entities)
        {
            if(player->grid_x == entity->grid_x && player->grid_y == entity->grid_y)
            {
                paused = true;
                quiz->triggerQuiz();
                break;
            }
        }
    }

    if(!paused || !quiz->active)
    {
        // tick the player first
        player->tick();
    
        // tick all entities in the game
        for(auto entity : entities)
        {
            entity->tick();
        }
    }

    // update quiz
    if(quiz->state == 1)
    {
        --lives;
        quiz->state = 0;
        quiz->active = false;
        paused = false;
        for(auto entity : entities)
        {
            entity->grid_x = entity->init_grid_x;
            entity->grid_y = entity->init_grid_y;
        }
    }
    if(quiz->state == 2)
    {
        --lives;
        quiz->state = 0;
        quiz->active = false;
        paused = false;
        for(auto entity : entities)
        {
            entity->grid_x = entity->init_grid_x;
            entity->grid_y = entity->init_grid_y;
        }
    }
}

void PacmanGame::render(SDL_Renderer* renderer)
{
    // render the tile grid
    for(int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for(int j = 0; j < BOARD_WIDTH; ++j)
        {
            SDL_FRect tile_c = tile;
            if(board[i][j] == 1)
            {
                SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
                tile_c.x = tile.x + (tile.w) * j;
                tile_c.y = tile.y + (tile.h) * i;
                SDL_RenderRect(renderer, &tile_c);
            } else if(board[i][j] == 2)
            {
                SDL_SetRenderDrawColor(renderer, 244, 193, 156, 255);
                tile_c.w = 4;
                tile_c.h = 4;
                tile_c.x = tile.x + (j + 1) * (TILE_WIDTH) - (tile_c.w / 2 + ((TILE_WIDTH) / 2));
                tile_c.y = tile.y + (i + 1) * (TILE_HEIGHT) - (tile_c.h / 2 + ((TILE_HEIGHT) / 2));
                SDL_RenderFillRect(renderer, &tile_c);
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

    // render quiz
    quiz->render(renderer);
}

PacmanGame::~PacmanGame()
{
    // destructor
    // free entities/players spirtes ...
}