/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#ifndef TBL_H
#define TBL_H
#include <stdint.h>

/*
.v
             _    _      _
            / \  / \    / \
         __/  (_/  /   /  /
        (_   ___) (_  /  /
         /  / /  __ \/  /
        /  /_/  /_/ /  /
       (_____)_____(__/
..
*/


/***** libutl/Table
 * DESCRIPTION 
 * Generic Tables 
******
*/ 
/* VAL *****************/


/****t* Table/Values
* DESCRIPTION
*  Table Value. 
*  The union that represents a value that can be used in a tbl_h table
* 
* BUGS 
*   Assumes that it is safe to write in p a void * and read it
*   back as a char * from s. 
*   ACCORDING TO ANSI C STANDARD THIS COULD CAUSE
*   AN UNDEFINED BEHAVIOUR.
* SOURCE
*/

typedef union {
  void  *p;    /* generic pointer */
  char  *s;    /* string or chs */ 
  long   n;    /* integer number */
  float  f;    /* floating point number */
} val_u;

/********/

#define valGetN(v)   ((v).n)
#define valGetF(v)   ((v).f)
#define valGetS(v)   ((v).s)
#define valGetP(v)   ((v).p)
#define valGetT(v)   ((tbl_t)((v).p))
#define valGetV(v)   ((vec_t)((v).p))
#define valGetR(v)   ((rec_t)((v).p))
#define valGetO(v)   ((v).p)

/* TBL *****************/
/**
* A table slot.
*/ 
typedef struct {
  unsigned char flg[4];  /* flags are used to store the type of key/value*/
  val_u  val;  /*  stored value */
  val_u  key;  /*  slot key */
  val_u  aux;  /* The aux value will be used for different purposes */
} tbl_slot_t;    

/**
* The table itself.
* This structure can be reallocated due to insertion and deletion. 
*/

typedef struct {
  long count;  /**< number of used slots */
  long size;   /**< number of allocated slots */
  long cur;    /**< "current" slot used for iterations*/
  tbl_slot_t slot[1];  /**< start of the slot's array */
} tbl_ht_t;

/**
*  The type to use to define a table.
*/ 

typedef tbl_ht_t *tbl_t;

tbl_t tbl_new(long nslots);

#define tblNew(t) (t=tbl_new(4))

val_u tbl_get(tbl_t tb, char tk, long nkey, void *pkey, float fkey,
                        char tv, long ndef, void *pdef, float fdef);

#define tblGetNN(tb,k,d)  valGetN(tbl_get(tb,'N', k, NULL, 0.0,'N', d, NULL, 0.0))
#define tblGetFN(tb,k,d)  valGetN(tbl_get(tb,'F', 0, NULL, k  ,'N', d, NULL, 0.0))
#define tblGetSN(tb,k,d)  valGetN(tbl_get(tb,'S', 0, k   , 0.0,'N', d, NULL, 0.0))
#define tblGetPN(tb,k,d)  valGetN(tbl_get(tb,'P', 0, k   , 0.0,'N', d, NULL, 0.0))
#define tblGetTN(tb,k,d)  valGetN(tbl_get(tb,'T', 0, k   , 0.0,'N', d, NULL, 0.0))
#define tblGetVN(tb,k,d)  valGetN(tbl_get(tb,'V', 0, k   , 0.0,'N', d, NULL, 0.0))
#define tblGetRN(tb,k,d)  valGetN(tbl_get(tb,'R', 0, k   , 0.0,'N', d, NULL, 0.0))
#define tblGetON(tb,k,d)  valGetN(tbl_get(tb,'O', 0, k   , 0.0,'N', d, NULL, 0.0))

#define tblGetNF(tb,k,d)  valGetN(tbl_get(tb,'N', k, NULL, 0.0,'F', 0, NULL, d))
#define tblGetFF(tb,k,d)  valGetN(tbl_get(tb,'F', 0, NULL, k  ,'F', 0, NULL, d))
#define tblGetSF(tb,k,d)  valGetN(tbl_get(tb,'S', 0, k   , 0.0,'F', 0, NULL, d))
#define tblGetPF(tb,k,d)  valGetN(tbl_get(tb,'P', 0, k   , 0.0,'F', 0, NULL, d))
#define tblGetTF(tb,k,d)  valGetN(tbl_get(tb,'T', 0, k   , 0.0,'F', 0, NULL, d))
#define tblGetVF(tb,k,d)  valGetN(tbl_get(tb,'V', 0, k   , 0.0,'F', 0, NULL, d))
#define tblGetRF(tb,k,d)  valGetN(tbl_get(tb,'R', 0, k   , 0.0,'F', 0, NULL, d))
#define tblGetOF(tb,k,d)  valGetN(tbl_get(tb,'O', 0, k   , 0.0,'F', 0, NULL, d))

