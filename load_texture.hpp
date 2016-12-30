#pragma once
#include <SDL.h>
#include <string>

SDL_Texture *loadTexture(SDL_Renderer *, const std::string &fileName);
