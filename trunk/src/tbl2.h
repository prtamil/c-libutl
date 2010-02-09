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
 
#define tbl_setXX(tb,tk,k,fk,tv,v,fv) \
   do {val_u ak,av; ak.fk = k; av.fv = v; tb = tbl_set(tb,tk,ak,tv,av);} while (0)
 
#define tblSetMM(tb,k,v) tbl_setXX(tb,'M',k,p,'M',v,p)
#define tblSetMT(tb,k,v) tbl_setXX(tb,'M',k,p,'T',v,p)
#define tblSetMV(tb,k,v) tbl_setXX(tb,'M',k,p,'V',v,p)
#define tblSetMR(tb,k,v) tbl_setXX(tb,'M',k,p,'R',v,p)
#define tblSetMP(tb,k,v) tbl_setXX(tb,'M',k,p,'P',v,p)
#define tblSetMS(tb,k,v) tbl_setXX(tb,'M',k,p,'S',val_Sdup(v),s)
#define tblSetMN(tb,k,v) tbl_setXX(tb,'M',k,p,'N',v,n)
#define tblSetMU(tb,k,v) tbl_setXX(tb,'M',k,p,'U',v,u)
#define tblSetMF(tb,k,v) tbl_setXX(tb,'M',k,p,'F',v,f)

#define tblSetTM(tb,k,v) tbl_setXX(tb,'T',k,p,'M',v,p)
#define tblSetTT(tb,k,v) tbl_setXX(tb,'T',k,p,'T',v,p)
#define tblSetTV(tb,k,v) tbl_setXX(tb,'T',k,p,'V',v,p)
#define tblSetTR(tb,k,v) tbl_setXX(tb,'T',k,p,'R',v,p)
#define tblSetTP(tb,k,v) tbl_setXX(tb,'T',k,p,'P',v,p)
#define tblSetTS(tb,k,v) tbl_setXX(tb,'T',k,p,'S',val_Sdup(v),s)
#define tblSetTN(tb,k,v) tbl_setXX(tb,'T',k,p,'N',v,n)
#define tblSetTU(tb,k,v) tbl_setXX(tb,'T',k,p,'U',v,u)
#define tblSetTF(tb,k,v) tbl_setXX(tb,'T',k,p,'F',v,f)

#define tblSetVM(tb,k,v) tbl_setXX(tb,'V',k,p,'M',v,p)
#define tblSetVT(tb,k,v) tbl_setXX(tb,'V',k,p,'T',v,p)
#define tblSetVV(tb,k,v) tbl_setXX(tb,'V',k,p,'V',v,p)
#define tblSetVR(tb,k,v) tbl_setXX(tb,'V',k,p,'R',v,p)
#define tblSetVP(tb,k,v) tbl_setXX(tb,'V',k,p,'P',v,p)
#define tblSetVS(tb,k,v) tbl_setXX(tb,'V',k,p,'S',val_Sdup(v),s)
#define tblSetVN(tb,k,v) tbl_setXX(tb,'V',k,p,'N',v,n)
#define tblSetVU(tb,k,v) tbl_setXX(tb,'V',k,p,'U',v,u)
#define tblSetVF(tb,k,v) tbl_setXX(tb,'V',k,p,'F',v,f)

#define tblSetRM(tb,k,v) tbl_setXX(tb,'R',k,p,'M',v,p)
#define tblSetRT(tb,k,v) tbl_setXX(tb,'R',k,p,'T',v,p)
#define tblSetRV(tb,k,v) tbl_setXX(tb,'R',k,p,'V',v,p)
#define tblSetRR(tb,k,v) tbl_setXX(tb,'R',k,p,'R',v,p)
#define tblSetRP(tb,k,v) tbl_setXX(tb,'R',k,p,'P',v,p)
#define tblSetRS(tb,k,v) tbl_setXX(tb,'R',k,p,'S',val_Sdup(v),s)
#define tblSetRN(tb,k,v) tbl_setXX(tb,'R',k,p,'N',v,n)
#define tblSetRU(tb,k,v) tbl_setXX(tb,'R',k,p,'U',v,u)
#define tblSetRF(tb,k,v) tbl_setXX(tb,'R',k,p,'F',v,f)

