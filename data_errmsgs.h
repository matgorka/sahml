#ifndef _DATA_ERRMSGS_H
#define _DATA_ERRMSGS_H

/* LIST OF ERRORS AND WARNINGS
 * if displaying it needs additional info it is noted in a comment
 */

#define ERR_MALLOC         (1) /* + str (strerror) */
#define ERR_EMPTYSTACK     (2)
#define ERR_VOIDELEMENT    (3)

#define WARN_WHYESCAPE     (1) /* + ch */
#define WARN_UNKNOWNESCAPE (2) /* + ch */

/* above macros are to be used with "warn" and "err" functions;
 * to provide additional info, use "specify_msg_*" functions;
 * this header is included by io.h
 */

#endif
