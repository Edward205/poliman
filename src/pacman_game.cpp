#include "include/pacman_game.h"
#include "SDL3/SDL_render.h"

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

            tile_c.x = tile.x + (tile.w) * j;
            tile_c.y = tile.y + (tile.h) * i;
            SDL_FRect srcrect({(float) 0, (float) 0, 32, 32});
          
            SDL_RenderTexture(renderer, air_texture, &srcrect, &tile_c);

            if(board[i][j] == 1)
            {
                SDL_RenderTexture(renderer, wall_texture, &srcrect, &tile_c);
            } 
            else if(board[i][j] == 2)
            {
                SDL_RenderTexture(renderer, point_texture, &srcrect, &tile_c);
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

bool PacmanGame::loadSprites(SDL_Renderer *renderer, const char* air_sprite, const char* wall_sprite, const char* point_sprite)
{
    surface = SDL_LoadBMP(air_sprite);
    if(!surface)
        return false;
  
    SDL_Texture* aux_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    if(!aux_texture)
        return false;
  
    SDL_SetTextureScaleMode(aux_texture, SDL_SCALEMODE_NEAREST);
    air_texture = aux_texture;


    surface = SDL_LoadBMP(wall_sprite);
    if(!surface)
        return false;
  
    aux_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    if(!aux_texture)
        return false;
  
    SDL_SetTextureScaleMode(aux_texture, SDL_SCALEMODE_NEAREST);
    wall_texture = aux_texture;


    surface = SDL_LoadBMP(point_sprite);
    if(!surface)
        return false;
  
    aux_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    if(!aux_texture)
        return false;
  
    SDL_SetTextureScaleMode(aux_texture, SDL_SCALEMODE_NEAREST);
    point_texture = aux_texture;

    return true;
}


PacmanGame::~PacmanGame()
{
    SDL_DestroyTexture(air_texture);
    SDL_DestroyTexture(wall_texture);
    SDL_DestroyTexture(point_texture);
}