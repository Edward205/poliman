#include "SDL3/SDL_init.h"
#include <iostream>

#include "SDL3/SDL_timer.h"
#include "include/entity.h"

class Player : public Entity {
public:
  void handleInput(SDL_Event *e) {

  }
  void tick() {
    ++x;
  }
  void render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 50, 25, 255);
    SDL_RenderPoint(renderer, x, y);
  }

  ~Player()
  {
    
  }
};

int main() {
  const int window_width = 800;
  const int window_height = 600;

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO )) {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Window *window = SDL_CreateWindow("Pacman", window_width, window_height, 0);

  if (!window) {
    std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  Player player;

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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // game code
    player.tick();
    player.render(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(20);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}