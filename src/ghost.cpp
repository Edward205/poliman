#include "include/ghost.h"

void Ghost::tick()
{
    for(int i = 0; i < BOARD_HEIGHT; ++i)
    {
      for(int j = 0; j < BOARD_WIDTH; ++j)
      {
        std::vector<int> aux;
        if(i + 1 > 0 && board[i + 1][j] == 1)
          aux.push_back((i + 1) * j);
      }
    }
}