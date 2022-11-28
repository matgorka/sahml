#ifndef _SME_TYPES_H
#define _SME_TYPES_H

typedef struct {
  int    type;
  size_t siz;

  union {
    uint64_t  v_uint;
    int64_t   v_sint;
    double    v_dbl;
    void     *v_ptr;
  };
} Var;

typedef struct {
  Var      var;
  uint32_t hash;
} Config;

typedef struct List {
  struct List *next;
  Var         *val;
} List;

/* basic types */
#define TYPE_NUM         (0x0004)
#define TYPE_STR         (0x0008)
#define TYPE_ENUM        (0x0100)
#define TYPE_LIST        (0x0200)

/* basic subtypes */
#define TYPE_UINT        (0x0004)
#define TYPE_UDBL        (0x0005)
#define TYPE_SINT        (0x0006)
#define TYPE_DBL         (0x0007)
#define TYPE_URL         (0x0009)

/* advanced subtypes */
#define TYPE_STRLIST     (0x0208)
#define TYPE_URLLIST     (0x0209)
#define TYPE_REFRESHLIST (0x0210)
#define TYPE_METHODENUM  (0x0101)
#define TYPE_LANGENUM    (0x0102)

#endif
