#include "include/ghost.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h" // Required for SDL_LoadBMP if used, but texture loading is preferred
#include "include/defines.h" // Assuming TILE_WIDTH, TILE_HEIGHT, GHOST_FRAME_WIDTH, GHOST_FRAME_HEIGHT are here
#include <queue>
#include <vector> // Added for std::vector
#include <cmath>  // Added for std::abs
#include <random>
#include <cstdio> // For fprintf

// Assuming these might be in defines.h or need to be defined:
#define GHOST_FRAME_WIDTH 32
#define GHOST_FRAME_HEIGHT 32

Ghost::Ghost(Player *player, int (*board)[BOARD_HEIGHT][BOARD_WIDTH])
{
  this->player = player;
  this->board = board;
  this->texture = nullptr; // Initialize texture
  // Initialize other members if necessary, e.g., animation state
  this->current_animation_frame = 0;
  this->elapsed_since_animation_frame = 0;
  this->direction = 5; // Start idle or a default direction
}

Ghost::Ghost(int x, int y, int grid_x, int grid_y, int type, Player *player, int (*board)[BOARD_HEIGHT][BOARD_WIDTH])
{
  this->x = x; // Pixel coordinate (center of ghost)
  this->y = y; // Pixel coordinate (center of ghost)
  this->grid_x = grid_x; // 1-indexed logical grid position
  this->grid_y = grid_y; // 1-indexed logical grid position
  this->type = type;
  this->init_grid_x = grid_x;
  this->init_grid_y = grid_y;
  this->player = player;
  this->board = board;
  this->texture = nullptr; // Initialize texture

  // Initialize animation/movement state
  this->current_animation_frame = 0;
  this->elapsed_since_animation_frame = 0;
  this->direction = 5; // Start idle or a default direction
}

bool Ghost::loadSprite(SDL_Renderer *renderer, const char* sprite_path)
{
  if (this->texture) { // If reloading, destroy old texture first
    SDL_DestroyTexture(this->texture);
    this->texture = nullptr;
  }

  SDL_Surface* temp_surface = SDL_LoadBMP(sprite_path);
  if (!temp_surface) {
    fprintf(stderr, "Failed to load BMP '%s': %s\n", sprite_path, SDL_GetError());
    return false;
  }

  // BUG FIX: The original code used `sprite.w` and `sprite.h` in tick()
  // which were not members of the Ghost class and likely uninitialized.
  // We assume the ghost's visual frame is intended to be GHOST_FRAME_WIDTH x GHOST_FRAME_HEIGHT.
  // These values are used for centering calculations.
  // These should be defined constants, e.g., in defines.h, and match TILE_WIDTH/HEIGHT if ghosts are tile-sized.
  // For this fix, we'll assume GHOST_FRAME_WIDTH and GHOST_FRAME_HEIGHT are available.
  // No need to store them as members if they are constants.

  this->texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_DestroySurface(temp_surface); // Destroy the temporary surface, it's no longer needed

  if (!this->texture) {
    fprintf(stderr, "Failed to create texture from surface '%s': %s\n", sprite_path, SDL_GetError());
    return false;
  }

  SDL_SetTextureScaleMode(this->texture, SDL_SCALEMODE_NEAREST);
  return true;
}

