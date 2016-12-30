#pragma once
#include <SDL.h>
#include "consts.hpp"

class Cat
{
public:
  Cat(SDL_Renderer *);
  ~Cat();
  void draw();
  int x = Width / 2;
  float y = Height / 2;
  float vy = 0.0f;
  int accX = 0;
  bool inAir = true;
  bool directionForward = true;
  void tick(unsigned keys);
private:
  SDL_Renderer *renderer;
  SDL_Texture *texture;
};
