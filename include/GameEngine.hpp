#ifndef __GAME_ENGINE_HPP__
#define __GAME_ENGINE_HPP__

#include <SDL.h>

class GameEngine {

  SDL_Window * game_window;
  SDL_Renderer * game_renderer;

  void game_loop();


  public: 
    bool initialize_sdl();
    void play();
  
};

#endif