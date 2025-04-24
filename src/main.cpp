#include <iostream>

#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_init.h"

#include "include/ghost.h"
#include "include/pacman_game.h"
#include "include/player.h"
#include "include/defines.h"

PacmanGame game;

int main()
{
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
  {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Window *window = SDL_CreateWindow("Pacman", WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  if (!window)
  {
    std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  Player player(27, 27, 2, 2, game.board);
  game.player = &player;

  Ghost ghost(&player, game.board);
  ghost.grid_x = 12;
  ghost.grid_y = 14;
  game.entities.push_back(&ghost);

  bool is_running = true;

  Uint64 performanceFrequency = SDL_GetPerformanceFrequency();
  Uint64 targetTicksPerFrame = performanceFrequency / SCREEN_FPS;

  Uint64 lastCounter = SDL_GetPerformanceCounter();

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
    player.handleInput();
    game.tick();
    game.render(renderer);

    // display the frame (flip buffer)
    SDL_RenderPresent(renderer);

    // delay the next frame to cap FPS
    Uint64 currentCounter = SDL_GetPerformanceCounter();
    Uint64 elapsedTicks = currentCounter - lastCounter;

    if (elapsedTicks < targetTicksPerFrame) 
    {
        Uint64 remainingTicks = targetTicksPerFrame - elapsedTicks;
        Uint32 delayMs = (remainingTicks * 1000) / performanceFrequency;
        SDL_Delay(delayMs);
    }

    lastCounter = SDL_GetPerformanceCounter(); 
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}