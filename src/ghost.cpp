#include "include/ghost.h"
#include "SDL3/SDL_render.h"
#include "include/defines.h"
#include <queue>

Ghost::Ghost(Player *player, int (*board)[BOARD_WIDTH], GhostType type)
{
  this->player = player;
  this->board = board;
}

void Ghost::tick()
{
  int ghost_x = grid_x;
  int ghost_y = grid_y;
  int pacman_x = player->grid_x;
  int pacman_y = player->grid_y;

  int dir_x = 0, dir_y = 0;
  switch (player->direction) {
    case 0: dir_x = 0;  dir_y = -1; break; // up
    case 1: dir_x = 1;  dir_y = 0;  break; // right
    case 2: dir_x = 0;  dir_y = 1;  break; // down
    case 3: dir_x = -1; dir_y = 0;  break; // left
  }

  switch (type) {
    case BLINKY:
        desired_x = pacman_x;
        desired_y = pacman_y;
        break;

    case PINKY:
        desired_x = pacman_x + 4 * dir_x;
        desired_y = pacman_y + 4 * dir_y;
        break;

    case INKY:
        desired_x = pacman_x + 2 * dir_x;
        desired_y = pacman_y + 2 * dir_y;
        break;

    case CLYDE:
        int dx = pacman_x - ghost_x;
        int dy = pacman_y - ghost_y;
        if (dx * dx + dy * dy > 64) {
            desired_x = pacman_x;
            desired_y = pacman_y;
        } else {
            desired_x = 0;
            desired_y = BOARD_HEIGHT - 1;
        }
        break;
  }

  int start = xyToIndex(ghost_x, ghost_y);
  int target = xyToIndex(desired_x, desired_y);
  int next = bfs(board_graph, start, target);

  int next_x = next % BOARD_WIDTH;
  int next_y = next / BOARD_WIDTH;

  // Move the ghost to the next cell
  x = next_x * TILE_SIZE;
  y = next_y * TILE_SIZE;

  // logic for smooth movment
  // set the desired position to the middle of the cell which the player should be in
  desired_x = BOARD_CENTER_OFFSET_X + grid_x * (TILE_WIDTH) - (sprite.w / 2 + ((TILE_WIDTH) / 2));
  desired_y = BOARD_CENTER_OFFSET_Y + grid_y * (TILE_HEIGHT) - (sprite.h / 2 + ((TILE_HEIGHT) / 2));

  // if the position is in range of the desired position, set it exactly to the desired position
  if (x > desired_x - desired_speed && x < desired_x + desired_speed)
    x = desired_x;
  if (y > desired_y - desired_speed && y < desired_y + desired_speed)
    y = desired_y;

  if (x != desired_x)
  {
    if (x < desired_x)
      x += desired_speed;
    else
      x -= desired_speed;
  }

  if (y != desired_y)
  {
    if (y < desired_y)
      y += desired_speed;
    else
      y -= desired_speed;
  }

  // if the ghost is in its desired position, update its desired position
  if (x == desired_x && y == desired_y)
  {
    board_graph.clear();
    board_graph.resize(BOARD_HEIGHT * BOARD_WIDTH);

    // generate the graph
    for (int j = 0; j < BOARD_HEIGHT; ++j)
    {
      for (int i = 0; i < BOARD_WIDTH; ++i)
      {
        int currentIndex = xyToIndex(i, j);

        // skip cell if it's a wall
        if (board[j][i] == 1)
          continue;

        // up
        if (j > 0 && board[j - 1][i] != 1)
          board_graph[currentIndex].push_back(xyToIndex(i, j - 1));

        // down
        if (j < BOARD_HEIGHT - 1 && board[j + 1][i] != 1)
          board_graph[currentIndex].push_back(xyToIndex(i, j + 1));

        // left
        if (i > 0 && board[j][i - 1] != 1)
          board_graph[currentIndex].push_back(xyToIndex(i - 1, j));

        // right
        if (i < BOARD_WIDTH - 1 && board[j][i + 1] != 1)
          board_graph[currentIndex].push_back(xyToIndex(i + 1, j));
      }
    }

    int playerIndex = xyToIndex(player->grid_x - 1, player->grid_y - 1);
    int neighbor = bfs(board_graph, xyToIndex(grid_x - 1, grid_y - 1), playerIndex);
    grid_x = neighbor % BOARD_WIDTH + 1;
    grid_y = neighbor / BOARD_WIDTH + 1;
  }
}

void Ghost::render(SDL_Renderer *renderer)
{
    switch (type) {
        case GhostType::BLINKY: SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break;
        case GhostType::PINKY: SDL_SetRenderDrawColor(renderer, 255, 192, 203, 255); break;
        case GhostType::INKY: SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); break;
        case GhostType::CLYDE: SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); break;
        default: SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); break;
    }

    constexpr int ghost_size = 12;
    int offset = (TILE_SIZE - ghost_size) / 2;

    sprite.w = ghost_size;
    sprite.h = ghost_size;
    sprite.x = grid_x * TILE_SIZE + offset;
    sprite.y = grid_y * TILE_SIZE + offset;

    SDL_RenderFillRect(renderer, &sprite);
}


int Ghost::xyToIndex(int x, int y)
{
  return y * BOARD_WIDTH + x;
}

int Ghost::bfs(const std::vector<std::vector<int>> &graph, int start, int target)
{
  int n = graph.size();
  if (start < 0 || start >= n || target < 0 || target >= n || n == 0)
  {
    return -1;
  }
  if (start == target)
  {
    return start;
  }
  std::vector<int> parent(n, -1);
  std::vector<bool> visited(n, false);
  std::queue<int> q;

  q.push(start);
  visited[start] = true;

  // BFS traversal
  while (!q.empty())
  {
    int u = q.front();
    q.pop();
    if (u == target)
    {
      int current = target;
      // path reconstruction
      while (parent[current] != start)
      {
        current = parent[current];
      }
      return current;
    }
    for (int v : graph[u])
    {
      if (v >= 0 && v < n && !visited[v])
      {
        visited[v] = true;
        parent[v] = u;
        q.push(v);
      }
    }
  }
  return -1;
}