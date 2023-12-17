#include <cassert>

#include "tiny_picosystem.hpp"

namespace tiny_picosystem {

extern buffer_t *dt;

color_t rgb(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  // color_t will contain pixel data in the format aaaarrrrggggbbbb
  return (r & 0xf) | ((a & 0xf) << 4) | ((b & 0xf) << 8) | ((g & 0xf) << 12);
}

// clear screen
void clear(color_t c) {
  color_t *dst = _dt->data;
  for (int32_t y = 0; y < SCREEN_HEIGHT; y++) {
    for (int32_t x = 0; x < SCREEN_WIDTH; x++) {
      *dst++ = c;
    }
  }
}


#define write_pixel(x, y) dst[x + y * SCREEN_WIDTH] = color; 

void draw_line_EFLA(color_t *fb, int x1, int y1, int x2, int y2, color_t color)
{
  bool yLonger = false;
  int shortLen = y2 - y1;
  int longLen = x2 - x1;
  int decInc;
  color_t *dst;

  if (fb == nullptr) {
    dst = _dt->data;
  } else {
    dst = fb;
  }

#if 1
  if ((shortLen ^ (shortLen >> 31)) - (shortLen >> 31) > (longLen ^ (longLen >> 31)) - (longLen >> 31)) {
    shortLen ^= longLen;
    longLen ^= shortLen;
    shortLen ^= longLen;
    yLonger = true;
  }
#else
  if (abs(shortLen) > abs(longLen)) {
    int swap = shortLen;
    shortLen = longLen;
    longLen = swap;
    yLonger = true;
  }
#endif
  if (longLen == 0) decInc = 0;
  else decInc = (shortLen << 16) / longLen;

  if (yLonger) {
    if (longLen > 0) {
      longLen += y1;
      for (int j = 0x8000 + (x1 << 16); y1 <= longLen; ++y1) {
        //fb[(j >> 16) + THUMBY_SCREEN_WIDTH * y1] = color;
        write_pixel((j >> 16), y1);
        j+= decInc;
      }
      return;
    }
    longLen += y1;
    for (int j = 0x8000 + (x1 << 16); y1 >= longLen; --y1) {
      //fb[(j >> 16) + THUMBY_SCREEN_WIDTH * y1] = color;
      write_pixel((j >> 16), y1);
      j -= decInc;
    }
    return;
  }

  if (longLen > 0) {
    longLen += x1;
    for (int j = 0x8000 + (y1 << 16); x1 <= longLen; ++x1) {
      //fb[x1 + (j >> 16) * THUMBY_SCREEN_WIDTH] = color;
      write_pixel(x1, (j >> 16));
      j += decInc;
    }
    return;
  }
  longLen += x1;
  for (int j = 0x8000 + (y1 << 16); x1 >= longLen; --x1) {
    // fb[x1 + (j >> 16) * THUMBY_SCREEN_WIDTH] = color;
    write_pixel(x1, (j >> 16));
    j -= decInc;
  }
}

} // namespace tiny_picosystem