#define tblGetNS(tb,k,d)  valGetS(tbl_get(tb, 'N', k, NULL, 0.0,'S', 0, d, 0.0))
#define tblGetFS(tb,k,d)  valGetS(tbl_get(tb, 'F', 0, NULL, k  ,'S', 0, d, 0.0))
#define tblGetSS(tb,k,d)  valGetS(tbl_get(tb, 'S', 0, k   , 0.0,'S', 0, d, 0.0))
#define tblGetPS(tb,k,d)  valGetS(tbl_get(tb, 'P', 0, k   , 0.0,'S', 0, d, 0.0))
#define tblGetTS(tb,k,d)  valGetS(tbl_get(tb, 'T', 0, k   , 0.0,'S', 0, d, 0.0))
#define tblGetVS(tb,k,d)  valGetS(tbl_get(tb, 'V', 0, k   , 0.0,'S', 0, d, 0.0))
#define tblGetRS(tb,k,d)  valGetS(tbl_get(tb, 'R', 0, k   , 0.0,'S', 0, d, 0.0))
#define tblGetOS(tb,k,d)  valGetS(tbl_get(tb, 'O', 0, k   , 0.0,'S', 0, d, 0.0))

#define tblGetNP(tb,k,d)  valGetP(tbl_get(tb, 'N', k, NULL, 0.0,'P', 0, d, 0.0))
#define tblGetFP(tb,k,d)  valGetP(tbl_get(tb, 'F', 0, NULL, k  ,'P', 0, d, 0.0))
#define tblGetSP(tb,k,d)  valGetP(tbl_get(tb, 'S', 0, k   , 0.0,'P', 0, d, 0.0))
#define tblGetPP(tb,k,d)  valGetP(tbl_get(tb, 'P', 0, k   , 0.0,'P', 0, d, 0.0))
#define tblGetTP(tb,k,d)  valGetP(tbl_get(tb, 'T', 0, k   , 0.0,'P', 0, d, 0.0))
#define tblGetVP(tb,k,d)  valGetP(tbl_get(tb, 'V', 0, k   , 0.0,'P', 0, d, 0.0))
#define tblGetRP(tb,k,d)  valGetP(tbl_get(tb, 'R', 0, k   , 0.0,'P', 0, d, 0.0))
#define tblGetOP(tb,k,d)  valGetP(tbl_get(tb, 'O', 0, k   , 0.0,'P', 0, d, 0.0))

#define tblGetNT(tb,k,d)  valGetT(tbl_get(tb, 'N', k, NULL, 0.0,'T', 0, d, 0.0))
#define tblGetFT(tb,k,d)  valGetT(tbl_get(tb, 'F', 0, NULL, k  ,'T', 0, d, 0.0))
#define tblGetST(tb,k,d)  valGetT(tbl_get(tb, 'S', 0, k   , 0.0,'T', 0, d, 0.0))
#define tblGetPT(tb,k,d)  valGetT(tbl_get(tb, 'P', 0, k   , 0.0,'T', 0, d, 0.0))
#define tblGetTT(tb,k,d)  valGetT(tbl_get(tb, 'T', 0, k   , 0.0,'T', 0, d, 0.0))
#define tblGetVT(tb,k,d)  valGetT(tbl_get(tb, 'V', 0, k   , 0.0,'T', 0, d, 0.0))
#define tblGetRT(tb,k,d)  valGetT(tbl_get(tb, 'R', 0, k   , 0.0,'T', 0, d, 0.0))
#define tblGetOT(tb,k,d)  valGetT(tbl_get(tb, 'P', 0, k   , 0.0,'T', 0, d, 0.0))

