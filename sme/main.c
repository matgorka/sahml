#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "sme_types.h"

extern Config cfg[];
extern int    cfg_siz;

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

Var *property(const char *prop)
{
  int      l = 0,
           c,
           r;
  uint32_t needle;

  needle = lowercase_fnv1a32(prop);
  r      = cfg_siz - 1;
  c      = r / 2;

  while (l <= r) {
    if (needle < cfg[c].hash)
      r = c - 1;
    else if (needle > cfg[c].hash)
      l = c + 1;
    else
      return &cfg[c].var;

    c = (l + r) / 2;
  }

  return NULL;
}

void set_str(const char *prop, const char *val)
{
  Var *var;

  if (!(var = property(prop))) {
    fprintf(stderr, "ERR\n");
    exit(0);
  }

  var->siz   = strlen(val);
  var->v_ptr = malloc(var->siz);
  strcpy(var->v_ptr, val);
}

int main()
{
  /* set default values */
  set_str("title", ".sme");
  printf("%s\n", (char *)property("title")->v_ptr);
  return 0;
}
