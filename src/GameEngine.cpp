#include <iostream>
#include <SDL_image.h>
#include "../include/GameEngine.hpp"
#include "../include/Sprite.hpp"

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

SDL_Texture * GameEngine::load_texture(std::string path) {
  SDL_Surface * temp = IMG_Load(path.c_str());
  return SDL_CreateTextureFromSurface(game_renderer, temp);
}

/**
 * @brief Present the start menu and get the resulting choice from the user.
 * 
 * @return int choice (New Game / Continue / Exit Game)
 */
int GameEngine::present_start_menu() {


  Sprite menu_background;
  Sprite new_game_button;
  Sprite continue_game_button;
  Sprite exit_game_button;

  menu_background.set_texture(load_texture("./assets/menu_background.png"));
  new_game_button.set_texture(load_texture("./assets/new_game_button.png"));
  continue_game_button.set_texture(load_texture("./assets/continue_button.png"));
  exit_game_button.set_texture(load_texture("./assets/exit_game_button.png"));

  new_game_button.set_dst_rect(220,100,220,60);
  continue_game_button.set_dst_rect(220,200,220,60);
  exit_game_button.set_dst_rect(220,300,220,60);

  new_game_button.set_src_rect(0,60,220,60);
  continue_game_button.set_src_rect(0,0,220,60);
  exit_game_button.set_src_rect(0,0,220,60);
 
  int selected = MENU_NEW;

  SDL_Event e;
  bool show_screen = true;

  while(show_screen) {
    while (SDL_PollEvent(&e) != 0) {
      if (SDL_QUIT == e.type) {
        return false;
      } else if (SDL_KEYDOWN == e.type) {
        switch(e.key.keysym.sym) {
          case SDLK_DOWN:
            selected++;
            if (selected > MENU_EXIT) {
              selected = MENU_EXIT;
            }
            break;
          case SDLK_UP:
            selected--;
            if (selected < MENU_NEW) {
              selected = MENU_NEW;
            }
            break;
          case SDLK_RETURN:
            show_screen = false;
            break;
        }
      }
    }

    switch(selected) {
      case MENU_NEW:
        new_game_button.set_src_rect(0,60,220,60);
        continue_game_button.set_src_rect(0,0,220,60);
        exit_game_button.set_src_rect(0,0,220,60);
        break;
      case MENU_CONTINUE:
        new_game_button.set_src_rect(0,0,220,60);
        continue_game_button.set_src_rect(0,60,220,60);
        exit_game_button.set_src_rect(0,0,220,60);
        break;
      case MENU_EXIT:
        new_game_button.set_src_rect(0,0,220,60);
        continue_game_button.set_src_rect(0,0,220,60);
        exit_game_button.set_src_rect(0,60,220,60);
        break;
    }

    SDL_RenderClear(game_renderer);

    menu_background.render(game_renderer);
    new_game_button.render(game_renderer);
    continue_game_button.render(game_renderer);
    exit_game_button.render(game_renderer);

    SDL_RenderPresent(game_renderer);
  }

  return selected;
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

  int option = present_start_menu();
  if (MENU_EXIT == option) {
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