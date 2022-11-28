#include <stdint.h>
#include <ctype.h>

static const uint32_t hashlist[19] = {
  0x0DDB0669,
  0x1BCF29D8,
  0x25DC1DCA,
  0x281BA64E,
  0x3116B465,
  0x3DDC94D8,
  0x4E0E3632,
  0x4F2BC4B5,
  0x4F3ACF3F,
  0x71D07991,
  0x7B3D6C3C,
  0x81FE4F58,
  0x84E72504,
  0x93594AB2,
  0x9B0F2144,
  0xA4DB2C36,
  0xB2B63175,
  0xF28DD471,
  0xF9D86F7B
};

static uint32_t lowercase_fnv1a32(const char *str)
{
  uint32_t h;

  h = 0x811C9DC5;

  for (; *str; ++str) {
    h ^= tolower(*str);
    h *= 0x01000193;
  }

  return h;
}

int is_void_element(const char *tag)
{
  uint32_t h;
  int      l  = 0,
           c  = 9,
           r  = 18;

  if (tag[0] == '!')
    return 1;

  h = lowercase_fnv1a32(tag);

  while (l <= r) {
    if (h < hashlist[c])
      r = c - 1;
    else if (h > hashlist[c])
      l = c + 1;
    else
      return 1;

    c = (l + r) / 2;
  }

  return 0;
}
