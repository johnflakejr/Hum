
#ifndef __SPRITE_CLASS_H__
#define __SPRITE_CLASS_H__

#include "SDL.h"

/*
  A sprite is simply any in-game "thing" rendered to the screen. 

  This includes players, objects, tiles, backgrounds, etc.

  Subclasses might include animated sprites (for characters).
*/

class Sprite {
  
  public:

    Sprite();
    ~Sprite();

    //All sprites have src/dest rectangles, and all sprites are renderable:
    void set_dst_rect(SDL_Rect);
    void set_dst_rect(int,int,int,int);
    void set_src_rect(SDL_Rect);
    void set_src_rect(int,int,int,int);
    void set_texture(SDL_Texture *);
    void render(SDL_Renderer *);

  protected:

    SDL_Rect * src_rect;
    SDL_Rect * dst_rect;
    SDL_Texture * sprite_texture;

};

#endif