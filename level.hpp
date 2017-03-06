#pragma once
#include <SDL.h>
#include "consts.hpp"
#include <vector>

class Level
{
public:
  Level(SDL_Renderer *, int &scroll);
  ~Level();
  void draw();
  bool isInAir(int x, int y);
  void correctXY(int &x, float &y);
  void checkCoin(int x, int y);
private:
  SDL_Renderer *renderer;
  SDL_Texture *brick;
  SDL_Texture *coin;
  int &scroll;
  std::vector<char> data[Height / 64];
};
