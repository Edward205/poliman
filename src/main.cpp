#include <iostream>

#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_assert.h"
#include "SDL3/SDL_keyboard.h"
#include "include/entity.h"
#include "include/pacman_game.h"

class Player : public Entity
{
public:
  int (*board)[BOARD_WIDTH];
  void handleInput(SDL_Event *e)
  {
    const bool *keys = SDL_GetKeyboardState(NULL);

    if (x == desired_x && y == desired_y) // read keys only when the player is in its desired position
    {
      if (keys[SDL_SCANCODE_W])
        direction = 0;
      else if (keys[SDL_SCANCODE_S])
        direction = 2;
      else if (keys[SDL_SCANCODE_A])
        direction = 3;
      else if (keys[SDL_SCANCODE_D])
        direction = 1;

      if (direction == 0)
        --grid_y;
      else if (direction == 2)
        ++grid_y;
      else if (direction == 3)
        --grid_x;
      else if (direction == 1)
        ++grid_x;
    }
  }
  void tick()
  {
    // logic for smooth movment
    // set the desired position to the middle of the cell which the player should be in
    desired_x = grid_x * (800 / BOARD_WIDTH) - (sprite.w / 2 + ((800 / BOARD_WIDTH) / 2));
    desired_y = grid_y * (600 / BOARD_HEIGHT) - (sprite.h / 2 + ((600 / BOARD_HEIGHT) / 2));

    // if the player's position is in range of the desired position, set it exactly to the desired position
    if (x > desired_x - desired_speed && x < desired_x + desired_speed)
      x = desired_x;
    if (y > desired_y - desired_speed && y < desired_y + desired_speed)
      y = desired_y;
    
    // if ahead of the player is a wall, stop his movment by setting the direction to something else
    if(direction == 0 && board[grid_y - 2][grid_x - 1] == 1)
      // directia 5
      direction = 5;
    if(direction == 1 && board[grid_y - 1][grid_x] == 1)
      direction = 5;
    if(direction == 2 && board[grid_y][grid_x - 1] == 1)
      direction = 5;
    if(direction == 3 && board[grid_y - 1][grid_x - 2] == 1)
      direction = 5;

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
      grid_x = 0;
      desired_x = 0;
      x = 0;
    }
    if (grid_x < 0)
    {
      grid_x = BOARD_WIDTH;
      desired_x = 800;
      x = 800;
    }
    if (grid_y > BOARD_HEIGHT)
    {
      grid_y = 0;
      desired_y = 0;
      y = 0;
    }
    if (grid_y < 0)
    {
      grid_y = BOARD_HEIGHT;
      desired_y = 600;
      y = 600;
    }
  }
  void render(SDL_Renderer *renderer)
  {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    sprite.w = 11;
    sprite.h = 11;
    sprite.x = x;
    sprite.y = y;
    SDL_RenderFillRect(renderer, &sprite);
  }

  ~Player()
  {
  }

private:
  int desired_speed = 4;
};

PacmanGame game;

int main()
{
  const int window_width = 800;
  const int window_height = 600;

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
  {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Window *window = SDL_CreateWindow("Pacman", window_width, window_height, 0);

  if (!window)
  {
    std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  Player player;
  player.x = 0;
  player.y = 0;
  player.grid_x = 10;
  player.grid_y = 10;
  player.board = game.board;

  game.player = &player;

  bool is_running = true;
  while (is_running)
  {
    // handle input events
    SDL_Event event = {0};
    while (SDL_PollEvent(&event))
    {
      if (!is_running)
        break;

      switch (event.type)
      {
      case SDL_EVENT_QUIT: // pressing the close button
      {
        is_running = false; // end the main loop
      }
      break;
      }
    }

    // clear the screen to prepare for the next frame
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // game code
    player.handleInput(&event);
    game.tick();
    game.render(renderer);

    // display the frame (flip buffer)
    SDL_RenderPresent(renderer);

    // shoddy way to cap the FPS, should work fine for now
    SDL_Delay(20);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}