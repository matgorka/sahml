#include <stdio.h>
#include "io.h"
#include "flags.h"
#include "intern_time.h"

static void escseq_universal(int *flags, int ch)
{
  switch (ch) {
    case 'x':
      *flags |= MANUAL_SPACING_FLAG;
      printf("%s", "&nbsp;");
      return;

    case 'D':
      print_date();
      return;

    case 'T':
      print_time();
      return;

    case 'Y':
      print_year();
      return;

    default:
      warn(WARN_UNKNOWNESCAPE);
      return;
  }
}

static void escseq_unencl_str(int *flags, int ch)
{
  switch (ch) {
    case '\'':
      printf("%s", "&#39;");
      return;

    case '\"':
      printf("%s", "&#34;");
      return;

    case '`':
      printf("%s", "&#96;");
      return;

    case '(':
    case ')':
    case ':':
      putchar(ch);
      return;

    case '\\':
      putchar('\\');
      return;

    case 's':
      printf("%s", "&#32;");
      return;

    case 't':
      printf("%s", "&#9;");
      return;

    case 'n':
      printf("%s", "&#10;");
      return;

    default:
      escseq_universal(flags, ch);
      return;
  }
}

void escseq_quoted_str(int *flags, int ch)
{
  switch (ch) {
    case '\'':
      if (*flags & SQUOT_STR_FLAG) {
        printf("%s", "&#39;");
        return;
      }

      warn(WARN_WHYESCAPE);
      break;

    case '\"':
      if (*flags & DQUOT_STR_FLAG) {
        printf("%s", "&#34;");
        return;
      }

      warn(WARN_WHYESCAPE);
      break;

    case '(':
    case ')':
    case ':':
      warn(WARN_WHYESCAPE);
      break;

    case '\\':
      break;

    case 's':
      warn(WARN_WHYESCAPE);
      ch = ' ';
      break;

    case 't':
      ch = '\t';
      break;

    case 'n':
      printf("%s", "&#10;");
      return;

    default:
      escseq_universal(flags, ch);
      return;
  }

  putchar(ch);
}

void escseq_content(int *flags, int ch)
{
  switch (ch) {
    case '\'':
    case '\"':
    case ':':
      warn(WARN_WHYESCAPE);
      break;

    case '(':
    case ')':
    case '\\':
      break;

    case 's':
      *flags |= MANUAL_SPACING_FLAG;
      ch = ' ';
      break;

    case 't':
      *flags |= MANUAL_SPACING_FLAG;
      ch = '\t';
      break;

    case 'n':
      *flags |= MANUAL_SPACING_FLAG;
      ch = '\n';
      break;

    default:
      escseq_universal(flags, ch);
      return;
  }

  putchar(ch);
}

static void escseq(int *flags)
{
  int ch;

  ch = readch();
  specify_msg_ch(ch);

  if (*flags & STR_FLAG) {
    if (*flags & UNENCL_STR_FLAG)
      escseq_unencl_str(flags, ch);
    else
      escseq_quoted_str(flags, ch);

    return;
  }

  escseq_content(flags, ch);
}

int escape(int *flags, int ch)
{
  if (ch == '\\') {
    escseq(flags);
    return 1;
  }

  if (ch == '&') {
    printf("%s", "&amp;");
    return 1;
  }

  if (!(*flags & STR_FLAG) || *flags & UNENCL_STR_FLAG) {
    if (ch == '<')
      printf("%s", "&lt;");
    else if (ch == '>')
      printf("%s", "&gt;");
    else if (ch == '=' && *flags & UNENCL_STR_FLAG)
      printf("%s", "&#61;");
    else
      return 0;

    return 1;
  }

  return 0;
}