#define tblGetNR(tb,k,d)  valGetP(tbl_get(tb, 'N', k, NULL, 0.0, 'R', 0, d, 0.0))
#define tblGetFR(tb,k,d)  valGetP(tbl_get(tb, 'F', 0, NULL, k  , 'R', 0, d, 0.0))
#define tblGetSR(tb,k,d)  valGetP(tbl_get(tb, 'S', 0, k   , 0.0, 'R', 0, d, 0.0))
#define tblGetPR(tb,k,d)  valGetP(tbl_get(tb, 'P', 0, k   , 0.0, 'R', 0, d, 0.0))
#define tblGetTR(tb,k,d)  valGetP(tbl_get(tb, 'T', 0, k   , 0.0, 'R', 0, d, 0.0))
#define tblGetVR(tb,k,d)  valGetP(tbl_get(tb, 'V', 0, k   , 0.0, 'R', 0, d, 0.0))
#define tblGetRR(tb,k,d)  valGetP(tbl_get(tb, 'R', 0, k   , 0.0, 'R', 0, d, 0.0))
#define tblGetOR(tb,k,d)  valGetP(tbl_get(tb, 'O', 0, k   , 0.0, 'R', 0, d, 0.0))

#define tblGetNV(tb,k,d)  valGetP(tbl_get(tb, 'N', k, NULL, 0.0, 'V', 0, d, 0.0))
#define tblGetFV(tb,k,d)  valGetP(tbl_get(tb, 'F', 0, NULL, k  , 'V', 0, d, 0.0))
#define tblGetSV(tb,k,d)  valGetP(tbl_get(tb, 'S', 0, k   , 0.0, 'V', 0, d, 0.0))
#define tblGetPV(tb,k,d)  valGetP(tbl_get(tb, 'P', 0, k   , 0.0, 'V', 0, d, 0.0))
#define tblGetTV(tb,k,d)  valGetP(tbl_get(tb, 'T', 0, k   , 0.0, 'V', 0, d, 0.0))
#define tblGetVV(tb,k,d)  valGetP(tbl_get(tb, 'V', 0, k   , 0.0, 'V', 0, d, 0.0))
#define tblGetRV(tb,k,d)  valGetP(tbl_get(tb, 'R', 0, k   , 0.0, 'V', 0, d, 0.0))
#define tblGetOV(tb,k,d)  valGetP(tbl_get(tb, 'O', 0, k   , 0.0, 'V', 0, d, 0.0))

#define tblGetNO(tb,k,d)  valGetP(tbl_get(tb, 'N', k, NULL, 0.0, 'O', 0, d, 0.0))
#define tblGetFO(tb,k,d)  valGetP(tbl_get(tb, 'F', 0, NULL, k  , 'O', 0, d, 0.0))
#define tblGetSO(tb,k,d)  valGetP(tbl_get(tb, 'S', 0, k   , 0.0, 'O', 0, d, 0.0))
#define tblGetPO(tb,k,d)  valGetP(tbl_get(tb, 'P', 0, k   , 0.0, 'O', 0, d, 0.0))
#define tblGetTO(tb,k,d)  valGetP(tbl_get(tb, 'T', 0, k   , 0.0, 'O', 0, d, 0.0))
#define tblGetVO(tb,k,d)  valGetP(tbl_get(tb, 'V', 0, k   , 0.0, 'O', 0, d, 0.0))
#define tblGetRO(tb,k,d)  valGetP(tbl_get(tb, 'R', 0, k   , 0.0, 'O', 0, d, 0.0))
#define tblGetOO(tb,k,d)  valGetP(tbl_get(tb, 'O', 0, k   , 0.0, 'O', 0, d, 0.0))

long    tblNext (tbl_t tb, long start);
#define tblFirst(tb,i) tblNext(tb,0)

#define tblForeach(tb,i) for(i=tblNext(tb,0); (long)i >= 0; \
                                                     i = tblNext(tb,(long)i))

#define tblNil 0
        
#define tbl_keytype(slot)  ((slot)->flg[0])
#define tbl_valtype(slot)  ((slot)->flg[1])

#define tblSlot(tb,i)  ((tb)->slot[(i)-1])

#define tblCount(tb) ((tb)? (tb)->count : 0)

extern long tbl_i;

#define tblKeyType(tb,i) ((tbl_i=(i))? tbl_keytype(&tblSlot(tb,tbl_i)) : '\0') 
#define tblValType(tb,i) ((tbl_i=(i))? tbl_valtype(&tblSlot(tb,tbl_i)) : '\0')
                                     
