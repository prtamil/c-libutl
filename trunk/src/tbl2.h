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
  unsigned char max_dist;
  unsigned char flags;
  unsigned char pad1;
  unsigned char pad2;
  tbl_slot_t slot[1];  /* start of the slots array */
} tbl_table_t;

typedef tbl_table_t *tbl_t;
 
tbl_t tbl_new(long nslots);
#define tblNew(tb) (tb = tbl_new(2))

#define tblFree(tb) (tb = tbl_free(tb)) 
 
#define tblCount(tb) (tb?tb->count:0)

tbl_t tbl_set(tbl_t tb, char k_type, val_u key, char v_type, val_u val);
 
#define tbl_setXX(tb,tk,k,fk,tv,v,fv) \
   do {val_u ak,av; ak.fk = k; av.fv = v; tb = tbl_set(tb,tk,ak,tv,av);} while (0)
 
#define tblSetPT(tb,k,v) tbl_setXX(tb,'P',k,p,'T',v,p)
#define tblSetPP(tb,k,v) tbl_setXX(tb,'P',k,p,'P',v,p)
#define tblSetPS(tb,k,v) tbl_setXX(tb,'P',k,p,'S',val_Sdup(v),s)
#define tblSetPN(tb,k,v) tbl_setXX(tb,'P',k,p,'N',v,n)
#define tblSetPU(tb,k,v) tbl_setXX(tb,'P',k,p,'U',v,u)
#define tblSetPF(tb,k,v) tbl_setXX(tb,'P',k,p,'F',v,f)

#define tblSetNT(tb,k,v) tbl_setXX(tb,'N',k,n,'T',v,p)
#define tblSetNP(tb,k,v) tbl_setXX(tb,'N',k,n,'P',v,p)
#define tblSetNS(tb,k,v) tbl_setXX(tb,'N',k,n,'S',val_Sdup(v),s)
#define tblSetNN(tb,k,v) tbl_setXX(tb,'N',k,n,'N',v,n)
#define tblSetNU(tb,k,v) tbl_setXX(tb,'N',k,n,'U',v,u)
#define tblSetNF(tb,k,v) tbl_setXX(tb,'N',k,n,'F',v,f)


val_u tbl_getN(tbl_t tb, long key, long def);

#define tblGetNN(tb,k,d) valGetN(tbl_getN(tb,k,d))
#define tblGetNS(tb,k,d) valGetS(tbl_getN(tb,k,d))

#define tbl_delX(tb,tk,k,fk) do {val_u key; key.fk = k; tb = tbl_del(tb,tk,key);} while (0)

#define tblDelP(tb,k) tbl_delX(tb,'P',k,p)
#define tblDelS(tb,k) tbl_delX(tb,'S',k,s)
#define tblDelN(tb,k) tbl_delX(tb,'N',k,n)
#define tblDelU(tb,k) tbl_delX(tb,'U',k,u)
#define tblDelF(tb,k) tbl_delX(tb,'F',k,f)

#endif
