#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

const uint32_t all_tags_hl[147]= {
  0x01C46E5E,
  0x0214FC64,
  0x02ACE84B,
  0x058C4484,
  0x07617589,
  0x08F58208,
  0x0AA7F0B9,
  0x0DDB0669,
  0x10A44713,
  0x114985B2,
  0x11C2662D,
  0x150C5D8B,
  0x17676759,
  0x178EEDF2,
  0x1BCF29D8,
  0x1C14DB4D,
  0x203E6FAA,
  0x23375D91,
  0x25B4AF4F,
  0x25DC1DCA,
  0x274E1290,
  0x281BA64E,
  0x290182C1,
  0x29E2AF71,
  0x2C6A2953,
  0x3116B465,
  0x312FD389,
  0x32694BC3,
  0x3A43C561,
  0x3D454045,
  0x3DDC94D8,
  0x3F2BAB85,
  0x3FCFAE70,
  0x401A63F7,
  0x4031BD46,
  0x4058C747,
  0x41454691,
  0x43B27471,
  0x47455003,
  0x49545DB3,
  0x4A7AB7E6,
  0x4A9C9BDF,
  0x4D1CB705,
  0x4D455975,
  0x4D5463FF,
  0x4E0E3632,
  0x4F2BC4B5,
  0x4F3ACF3F,
  0x539D0E7B,
  0x53C9EB91,
  0x53CACDB9,
  0x5967F3A5,
  0x5D1CD035,
  0x5D3C9BE4,
  0x5F433734,
  0x5F548055,
  0x61A6D509,
  0x633432F6,
  0x651CDCCD,
  0x694AAA0B,
  0x69EAC520,
  0x70954771,
  0x71D07991,
  0x79A94F04,
  0x79B0C60E,
  0x7B049D34,
  0x7B3D6C3C,
  0x7BB0C934,
  0x7FAA0EDE,
  0x81FE4F58,
  0x83172271,
  0x83D3A088,
  0x84E72504,
  0x8512EF1E,
  0x89D15661,
  0x8A25E7BE,
  0x8B3B2DB3,
  0x8B7CD36B,
  0x8C3B2F46,
  0x8D3B30D9,
  0x8E3B326C,
  0x8F3B33FF,
  0x903B3592,
  0x90BEC3C2,
  0x93594AB2,
  0x94C91BFD,
  0x9865B509,
  0x98E98317,
  0x99E4DD3A,
  0x9AB21F4E,
  0x9B0F2144,
  0xA2C4F48C,
  0xA4DB2C36,
  0xAA108E99,
  0xAC307ED6,
  0xB2B63175,
  0xB35135FA,
  0xB48709DF,
  0xB72FCA95,
  0xB8C60CBA,
  0xBFB4741B,
  0xC00C35C4,
  0xC51F5D7A,
  0xC5611FE2,
  0xC77AE4A0,
  0xCA4E1CBF,
  0xCB084E46,
  0xCEF90B6C,
  0xCF574FB3,
  0xCF598E4A,
  0xD00085A1,
  0xD20A71A6,
  0xD630B4BE,
  0xD670686A,
  0xD6AAB9FB,
  0xD775A7D0,
  0xD872E2A5,
  0xDBAA7975,
  0xDBC0DCC7,
  0xDC4E3915,
  0xDCDA01ED,
  0xDFA2EFB1,
  0xE0613999,
  0xE18D189E,
  0xE40C292C,
  0xE488D460,
  0xE562AB48,
  0xE70C2DE5,
  0xE7478EA1,
  0xE7E19B94,
  0xE962B194,
  0xEA0E4AD5,
  0xEA90E208,
  0xEC0C35C4,
  0xEE88998F,
  0xEF131C65,
  0xF00C3C10,
  0xF28DD471,
  0xF40C425C,
  0xF4BA662A,
  0xF4EF80A7,
  0xF50C43EF,
  0xF60C4582,
  0xF69717FD,
  0xF9316CF4,
  0xF9D86F7B,
  0xFCDD0CCC
};

const uint32_t p_next_hl[30]= {
  0x114985B2,
  0x17676759,
  0x178EEDF2,
  0x2C6A2953,
  0x4058C747,
  0x4A7AB7E6,
  0x4A9C9BDF,
  0x4F3ACF3F,
  0x5967F3A5,
  0x5F433734,
  0x61A6D509,
  0x633432F6,
  0x651CDCCD,
  0x8512EF1E,
  0x8B3B2DB3,
  0x8C3B2F46,
  0x8D3B30D9,
  0x8E3B326C,
  0x8F3B33FF,
  0x903B3592,
  0x94C91BFD,
  0x99E4DD3A,
  0xB72FCA95,
  0xDBC0DCC7,
  0xE18D189E,
  0xE488D460,
  0xE562AB48,
  0xEA90E208,
  0xF50C43EF,
  0xFCDD0CCC
};

