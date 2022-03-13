#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "../include/GameEngine.hpp"

using namespace std;
        
int main() {
  std::cout << "Humming along. " << std::endl;

  GameEngine game;
  game.initialize_sdl();
  game.play();
  return 0;
}