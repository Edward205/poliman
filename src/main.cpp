#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_scancode.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_init.h"

#include "include/font_renderer.h"
#include "include/ghost.h"
#include "include/pacman_game.h"
#include "include/player.h"
#include "include/defines.h"

SDL_Renderer *renderer;

PacmanGame game;
Quiz quiz;

bool load_level(std::string file, PacmanGame* game)
{
  std::cout << "Loading level " << file << std::endl;
  std::ifstream l("../levels/" + file);
  if(!l.is_open())
    return false;

  game->entities.clear();
  game->max_points = 0;
  // load board
  for(int i = 0; i < BOARD_HEIGHT; ++i)
  {
    for(int j = 0; j < BOARD_WIDTH; ++j)
    {
      int aux;
      l >> aux;
      game->board[i][j] = aux;
      if(aux == 2)
        ++game->max_points;
    }
  }

  // load player first
  for(int i = 0; i < BOARD_HEIGHT; ++i)
  {
    for(int j = 0; j < BOARD_WIDTH; ++j)
    {
      if (game->board[i][j] == 4)
      {
        if(game->player != nullptr)
          delete game->player;
        game->player = new Player(BOARD_CENTER_OFFSET_X + (j + 1) * TILE_WIDTH, BOARD_CENTER_OFFSET_Y + (i + 1) * TILE_HEIGHT, j + 1, i + 1, &game->board);
        
        if(!game->player->loadSprite(renderer, "../res/student.bmp"))
          std::cerr << "Failed to load player sprite" << std::endl;
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
        game->entities.push_back(new Ghost(BOARD_CENTER_OFFSET_X + (j + 1) * TILE_WIDTH, BOARD_CENTER_OFFSET_Y + (i + 1) * TILE_HEIGHT, j + 1, i + 1, game->entities.size(), game->player, &game->board));
      }
    }
  }
  // load the entities sprites
  for(auto entity : game->entities)
  {
    entity->loadSprite(renderer, "../res/professor.bmp");
  }

  std::string air_sprite_filename, wall_sprite_filename;
  std::getline(l, air_sprite_filename); // first getline is blank

  std::getline(l, air_sprite_filename);
  std::getline(l, wall_sprite_filename);

  // load the level sprites 
  if(!game->loadSprites(renderer, air_sprite_filename.c_str(), wall_sprite_filename.c_str(), "../res/point.bmp"))
  {
    std::cerr << "Failed to load game sprites" << std::endl; 
  }


  
  return true;
}

int main()
{
  // initialise SDL
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Window *window = SDL_CreateWindow("Poliman", WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  if (!window)
  {
    std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, NULL);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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
  int current_level = 0;
  if(!load_level(level_files[current_level], &game))
  {
    std::cerr << "Failed to load level " << level_files[0] << std::endl;
    return 1;
  }

  // load score display
  FontRenderer scoreDisplay(renderer, "../res/monogram.bmp", 10, 10, 3, 7);
  scoreDisplay.text = "00000";

  FontRenderer livesDisplay(renderer, "../res/monogram.bmp", 10, 50, 3, 7);
  scoreDisplay.text = std::to_string(game.lives);

  // initialise quiz
  quiz.init(renderer);
  game.quiz = &quiz;

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

      // TODO this is not optimal; create a handleInput method for the PacmanGame class
      game.quiz->handleInput(event);
      switch (event.type)
      {
      case SDL_EVENT_QUIT: // pressing the close button
      {
        is_running = false; // end the main loop
      }
      case SDL_EVENT_KEY_DOWN:
      {
        if(event.key.scancode == SDL_SCANCODE_LEFTBRACKET && current_level > 0)
        {
          --current_level;
          load_level(level_files[current_level], &game);
        }
        if(event.key.scancode == SDL_SCANCODE_RIGHTBRACKET && current_level < 2)
        {
          ++current_level;
          load_level(level_files[current_level], &game);
        }
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
    scoreDisplay.text = aux;
    scoreDisplay.render(renderer);

    livesDisplay.text = std::to_string(game.lives);
    livesDisplay.render(renderer);

    if(game.lives <= 0)
    {
      SDL_SetRenderDrawColor(renderer, 40, 0, 0, 255);
      SDL_RenderClear(renderer);
      livesDisplay.text = "RESTANTA !!!";
      livesDisplay.scale = 6;
      livesDisplay.max_chars = 15;
      livesDisplay.x = 200;
      livesDisplay.y = 200;
      livesDisplay.render(renderer);
    }

    if(game.max_points == game.player->points)
    {
      SDL_Delay(2000);
      ++current_level;
      if(!load_level(level_files[current_level], &game))
        std::cerr << "Failed to load level " << level_files[current_level] << std::endl;
    }

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