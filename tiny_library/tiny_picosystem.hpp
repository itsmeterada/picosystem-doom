#pragma once

#include <memory>
#include <cstdint>
#include <climits>
#include <initializer_list>

#include <string>
#include <vector>

#include "pico/stdlib.h"

void tiny_picosystem_init();
void tiny_picosystem_update(uint32_t tick);
void tiny_picosystem_draw(uint32_t tick);

namespace tiny_picosystem {

  #define SCREEN_WIDTH  240
  #define SCREEN_HEIGHT 240

  extern uint32_t _debug;

  typedef uint16_t color_t;

  struct buffer_t {
    int32_t w, h;
    color_t *data;
    bool alloc;

    color_t *p(int32_t x, int32_t y) {
      return data + (x + y * w);
    }

    ~buffer_t() {
      if (alloc) delete data;
    }
  };

  extern uint32_t       _io, _lio;           // io state and last io state
  extern buffer_t      * SCREEN;             // framebuffer
  extern buffer_t      *_dt;                 // drawing target

  // user functions
  color_t     rgb(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xf);
  void        clear(color_t c);
  buffer_t*   buffer(uint32_t w, uint32_t h, void *data);
  uint32_t    time();
  uint32_t    time_us();
  void        draw_line_EFLA(color_t *fb, int x1, int y1, int x2, int y2, color_t color);

  // hardware
  bool        pressed(uint32_t b);
  bool        button(uint32_t b);
  uint32_t    battery();
  void        led(uint8_t r, uint8_t g, uint8_t b);
  void        backlight(uint8_t b);

  // weird and wonderful...
  //void        screenshot();

  // internal methods - do not call directly, will change!
  void       _init_hardware();
  uint32_t   _gpio_get();
  float      _battery_voltage();
  void       _reset_to_dfu();
  void       _wait_vsync();
  void       _flip();
  bool       _is_flipping();

  // input pins
  enum button {
    UP    = 23,
    DOWN  = 20,
    LEFT  = 22,
    RIGHT = 21,
    A     = 18,
    B     = 19,
    X     = 17,
    Y     = 16
  };

}