#include "flags.h"

void set_str_flag(int *flags, int flag)
{
  *flags |= STR_FLAG | flag;
}
