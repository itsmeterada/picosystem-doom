#include "tiny_picosystem.hpp"

using namespace tiny_picosystem;


// initialise the world
void tiny_picosystem_init() 
{

}

// process user input and update the world state
void tiny_picosystem_update(uint32_t tick) {
  if(pressed(A))
    tiny_picosystem_init();
}

// draw the world
void tiny_picosystem_draw(uint32_t tick) 
{
  static uint8_t rcol = 0;
  static uint32_t x = 0;
  static uint32_t y = 0;
  static uint32_t v = 1;
  int i, j;
  color_t col = rgb(15, 15, 15);

  clear(0);
#if 1
  draw_line_EFLA(nullptr, x, 0, SCREEN_WIDTH - x - 1, SCREEN_HEIGHT - 1, col);
  x += v;
  if ((x >= SCREEN_WIDTH - 1) || x <= 0) {
    v = -v;
  }
#else
  for (i = 0; i < SCREEN_WIDTH; i++) {
    draw_line_EFLA(nullptr, i, 0, SCREEN_WIDTH - i - 1, SCREEN_HEIGHT - 1, col);
    rcol++;
    if (rcol > 15) rcol = 0;
  }
  for (j = 0; j < SCREEN_HEIGHT; j++) {
    //draw_line_EFLA(nullptr, 0, j, SCREEN_WIDTH - 1, SCREEN_HEIGHT -j - 1, col);
    rcol++;
    if (rcol > 15) rcol = 0;
  }
#endif
}
