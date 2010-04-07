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

#define valGetM(v)   ((v).p)
#define valGetT(v)   ((tbl_t)((v).p))
#define valGetV(v)   ((vec_t)((v).p))
#define valGetR(v)   (((v).p))
#define valGetP(v)   ((v).p)
#define valGetS(v)   ((v).s)
#define valGetN(v)   ((v).n)
#define valGetU(v)   ((v).u)
#define valGetF(v)   ((v).f)

#define valM(x) valP(x)
#define valT(x) valP(x)
#define valV(x) valP(x)
#define valR(x) valP(x)
val_u   valP(void *val);        
val_u   valS(char *val);         
val_u   valN(long val);
val_u   valU(unsigned long val);
val_u   valF(float val);


char *val_Sdup(char *s);
char *val_Sfree(char *s);

/********************************************/

/* A table slot.
*/ 

typedef struct {
  val_u  val;
  val_u  key;
  char   info[sizeof(val_u)]; /* to ensure alignment */
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

tbl_t tbl_free(tbl_t tb);
#define tblFree(tb) (tb = tbl_free(tb)) 
 
#define tblCount(tb) (tb?(tb)->count:0)

tbl_t tbl_set(tbl_t tb, char k_type, val_u key, char v_type, val_u val);

#define tblSetMM(tb,k,v) (tb = tbl_set(tb,'M',valM(k),'M',valM(v)))
#define tblSetMT(tb,k,v) (tb = tbl_set(tb,'M',valM(k),'T',valT(v)))
#define tblSetMV(tb,k,v) (tb = tbl_set(tb,'M',valM(k),'V',valV(v)))
#define tblSetMR(tb,k,v) (tb = tbl_set(tb,'M',valM(k),'R',valR(v)))
#define tblSetMP(tb,k,v) (tb = tbl_set(tb,'M',valM(k),'P',valP(v)))
#define tblSetMS(tb,k,v) (tb = tbl_set(tb,'M',valM(k),'S',valS(val_Sdup(v))))
#define tblSetMH(tb,k,v) (tb = tbl_set(tb,'M',valM(k),'S',valS(v)))
#define tblSetMN(tb,k,v) (tb = tbl_set(tb,'M',valM(k),'N',valN(v)))
#define tblSetMU(tb,k,v) (tb = tbl_set(tb,'M',valM(k),'U',valU(v)))
#define tblSetMF(tb,k,v) (tb = tbl_set(tb,'M',valM(k),'F',valF(v)))

#define tblSetTM(tb,k,v) (tb = tbl_set(tb,'T',valT(k),'M',valM(v)))
#define tblSetTT(tb,k,v) (tb = tbl_set(tb,'T',valT(k),'T',valT(v)))
#define tblSetTV(tb,k,v) (tb = tbl_set(tb,'T',valT(k),'V',valV(v)))
#define tblSetTR(tb,k,v) (tb = tbl_set(tb,'T',valT(k),'R',valR(v)))
#define tblSetTP(tb,k,v) (tb = tbl_set(tb,'T',valT(k),'P',valP(v)))
#define tblSetTS(tb,k,v) (tb = tbl_set(tb,'T',valT(k),'S',valS(val_Sdup(v))))
#define tblSetTH(tb,k,v) (tb = tbl_set(tb,'T',valT(k),'S',valS(v)))
#define tblSetTN(tb,k,v) (tb = tbl_set(tb,'T',valT(k),'N',valN(v)))
#define tblSetTU(tb,k,v) (tb = tbl_set(tb,'T',valT(k),'U',valU(v)))
#define tblSetTF(tb,k,v) (tb = tbl_set(tb,'T',valT(k),'F',valF(v)))

#define tblSetVM(tb,k,v) (tb = tbl_set(tb,'V',valV(k),'M',valM(v)))
#define tblSetVT(tb,k,v) (tb = tbl_set(tb,'V',valV(k),'T',valT(v)))
#define tblSetVV(tb,k,v) (tb = tbl_set(tb,'V',valV(k),'V',valV(v)))
#define tblSetVR(tb,k,v) (tb = tbl_set(tb,'V',valV(k),'R',valR(v)))
#define tblSetVP(tb,k,v) (tb = tbl_set(tb,'V',valV(k),'P',valP(v)))
#define tblSetVS(tb,k,v) (tb = tbl_set(tb,'V',valV(k),'S',valS(val_Sdup(v))))
#define tblSetVH(tb,k,v) (tb = tbl_set(tb,'V',valV(k),'S',valS(v)))
#define tblSetVN(tb,k,v) (tb = tbl_set(tb,'V',valV(k),'N',valN(v)))
#define tblSetVU(tb,k,v) (tb = tbl_set(tb,'V',valV(k),'U',valU(v)))
#define tblSetVF(tb,k,v) (tb = tbl_set(tb,'V',valV(k),'F',valF(v)))

#define tblSetRM(tb,k,v) (tb = tbl_set(tb,'R',valR(k),'M',valM(v)))
#define tblSetRT(tb,k,v) (tb = tbl_set(tb,'R',valR(k),'T',valT(v)))
#define tblSetRV(tb,k,v) (tb = tbl_set(tb,'R',valR(k),'V',valV(v)))
#define tblSetRR(tb,k,v) (tb = tbl_set(tb,'R',valR(k),'R',valR(v)))
#define tblSetRP(tb,k,v) (tb = tbl_set(tb,'R',valR(k),'P',valP(v)))
#define tblSetRS(tb,k,v) (tb = tbl_set(tb,'R',valR(k),'S',valS(val_Sdup(v))))
#define tblSetRH(tb,k,v) (tb = tbl_set(tb,'R',valR(k),'S',valS(v)))
#define tblSetRN(tb,k,v) (tb = tbl_set(tb,'R',valR(k),'N',valN(v)))
#define tblSetRU(tb,k,v) (tb = tbl_set(tb,'R',valR(k),'U',valU(v)))
#define tblSetRF(tb,k,v) (tb = tbl_set(tb,'R',valR(k),'F',valF(v)))

#define tblSetPM(tb,k,v) (tb = tbl_set(tb,'P',valP(k),'M',valM(v)))
#define tblSetPT(tb,k,v) (tb = tbl_set(tb,'P',valP(k),'T',valT(v)))
#define tblSetPV(tb,k,v) (tb = tbl_set(tb,'P',valP(k),'V',valV(v)))
#define tblSetPR(tb,k,v) (tb = tbl_set(tb,'P',valP(k),'R',valR(v)))
#define tblSetPP(tb,k,v) (tb = tbl_set(tb,'P',valP(k),'P',valP(v)))
#define tblSetPS(tb,k,v) (tb = tbl_set(tb,'P',valP(k),'S',valS(val_Sdup(v))))
#define tblSetPH(tb,k,v) (tb = tbl_set(tb,'P',valP(k),'S',valS(v)))
#define tblSetPN(tb,k,v) (tb = tbl_set(tb,'P',valP(k),'N',valN(v)))
#define tblSetPU(tb,k,v) (tb = tbl_set(tb,'P',valP(k),'U',valU(v)))
#define tblSetPF(tb,k,v) (tb = tbl_set(tb,'P',valP(k),'F',valF(v)))

#define tblSetSM(tb,k,v) (tb = tbl_set(tb,'S',valS(val_Sdup(k)),'M',valM(v)))
#define tblSetST(tb,k,v) (tb = tbl_set(tb,'S',valS(val_Sdup(k)),'T',valT(v)))
#define tblSetSV(tb,k,v) (tb = tbl_set(tb,'S',valS(val_Sdup(k)),'V',valV(v)))
#define tblSetSR(tb,k,v) (tb = tbl_set(tb,'S',valS(val_Sdup(k)),'R',valR(v)))
#define tblSetSP(tb,k,v) (tb = tbl_set(tb,'S',valS(val_Sdup(k)),'P',valP(v)))
#define tblSetSS(tb,k,v) (tb = tbl_set(tb,'S',valS(val_Sdup(k)),'S',valS(val_Sdup(v))))
#define tblSetSH(tb,k,v) (tb = tbl_set(tb,'S',valS(val_Sdup(k)),'S',valS(v)))
#define tblSetSN(tb,k,v) (tb = tbl_set(tb,'S',valS(val_Sdup(k)),'N',valN(v)))
#define tblSetSU(tb,k,v) (tb = tbl_set(tb,'S',valS(val_Sdup(k)),'U',valU(v)))
#define tblSetSF(tb,k,v) (tb = tbl_set(tb,'S',valS(val_Sdup(k)),'F',valF(v)))

#define tblSetHM(tb,k,v) (tb = tbl_set(tb,'S',valS(k),'M',valM(v)))
#define tblSetHT(tb,k,v) (tb = tbl_set(tb,'S',valS(k),'T',valT(v)))
#define tblSetHV(tb,k,v) (tb = tbl_set(tb,'S',valS(k),'V',valV(v)))
#define tblSetHR(tb,k,v) (tb = tbl_set(tb,'S',valS(k),'R',valR(v)))
#define tblSetHP(tb,k,v) (tb = tbl_set(tb,'S',valS(k),'P',valP(v)))
#define tblSetHS(tb,k,v) (tb = tbl_set(tb,'S',valS(k),'S',valS(v)))
#define tblSetHH(tb,k,v) (tb = tbl_set(tb,'S',valS(k),'S',valS(v)))
#define tblSetHN(tb,k,v) (tb = tbl_set(tb,'S',valS(k),'N',valN(v)))
#define tblSetHU(tb,k,v) (tb = tbl_set(tb,'S',valS(k),'U',valU(v)))
#define tblSetHF(tb,k,v) (tb = tbl_set(tb,'S',valS(k),'F',valF(v)))

#define tblSetNM(tb,k,v) (tb = tbl_set(tb,'N',valN(k),'M',valM(v)))
#define tblSetNT(tb,k,v) (tb = tbl_set(tb,'N',valN(k),'T',valT(v)))
#define tblSetNV(tb,k,v) (tb = tbl_set(tb,'N',valN(k),'V',valV(v)))
#define tblSetNR(tb,k,v) (tb = tbl_set(tb,'N',valN(k),'R',valR(v)))
#define tblSetNP(tb,k,v) (tb = tbl_set(tb,'N',valN(k),'P',valP(v)))
#define tblSetNS(tb,k,v) (tb = tbl_set(tb,'N',valN(k),'S',valS(val_Sdup(v))))
#define tblSetNH(tb,k,v) (tb = tbl_set(tb,'N',valN(k),'S',valS(v)))
#define tblSetNN(tb,k,v) (tb = tbl_set(tb,'N',valN(k),'N',valN(v)))
#define tblSetNU(tb,k,v) (tb = tbl_set(tb,'N',valN(k),'U',valU(v)))
#define tblSetNF(tb,k,v) (tb = tbl_set(tb,'N',valN(k),'F',valF(v)))

#define tblSetUM(tb,k,v) (tb = tbl_set(tb,'U',valU(k),'M',valM(v)))
#define tblSetUT(tb,k,v) (tb = tbl_set(tb,'U',valU(k),'T',valT(v)))
#define tblSetUV(tb,k,v) (tb = tbl_set(tb,'U',valU(k),'V',valV(v)))
#define tblSetUR(tb,k,v) (tb = tbl_set(tb,'U',valU(k),'R',valR(v)))
#define tblSetUP(tb,k,v) (tb = tbl_set(tb,'U',valU(k),'P',valP(v)))
#define tblSetUS(tb,k,v) (tb = tbl_set(tb,'U',valU(k),'S',valS(val_Sdup(v))))
#define tblSetUH(tb,k,v) (tb = tbl_set(tb,'U',valU(k),'S',valS(v)))
#define tblSetUN(tb,k,v) (tb = tbl_set(tb,'U',valU(k),'N',valN(v)))
#define tblSetUU(tb,k,v) (tb = tbl_set(tb,'U',valU(k),'U',valU(v)))
#define tblSetUF(tb,k,v) (tb = tbl_set(tb,'U',valU(k),'F',valF(v)))

#define tblSetFM(tb,k,v) (tb = tbl_set(tb,'F',valF(k),'M',valM(v)))
#define tblSetFT(tb,k,v) (tb = tbl_set(tb,'F',valF(k),'T',valT(v)))
#define tblSetFV(tb,k,v) (tb = tbl_set(tb,'F',valF(k),'V',valV(v)))
#define tblSetFR(tb,k,v) (tb = tbl_set(tb,'F',valF(k),'R',valR(v)))
#define tblSetFP(tb,k,v) (tb = tbl_set(tb,'F',valF(k),'P',valP(v)))
#define tblSetFS(tb,k,v) (tb = tbl_set(tb,'F',valF(k),'S',valS(val_Sdup(v))))
#define tblSetFH(tb,k,v) (tb = tbl_set(tb,'F',valF(k),'S',valS(v)))
#define tblSetFN(tb,k,v) (tb = tbl_set(tb,'F',valF(k),'N',valN(v)))
#define tblSetFU(tb,k,v) (tb = tbl_set(tb,'F',valF(k),'U',valU(v)))
#define tblSetFF(tb,k,v) (tb = tbl_set(tb,'F',valF(k),'F',valF(v)))

val_u tbl_get(tbl_t tb, char k_type, val_u key, char v_type, val_u def);

#define tblGetSM(tb,k,d) valGetM(tbl_get(tb,'S',valS(k),'M',valM(d)))
#define tblGetST(tb,k,d) valGetT(tbl_get(tb,'S',valS(k),'T',valT(d)))
#define tblGetSV(tb,k,d) valGetT(tbl_get(tb,'S',valS(k),'V',valV(d)))
#define tblGetSR(tb,k,d) valGetT(tbl_get(tb,'S',valS(k),'R',valR(d)))
#define tblGetSP(tb,k,d) valGetP(tbl_get(tb,'S',valS(k),'P',valP(d)))
#define tblGetSS(tb,k,d) valGetS(tbl_get(tb,'S',valS(k),'S',valS(d)))
#define tblGetSN(tb,k,d) valGetN(tbl_get(tb,'S',valS(k),'N',valN(d)))
#define tblGetSU(tb,k,d) valGetU(tbl_get(tb,'S',valS(k),'U',valU(d)))
#define tblGetSF(tb,k,d) valGetF(tbl_get(tb,'S',valS(k),'F',valF(d)))

#define tblGetNM(tb,k,d) valGetM(tbl_get(tb,'N',valN(k),'M',valM(d)))
#define tblGetNT(tb,k,d) valGetT(tbl_get(tb,'N',valN(k),'T',valT(d)))
#define tblGetNV(tb,k,d) valGetT(tbl_get(tb,'N',valN(k),'V',valV(d)))
#define tblGetNR(tb,k,d) valGetT(tbl_get(tb,'N',valN(k),'R',valR(d)))
#define tblGetNP(tb,k,d) valGetP(tbl_get(tb,'N',valN(k),'P',valP(d)))
#define tblGetNS(tb,k,d) valGetS(tbl_get(tb,'N',valN(k),'S',valS(d)))
#define tblGetNN(tb,k,d) valGetN(tbl_get(tb,'N',valN(k),'N',valN(d)))
#define tblGetNU(tb,k,d) valGetU(tbl_get(tb,'N',valN(k),'U',valU(d)))
#define tblGetNF(tb,k,d) valGetF(tbl_get(tb,'N',valN(k),'F',valF(d)))

#define tblGetUM(tb,k,d) valGetM(tbl_get(tb,'U',valU(k),'M',valM(d)))
#define tblGetUT(tb,k,d) valGetT(tbl_get(tb,'U',valU(k),'T',valT(d)))
#define tblGetUV(tb,k,d) valGetT(tbl_get(tb,'U',valU(k),'V',valV(d)))
#define tblGetUR(tb,k,d) valGetT(tbl_get(tb,'U',valU(k),'R',valR(d)))
#define tblGetUP(tb,k,d) valGetP(tbl_get(tb,'U',valU(k),'P',valP(d)))
#define tblGetUS(tb,k,d) valGetS(tbl_get(tb,'U',valU(k),'S',valS(d)))
#define tblGetUN(tb,k,d) valGetN(tbl_get(tb,'U',valU(k),'N',valN(d)))
#define tblGetUU(tb,k,d) valGetU(tbl_get(tb,'U',valU(k),'U',valU(d)))
#define tblGetUF(tb,k,d) valGetF(tbl_get(tb,'U',valU(k),'F',valF(d)))

#define tblGetFM(tb,k,d) valGetM(tbl_get(tb,'F',valF(k),'M',valM(d)))
#define tblGetFT(tb,k,d) valGetT(tbl_get(tb,'F',valF(k),'T',valT(d)))
#define tblGetFV(tb,k,d) valGetT(tbl_get(tb,'F',valF(k),'V',valV(d)))
#define tblGetFR(tb,k,d) valGetT(tbl_get(tb,'F',valF(k),'R',valR(d)))
#define tblGetFP(tb,k,d) valGetP(tbl_get(tb,'F',valF(k),'P',valP(d)))
#define tblGetFS(tb,k,d) valGetS(tbl_get(tb,'F',valF(k),'S',valS(d)))
#define tblGetFN(tb,k,d) valGetN(tbl_get(tb,'F',valF(k),'N',valN(d)))
#define tblGetFU(tb,k,d) valGetU(tbl_get(tb,'F',valF(k),'U',valU(d)))
#define tblGetFF(tb,k,d) valGetF(tbl_get(tb,'F',valF(k),'F',valF(d)))


tbl_t tbl_del(tbl_t tb, char k_type, val_u key);

#define tblDelM(tb,k) (tb = tbl_del(tb,'M',valM(k)))
#define tblDelT(tb,k) (tb = tbl_del(tb,'T',valT(k)))
#define tblDelV(tb,k) (tb = tbl_del(tb,'V',valV(k)))
#define tblDelR(tb,k) (tb = tbl_del(tb,'R',valR(k)))
#define tblDelP(tb,k) (tb = tbl_del(tb,'P',valP(k)))
#define tblDelS(tb,k) (tb = tbl_del(tb,'S',valS(k)))
#define tblDelN(tb,k) (tb = tbl_del(tb,'N',valN(k)))
#define tblDelU(tb,k) (tb = tbl_del(tb,'U',valU(k)))
#define tblDelF(tb,k) (tb = tbl_del(tb,'F',valF(k)))

typedef long tblptr_t;

tblptr_t tblNext(tbl_t tb, tblptr_t ndx);
#define tblFirst(tb) tblNext(tb,0)

#define tblForeach(tb,i) for(i=tblFirst(tb); i != 0; i = tblNext(tb,i))


tblptr_t tbl_find(tbl_t tb, char k_type, val_u key);

#define tblFindM(tb,k)  tbl_find(tb,'M',valM(k))
#define tblFindT(tb,k)  tbl_find(tb,'T',valT(k))
#define tblFindV(tb,k)  tbl_find(tb,'V',valT(k))
#define tblFindR(tb,k)  tbl_find(tb,'R',valT(k))
#define tblFindP(tb,k)  tbl_find(tb,'P',valP(k))
#define tblFindS(tb,k)  tbl_find(tb,'S',valS(k))
#define tblFindN(tb,k)  tbl_find(tb,'N',valN(k))
#define tblFindU(tb,k)  tbl_find(tb,'U',valU(k))
#define tblFindF(tb,k)  tbl_find(tb,'F',valF(k))

char tblKeyType(tbl_t tb, tblptr_t ndx);
char tblValType(tbl_t tb, tblptr_t ndx);

val_u tbl_key(tbl_t tb, tblptr_t ndx);
val_u tbl_val(tbl_t tb, tblptr_t ndx);

#define tblKeyM(tb,n)  valGetM(tbl_key(tb,n))
#define tblKeyT(tb,n)  valGetT(tbl_key(tb,n))
#define tblKeyV(tb,n)  valGetV(tbl_key(tb,n))
#define tblKeyR(tb,n)  valGetR(tbl_key(tb,n))
#define tblKeyP(tb,n)  valGetP(tbl_key(tb,n))
#define tblKeyS(tb,n)  valGetS(tbl_key(tb,n))
#define tblKeyN(tb,n)  valGetN(tbl_key(tb,n))
#define tblKeyU(tb,n)  valGetU(tbl_key(tb,n))
#define tblKeyF(tb,n)  valGetF(tbl_key(tb,n))

#define tblValM(tb,n)  valGetM(tbl_val(tb,n))
#define tblValT(tb,n)  valGetT(tbl_val(tb,n))
#define tblValV(tb,n)  valGetV(tbl_val(tb,n))
#define tblValR(tb,n)  valGetR(tbl_val(tb,n))
#define tblValP(tb,n)  valGetP(tbl_val(tb,n))
#define tblValS(tb,n)  valGetS(tbl_val(tb,n))
#define tblValN(tb,n)  valGetN(tbl_val(tb,n))
#define tblValU(tb,n)  valGetU(tbl_val(tb,n))
#define tblValF(tb,n)  valGetF(tbl_val(tb,n))


/******************/

typedef struct {
  val_u  val;
  char   info[sizeof(val_u)]; /* to ensure alignment */
} vec_slot_t;

typedef struct {
  long count;
  long size;
  long cur;
  long stride;
  vec_slot_t slot[1];
} vec_vector_t;

typedef vec_vector_t *vec_t;

vec_t vec_setsize(vec_t vt, long nslots);

#define vecNew(v)  (v = vec_setsize(NULL, 2))

#define vecStrided(v,n)  (v? (v)->stride = n: n)

vec_t vec_free(vec_t vt) ;
#define vecFree(v) (v = vec_free(v));

long vecSize(vec_t vt);
long vecCount(vec_t vt);


vec_t vec_set(vec_t vt, long ndx, char v_type, val_u val, int del);

#define vecSetM(vt,n,v)  (vt = vec_set(vt, n, 'M', valM(v),1))
#define vecSetT(vt,n,v)  (vt = vec_set(vt, n, 'T', valT(v),1))
#define vecSetV(vt,n,v)  (vt = vec_set(vt, n, 'V', valV(v),1))
#define vecSetR(vt,n,v)  (vt = vec_set(vt, n, 'R', valR(v),1))
#define vecSetP(vt,n,v)  (vt = vec_set(vt, n, 'P', valP(v),1))
#define vecSetS(vt,n,v)  (vt = vec_set(vt, n, 'S', valS(val_Sdup(v)),1))
#define vecSetH(vt,n,v)  (vt = vec_set(vt, n, 'S', valS(v),1))
#define vecSetN(vt,n,v)  (vt = vec_set(vt, n, 'N', valN(v),1))
#define vecSetU(vt,n,v)  (vt = vec_set(vt, n, 'U', valU(v),1))
#define vecSetF(vt,n,v)  (vt = vec_set(vt, n, 'F', valF(v),1))

#define vecSetZM(vt,n,v)  (vt = vec_set(vt, n, 'M', valM(v),0))
#define vecSetZT(vt,n,v)  (vt = vec_set(vt, n, 'T', valT(v),0))
#define vecSetZV(vt,n,v)  (vt = vec_set(vt, n, 'V', valV(v),0))
#define vecSetZR(vt,n,v)  (vt = vec_set(vt, n, 'R', valR(v),0))
#define vecSetZP(vt,n,v)  (vt = vec_set(vt, n, 'P', valP(v),0))
#define vecSetZS(vt,n,v)  (vt = vec_set(vt, n, 'S', valS(val_Sdup(v)),0))
#define vecSetZH(vt,n,v)  (vt = vec_set(vt, n, 'S', valS(v),0))
#define vecSetZN(vt,n,v)  (vt = vec_set(vt, n, 'N', valN(v),0))
#define vecSetZU(vt,n,v)  (vt = vec_set(vt, n, 'U', valU(v),0))
#define vecSetZF(vt,n,v)  (vt = vec_set(vt, n, 'F', valF(v),0))

#define vecAddM(vt,v)   vecSetM(vt,vecCount(vt),v)
#define vecAddT(vt,v)   vecSetT(vt,vecCount(vt),v)
#define vecAddV(vt,v)   vecSetV(vt,vecCount(vt),v)
#define vecAddR(vt,v)   vecSetR(vt,vecCount(vt),v)
#define vecAddP(vt,v)   vecSetP(vt,vecCount(vt),v)
#define vecAddS(vt,v)   vecSetS(vt,vecCount(vt),v)
#define vecAddH(vt,v)   vecSetH(vt,vecCount(vt),v)
#define vecAddN(vt,v)   vecSetN(vt,vecCount(vt),v)
#define vecAddU(vt,v)   vecSetU(vt,vecCount(vt),v)
#define vecAddF(vt,v)   vecSetF(vt,vecCount(vt),v)

vec_t vec_ins(vec_t vt, long ndx, char v_type, val_u val);

#define vecInsM(vt,n,v)  (vt = vec_ins(vt, n, 'M', valM(v)))
#define vecInsT(vt,n,v)  (vt = vec_ins(vt, n, 'T', valT(v)))
#define vecInsV(vt,n,v)  (vt = vec_ins(vt, n, 'V', valV(v)))
#define vecInsR(vt,n,v)  (vt = vec_ins(vt, n, 'R', valR(v)))
#define vecInsP(vt,n,v)  (vt = vec_ins(vt, n, 'P', valP(v)))
#define vecInsS(vt,n,v)  (vt = vec_ins(vt, n, 'S', valS(val_Sdup(v))))
#define vecInsH(vt,n,v)  (vt = vec_ins(vt, n, 'S', valS(v)))
#define vecInsN(vt,n,v)  (vt = vec_ins(vt, n, 'N', valN(v)))
#define vecInsU(vt,n,v)  (vt = vec_ins(vt, n, 'U', valU(v)))
#define vecInsF(vt,n,v)  (vt = vec_ins(vt, n, 'F', valF(v)))

val_u vec_get(vec_t vt, long ndx, char v_type, val_u def);

#define vecGetM(vt,n,d) valGetM(vec_get(vt,n,'M',valM(d)))
#define vecGetT(vt,n,d) valGetT(vec_get(vt,n,'T',valT(d)))
#define vecGetV(vt,n,d) valGetV(vec_get(vt,n,'V',valV(d)))
#define vecGetR(vt,n,d) valGetR(vec_get(vt,n,'R',valR(d)))
#define vecGetP(vt,n,d) valGetP(vec_get(vt,n,'P',valP(d)))
#define vecGetS(vt,n,d) valGetS(vec_get(vt,n,'S',valS(d)))
#define vecGetN(vt,n,d) valGetN(vec_get(vt,n,'N',valN(d)))
#define vecGetU(vt,n,d) valGetU(vec_get(vt,n,'U',valU(d)))
#define vecGetF(vt,n,d) valGetF(vec_get(vt,n,'F',valF(d)))

val_u vec_getz(vec_t vt, long ndx, char v_type, val_u def);

#define vecGetZM(vt,n,d) valGetM(vec_getz(vt,n,'M',valM(d)))
#define vecGetZT(vt,n,d) valGetT(vec_getz(vt,n,'T',valT(d)))
#define vecGetZV(vt,n,d) valGetV(vec_getz(vt,n,'V',valV(d)))
#define vecGetZR(vt,n,d) valGetR(vec_getz(vt,n,'R',valR(d)))
#define vecGetZP(vt,n,d) valGetP(vec_getz(vt,n,'P',valP(d)))
#define vecGetZS(vt,n,d) valGetS(vec_getz(vt,n,'S',valS(d)))
#define vecGetZN(vt,n,d) valGetN(vec_getz(vt,n,'N',valN(d)))
#define vecGetZU(vt,n,d) valGetU(vec_getz(vt,n,'U',valU(d)))
#define vecGetZF(vt,n,d) valGetF(vec_getz(vt,n,'F',valF(d)))

val_u vec_slot_get(vec_slot_t *slot, char v_type, val_u def);

#define vecSlotGetM(n,d) valGetM(vec_slot_get(n,'M',valM(d)))
#define vecSlotGetT(n,d) valGetT(vec_slot_get(n,'T',valT(d)))
#define vecSlotGetV(n,d) valGetV(vec_slot_get(n,'V',valV(d)))
#define vecSlotGetR(n,d) valGetR(vec_slot_get(n,'R',valR(d)))
#define vecSlotGetP(n,d) valGetP(vec_slot_get(n,'P',valP(d)))
#define vecSlotGetS(n,d) valGetS(vec_slot_get(n,'S',valS(d)))
#define vecSlotGetN(n,d) valGetN(vec_slot_get(n,'N',valN(d)))
#define vecSlotGetU(n,d) valGetU(vec_slot_get(n,'U',valU(d)))
#define vecSlotGetF(n,d) valGetF(vec_slot_get(n,'F',valF(d)))

#define vecSlots(v) ((v)->slot)


char vecType(vec_t vt, long ndx);
char vecValType(vec_slot_t *slot);

vec_t vec_del(vec_t vt, long from, long to);
#define vecDel(vt,f,t)  (vt = vec_del(vt, f,t))

int vec_cmp (const void *a, const void *b);
#define vecSort(v)  qsort((v)->slot, vecCount(v) , sizeof(vec_slot_t), vec_cmp)

#define vecSortP(v,f)  qsort((v)->slot, vecCount(v) , sizeof(vec_slot_t), f)


vec_t vec_split(char *s, char *sep,char *trim, int dup);

#define vecSplit(s, sep, trim) vec_split(s,sep,trim,1)
#define vecSplitP(s, sep, trim) vec_split(s,sep,trim,0)


/*****************/

/* .%% Stack discipline */

#define stk_t vec_t

#define stkNew(tb)       vecNew(tb)
#define stkFree(tb)      vecFree(tb)

#define stkPushM(tb,v)   vecAddM(tb,v)
#define stkPushT(tb,v)   vecAddT(tb,v)
#define stkPushV(tb,v)   vecAddV(tb,v)
#define stkPushR(tb,v)   vecAddR(tb,v)
#define stkPushP(tb,v)   vecAddP(tb,v)
#define stkPushS(tb,v)   vecAddS(tb,v)
#define stkPushH(tb,v)   vecAddH(tb,v)
#define stkPushN(tb,v)   vecAddN(tb,v)
#define stkPushU(tb,v)   vecAddU(tb,v)
#define stkPushF(tb,v)   vecAddF(tb,v)

#define stkIsEmpty(tb)   (vecCount(tb) == 0)
#define stkTopType(tb)   vecType(tb,-1)

#define stkTopM(tb)      vecGetM(tb,vecCount(tb),NULL)
#define stkTopT(tb)      vecGetT(tb,vecCount(tb),NULL)
#define stkTopV(tb)      vecGetV(tb,vecCount(tb),NULL)
#define stkTopR(tb)      vecGetR(tb,vecCount(tb),NULL)
#define stkTopP(tb)      vecGetP(tb,vecCount(tb),NULL)
#define stkTopS(tb)      vecGetS(tb,vecCount(tb),NULL)
#define stkTopN(tb)      vecGetN(tb,vecCount(tb),0)
#define stkTopU(tb)      vecGetN(tb,vecCount(tb),0)
#define stkTopF(tb)      vecGetF(tb,vecCount(tb),0.0)

#define stkPop(tb)       vecDel(tb,-1,-1)

/*****************/

#define que_t vec_t

#define queNew(qu)       vecNew(qu)
#define queFree(qu)      vecFree(qu)
#define queAddFirst(qu,v)
#define queAddLast(qu,v)
#define queDelFirst(qu)
#define queDelLast(qu)
#define queCount(qu)

#define queFirstType(qu)
#define queLastType(qu)

#define queFirst
#define queLast

/*****************/

#define que_t vec_t

#define prqNew(qu)       vecNew(qu)
#define prqFree(qu)      vecFree(qu)
#define prqAdd(qu,v,p)
#define prqDelFirst(qu)
#define prqDelLast(qu)
#define prqCount(qu)

#define prqFirstType(qu)
#define prqLastType(qu)

#define prqFirstPri(qu)
#define prqLastPri(qu)

#define prqFirst
#define prqLast

/*****************/
struct rec_f_t {
  int size;
  char  *name;
  int   (*cmp)  (void * , void *) ;
  void *(*cpy)  (void * , void *) ;
  char *(*uid)  (void *) ;
  void  (*free) (void *) ;
};

typedef struct { struct rec_f_t  *rec_f; } *rec_t;

#define rec(t,y) \
  struct rec_##t##_f;\
  typedef struct t##_s { struct rec_##t##_f *rec_f; y } t; \
  int    t##_cmp(t *a, t *b); \
  void   t##_cpy(t *a, t *b);\
  char  *t##_uid(t *a);\
  void   t##_free(t *a); \
  void   t##_init(t *); \
  char  *t##_name = #t; \
  struct rec_##t##_f {\
    int    size;\
    char  *name; \
    int   (*cmp)  (t * , t *) ;\
    void  (*cpy)  (t * , t *) ;\
    char *(*uid)  (t *) ;\
    void  (*free) (t *) ;\
  }

