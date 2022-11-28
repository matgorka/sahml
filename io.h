#ifndef _IO_H
#define _IO_H
#include "data_errmsgs.h"

/* ERROR HANDLING */
void warn           (int);
void err            (int);
void specify_msg_ch (const char);
void specify_msg_str(const char *);
void specify_msg_n  (int);
int  has_error      (void);

/* INPUT */
int  readch         (void);

#endif
