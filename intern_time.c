#include <stdio.h>
#include <string.h>
#include <time.h>

static char date_fmt[256] = "%Y-%m-%d";
static char time_fmt[256] = "%H:%M:%S";
static char year_fmt[256] = "%Y";

static struct tm *get_time(void)
{
  static time_t     t        = 0;
  static struct tm *tm_info;

  /* ensuring a global timestamp for a document */
  if (t == 0) {
    t       = time(NULL);
    tm_info = localtime(&t);
  }

  return tm_info;
}

/* print formated date/time */
static void print_fmt_dt(const char *fmt)
{
  char       str[256];
  struct tm *tm_info;

  tm_info = get_time();
  strftime(str, 256, fmt, tm_info);
  printf("%s", str);
}

void print_date(void)
{
  print_fmt_dt(date_fmt);
}

void print_time(void)
{
  print_fmt_dt(time_fmt);
}

void print_year(void)
{
  print_fmt_dt(year_fmt);
}

void set_date_fmt(const char *fmt)
{
  strncpy(date_fmt, fmt, 256);
}

void set_time_fmt(const char *fmt)
{
  strncpy(time_fmt, fmt, 256);
}

void set_year_fmt(const char *fmt)
{
  strncpy(year_fmt, fmt, 256);
}
