#include <stddef.h>
#include <stdint.h>
#include "sme_types.h"

Config cfg[11] = {
  { { TYPE_STR, 0, { 0 } }, 0x346F3B69 },
  { { TYPE_STR, 0, { 0 } }, 0x4F7ABA56 },
  { { TYPE_LANGENUM, 0, { 0 } }, 0x70EA3B55 },
  { { TYPE_URL, 0, { 0 } }, 0x7C86BCA9 },
  { { TYPE_METHODENUM, 0, { 0 } }, 0x8DEAFAA1 },
  { { TYPE_STR, 0, { 0 } }, 0x9865B509 },
  { { TYPE_URLLIST, 0, { 0 } }, 0x9B4A129B },
  { { TYPE_URLLIST, 0, { 0 } }, 0xAC307ED6 },
  { { TYPE_REFRESHLIST, 0, { 0 } }, 0xD4F26634 },
  { { TYPE_URL, 0, { 0 } }, 0xE64015F0 },
  { { TYPE_STRLIST, 0, { 0 } }, 0xFAF78155 }
};

int cfg_siz = 11;
