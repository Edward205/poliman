#include "include/ghost.h"
#include "SDL3/SDL_render.h"
#include "include/pacman_game.h"
#include <stdio.h>

Ghost::Ghost(Player* player, int(*board)[BOARD_WIDTH])
{
  this->player = player;
  this->board = board;
}

void Ghost::tick()
{
  board_graph.clear();
  for(int i = 0; i < BOARD_HEIGHT; ++i)
  {
    std::vector<int> aux;
    for(int j = 0; j < BOARD_WIDTH; ++j)
    {
      if(i - 1 >= 0 && board[i - 1][j] == 0)
        aux.push_back(xyToIndex( (i + 1), j));
      if(j + 1 < BOARD_WIDTH && board[i][j + 1] == 0)
        aux.push_back(xyToIndex(i, (j + 1)));
      if(i + 1 < BOARD_HEIGHT && board[i + 1][j] == 0)
        aux.push_back(xyToIndex((i + 1), j));
      if(j - 1 >= 0 && board[i][j - 1] == 0)
        aux.push_back(xyToIndex(i, (j - 1)));
    }
    board_graph.push_back(aux);
  }

  /*printf("%d, %d, %d: ", player->grid_x, player->grid_y, xyToIndex(player->grid_x, player->grid_y));

  for(int i = 0; i < board_graph[player->grid_x * player->grid_y].size(); ++i)
  {
    printf("%d ", board_graph[player->grid_x * player->grid_y][i]);
  }
  printf("\n");*/
}

void Ghost::render(SDL_Renderer *renderer)
{

}

int Ghost::xyToIndex(int x, int y)
{
  return y * BOARD_WIDTH + x;
}