#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "err.h"
#include "stack.h"

/* import from voidelements.c */
int is_void_element(const char *);

DOMStack *push(DOMStack *old)
{
  DOMStack *new;

  if (old && old->is_void)
    err(ERR_VOIDELEMENT);

  if ((new = malloc(sizeof(DOMStack))) == NULL)
    err(ERR_MALLOC);

  new->has_content = 0;
  new->prev        = old;
  return new;
}

DOMStack *pop(DOMStack *s)
{
  DOMStack *r;
  r = s->prev;
  free(s);
  return r;
}

int set_has_content(DOMStack *s)
{
  if (!s)
    return 0;

  if (!s->has_content) {
    s->has_content = 1;
    putchar('>');
    return 0;
  }

  return 1;
}

void set_tag(DOMStack *s, const char *tag)
{
  strcpy(s->tag, tag);
  s->is_void = is_void_element(tag);
}
