/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#ifndef TBL_H
#define TBL_H

typedef union {
  void           *p;
  char           *s;
  long            n;
  unsigned long   u;
  float           f;
} val_u;


#define valGetP(v)   ((v).p)
#define valGetS(v)   ((v).s)
#define valGetN(v)   ((v).n)
#define valGetU(v)   ((v).u)
#define valGetF(v)   ((v).f)


/* TBL *****************/
/**
* A table slot.
*/ 
typedef struct {
  val_u  key;
  val_u  val;
  char key_type;
  char val_type;
  unsigned char dist;
  unsigned char falgs;
} tbl_slot_t;    


typedef struct {
  long count;
  long size;
  tbl_slot_t slot[1];  /**< start of the slot's array */
} tbl_table_t;

typedef tbl_table_t *tbl_t;

#define tbl_SetXX(tb, k, v, k_t, k_f, v_t, v_f) \
  do {val_u k_v; val_u v_v; \
      k_v.##k_f = k; v_v.##v_f = v; \
      tb = tbl_set(tb, k, k_v, v, v_v); \
  } while (utlZero)

#define tblSetPP(tb,k,v) tbl_SetXX(tb,'P',p,'P',p)
#define tblSetPS(tb,k,v) tbl_SetXX(tb,'P',p,'S',s)
#define tblSetPN(tb,k,v) tbl_SetXX(tb,'P',p,'N',n)
#define tblSetPU(tb,k,v) tbl_SetXX(tb,'P',p,'U',u)
#define tblSetPF(tb,k,v) tbl_SetXX(tb,'P',p,'F',f)

tbl_t tbl_new(long nslots);
#define tblNew(tb) (tb = tbl_new(0))
 
#define tblCount(tb) (tb?tb->count:0)
 
#endif
