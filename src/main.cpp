#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_init.h"

#include "include/font_renderer.h"
#include "include/ghost.h"
#include "include/pacman_game.h"
#include "include/player.h"
#include "include/defines.h"

PacmanGame game;

bool load_level(std::string file, PacmanGame* game)
{
  std::cout << "Loading level " << file << std::endl;
  std::ifstream l("../levels/" + file);
  if(!l.is_open())
    return false;

  game->entities.clear();

  // load board
  for(int i = 0; i < BOARD_HEIGHT; ++i)
  {
    for(int j = 0; j < BOARD_WIDTH; ++j)
    {
      int aux;
      l >> aux;
      game->board[i][j] = aux;
    }
  }

  // load player first
  for(int i = 0; i < BOARD_HEIGHT; ++i)
  {
    for(int j = 0; j < BOARD_WIDTH; ++j)
    {
      if (game->board[i][j] == 4)
      {
        game->player = new Player(BOARD_CENTER_OFFSET_X + (j + 1) * TILE_WIDTH, BOARD_CENTER_OFFSET_Y + (i + 1) * TILE_HEIGHT, j + 1, i + 1, &game->board);
        break;
      }
    }
  }

  // lastly, load entities (ghosts)
  for(int i = 0; i < BOARD_HEIGHT; ++i)
  {
    for(int j = 0; j < BOARD_WIDTH; ++j)
    {
      if (game->board[i][j] == 5)
      {
        game->entities.push_back(new Ghost(BOARD_CENTER_OFFSET_X + (j + 1) * TILE_WIDTH, BOARD_CENTER_OFFSET_Y + (i + 1) * TILE_HEIGHT, j + 1, i + 1, game->player, &game->board));
        break;
      }
    }
  }
  
  return true;
}

int main()
{
  // initialise SDL
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
  bool is_running = true;

  // read levels list
  std::cout << "Loading levels list..." << std::endl;
  std::ifstream l("../levels/list");
  if(!l.is_open())
  {
    std::cerr << "Failed to load level list" << std::endl;
    return 1;
  }
  std::string level_file;
  std::vector<std::string> level_files;
  while (std::getline(l, level_file)) {
    level_files.push_back(level_file);
    std::cout << level_file << std::endl;
  }
  
  // load the first level
  if(!load_level(level_files[0], &game))
  {
    std::cerr << "Failed to load level " << level_files[0] << std::endl;
    return 1;
  }

  // load a font
  std::cout << "Loading font..." << std::endl;
  FontRenderer fontRenderer(renderer, "../res/monogram.bmp", 10, 10, 3);
  fontRenderer.text = "00000";

  // FPS cap counter
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
    
    game.player->handleInput();

    // game code
    game.tick();
    game.render(renderer);

    // update the points counter on screen
    std::string aux = std::to_string(game.player->points);
    aux.insert(0, 6 - aux.length(), '0');
    fontRenderer.text = aux;
    fontRenderer.render(renderer);

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