#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"

#include "include/defines.h"
#include "include/player.h"

Player::Player(int x, int y, int grid_x, int grid_y, int (*board)[BOARD_HEIGHT][BOARD_WIDTH])
{
  this->x = x;
  this->y = y;
  this->grid_x = grid_x;
  this->grid_y = grid_y;
  this->board = board;
}
Player::Player()
{
  this->x = 0;
  this->y = 0;
  this->grid_x = 1;
  this->grid_y = 1;
  this->board = nullptr;
}
bool Player::loadSprite(SDL_Renderer *renderer, const char* sprite)
{
  surface = SDL_LoadBMP(sprite);
  if(!surface)
      return false;

  SDL_Texture* aux_texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
  if(!aux_texture)
      return false;

  SDL_SetTextureScaleMode(aux_texture, SDL_SCALEMODE_NEAREST);
  texture = aux_texture;
  return true;
}

void Player::handleInput()
{
  const bool *keys = SDL_GetKeyboardState(NULL);

  if (x == desired_x && y == desired_y) // read keys only when the player is in its desired position
  {
    if (keys[SDL_SCANCODE_W] && isValidDirection(0))
      direction = 0;
    else if (keys[SDL_SCANCODE_S] && isValidDirection(2))
      direction = 2;
    else if (keys[SDL_SCANCODE_A] && isValidDirection(3))
      direction = 3;
    else if (keys[SDL_SCANCODE_D] && isValidDirection(1))
      direction = 1;

    if (direction == 0 && isValidDirection(0))
      --grid_y;
    else if (direction == 2 && isValidDirection(2))
      ++grid_y;
    else if (direction == 3 && isValidDirection(3))
      --grid_x;
    else if (direction == 1 && isValidDirection(1))
      ++grid_x;
  }
}

void Player::tick()
{
  // logic for smooth movment
  // set the desired position to the middle of the cell which the player should be in
  desired_x = BOARD_CENTER_OFFSET_X + grid_x * (TILE_WIDTH) - (sprite.w / 2 + ((TILE_WIDTH) / 2));
  desired_y = BOARD_CENTER_OFFSET_Y + grid_y * (TILE_HEIGHT) - (sprite.h / 2 + ((TILE_HEIGHT) / 2));

  // if the player's position is in range of the desired position, set it exactly to the desired position
  if (x > desired_x - desired_speed && x < desired_x + desired_speed)
    x = desired_x;
  if (y > desired_y - desired_speed && y < desired_y + desired_speed)
    y = desired_y;

  // check if the current direction is valid (does not hit a wall)
  if (!isValidDirection(direction))
    direction = 5; // stop his movment by setting the direction to something else

  // if the player is not in the desired position, move him towards it
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

  // wrap-around logic
  if (grid_x > BOARD_WIDTH)
  {
    grid_x = 1;
    desired_x = BOARD_CENTER_OFFSET_X + grid_x * (TILE_WIDTH) - (sprite.w / 2 + ((TILE_WIDTH) / 2));
    x = desired_x;
  }
  if (grid_x <= 0)
  {
    grid_x = BOARD_WIDTH;
    desired_x = BOARD_CENTER_OFFSET_X + grid_x * (TILE_WIDTH) - (sprite.w / 2 + ((TILE_WIDTH) / 2));
    x = desired_x;
  }
  if (grid_y > BOARD_HEIGHT)
  {
    grid_y = 1;
    desired_y = BOARD_CENTER_OFFSET_Y + grid_y * (TILE_HEIGHT) - (sprite.h / 2 + ((TILE_HEIGHT) / 2));
    y = desired_y;
  }
  if (grid_y <= 0)
  {
    grid_y = BOARD_HEIGHT;
    desired_y = BOARD_CENTER_OFFSET_Y + grid_y * (TILE_HEIGHT) - (sprite.h / 2 + ((TILE_HEIGHT) / 2));
    y = desired_y;
  }

  // eat points
  if (x == desired_x && y == desired_y && (*board)[grid_y - 1][grid_x - 1] == 2)
  {
    (*board)[grid_y - 1][grid_x - 1] = 0;
    ++points;
  }

  // animation logic
  if(elapsed_since_animation_frame >= ticks_per_animation_frame && direction != 5)
  {
    elapsed_since_animation_frame = 0;
    if(current_animation_frame < 3)
      ++current_animation_frame;
    else
      current_animation_frame = 0;
  }

  ++elapsed_since_animation_frame;
}

void Player::render(SDL_Renderer *renderer)
{
  int y_offset;
  if(direction < 5)
    y_offset = 32 * direction;
  else
    y_offset = 32 * 2;

  int x_offset = 32 * current_animation_frame;

  SDL_FRect srcrect({(float) x_offset, (float) y_offset, 32, 32});
  SDL_FRect destrect({(float) x - 16, (float) y - 16, 32, 32});

  SDL_RenderTexture(renderer, texture, &srcrect, &destrect);
}

Player::~Player()
{
  SDL_DestroySurface(surface);
}

bool Player::isValidDirection(int direction)
{
  // do not change this. trust me, it works

  // check if ahead of the player is the board limit
  if (grid_x >= BOARD_WIDTH || grid_x - 1 <= 0 || grid_y >= BOARD_HEIGHT + 1 || grid_y - 1 <= 0)
    return true; // allow the player to exit the area, in which case the wrap-around logic activates

  // check if ahead of the player is a wall
  // up
  if (direction == 0 && (*board)[grid_y - 2][grid_x - 1] == 1)
    return false;

  // right
  if (direction == 1 && (*board)[grid_y - 1][grid_x] == 1)
    return false;

  // down
  if (direction == 2 && (*board)[grid_y][grid_x - 1] == 1)
    return false;

  // left
  if (direction == 3 && (*board)[grid_y - 1][grid_x - 2] == 1)
    return false;
  return true;
}