#define tblSetPM(tb,k,v) tbl_setXX(tb,'P',k,p,'M',v,p)
#define tblSetPT(tb,k,v) tbl_setXX(tb,'P',k,p,'T',v,p)
#define tblSetPV(tb,k,v) tbl_setXX(tb,'P',k,p,'V',v,p)
#define tblSetPR(tb,k,v) tbl_setXX(tb,'P',k,p,'R',v,p)
#define tblSetPP(tb,k,v) tbl_setXX(tb,'P',k,p,'P',v,p)
#define tblSetPS(tb,k,v) tbl_setXX(tb,'P',k,p,'S',val_Sdup(v),s)
#define tblSetPN(tb,k,v) tbl_setXX(tb,'P',k,p,'N',v,n)
#define tblSetPU(tb,k,v) tbl_setXX(tb,'P',k,p,'U',v,u)
#define tblSetPF(tb,k,v) tbl_setXX(tb,'P',k,p,'F',v,f)

#define tblSetSM(tb,k,v) tbl_setXX(tb,'S',val_Sdup(k),n,'M',v,p)
#define tblSetST(tb,k,v) tbl_setXX(tb,'S',val_Sdup(k),n,'T',v,p)
#define tblSetSV(tb,k,v) tbl_setXX(tb,'S',val_Sdup(k),n,'V',v,p)
#define tblSetSR(tb,k,v) tbl_setXX(tb,'S',val_Sdup(k),n,'R',v,p)
#define tblSetSP(tb,k,v) tbl_setXX(tb,'S',val_Sdup(k),n,'P',v,p)
#define tblSetSS(tb,k,v) tbl_setXX(tb,'S',val_Sdup(k),n,'S',val_Sdup(v),s)
#define tblSetSN(tb,k,v) tbl_setXX(tb,'S',val_Sdup(k),n,'N',v,n)
#define tblSetSU(tb,k,v) tbl_setXX(tb,'S',val_Sdup(k),n,'U',v,u)
#define tblSetSF(tb,k,v) tbl_setXX(tb,'S',val_Sdup(k),n,'F',v,f)

#define tblSetNM(tb,k,v) tbl_setXX(tb,'N',k,n,'M',v,p)
#define tblSetNT(tb,k,v) tbl_setXX(tb,'N',k,n,'T',v,p)
#define tblSetNV(tb,k,v) tbl_setXX(tb,'N',k,n,'V',v,p)
#define tblSetNR(tb,k,v) tbl_setXX(tb,'N',k,n,'R',v,p)
#define tblSetNP(tb,k,v) tbl_setXX(tb,'N',k,n,'P',v,p)
#define tblSetNS(tb,k,v) tbl_setXX(tb,'N',k,n,'S',val_Sdup(v),s)
#define tblSetNN(tb,k,v) tbl_setXX(tb,'N',k,n,'N',v,n)
#define tblSetNU(tb,k,v) tbl_setXX(tb,'N',k,n,'U',v,u)
#define tblSetNF(tb,k,v) tbl_setXX(tb,'N',k,n,'F',v,f)

#define tblSetUM(tb,k,v) tbl_setXX(tb,'U',k,n,'M',v,p)
#define tblSetUT(tb,k,v) tbl_setXX(tb,'U',k,n,'T',v,p)
#define tblSetUV(tb,k,v) tbl_setXX(tb,'U',k,n,'V',v,p)
#define tblSetUR(tb,k,v) tbl_setXX(tb,'U',k,n,'R',v,p)
#define tblSetUP(tb,k,v) tbl_setXX(tb,'U',k,n,'P',v,p)
#define tblSetUS(tb,k,v) tbl_setXX(tb,'U',k,n,'S',val_Sdup(v),s)
#define tblSetUN(tb,k,v) tbl_setXX(tb,'U',k,n,'N',v,n)
#define tblSetUU(tb,k,v) tbl_setXX(tb,'U',k,n,'U',v,u)
#define tblSetUF(tb,k,v) tbl_setXX(tb,'U',k,n,'F',v,f)

#define tblSetFM(tb,k,v) tbl_setXX(tb,'F',k,n,'M',v,p)
#define tblSetFT(tb,k,v) tbl_setXX(tb,'F',k,n,'T',v,p)
#define tblSetFV(tb,k,v) tbl_setXX(tb,'F',k,n,'V',v,p)
#define tblSetFR(tb,k,v) tbl_setXX(tb,'F',k,n,'R',v,p)
#define tblSetFP(tb,k,v) tbl_setXX(tb,'F',k,n,'P',v,p)
#define tblSetFS(tb,k,v) tbl_setXX(tb,'F',k,n,'S',val_Sdup(v),s)
#define tblSetFN(tb,k,v) tbl_setXX(tb,'F',k,n,'N',v,n)
#define tblSetFU(tb,k,v) tbl_setXX(tb,'F',k,n,'U',v,u)
#define tblSetFF(tb,k,v) tbl_setXX(tb,'F',k,n,'F',v,f)

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



