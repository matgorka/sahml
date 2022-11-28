#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static uint32_t fnv1a32(const char *str)
{
  uint32_t h;

  h = 0x811C9DC5;

  for (; *str; ++str) {
    h ^= *str;
    h *= 0x01000193;
  }

  return h;
}

int comparator(const void *a, const void *b)
{
  return *((uint32_t *)a) < *((uint32_t *)b) ? -1 : 1;
}

int main()
{
  uint32_t hash_list[262144],
           i,
           n;
  char     id[64];

  scanf("%63s", id);
  printf("const uint32_t %s", id);

  for (i = 0; i < 262144 && scanf("%63s", id) > 0; ++i)
    hash_list[i] = fnv1a32(id);

  n = i;
  printf("[%u]", n);

  if (n == 0) {
    puts(";");
    return 0;
  }

  qsort(hash_list, n, sizeof(uint32_t), comparator);
  printf("= {\n  0x%08X", hash_list[0]);

  for (i = 1; i < n; ++i)
    printf(",\n  0x%08X", hash_list[i]);

  puts("\n};");
  return 0;
}