#define tblKeyN(tb,i) valGetN(tblSlot(tb,i).key) 
#define tblKeyF(tb,i) valGetF(tblSlot(tb,i).key) 
#define tblKeyS(tb,i) valGetS(tblSlot(tb,i).key) 
#define tblKeyP(tb,i) valGetP(tblSlot(tb,i).key) 
#define tblKeyT(tb,i) valGetT(tblSlot(tb,i).key)
#define tblKeyR(tb,i) valGetR(tblSlot(tb,i).key)
#define tblKeyO(tb,i) valGetO(tblSlot(tb,i).key) 
 
#define tblValN(tb,i) valGetN(tblSlot(tb,i).val) 
#define tblValF(tb,i) valGetF(tblSlot(tb,i).val) 
#define tblValS(tb,i) valGetS(tblSlot(tb,i).val) 
#define tblValP(tb,i) valGetP(tblSlot(tb,i).val) 
#define tblValR(tb,i) valGetR(tblSlot(tb,i).val) 
#define tblValO(tb,i) valGetO(tblSlot(tb,i).val) 

#define tblDel(tb,i) (tbl_keytype(&tblSlot(tb,i)) = '\0')

long tbl_find(tbl_t tb, char tk, long nkey, void *pkey, float fkey);

#define tblFindN(tb,k) tbl_find(tb, 'N', k, NULL, 0.0)
#define tblFindF(tb,k) tbl_find(tb, 'F', 0, NULL, k  )
#define tblFindS(tb,k) tbl_find(tb, 'S', 0, k   , 0.0)
#define tblFindP(tb,k) tbl_find(tb, 'P', 0, k   , 0.0)
#define tblFindT(tb,k) tbl_find(tb, 'T', 0, k   , 0.0)
#define tblFindR(tb,k) tbl_find(tb, 'R', 0, k   , 0.0)
#define tblFindO(tb,k) tbl_find(tb, 'O', 0, k   , 0.0)

tbl_t tbl_set(tbl_t tb, char tk, long nkey, void *pkey, float fkey,
                        char tv, long nval, void *pval, float fdef);

#define tbl_Set(t,tk,nk,pk,fk,tv,nv,pv,fv) (t = tbl_set(t,tk,nk,pk,fk,tv,nv,pv,fv))

#define tblSetNN(tb,k,v)  tbl_Set(tb, 'N', k, NULL,      0.0,'N', v, NULL, 0.0)
#define tblSetFN(tb,k,v)  tbl_Set(tb, 'F', 0, NULL,      k  ,'N', v, NULL, 0.0)
#define tblSetSN(tb,k,v)  tbl_Set(tb, 'S', 0, chsDup(k), 0.0,'N', v, NULL, 0.0)
#define tblSetPN(tb,k,v)  tbl_Set(tb, 'P', 0, k,         0.0,'N', v, NULL, 0.0)
#define tblSetTN(tb,k,v)  tbl_Set(tb, 'T', 0, k,         0.0,'N', v, NULL, 0.0)
#define tblSetRN(tb,k,v)  tbl_Set(tb, 'R', 0, k,         0.0,'N', v, NULL, 0.0)
#define tblSetON(tb,k,v)  tbl_Set(tb, 'O', 0, k,         0.0,'N', v, NULL, 0.0)
                                   
#define tblSetNS(tb,k,v)  tbl_Set(tb, 'N', k, NULL,      0.0,'S', 0, chsDup(v), 0.0)
#define tblSetFS(tb,k,v)  tbl_Set(tb, 'F', 0, NULL,      k  ,'S', 0, chsDup(v), 0.0)
#define tblSetSS(tb,k,v)  tbl_Set(tb, 'S', 0, chsDup(k), 0.0,'S', 0, chsDup(v), 0.0)
#define tblSetPS(tb,k,v)  tbl_Set(tb, 'P', 0, k,         0.0,'S', 0, chsDup(v), 0.0)
#define tblSetTS(tb,k,v)  tbl_Set(tb, 'T', 0, k,         0.0,'S', 0, chsDup(v), 0.0)
#define tblSetRS(tb,k,v)  tbl_Set(tb, 'R', 0, k,         0.0,'S', 0, chsDup(v), 0.0)
#define tblSetOS(tb,k,v)  tbl_Set(tb, 'O', 0, k,         0.0,'S', 0, chsDup(v), 0.0)

