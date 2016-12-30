#include "cat.hpp"
#include "consts.hpp"
#include "level.hpp"
#include "load_texture.hpp"
#include "sdl_check.hpp"
#include <SDL.h>

int main(int argc, char **argv)
{
  auto res = SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CHECK(res == 0, "SDL_Init");
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_BORDERLESS, &window, &renderer);
  SDL_CHECK(window, "SDL_CreateWindowAndRenderer");
  SDL_CHECK(renderer, "SDL_CreateWindowAndRenderer");
  SDL_SetWindowPosition(window, 65, 126);
  Cat cat(renderer);
  Level level(renderer, cat.x);
  unsigned keys = 0;
  auto currentTick = SDL_GetTicks();
  for (auto done = false; !done;)
  {
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
      case SDL_KEYDOWN:
        {
          switch (e.key.keysym.sym)
          {
          case SDLK_LEFT:
            keys |= KeyLeft;
            break;
          case SDLK_RIGHT:
            keys |= KeyRight;
            break;
          case SDLK_UP:
            keys |= KeyJump;
            break;
          }
        }
        break;
      case SDL_KEYUP:
        {
          switch (e.key.keysym.sym)
          {
          case SDLK_LEFT:
            keys &= ~KeyLeft;
            break;
          case SDLK_RIGHT:
            keys &= ~KeyRight;
            break;
          case SDLK_UP:
            keys &= ~KeyJump;
            break;
          }
        }
        break;
      case SDL_QUIT:
        done = true;
        break;
      }
    }
    auto oldTick = currentTick;
    currentTick = SDL_GetTicks();
    for (;oldTick < currentTick; ++oldTick)
    {
      cat.tick(keys);
      cat.inAir = level.isInAir(cat.x, cat.y);
      level.checkCoin(cat.x, cat.y);
    }
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
    SDL_RenderClear(renderer);
    level.draw();
    cat.draw();
    SDL_RenderPresent(renderer);
  }
  
  SDL_Quit();
}
