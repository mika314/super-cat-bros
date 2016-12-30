#include "level.hpp"
#include "load_texture.hpp"
#include <algorithm>

void addLine(std::vector<char> &v, const char *l)
{
  v.insert(v.end(), l, l + strlen(l));
}

Level::Level(SDL_Renderer *renderer, int &scroll):
  renderer(renderer),
  brick(loadTexture(renderer, "brick.bmp")),
  coin(loadTexture(renderer, "coin.bmp")),
  scroll(scroll)
{
  auto i = 0;
  addLine(data[i++], "                                                                                             ");
  addLine(data[i++], "                                                                                             ");
  addLine(data[i++], "                                                                                             ");
  addLine(data[i++], "                       $$                                                                    ");
  addLine(data[i++], "                       $$                                                                    ");
  addLine(data[i++], "                     ======                                                                  ");
  addLine(data[i++], "                  ===  $ $ =                    $$$$$              $$$$$$                    ");
  addLine(data[i++], "               ===     $ $ =          ===       $$$$$              $$$$$$                    ");
  addLine(data[i++], "            ===     ========       ===       $                           ===                 ");
  addLine(data[i++], "         $         =       ========          $           ==            =       $             ");
  addLine(data[i++], "=============================================================================================");
}

Level::~Level()
{
}

void Level::draw()
{
  auto mnIter = std::min_element(std::begin(data), std::end(data), [](const std::vector<char> &x, const std::vector<char> &y)
                             {
                               return x.size() < y.size();
                             });
  auto mn = mnIter->size();
  for (int y = 0; y < Height / 64; ++y)
    for (unsigned x = 0; x < mn; ++x)
    {
      SDL_Rect dest;
      dest.x = x * 64 - scroll + Width / 2;
      dest.y = y * 64;
      dest.w = 64;
      dest.h = 64;
      switch (data[y][x])
      {
      case '=':
        SDL_RenderCopy(renderer, brick, nullptr, &dest);
        break;
      case '$':
        SDL_RenderCopy(renderer, coin, nullptr, &dest);
        break;
      }
    }
}

bool Level::isInAir(int x, int y)
{
  auto x1 = x / 64;
  auto x2 = (x + 63) / 64;
  auto yy = (y + 128) / 64;
  return data[yy][x1] != '=' && data[yy][x2] != '=';
}

void Level::checkCoin(int x, int y)
{
  auto xx = (x + 32) / 64;
  auto y1 = (y + 32) / 64;
  auto y2 = (y + 32 + 64) / 64;
  if (data[y1][xx] == '$')
    data[y1][xx] = ' ';
  if (data[y2][xx] == '$')
    data[y2][xx] = ' ';
}