const uint32_t p_parent_hl[7]= {
  0x53C9EB91,
  0x98E98317,
  0xCEF90B6C,
  0xCF598E4A,
  0xDFA2EFB1,
  0xE0613999,
  0xE40C292C
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

#define N(A) (sizeof(A) / sizeof(uint32_t))

int find(uint32_t *hstack, uint32_t needle, size_t n)
{
  int l  = 0,
      c,
      r;

  r = n - 1;
  c = r / 2;

  while (l <= r) {
    if (needle < hstack[c])
      r = c - 1;
    else if (needle > hstack[c])
      l = c + 1;
    else
      return 1;

    c = (l + r) / 2;
  }

  return 0;
}

int p_end_tag(const char *next, const char *parent)
{
  uint32_t hash;

  hash = lowercase_fnv1a32(next);

  /* sibling rule = if next tag is one of those, then omit (0) */
  if (find(p_next_hl, hash, N(p_next_hl)))
    return 0;

  /* if there is more content, end tag is needed */
  if (*next != '\0')
    return 1;

  hash = lowercase_fnv1a32(parent);

  /* if parent element isn't found in the p_parent_hl list */
  if (!find(p_parent_hl, hash, N(p_parent_hl)))
    return 0;

  /* exception: if parent is an unknown tag then end tag is needed */
  if (find(all_tags_hl, hash, N(all_tags_hl)))
    return 1;

  return 0;
}

#include <string.h>

int li_end_tag(const char *next, ...)
{
  /* 0 if li is next or it's the last element */
  return *next != '\0' && strcmp(next, "li");
}

int dt_end_tag(const char *next, ...)
{
  /* 0 if next tag is dt or dd */
  return strcmp(next, "dd") && strcmp(next, "dt");
}

int dd_end_tag(const char *next, ...)
{
  /* 0 if last element or same as dt */
  return *next != '\0' && dt_end_tag(next);
}

/* same rule for rt and rp */
int rt_rp_end_tag(const char *next, ...)
{
  /* 0 if last element, or rt/rp is next */
	return *next != '\0' && strcmp(next, "rt") && strcmp(next, "rp");
}

int caption_end_tag(const char *next, ...)
{
  /* from HTML spec:
   * A caption element's end tag can be omitted if the caption element
   * is not immediately followed by ASCII whitespace or a comment.
   * TO DO!
   */

  return 1;
}

int colgroup_end_tag(const char *next, ...)
{
  return 1;
}

int tbody_end_tag(const char *next, ...)
{
  return 1;
}

int thead_end_tag(const char *next, ...)
{
  return strcmp(next, "tbody") && strcmp(next, "tfoot");
}

int tfoot_end_tag(const char *next, ...)
{
  return *next != '\0';
}

int tr_end_tag(const char *next, ...)
{
  return *next != '\0' && strcmp(next, "tr");
}

int td_th_end_tag(const char *next, ...)
{
  return *next != '\0' && strcmp(next, "td") && strcmp(next, "th");
}

int optgroup_end_tag(const char *next, ...)
{
  return *next != '\0' && strcmp(next, "optgroup");
}

int option_end_tag(const char *next, ...)
{
  return *next != '\0' && strcmp(next, "optgroup") && strcmp(next, "option");
}

int html_head_body_end_tag()
{
  return 0;
}



#include <stdio.h>

void test2
(
  int        (*func)(const char *, const char *),
  const char  *parent,
  const char  *next
)
{
  printf(
    "%s > p + %s: %s\n",
    parent,
    next, 
    func(next, parent) ? "needed" : "omit"
  );
}

void test
(
  int        (*func)(const char *, ...),
  const char  *tag,
  const char  *next
)
{
  printf(
    "%s + %s: %s\n",
    tag,
    next, 
    func(next) ? "needed" : "omit"
  );
}

int main()
{
  test(rt_end_tag, "rt", "div");
  test(rt_end_tag, "rt", "rt");
  test(rt_end_tag, "rt", "rp");
  test(rt_end_tag, "rt", "");
  return 0;
}
