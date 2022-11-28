#include <stdlib.h>
#include <stdio.h>
#include "err.h"

static int row = 1;
static int col = 0;

void err(int errcode)
{
  const char *errmsgs[] = {
    "Malloc failed.",
    "User tries to operate on an empty stack "
    "(too many closing paranetheses).",
    "Empty tags cannot have any content in them.",
    "Wrong order: after attaching content to an element"
    " you can't specify its attributes.",
    "No tag specified.",
    "Double colons.",
    "Invalid comment, proper syntax: \"(::: comment :::)\".",
    "Tag(s) left unclosed.",
    "No attribute specified.",
    "Invalid character in tag's name.",
    "Attribute is applied to a non-existent tag."
  };

  fprintf(
    stderr,
    "Error(%d) at line %d, col %d: %s\n",
    errcode,
    row,
    col,
    errmsgs[errcode - 1]
  );

  exit(1);
}

void update_counter(int ch)
{
  if (ch == '\n') {
    ++row;
    col = 0;
  } else
    ++col;
}