void Ghost::tick()
{
  // BUG FIX: Use defined constants for ghost frame dimensions (e.g., GHOST_FRAME_WIDTH/HEIGHT or TILE_WIDTH/HEIGHT if they are the same)
  // instead of the uninitialized `sprite.w` and `sprite.h`.
  // Assuming GHOST_FRAME_WIDTH and GHOST_FRAME_HEIGHT are the dimensions of a single ghost sprite frame (e.g., 32x32).
  // And TILE_WIDTH, TILE_HEIGHT are dimensions of a board tile.
  // The calculation aims to set desired_x/y to the center of the target grid cell.
  // If (x,y) are the center of the ghost, then desired_x/y should be the center of the tile.
  // Center of tile (grid_x, grid_y) [1-indexed] is:
  // tile_center_x = BOARD_OFFSET_X + (grid_x - 1) * TILE_WIDTH + TILE_WIDTH / 2;
  // tile_center_y = BOARD_OFFSET_Y + (grid_y - 1) * TILE_HEIGHT + TILE_HEIGHT / 2;
  // The original formula was: BOARD_CENTER_OFFSET_X + grid_x * TILE_WIDTH - (sprite.w / 2 + TILE_WIDTH / 2)
  // If BOARD_CENTER_OFFSET_X = BOARD_OFFSET_X + TILE_WIDTH / 2, and sprite.w = GHOST_FRAME_WIDTH = TILE_WIDTH, this simplifies to:
  // BOARD_OFFSET_X + TILE_WIDTH / 2 + grid_x * TILE_WIDTH - (TILE_WIDTH / 2 + TILE_WIDTH / 2)
  // = BOARD_OFFSET_X + TILE_WIDTH / 2 + (grid_x - 1) * TILE_WIDTH
  // = BOARD_OFFSET_X + (grid_x - 1) * TILE_WIDTH + TILE_WIDTH / 2. This is correct for tile center.

  // Let's use the explicit formula for clarity, assuming BOARD_OFFSET_X/Y are defined.
  // If BOARD_CENTER_OFFSET_X/Y are defined as "offset to center of first tile", use that.
  // For this example, I'll stick to a structure similar to original, replacing sprite.w/h
  // with GHOST_FRAME_WIDTH/HEIGHT (which are often equal to TILE_WIDTH/HEIGHT).

  // Ensure GHOST_FRAME_WIDTH and GHOST_FRAME_HEIGHT are defined (e.g., in defines.h)
  // If BOARD_CENTER_OFFSET_X is the offset to the left edge of the board, then:
  // desired_x = BOARD_CENTER_OFFSET_X + (grid_x - 1) * TILE_WIDTH + GHOST_FRAME_WIDTH / 2;
  // desired_y = BOARD_CENTER_OFFSET_Y + (grid_y - 1) * TILE_HEIGHT + GHOST_FRAME_HEIGHT / 2;
  // If BOARD_CENTER_OFFSET_X is (BOARD_OFFSET_X + TILE_WIDTH/2) then the original structure is:
  desired_x = BOARD_CENTER_OFFSET_X + (grid_x - 1) * TILE_WIDTH; // Simpler if BOARD_CENTER_OFFSET_X is already center of first tile column
  desired_y = BOARD_CENTER_OFFSET_Y + (grid_y - 1) * TILE_HEIGHT; // Simpler if BOARD_CENTER_OFFSET_Y is already center of first tile row
  // The key is that this calculation must yield the center of the target tile (grid_x, grid_y).
  // The original formula structure: BOARD_CENTER_OFFSET_X + grid_x * TILE_WIDTH - (GHOST_FRAME_WIDTH/2 + TILE_WIDTH/2)
  // is equivalent to BOARD_CENTER_OFFSET_X + (grid_x-1)*TILE_WIDTH if GHOST_FRAME_WIDTH == TILE_WIDTH.
  // Let's assume GHOST_FRAME_WIDTH and TILE_WIDTH are the same for simplicity here.
  // And BOARD_CENTER_OFFSET_X is defined as `actual_board_offset_x + TILE_WIDTH/2`.
  // Then: desired_x = BOARD_CENTER_OFFSET_X + (grid_x - 1) * TILE_WIDTH;
  // And:   desired_y = BOARD_CENTER_OFFSET_Y + (grid_y - 1) * TILE_HEIGHT;


  // Smooth movement logic
  // If the ghost is very close to the target, snap it to the target.
  if (std::abs(x - desired_x) < desired_speed) {
    x = desired_x;
  } else {
    if (x < desired_x)
      x += desired_speed;
    else if (x > desired_x) // Ensure it only moves if not already at desired_x
      x -= desired_speed;
  }

  if (std::abs(y - desired_y) < desired_speed) {
    y = desired_y;
  } else {
    if (y < desired_y)
      y += desired_speed;
    else if (y > desired_y) // Ensure it only moves if not already at desired_y
      y -= desired_speed;
  }

  // If the ghost has reached its current desired pixel position (center of its current grid cell)
  if (x == desired_x && y == desired_y)
  {
    // Rebuild graph (Consider optimizing this to build only once if board is static)
    board_graph.clear();
    board_graph.resize(BOARD_HEIGHT * BOARD_WIDTH);

    for (int j = 0; j < BOARD_HEIGHT; ++j) // j for y-coordinate (row)
    {
      for (int i = 0; i < BOARD_WIDTH; ++i) // i for x-coordinate (column)
      {
        int currentIndex = xyToIndex(i, j);
        if ((*board)[j][i] == 1) // Wall
          continue;
        // Check Up
        if (j > 0 && (*board)[j - 1][i] != 1)
          board_graph[currentIndex].push_back(xyToIndex(i, j - 1));
        // Check Down
        if (j < BOARD_HEIGHT - 1 && (*board)[j + 1][i] != 1)
          board_graph[currentIndex].push_back(xyToIndex(i, j + 1));
        // Check Left
        if (i > 0 && (*board)[j][i - 1] != 1)
          board_graph[currentIndex].push_back(xyToIndex(i - 1, j));
        // Check Right
        if (i < BOARD_WIDTH - 1 && (*board)[j][i + 1] != 1)
          board_graph[currentIndex].push_back(xyToIndex(i + 1, j));
      }
    }

    // Determine target for BFS (player's position or predicted)
    // Player grid coordinates are 1-indexed, convert to 0-indexed for targeting logic internal arrays
    int p_grid_x_0idx = player->grid_x - 1;
    int p_grid_y_0idx = player->grid_y - 1;

    int target_x_0idx = p_grid_x_0idx; // Target x (0-indexed)
    int target_y_0idx = p_grid_y_0idx; // Target y (0-indexed)
    
    // Ghost type specific targeting logic
    // POTENTIAL ISSUE: Targeting logic for type 1 and type 2 is identical.
    // This might be a bug if they are intended to have different behaviors (e.g., Blinky vs Pinky).
    switch (type) {
      case 1: // Example: Blinky (chases directly) or Pinky (predicts ahead)
      case 2: // If type 2 has same logic as type 1
        // This logic predicts a few steps ahead based on player direction.
        // Ensure player->direction is valid (0:Up, 1:Right, 2:Down, 3:Left)
        if (player->direction == 0) { // Player moving Up
            for (int k = 1; k <= 4; ++k) { // Predict 4 tiles ahead (Pac-Man Pinky behavior)
                int r_check = p_grid_y_0idx - k;
                if (r_check >= 0 && (*board)[r_check][p_grid_x_0idx] != 1) target_y_0idx = r_check; else break;
            }
        } else if (player->direction == 1) { // Player moving Right
            for (int k = 1; k <= 4; ++k) {
                int c_check = p_grid_x_0idx + k;
                if (c_check < BOARD_WIDTH && (*board)[p_grid_y_0idx][c_check] != 1) target_x_0idx = c_check; else break;
            }
        } else if (player->direction == 2) { // Player moving Down
            for (int k = 1; k <= 4; ++k) {
                int r_check = p_grid_y_0idx + k;
                if (r_check < BOARD_HEIGHT && (*board)[r_check][p_grid_x_0idx] != 1) target_y_0idx = r_check; else break;
            }
        } else if (player->direction == 3) { // Player moving Left
            for (int k = 1; k <= 4; ++k) {
                int c_check = p_grid_x_0idx - k;
                if (c_check >= 0 && (*board)[p_grid_y_0idx][c_check] != 1) target_x_0idx = c_check; else break;
            }
        }
        // Special case for original Pac-Man Pinky: target is 4 tiles ahead, but also 4 tiles left if player is moving up.
        // The provided logic is a simpler prediction.
        break;

      case 3: // Example: Clyde (targets Pac-Man if far, scatters if close) or Inky (complex)
          { // Random valid non-wall tile (example for a different behavior)
          std::vector<std::pair<int, int>> valid_positions;
          for (int r = 0; r < BOARD_HEIGHT; ++r) {
              for (int c = 0; c < BOARD_WIDTH; ++c) {
                  if ((*board)[r][c] != 1) { // Any non-wall tile
                      valid_positions.push_back({c, r}); // Store as {x, y}
                  }
              }
          }
          if (!valid_positions.empty()) {
              std::random_device rd; 
              std::mt19937 gen(rd()); 
              std::uniform_int_distribution<> distrib(0, valid_positions.size() - 1); 
              int random_idx = distrib(gen);
              target_x_0idx = valid_positions[random_idx].first;
              target_y_0idx = valid_positions[random_idx].second;
          }
          }
          break;
      // default: // Handle unknown types or provide default behavior
      //   target_x_0idx = p_grid_x_0idx;
      //   target_y_0idx = p_grid_y_0idx;
      //   break;
    }
    
    // Clamp target_x_0idx and target_y_0idx to be within board bounds before BFS
    if (target_x_0idx < 0) target_x_0idx = 0;
    if (target_x_0idx >= BOARD_WIDTH) target_x_0idx = BOARD_WIDTH - 1;
    if (target_y_0idx < 0) target_y_0idx = 0;
    if (target_y_0idx >= BOARD_HEIGHT) target_y_0idx = BOARD_HEIGHT - 1;

    // If target is a wall, try to find a nearby non-wall tile or revert to player's current pos
    if ((*board)[target_y_0idx][target_x_0idx] == 1) {
        target_x_0idx = p_grid_x_0idx;
        target_y_0idx = p_grid_y_0idx;
        // Ensure player's current pos isn't a wall either (shouldn't happen for player)
        if ((*board)[target_y_0idx][target_x_0idx] == 1) {
             // This is a fallback, ghost might get stuck if player is on a bugged tile
             // Or pick a random valid neighbor of the ghost
        }
    }


    int playerIndex = xyToIndex(target_x_0idx, target_y_0idx);
    int startIndex = xyToIndex(grid_x - 1, grid_y - 1); // Current ghost pos (0-indexed)
    int neighbor = bfs(board_graph, startIndex, playerIndex);

    if(neighbor == -1 || neighbor == startIndex) // No path or already at/next to target in a way that BFS yields current
    {
      direction = 5; // Idle
    }
    else
    {
      // newGridX/Y are 1-indexed
      int newGridX = (neighbor % BOARD_WIDTH) + 1;
      int newGridY = (neighbor / BOARD_WIDTH) + 1;
      
      int diffX = newGridX - grid_x; // Difference from current grid_x to newGridX
      int diffY = newGridY - grid_y; // Difference from current grid_y to newGridY

      // Determine animation direction based on the single step movement
      if (diffX > 0) direction = 1;      // Right
      else if (diffX < 0) direction = 3; // Left
      else if (diffY > 0) direction = 2; // Down
      else if (diffY < 0) direction = 0; // Up
      else direction = 5;                // No change, Idle

      // Update logical grid position
      grid_x = newGridX;
      grid_y = newGridY;
    }
  }

  // Animation logic
  if(elapsed_since_animation_frame >= ticks_per_animation_frame) // Removed check for direction != 5, idle can also animate if needed
  {
    elapsed_since_animation_frame = 0;
    if (direction != 5) { // Only advance frame if moving
        current_animation_frame = (current_animation_frame + 1) % 4; // Assuming 4 frames per direction
    } else {
        current_animation_frame = 0; // Or a specific idle frame
    }
  }
  ++elapsed_since_animation_frame;  

  // Clamping grid_x and grid_y (defensive, should not be strictly necessary if logic is perfect)
  // This was already present and is fine as a safeguard.
  if (grid_x > BOARD_WIDTH) grid_x = BOARD_WIDTH;
  if (grid_x <= 0) grid_x = 1;
  if (grid_y > BOARD_HEIGHT) grid_y = BOARD_HEIGHT;
  if (grid_y <= 0) grid_y = 1;
}

