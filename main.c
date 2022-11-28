#include <stdio.h>
#include <ctype.h>
#include "io.h"
#include "stack.h"
#include "flags.h"

/* import from escape.c */
int escape(int *, int);


int is_tok_delim(int ch)
{
  return isspace(ch) || ch == EOF;
}

void read_unencl_str(int *flags, int ch)
{
  do {
    if (escape(flags, ch))
      continue;
    else if (ch == '=')
      printf("%s", "&#61;");
  } while (!is_tok_delim(ch = readch()));
}

void read_content(int *flags, int ch)
{
  do {
    if (!escape(flags, ch))
      putchar(ch); 
  } while (!is_tok_delim(ch = readch()));
}

void read_tagname(void)
{
}

void end_tag(void)
{
}

int read_token(void)
{
  int ch,
      flags = 0;

  while (isspace(ch = readch()));

  switch (ch) {
    case '(':
      read_tagname();
      break;

    case ')':
      end_tag();
      break;

    default:
      read_content(&flags, ch);
      break;

    case EOF:
      return 0;
  }

  return 1;
}

int main()
{
  int flags;
  int ch;

  set_str_flag(&flags, UNENCL_STR_FLAG);

  while ((ch = readch()) != EOF) {
    if (!escape(&flags, ch))
      putchar(ch);
  }

  /*printf("<!DOCTYPE html>");
  while (read_token());*/

  return 0;
}
