#include <iostream>
#include <SDL_image.h>
#include "../include/GameEngine.hpp"

/**
 * @brief Startup SDL and initialize window/renderer variables.
 * 
 * @return true Successful initialization
 * @return false Error during SDL initialization
 */
bool GameEngine::initialize_sdl() {

  int res = SDL_Init(SDL_INIT_VIDEO);

	if (res < 0) {
		std::cout << "SDL could not initialize! SDL_Error: ";
    std::cout << SDL_GetError() << std::endl;
    return false;
  }

  const char * title = "Hum";


  //TODO: let user define these settings.  for now, just keep constant.
  int width = 640;
  int height = 480;

  int x_pos = SDL_WINDOWPOS_CENTERED;
  int y_pos = SDL_WINDOWPOS_CENTERED;
  int flags = SDL_WINDOW_SHOWN;

  game_window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);

  if (NULL == game_window) {
      std::cout << "Window could not be created! SDL_Error: ";
      std::cout << SDL_GetError() << std::endl;
      return false;
  }

  game_renderer = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_ACCELERATED);

  if (NULL == game_renderer){
      std::cout << "Renderer could not be created. ";
      std::cout << SDL_GetError() << std::endl;
      return false;
  }

  flags = IMG_INIT_PNG;

  res = IMG_Init(flags) & flags;

  if (!res) {
      std::cout << "Window could not be created! SDL_Error: ";
      std::cout << IMG_GetError() << std::endl;
      return false;
  }
  return true;

}



/**
 * @brief play the game.  Clean up on exit. 
 */
void GameEngine::play() {

  bool game_over = false;
  int step_delay = 2000;
  SDL_Event e;

  while (!game_over) {
    std::cout << "Playin some games." << std::endl;

    int event = 0;

    do {
        event = SDL_PollEvent(&e);
        if (SDL_QUIT == e.type) {
            game_over = true;
        }
    } while (event != 0);


    SDL_RenderClear(game_renderer);
    SDL_RenderPresent(game_renderer);
    SDL_Delay(step_delay);
  }

  SDL_DestroyRenderer(game_renderer);
  SDL_DestroyWindow(game_window);
  IMG_Quit();
  SDL_Quit();
}