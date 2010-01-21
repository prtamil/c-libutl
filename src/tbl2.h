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

char *val_Sdup(char *s);
char *val_Sfree(char *s);


/* A table slot.
*/ 
typedef struct {
  val_u  key;
  val_u  val;
  char key_type;
  char val_type;
  unsigned char dist;
  unsigned char flags;
} tbl_slot_t;    

typedef struct {
  long count;
  long size;
  tbl_slot_t slot[1];  /* start of the slot's array */
} tbl_table_t;

typedef tbl_table_t *tbl_t;
 
tbl_t tbl_new(long nslots);
#define tblNew(tb) (tb = tbl_new(2))

#define tblFree(tb) (tb = tbl_free(tb)) 
 
#define tblCount(tb) (tb?tb->count:0)

tbl_t tbl_set(tbl_t tb, char k_type, val_u key, char v_type, val_u val);
 
#define tbl_setXX(tb,tk,k,fk,tv,v,fv) \
   do {val_u ak,av; ak.fk = k; av.fv = v; tb = tbl_set(tb,tk,ak,tv,av);} while (0)
 
#define tblSetNS(tb,k,v) tbl_setXX(tb,'N',k,n,'S',val_Sdup(v),s)
 

 
#endif
