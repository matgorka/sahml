#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

typedef struct {
  char      type[64];
  uint32_t  hash;
} Property;

uint32_t lowercase_fnv1a32(const char *str)
{
  uint32_t h;

  h = 0x811C9DC5;

  for (; *str; ++str) {
    h ^= tolower(*str);
    h *= 0x01000193;
  }

  return h;
}

int comparator(const void *p1, const void *p2)
{
  uint32_t a,
           b;

  a = ((Property *) p1)->hash;
  b = ((Property *) p2)->hash;

  return a < b ? -1 : 1;
}

void print_prop(FILE *out, Property prop)
{
  fprintf(out, "\n  { { %s, 0, { 0 } }, 0x%08X }", prop.type, prop.hash);
}

int main()
{
  FILE     *in,
           *out;
  Property  prop[15000];
  uint32_t  i,
            n;
  char      tok[64];

  if (
    !(in  = fopen("data_sme.txt", "r")) ||
    !(out = fopen("data_sme.c", "w"))
  ) {
    perror("fopen");
    exit(1);
  }

  for (i = 0; i < 15000; ++i) {
    if (fscanf(in, "%63s", tok) < 1)
      break;

    prop[i].hash = lowercase_fnv1a32(tok);

    if (fscanf(in, "%63s", tok) < 1) {
      fprintf(stderr, "No type specified");
      exit(1);
    }

    strcpy(prop[i].type, tok);
  }

  n = i;

  fprintf(out,
    "#include <stddef.h>\n"
    "#include <stdint.h>\n"
    "#include \"sme_types.h\"\n\n"
    "Config cfg[%u]",
    n
  );

  if (n == 0) {
    fprintf(out, ";\n\nint cfg_siz = 0;\n");
    return 0;
  }

  qsort(prop, n, sizeof(Property), comparator);

  fprintf(out, " = {");
  print_prop(out, prop[0]);

  for (i = 1; i < n; ++i) {
    fprintf(out, ",");
    print_prop(out, prop[i]);
  }

  fprintf(out, "\n};\n\nint cfg_siz = %d;\n", n);
  return 0;
}
