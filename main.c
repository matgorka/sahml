#include <stdio.h>
#include <ctype.h>
#include "err.h"
#include "stack.h"

typedef enum {
  E_NONE, E_TAG, E_ATTR, E_CONTENT, E_CLOSINGTAG
} Mode;

void end_tag_parsing(DOMStack *s, char *tag, char *p, Mode *mode)
{
  if (p == tag)
    err(ERR_NOTAG);

  *mode = E_NONE;
  *p    = '\0';
  set_tag(s, tag);
}

void end_attr_parsing(DOMStack *s, Mode *mode)
{
  *mode = E_CONTENT;
  set_has_content(s);
}

void put_space(int *needs_space)
{
  if (*needs_space)
    putchar(' ');

  *needs_space = 0;
}

void check_if_wrong_attr(void)
{
  int ch;

  ch = getchar();

  if (ch == ':')
    err(ERR_DBLCOLONS);
  else if (isspace(ch))
    err(ERR_NOATTR);

  ungetc(ch, stdin);
}

int parse_comments(void)
{
  int ch,
      i;

  if ((ch = getchar()) != ':') {
    ungetc(ch, stdin);
    return 0;
  }

  for (i = 0; i < 2; ++i)
    if ((ch = getchar()) != ':')
      err(ERR_COMMENT);

  for (i = 0; i < 3; ++i)
    update_counter(':');

  i = 0;

  while ((ch = getchar()) != EOF) {
    update_counter(ch);

    if (ch == ':')
      ++i;
    else
      i = 0;

    if (i == 3) {
      if ((ch = getchar()) == ')') {
        update_counter(ch);
        return 1;
      }

      i = 0;
    }
  }

  return 1;
}

int main()
{
  DOMStack *s           = NULL;
  Mode      mode        = E_CONTENT;
  char      tag[256],
           *p;
  int       needs_space = 0,
            ch,
            endch;

  while ((ch = getchar()) != EOF) {
    update_counter(ch);

    switch (ch) {
      case '(':
        if (parse_comments())
          break;

        if (mode == E_TAG)
          end_tag_parsing(s, tag, p, &mode);

        set_has_content(s);
        putchar('<');
        mode = E_TAG;
        p    = tag;
        s    = push(s);
        break;

      case ')':
        if (!s)
          err(ERR_EMPTYSTACK);

        if (mode == E_TAG)
          end_tag_parsing(s, tag, p, &mode);

        set_has_content(s);

        if (!s->is_void)
          printf("</%s>", s->tag);

        mode        = E_CLOSINGTAG;
        needs_space = 0;
        s           = pop(s);
        break;

      case ':':
        check_if_wrong_attr();

        if (mode == E_TAG)
          end_tag_parsing(s, tag, p, &mode);
        else if (mode == E_CONTENT || mode == E_CLOSINGTAG)  {
          if (!s)
            err(ERR_WTF);

          err(ERR_ATTR);
        }

        putchar(' ');
        mode = E_ATTR;
        break;

      case '\\':
        if (mode == E_TAG)
          err(ERR_INVALIDCHAR);

        if (mode == E_CLOSINGTAG)
          mode = E_CONTENT;

        if (mode == E_CONTENT)
          put_space(&needs_space);

        putchar(ch = getchar());
        update_counter(ch);
        break;

      case '\'':
      case '\"':
        if (mode == E_TAG)
          err(ERR_INVALIDCHAR);

        if (mode == E_CLOSINGTAG)
          mode = E_CONTENT;

        endch = ch;

        if (mode == E_NONE)
          end_attr_parsing(s, &mode);
        else if (mode == E_ATTR)
          putchar(endch);
        else if (mode == E_CONTENT)
          put_space(&needs_space);

        while ((ch = getchar()) != endch) {
          update_counter(ch);

          if (ch == '\\') {
            putchar(ch = getchar());
            update_counter(ch);
          } else
            putchar(ch);
        }

        update_counter(ch);

        if (mode == E_ATTR)
          putchar(endch);

        break;

      case ' ':
      case '\t':
      case '\n':
        if (mode == E_TAG && p != tag)
          end_tag_parsing(s, tag, p, &mode);
        else if (mode == E_ATTR)
          mode = E_NONE;
        else if (mode == E_CONTENT) {
          /* trim */
          while (isspace(ch = getchar()))
            update_counter(ch);

          ungetc(ch, stdin);

          if (mode == E_CLOSINGTAG)
            mode = E_CONTENT;
          else
            needs_space = 1;
        }

        break;

      default:
        if (mode == E_CLOSINGTAG)
          mode = E_CONTENT;

        if (mode == E_TAG) {
          *p = ch;
          ++p;
        } else if (mode == E_NONE) {
          end_attr_parsing(s, &mode);
          needs_space = 0;
        } else if (mode == E_CONTENT)
          put_space(&needs_space);

        putchar(ch);
    }

    if (mode == E_CONTENT && s && s->is_void)
      err(ERR_VOIDELEMENT);
  }

  if (s)
    err(ERR_UNCLOSED);

  return 0;
}