#define recFunCmp(t,a,b)   int   t##_cmp(t *a, t *b)
#define recFunCpy(t,a,b)   void  t##_cpy(t *a, t *b)
#define recFunUid(t,a)     char *t##_uid(t *a)
#define recFunFree(t,a)    void  t##_free(t *a)

#define recFunNew(t,a) \
    static struct rec_##t##_f rec_##t##_func; \
    t *t##_new() {\
      t *p = calloc(1,sizeof(t));      \
      rec_##t##_func.size = sizeof(t); \
      rec_##t##_func.name = t##_name;  \
      rec_##t##_func.cmp  = t##_cmp;   \
      rec_##t##_func.cpy  = t##_cpy;   \
      rec_##t##_func.uid  = t##_uid;   \
      rec_##t##_func.free = t##_free;  \
      if (p) {\
        p->rec_f = &rec_##t##_func;\
        t##_init(p);\
      }\
      return p;\
    }\
    void t##_init(t *a)

#define recDef    rec
#define recDefCmp recFunCmp
#define recDefCpy recFunCpy
#define recDefUid recFunUid
#define recDefDel recFunFree
#define recDefFree recFunFree
#define recDefNew recFunNew

#define recCpy(a,b)  (a = rec_cpy((rec_t)a,(rec_t)b))

