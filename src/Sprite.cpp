#include "../include/Sprite.hpp"

/**
 * @brief Set the destination rectangle for the sprite.
 * 
 * This is the rectangle where the sprite is 
 * rendered to the screen.
 * 
 * @param r destination rectangle
 */
void Sprite::set_dst_rect(SDL_Rect r) {
  dst_rect = new SDL_Rect(r);
}

/**
 * @brief Set the source rectangle for the sprite.
 * 
 * This is the rectangle where the sprite is grabbed
 * from the texture. 
 * 
 * @param r source rectangle
 */
void Sprite::set_src_rect(SDL_Rect r) {
  src_rect = new SDL_Rect(r);
}

/**
 * @brief Set the texture for the sprite.
 * 
 * The texture (usually from a .png) is the image
 * the sprite is taken from.
 * 
 * @param tex sprite texture
 */
void Sprite::set_texture(SDL_Texture * tex) {
  sprite_texture = tex;
}

void Sprite::render(SDL_Renderer * rend) {
  SDL_RenderCopy(rend, sprite_texture, src_rect, dst_rect);
}

Sprite::Sprite() {
  src_rect = NULL;
  dst_rect = NULL;
}

Sprite::~Sprite() {
  delete src_rect;
  src_rect = NULL;
  delete dst_rect;
  dst_rect = NULL;

  SDL_DestroyTexture(sprite_texture);
  sprite_texture = NULL;
}