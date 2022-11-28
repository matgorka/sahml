#ifndef _ERR_H
#define _ERR_H

#define ERR_MALLOC      (1)
#define ERR_EMPTYSTACK  (2)
#define ERR_VOIDELEMENT (3)
#define ERR_ATTR        (4)
#define ERR_NOTAG       (5)
#define ERR_DBLCOLONS   (6)
#define ERR_COMMENT     (7)
#define ERR_UNCLOSED    (8)
#define ERR_NOATTR      (9)
#define ERR_INVALIDCHAR (10)
#define ERR_WTF         (11)

void err           (int);
void update_counter(int);

#endif
