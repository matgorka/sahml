#ifndef _STACK_H
#define _STACK_H
/* you need to include debug.h before this header */

typedef struct DOMStack {
  struct DOMStack *prev;
  char             tag[256];
  int              is_void;
  int              has_content;
} DOMStack;

DOMStack *push           (DOMStack *);
/* pop takes a non-NULL pointer (you need to check it by yourself), otherwise
   it will result in NULL pointer dereference */
DOMStack *pop            (DOMStack *);
/* set_has_content outputs '>' character if flag changes from 0 to 1,
   returns previous value of the flag */
int       set_has_content(DOMStack *);
void      set_tag        (DOMStack *, const char *);

#endif
