#include "cat.hpp"
#include "load_texture.hpp"

Cat::Cat(SDL_Renderer *renderer):
  renderer(renderer),
  texture(loadTexture(renderer, "cat.bmp"))
{}

Cat::~Cat()
{
  SDL_DestroyTexture(texture);
}


void Cat::draw()
{
  SDL_Rect src;
  src.x = (SDL_GetTicks() / (1000 / 12) % 8) * 64;
  src.y = 0;
  src.w = 64;
  src.h = 128;
  SDL_Rect dest;
  dest.x = Width / 2;
  dest.y = y;
  dest.w = 64;
  dest.h = 128;
  SDL_RenderCopyEx(renderer,
                   texture,
                   &src, &dest,
                   0, nullptr,
                   directionForward ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void Cat::tick(unsigned keys)
{
  if (keys & KeyLeft)
  {
    accX--;
    directionForward = false;
  }
  if (keys & KeyRight)
  {
    accX++;
    directionForward = true;
  }
  if (keys & KeyJump && !inAir && vy >= 0)
  {
    vy -= 1.0f;
  }
  for ( ;accX > 3; accX -= 3)
    ++x;
  for ( ;accX < -3; accX += 3)
    --x;
  
  if (inAir)
    vy += 0.003;
  else
  {
    if (vy > 0)
      vy = 0;
  }
  y += vy;
}