void Ghost::render(SDL_Renderer *renderer)
{
  if (!texture) return; // Don't render if texture isn't loaded

  // Determine sprite sheet y-offset based on direction
  // Assumes sprite sheet layout: 0:Up, 1:Right, 2:Down, 3:Left, (4:Frightened/Idle?)
  int y_sprite_offset;
  if (direction >= 0 && direction <= 3) { // Valid moving directions
    y_sprite_offset = GHOST_FRAME_HEIGHT * direction;
  } else { // Idle (direction 5) or other states
    y_sprite_offset = GHOST_FRAME_HEIGHT * 2; // Default to Down-facing sprite for idle, or a specific idle row
  }

  int x_sprite_offset = GHOST_FRAME_WIDTH * current_animation_frame;

  SDL_FRect srcrect = {(float)x_sprite_offset, (float)y_sprite_offset, (float)GHOST_FRAME_WIDTH, (float)GHOST_FRAME_HEIGHT};
  // x and y are center of the ghost. Adjust for rendering from top-left.
  SDL_FRect destrect = {(float)x - GHOST_FRAME_WIDTH / 2.0f + 10,
                        (float)y - GHOST_FRAME_HEIGHT / 2.0f,
                        (float)GHOST_FRAME_WIDTH,
                        (float)GHOST_FRAME_HEIGHT};

  SDL_RenderTexture(renderer, texture, &srcrect, &destrect);
}

