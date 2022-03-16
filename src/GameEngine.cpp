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
 * @brief Show the start screen to the user.  Proceed when a key is pressed. 
 * 
 */
bool GameEngine::present_static_screen(std::string path) {

  SDL_Surface * temp = IMG_Load(path.c_str());
  SDL_Texture * start_screen_texture = SDL_CreateTextureFromSurface(game_renderer, temp);
  SDL_Event e;
  
  SDL_RenderClear(game_renderer);
  SDL_RenderCopy(game_renderer, start_screen_texture, NULL, NULL);
  SDL_RenderPresent(game_renderer);
  bool show_screen = true;

  while(show_screen) {
    while (SDL_PollEvent(&e) != 0) {
      if (SDL_QUIT == e.type) {
        return false;
      } else if (SDL_KEYDOWN == e.type) {
        show_screen = false;
      }
    }
  }

  SDL_DestroyTexture(start_screen_texture);
  start_screen_texture = NULL;
  temp = NULL;
  return true;
}


/**
 * @brief play the game.  Clean up on exit. 
 */
void GameEngine::play() {

  if (!present_static_screen("./assets/first_screen.png")){
    return;
  }

  if (!present_static_screen("./assets/second_screen.png")){
    return;
  }
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
    //renderObjects
    //checkevents
    SDL_RenderPresent(game_renderer);
    SDL_Delay(step_delay);
  }
}

/**
 * @brief destroy GameEngine variables and shutdown SDL.
 * 
 */
void GameEngine::shutdown_sdl() {
  SDL_DestroyRenderer(game_renderer);
  game_renderer = NULL;

  SDL_DestroyWindow(game_window);
  game_window = NULL;

  IMG_Quit();
  SDL_Quit();
}