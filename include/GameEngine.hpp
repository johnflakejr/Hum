#ifndef __GAME_ENGINE_HPP__
#define __GAME_ENGINE_HPP__

#include <SDL.h>

#define MENU_NEW 0
#define MENU_CONTINUE 1
#define MENU_EXIT 2

class GameEngine {

  SDL_Window * game_window;
  SDL_Renderer * game_renderer;

  void game_loop();
  SDL_Texture * load_texture(std::string);
  bool present_static_screen(std::string);
  int present_start_menu();

  public: 
    bool initialize_sdl();
    void play();
    void shutdown_sdl();
  
};

#endif