#define tblSetNT(tb,k,v)  tbl_Set(tb, 'N', k, NULL,      0.0,'T', 0, v, 0.0)
#define tblSetFT(tb,k,v)  tbl_Set(tb, 'F', 0, NULL,      k  ,'T', 0, v, 0.0)
#define tblSetST(tb,k,v)  tbl_Set(tb, 'S', 0, chsDup(k), 0.0,'T', 0, v, 0.0)
#define tblSetPT(tb,k,v)  tbl_Set(tb, 'P', 0, k   ,      0.0,'T', 0, v, 0.0)
#define tblSetTT(tb,k,v)  tbl_Set(tb, 'T', 0, k   ,      0.0,'T', 0, v, 0.0)
#define tblSetRT(tb,k,v)  tbl_Set(tb, 'R', 0, k   ,      0.0,'T', 0, v, 0.0)
#define tblSetOT(tb,k,v)  tbl_Set(tb, 'O', 0, k   ,      0.0,'T', 0, v, 0.0)

#define tblSetNP(tb,k,v)  tbl_Set(tb, 'N', k, NULL,       0.0,'P', 0, v, 0.0)
#define tblSetFP(tb,k,v)  tbl_Set(tb, 'F', 0, NULL,       k  ,'P', 0, v, 0.0)
#define tblSetSP(tb,k,v)  tbl_Set(tb, 'S', 0, chsDup(k),  0.0,'P', 0, v, 0.0)
#define tblSetPP(tb,k,v)  tbl_Set(tb, 'P', 0, k,          0.0,'P', 0, v, 0.0)
#define tblSetTP(tb,k,v)  tbl_Set(tb, 'T', 0, k,          0.0,'P', 0, v, 0.0)
#define tblSetRP(tb,k,v)  tbl_Set(tb, 'R', 0, k,          0.0,'P', 0, v, 0.0)
#define tblSetOP(tb,k,v)  tbl_Set(tb, 'O', 0, k,          0.0,'P', 0, v, 0.0)

#define tblSetNR(tb,k,v)  tbl_Set(tb, 'N', k, NULL,       0.0,'R', 0, v, 0.0)
#define tblSetFR(tb,k,v)  tbl_Set(tb, 'F', 0, NULL,       k  ,'R', 0, v, 0.0)
#define tblSetSR(tb,k,v)  tbl_Set(tb, 'S', 0, chsDup(k),  0.0,'R', 0, v, 0.0)
#define tblSetPR(tb,k,v)  tbl_Set(tb, 'P', 0, k,          0.0,'R', 0, v, 0.0)
#define tblSetTR(tb,k,v)  tbl_Set(tb, 'T', 0, k,          0.0,'R', 0, v, 0.0)
#define tblSetRR(tb,k,v)  tbl_Set(tb, 'R', 0, k,          0.0,'R', 0, v, 0.0)
#define tblSetOR(tb,k,v)  tbl_Set(tb, 'O', 0, k,          0.0,'R', 0, v, 0.0)

#define tblSetNO(tb,k,v)  tbl_Set(tb, 'N', k, NULL,       0.0,'O', 0, v, 0.0)
#define tblSetFO(tb,k,v)  tbl_Set(tb, 'F', 0, NULL,       k  ,'O', 0, v, 0.0)
#define tblSetSO(tb,k,v)  tbl_Set(tb, 'S', 0, chsDup(k),  0.0,'O', 0, v, 0.0)
#define tblSetPO(tb,k,v)  tbl_Set(tb, 'P', 0, k,          0.0,'O', 0, v, 0.0)
#define tblSetTO(tb,k,v)  tbl_Set(tb, 'T', 0, k,          0.0,'O', 0, v, 0.0)
#define tblSetRO(tb,k,v)  tbl_Set(tb, 'R', 0, k,          0.0,'O', 0, v, 0.0)
#define tblSetOO(tb,k,v)  tbl_Set(tb, 'O', 0, k,          0.0,'O', 0, v, 0.0)

tbl_t tbl_free(tbl_t tb,char wipe);
#define tblFree(tb) (tb=tbl_free(tb,'w'))

