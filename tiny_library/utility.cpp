//

#include "tiny_picosystem.hpp"

namespace tiny_picosystem {

//
buffer_t* buffer(uint32_t w, uint32_t h, void *data) {
  buffer_t *b = new buffer_t();
  b->w = w;
  b->h = h;
  if (data)
  {
    b->data = (color_t *)data;
    b->alloc = false;
  }
  else
  {
    b->data = new color_t[w * h]{};
    b->alloc = true;
  }
  return b;
}

}