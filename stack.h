#ifndef _STACK_H
#define _STACK_H
/* you need to include io.h before this header */

typedef struct DOMStack {
  struct DOMStack *parent;
  char             tag[256];
  int              is_void;
  int              no_attr_left;
} DOMStack;

DOMStack *push            (DOMStack *);
DOMStack *pop             (DOMStack *);
/* pop takes a non-NULL pointer (you need to check it by yourself), otherwise
   it will result in NULL pointer dereference */
int       set_no_attr_left(DOMStack *);
/* set_no_attr_left returns previous value of the flag */
void      set_tag         (DOMStack *, const char *);

#endif