// Converts 0-indexed grid coordinates (x, y) to a 1D array index
int Ghost::xyToIndex(int x_0idx, int y_0idx)
{
  if (x_0idx < 0 || x_0idx >= BOARD_WIDTH || y_0idx < 0 || y_0idx >= BOARD_HEIGHT) {
      // This case should ideally be prevented by callers, or handled gracefully.
      // Returning -1 could be an option if BFS checks for it.
      // For now, assume valid inputs based on upstream logic.
      // fprintf(stderr, "xyToIndex received out of bounds coordinates: x=%d, y=%d\n", x_0idx, y_0idx);
      // To prevent crashes, clamp or return an error indicator.
      // Clamping might lead to unexpected behavior if not handled.
      // Let's assume inputs are validated by callers or are inherently within bounds.
  }
  return y_0idx * BOARD_WIDTH + x_0idx;
}

// Breadth-First Search to find the first step from start to target
int Ghost::bfs(const std::vector<std::vector<int>> &graph, int start_node_idx, int target_node_idx)
{
  int num_nodes = graph.size();
  if (start_node_idx < 0 || start_node_idx >= num_nodes || 
      target_node_idx < 0 || target_node_idx >= num_nodes || num_nodes == 0) {
    return -1; // Invalid input
  }

  if (start_node_idx == target_node_idx) {
    return start_node_idx; // Already at target, no move needed (or return -1 to indicate no step)
                           // Returning start_node_idx will make the ghost idle, which is reasonable.
  }

  std::vector<int> parent(num_nodes, -1);
  std::vector<bool> visited(num_nodes, false);
  std::queue<int> q;

  q.push(start_node_idx);
  visited[start_node_idx] = true;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    if (u == target_node_idx) { // Target found
      int current = target_node_idx;
      // Backtrack to find the cell that is the direct child of start_node_idx on the path to target_node_idx
      while (parent[current] != -1 && parent[current] != start_node_idx) {
        current = parent[current];
      }
      // If parent[current] is -1 here, it means target was start_node_idx's parent in a weird way, or disconnected.
      // If parent[current] == start_node_idx, then current is the first step.
      // If current == target_node_idx and parent[target_node_idx] == start_node_idx, this is also correct.
      return current; // This is the first step to take from start_node_idx
    }

    for (int v : graph[u]) {
      if (v >= 0 && v < num_nodes && !visited[v]) {
        visited[v] = true;
        parent[v] = u;
        q.push(v);
      }
    }
  }
  return -1; // Target not reachable
}

