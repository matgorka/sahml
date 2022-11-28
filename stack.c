#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "io.h"
#include "stack.h"

/* import from voidelements.c */
int is_void_element(const char *);

DOMStack *push(DOMStack *old)
{
  DOMStack *new;

  if (old && old->is_void)
    err(ERR_VOIDELEMENT);

  if ((new = malloc(sizeof(DOMStack))) == NULL) {
    specify_msg_str(strerror(errno));
    err(ERR_MALLOC);
  }

  new->no_attr_left = 0;
  new->parent       = old;
  return new;
}

DOMStack *pop(DOMStack *s)
{
  DOMStack *r;
  r = s->parent;
  free(s);
  return r;
}

int set_no_attr_left(DOMStack *s)
{
  if (!s)
    return 0;

  if (s->no_attr_left)
    return 1;

  s->no_attr_left = 1;
  return 0;
}

void set_tag(DOMStack *s, const char *tag)
{
  strcpy(s->tag, tag);
  s->is_void = is_void_element(tag);
}