#define tbl_delX(tb,tk,k,fk) \
       do {val_u key; key.fk = k; tb = tbl_del(tb,tk,key);} while (0)

#define tblDelM(tb,k) tbl_delX(tb,'M',k,p)
#define tblDelT(tb,k) tbl_delX(tb,'T',k,p)
#define tblDelP(tb,k) tbl_delX(tb,'P',k,p)
#define tblDelS(tb,k) tbl_delX(tb,'S',k,s)
#define tblDelN(tb,k) tbl_delX(tb,'N',k,n)
#define tblDelU(tb,k) tbl_delX(tb,'U',k,u)
#define tblDelF(tb,k) tbl_delX(tb,'F',k,f)

typedef long tblptr_t;

tblptr_t tblNext(tbl_t tb, tblptr_t ndx);
#define tblFirst(tb) tblNext(tb,0)

tblptr_t tbl_find(tbl_t tb, char k_type, val_u key);

#define tblFindM(tb,k)  tbl_find(tb,'M',valM(k))
#define tblFindT(tb,k)  tbl_find(tb,'T',valT(k))
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
#define tblKeyP(tb,n)  valGetP(tbl_key(tb,n))
#define tblKeyS(tb,n)  valGetS(tbl_key(tb,n))
#define tblKeyN(tb,n)  valGetN(tbl_key(tb,n))
#define tblKeyU(tb,n)  valGetU(tbl_key(tb,n))
#define tblKeyF(tb,n)  valGetF(tbl_key(tb,n))

#define tblValM(tb,n)  valGetM(tbl_val(tb,n))
#define tblValT(tb,n)  valGetT(tbl_val(tb,n))
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
  vec_slot_t slot[1];
} vec_vector_t;

typedef vec_vector_t *vec_t;

vec_t vec_setsize(vec_t vt, long nslots);

#define vecNew(v)  (v = vec_setsize(NULL, 2))

vec_t vec_free(vec_t vt) ;
#define vecFree(v) (v = vec_free(v));

long vecSize(vec_t vt);

vec_t vec_set(vec_t vt, long ndx, char v_type, val_u val);

#define vecSetM(vt,n,v)  (vt = vec_set(vt, n, 'M', valM(v)))
#define vecSetT(vt,n,v)  (vt = vec_set(vt, n, 'T', valT(v)))
#define vecSetV(vt,n,v)  (vt = vec_set(vt, n, 'V', valV(v)))
#define vecSetR(vt,n,v)  (vt = vec_set(vt, n, 'R', valR(v)))
#define vecSetP(vt,n,v)  (vt = vec_set(vt, n, 'P', valP(v)))
#define vecSetS(vt,n,v)  (vt = vec_set(vt, n, 'S', valS(val_Sdup(v))))
#define vecSetN(vt,n,v)  (vt = vec_set(vt, n, 'N', valN(v)))
#define vecSetU(vt,n,v)  (vt = vec_set(vt, n, 'U', valU(v)))
#define vecSetF(vt,n,v)  (vt = vec_set(vt, n, 'F', valF(v)))
                          
#define vecAddM(vt,v)   vecSetM(vt,vecCount(vt),v)
#define vecAddT(vt,v)   vecSetT(vt,vecCount(vt),v)
#define vecAddV(vt,v)   vecSetV(vt,vecCount(vt),v)
#define vecAddR(vt,v)   vecSetR(vt,vecCount(vt),v)
#define vecAddP(vt,v)   vecSetP(vt,vecCount(vt),v)
#define vecAddS(vt,v)   vecSetS(vt,vecCount(vt),v)
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

char vecType(vec_t vt, long ndx);

vec_t vec_del(vec_t vt, long from, long to);
#define vecDel(vt,f,t)  (vt = vec_del(vt, f,t))


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
#define quePush(qu,v)
#define quePop(qu)
#define queAdd(qu,v)
#define queDel(qu)
#define queCount(qu)

#define queFrontType(qu)
#define queRearType(qu)

#define queFront
#define queRear

/*****************/


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

#endif