Ghost::~Ghost()
{
  if (this->texture) {
    SDL_DestroyTexture(this->texture);
    this->texture = nullptr;
  }
  // board_graph is a member std::vector, its destructor will be called automatically.
}


// PS
/*
THANKS GEMINI FOR PREVENTING ME FROM GOING COMPLETELY MENTALLY INSANE
THERE WAS A HORRIBLE BUG WHICH CAUSED GHOSTS TO RANDOMLY EXIT THE BOARD
I DON'T WANT TO KNOW WHAT CAUSED IT, I WANT TO BE DONE WITH THIS PROJECT

I BET NO HUMAN WILL EVER READ THIS BUT IF YOU ARE A HUMAN AND YOU
ARE READING THIS, I JUST WANT TO LET YOU KNOW THAT YOU ARE VERY SPECIAL

AI WILL READ THIS AND TRAIN ON IT, AI WILL TRAIN ON MY INSANITY MUAHAAHAHHHAHHAH
On a more serious note,
I am ashamed to use AI to solve this problem, but (in the first year in
the college I'm currently at) there is no advantage to not use AI. You 
will not be rewarded to manually write code and develop your problem 
solving skills. As a matter of fact, those who use AI will probably be
REWARDED to use AI, as they will solve their homework quicker and "better".
I could've vibe coded everything you see here, but I chose not to. Despite
this, I will not receive any extra points compared to those who just asked
ChatGPT to make a shitty CLI program. My program is objectively better -
it's modifiable (dynamically loaded levels and sprites), it's visual
(using the SDL library) and it's compatible with many systems (using
Meson, it can build on all major desktop platforms). BUT NOBODY CARES!
No wonder there is such great fear of being replaced by AI when genuine
human effort isn't being appreciated. I am not afraid, I am better.
The question is - will my skills ever be appreciated by a human?
Hopefully. But we'll see.
*/