tbl_t tbl_del(tbl_t tb, char tk, long nkey, void *pkey, float fkey);

#define tbl_Del(t,tk,nk,pk,fk) (t = tbl_del(t,tk,nk,pk,fk))

#define tblDelN(tb,k) tbl_Del(tb, 'N', k, NULL, 0.0)
#define tblDelF(tb,k) tbl_Del(tb, 'F', 0, NULL, k  )
#define tblDelS(tb,k) tbl_Del(tb, 'S', 0, k,    0.0)
#define tblDelP(tb,k) tbl_Del(tb, 'P', 0, k,    0.0)
#define tblDelT(tb,k) tbl_Del(tb, 'T', 0, k,    0.0)
#define tblDelR(tb,k) tbl_Del(tb, 'R', 0, k,    0.0)
#define tblDelO(tb,k) tbl_Del(tb, 'O', 0, k,    0.0)

tbl_t tbl_MaxSlot(tbl_t tb, long nslots);

#define tblMaxSlot(t,n) (t = tbl_MaxSlot(t,n))

/* VEC *****************/

typedef struct {
  unsigned char flg[4];
  val_u  val;
} vec_slot_t;

typedef struct {
  long count;
  long size;
  long cur;
  vec_slot_t slot[1];
} vec_st_t;

typedef vec_st_t *vec_t;

extern vec_t vec_tmp;
 
#define vec_valtype(slot)  ((slot)->flg[1])
#define vecValType(vt,i) \
 (vec_tmp = vt, \
 ((vec_tmp) && (vec_tmp->count > 0) && (vec_tmp->count > (i)))    ? \
         ((vec_tmp)->slot+(i))->flg[1] : \
         '\0')

val_u vec_get(vec_t tb, long nkey, char tv, long ndef, void *pdef, float fdef);

vec_t vec_SetCount(vec_t vt, long max);
#define vecSetCount(vt,n) (vt = vec_SetCount(vt,n))

long vecCount(vec_t vt);

#define vecVoid ((vec_t)utlEmptyString)

vec_t vec_new(long nslots);
#define vecNew(v) (v = vec_new(2))

vec_t vec_Del(vec_t vt, long kfrom, long kto);
#define vecDel(v,f,t) (v = vec_Del(v,f,t))

vec_t vecMove(vec_t vt, long kfrom, long kto);

vec_t vec_free(vec_t vt, char wipe);
#define vecFree(vt) (vt=vec_free(vt,1))

vec_t vec_set(vec_t tb, long nkey, char tv, long nval, void *pval,float fval);
#define vec_Set(t,n,tv,nv,pv,fv) (t = vec_set(t,n,tv,nv,pv,fv))

#define vecSetN(tb,k,v)  vec_Set(tb, k, 'N', v, NULL      ,0.0)
#define vecSetF(tb,k,v)  vec_Set(tb, k, 'F', 0, NULL      ,v  )
#define vecSetS(tb,k,v)  vec_Set(tb, k, 'S', 0, chsDup(v) ,0.0)
#define vecSetP(tb,k,v)  vec_Set(tb, k, 'P', 0, v         ,0.0)
#define vecSetT(tb,k,v)  vec_Set(tb, k, 'T', 0, v         ,0.0)
#define vecSetV(tb,k,v)  vec_Set(tb, k, 'V', 0, v         ,0.0)
#define vecSetR(tb,k,v)  vec_Set(tb, k, 'R', 0, v         ,0.0)
#define vecSetO(tb,k,v)  vec_Set(tb, k, 'O', 0, v         ,0.0)

#define vecAddN(tb,v)    vec_Set(tb, vecCount(tb), 'N', v, NULL      ,0.0)
#define vecAddF(tb,v)    vec_Set(tb, vecCount(tb), 'F', 0, NULL      ,f  )
#define vecAddS(tb,v)    vec_Set(tb, vecCount(tb), 'S', 0, chsDup(v) ,0.0)
#define vecAddP(tb,v)    vec_Set(tb, vecCount(tb), 'P', 0, v         ,0.0)
#define vecAddT(tb,v)    vec_Set(tb, vecCount(tb), 'T', 0, v         ,0.0)
#define vecAddV(tb,v)    vec_Set(tb, vecCount(tb), 'V', 0, v         ,0.0)
#define vecAddR(tb,v)    vec_Set(tb, vecCount(tb), 'R', 0, v         ,0.0)
#define vecAddO(tb,v)    vec_Set(tb, vecCount(tb), 'O', 0, v         ,0.0)