#define recNew(t,r)  (r = t##_new())

#define recFree(r)  \
  (r = (void *)(r? (( (rec_t)(r))->rec_f->free(r),free(r),NULL):NULL))

#define recSize(a)   ((a)? ((rec_t)(a))->rec_f->size : 0)

#define recUid(a)    ((a)? ((rec_t)(a))->rec_f->uid(a) : NULL)

#define recName(a)   ((a)? ((rec_t)(a))->rec_f->name : NULL)

#define recPtrCmp(a,b) ((char *)(a) - (char *)(b))

void *rec_cpy(rec_t a, rec_t b);
int   rec_cmp(rec_t a, rec_t b);

#define recCmp(a,b) rec_cmp((rec_t)a, (rec_t)b)

#define recIs(t,r) (r && (void *)(((rec_t)r)->rec_f) == (&rec_##t##_func))

/******************************/

#define lutItem(x,y) {x,y},

typedef struct { char *key;  int   val; } lutSN_slot_t;
typedef struct { int   key;  int   val; } lutNN_slot_t;
typedef struct { char *key;  char *val; } lutSS_slot_t;

typedef lutSN_slot_t lutSN_t[];
typedef lutNN_slot_t lutNN_t[];
typedef lutSS_slot_t lutSS_t[];

#define lutBegin(tt,lt) lut##tt##_t lt = {
#define lutEnd(lt)   } ; int lut_##lt##_size = sizeof(lt)/sizeof(lt[0]);

int lut_getSN(lutSN_t lt, int lt_size, char *key, int def);
#define lutGetSN(lt,k,d) lut_getSN(lt,lut_##lt##_size,k,d)

char *lut_getSS(lutSS_t lt, int lt_size, char *key, char *def);
#define lutGetSS(lt,k,d) lut_getSS(lt,lut_##lt##_size,k,d)


#endif
