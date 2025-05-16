#include "include/pacman_game.h"
#include "include/ghost.h"
#include "include/ghost_type.h"
#include "include/player.h"
#include "include/defines.h"
#include <iostream>

PacmanGame::~PacmanGame()
{
    for(Entity* e : entities)
        delete e;
    entities.clear();
}

void PacmanGame::initializeEntities() {
    int ghostCount = 0;

    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            int cell = board[y][x];

            if (cell == 3) {  // player spawn point
                player = new Player(x * TILE_SIZE, y * TILE_SIZE, x, y ,board);
                player->grid_x = x;
                player->grid_y = y;
                player->updatePixelPosition(TILE_SIZE);
                entities.push_back(player);
            }
            else if (cell == 4) {  // ghost spawn point
                GhostType type;
                switch (ghostCount) {
                    case 0: type = GhostType::BLINKY; break;
                    case 1: type = GhostType::PINKY; break;
                    case 2: type = GhostType::INKY; break;
                    default: type = GhostType::CLYDE; break;
                }
                ++ghostCount;

                Ghost* ghost = new Ghost(static_cast<Player*>(player), board, type);
                ghost->grid_x = x;
                ghost->grid_y = y;
                ghost->updatePixelPosition(TILE_SIZE);
                entities.push_back(ghost);
            }
        }
    }
}

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
}

PacmanGame::PacmanGame()
{
    initializeEntities();
}