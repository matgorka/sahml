#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* import from data_errmsgs.c */
extern const char *warn_msgs[];
extern const char *err_msgs [];

static char        adinfo   [256];      /* additional info for message */
static int         row             = 1;
static int         col             = 0;
static int         err_flag        = 0;

/* ERROR HANDLING */

static void print_msg(const char *t, const char **msgs, int code)
{
  char msg[256];

  /* if there is an additional info needed, we need to take it into account */
  snprintf(msg, 256, msgs[code - 1], adinfo);

  fprintf(
    stderr,
    "%s(%d) at line %d, col %d: %s.\n",
    /* t is a string indicating message type: warning or error */
    t,
    code,
    row,
    col,
    msg
  );
}

void warn(int code)
{
  print_msg("Warning", warn_msgs, code);
}

void err(int code)
{
  print_msg("Error", err_msgs, code);
  err_flag = 1;
}

int has_error(void)
{
  return err_flag;
}

/* ADDITIONAL INFO FUNCTIONS */

void specify_msg_ch(const char ch)
{
  adinfo[0] = ch;
  adinfo[1] = '\0';
}

void specify_msg_str(const char *str)
{
  strncpy(adinfo, str, 256);
}

void specify_msg_n(int n)
{
  itoa(n, adinfo, 10);
}

/* INPUT */

int readch(void)
{
  int ch;

  ch = getchar();

  if (ch == '\n') {
    ++row;
    col = 0;
    return ch;
  }

  ++col;
  return ch;
}
