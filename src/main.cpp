#include "SDL3/SDL_init.h"
#include <iostream>


int main() {
  const int window_width = 800;
  const int window_height = 600;

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Window *window = SDL_CreateWindow("test", window_width, window_height, 0);

  if (!window) {
    std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  bool is_running = true;
  while (is_running) {
    SDL_Event event = {0};
    while (SDL_PollEvent(&event)) {
      if (!is_running)
        break;

      switch (event.type) {
      case SDL_EVENT_QUIT: {
        is_running = false;
      } break;
      }
    }

    // game code
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}