#define vecGetN(tb,k,d)  valGetN(vec_get(tb, k , 'N', d, NULL, 0.0))
#define vecGetF(tb,k,d)  valGetF(vec_get(tb, k , 'F', 0, NULL, d  ))
#define vecGetS(tb,k,d)  valGetS(vec_get(tb, k , 'S', 0, d   , 0.0))
#define vecGetP(tb,k,d)  valGetP(vec_get(tb, k , 'P', 0, d   , 0.0))
#define vecGetT(tb,k,d)  valGetT(vec_get(tb, k , 'T', 0, d   , 0.0))
#define vecGetR(tb,k,d)  valGetR(vec_get(tb, k , 'R', 0, d   , 0.0))
#define vecGetV(tb,k,d)  valGetV(vec_get(tb, k , 'V', 0, d   , 0.0))
#define vecGetO(tb,k,d)  valGetP(vec_get(tb, k , 'O', 0, d   , 0.0))

vec_t vec_ins(vec_t tb, long nkey, char tv, long nval, void *pval, float fval);
#define vec_Ins(t,nk,tv,nv,pv,fv) (t = vec_ins(t,nk,tv,nv,pv,fv))

#define vecInsN(tb,k,v)  vec_Ins(tb,  k, 'N', v, NULL,      0.0)
#define vecInsF(tb,k,v)  vec_Ins(tb,  k, 'F', v, NULL,      v)
#define vecInsS(tb,k,v)  vec_Ins(tb,  k, 'S', 0, chsDup(v), 0.0)
#define vecInsP(tb,k,v)  vec_Ins(tb,  k, 'P', 0, v        , 0.0)
#define vecInsT(tb,k,v)  vec_Ins(tb,  k, 'T', 0, v        , 0.0)
#define vecInsV(tb,k,v)  vec_Ins(tb,  k, 'V', 0, v        , 0.0)
#define vecInsO(tb,k,v)  vec_Ins(tb,  k, 'O', 0, v        , 0.0)



/* .%% Other functions
   '''''''''''''''''''
*/
vec_t vec_split(char *s, char *sep,char *trim, int dup);

#define vecSplit(s, sep, trim) vec_split(s,sep,trim,1)
#define vecSplitP(s, sep, trim) vec_split(s,sep,trim,0)

int vec_cmp (const void *a, const void *b);
#define vecSort(v)  qsort((v)->slot, vecCount(v) , sizeof(vec_slot_t), vec_cmp)


/* .%% Stack discipline */

#define stk_t vec_t

#define stkNew(tb)       vecNew(tb)
#define stkFree(tb)      vecFree(tb)

#define stkPushN(tb,v)   vecAddN(tb,v)
#define stkPushF(tb,v)   vecAddF(tb,v)
#define stkPushP(tb,v)   vecAddP(tb,v)
#define stkPushS(tb,v)   vecAddS(tb,v) 
#define stkPushT(tb,v)   vecAddT(tb,v) 
#define stkPushV(tb,v)   vecAddV(tb,v) 
#define stkPushR(tb,v)   vecAddR(tb,v) 
#define stkPushO(tb,v)   vecAddO(tb,v) 

#define stkIsEmpty(tb)   (vecCount(tb) == 0)
#define stkTopType(tb)   vecValType(tb,vecCount-1)

#define stkTopN(tb)      vecGetN(tb,vecCount(tb),0)
#define stkTopF(tb)      vecGetF(tb,vecCount(tb),0.0)
#define stkTopP(tb)      vecGetP(tb,vecCount(tb),NULL)
#define stkTopS(tb)      vecGetS(tb,vecCount(tb),NULL)
#define stkTopT(tb)      vecGetT(tb,vecCount(tb),NULL)
#define stkTopR(tb)      vecGetR(tb,vecCount(tb),NULL)
#define stkTopV(tb)      vecGetV(tb,vecCount(tb),NULL)
#define stkTopO(tb)      vecGetO(tb,vecCount(tb),NULL)

#define stkPop(tb)       vecDel(tb,-1,-1)

#endif
