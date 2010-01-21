/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#include <stdio.h>
#include <stdlib.h>
#include "tbl2.h"

/************************/
static void utl_outofmem()
{ 
  if (stderr) fprintf(stderr,"OUT OF MEMORY");
  exit(1);
}

/************************/

/*
** Integer log base 2 of a 32 bits integer values.
**   llog2(0) == llog2(1) == 0
*/
static unsigned short llog2(unsigned long x)
{
  long l = 0;

    if (x==0) return 0;
    #if defined(__POCC__) || defined(_MSC_VER) || defined (__WATCOMC__)
        /* Pelles C            MS Visual C++         OpenWatcom*/
      __asm { mov eax, [x]
              bsr ecx, eax
              mov  l, ecx
      }
      return (unsigned short)l;
    #elif defined(__GNUC__)
      return (unsigned short) __builtin_clzl(x);
    #elif
      if (x & 0xFFFF0000)         {l += 16; x >>= 16;}
      if (x & 0xFF00)             {l += 8;  x >>= 8 ;}
      if (x & 0xF0)               {l += 4;  x >>= 4 ;}
      if (x & 0xC)                {l += 2;  x >>= 2 ;}
      if (x & 2)                  {l += 1;           }
      return (unsigned short)l;
    #endif  
}

/******************************************************************/

/* from Bit Twiddling Hacks 
** http://www-graphics.stanford.edu/~seander/bithacks.html
*/ 

#define roundpow2(v) (v--,\
                     (v |= v >> 1), (v |= v >> 2), \
                     (v |= v >> 4), (v |= v >> 8), \
                     (v |= v >> 16), \
                      v++)

/******************************************************************/

#define val_set(x, tv,nv,pv,fv) ((tv == 'N') ? (void)((x).n = (nv)) : \
                                 (tv == 'F') ? (void)((x).f = (fv)) : \
                                               (void)((x).p = (pv))) 

#define val_del(tv,v) do { switch (tv) { \
                             case 'S' : (v).s = val_Sfree((v).s); \
                             case 'P' : (v).p = NULL; \
                             case 'N' : (v).n = 0; \
                             case 'U' : (v).u = 0; \
                             case 'F' : (v).f = 0.0; \
                           }\
                      } while (0)


char *val_Sdup(char *s)
{
  char *str = NULL;
  int k;
  if (s && *s) {
    k = strlen(s);
    str = malloc(k+1);
    if (str) memcpy(str,s,k);
  } 
  return str;
}

char *val_Sfree(char *s)
{
  free(s);
  return NULL;
}

static int val_cmp(char atype, val_u a, char btype, val_u b)
{
  int ret;
  
  ret = atype - btype;
  if (ret == 0) {
    switch (atype) {
      case '\0': ret = 0;                                          break;
      case 'P' : ret = (char *)(a.p) - (char *)(b.p);              break;
      case 'S' : ret = strcmp(a.s, b.s);                           break;
      case 'N' : ret = a.n - b.n;                                  break;
      case 'U' : ret = (a.u == b.u) ? 0 : ((a.u > b.u) ? 1 : -1);  break;
      case 'F' : ret = (a.f == b.f) ? 0 : ((a.f > b.f) ? 1 : -1);  break;
      
      default  : ret = -1;
    }
  }
  return ret;
}

/* Bernstein hash */
static unsigned long hash_djb(unsigned char *str)
{
  unsigned long hash = 5381;
  while (*str) {
    hash = ((hash << 5) + hash) + *str++; /* hash = hash*33 + c */
  }
  return hash;
}

/* Bernstein hash */
static unsigned long hash_djbL(unsigned char *str, int len)
{
  unsigned long hash = 5381;
  while (len-- > 0) {
    hash = ((hash << 5) + hash) + *str++; /* hash = hash*33 + c */
  }
  return hash;
}

/* Thomas Wang */
static unsigned long hash_num(unsigned long a)
{
    a = (a ^ 61) ^ (a >> 16);
    a =  a + (a << 3);
    a =  a ^ (a >> 4);
    a =  a * 0x27d4eb2d;
    a =  a ^ (a >> 15);
    return a;
}

static unsigned long hash_float(float f)
{
  f = f + 1.0;
  return hash_djbL((unsigned char *)(&f),sizeof(float));  
}

static unsigned long hash_ptr(void *p)
{
  return hash_djbL((unsigned char *)(&p),sizeof(void *));  
}

static long val_hash(char k_type, val_u key)
{
  unsigned long h;
  switch (k_type) {
    case 'N' : h = hash_num((unsigned long)key.n);    break;
    case 'F' : h = hash_float(key.f);                 break;
    case 'S' : h = hash_djb((unsigned char *)key.s);  break;
    default  : h = hash_ptr(key.p);                   break;
  } 
   
  return (long)(h & 0x7FFFFFFF);
}

/******************************************************************/


tbl_t tbl_new(long nslots)
{
  tbl_t tb = NULL;
  long sz;
  
  if (nslots & (nslots - 1)) roundpow2(nslots);
  if (nslots < 2) nslots = 2;
  sz = sizeof(tbl_table_t) + sizeof(tbl_slot_t) * (nslots-1);
  tb = calloc(1, sz);
  if (!tb) utl_outofmem();
  
  tb->count = 0;
  tb->size  = nslots;
  return  tb;
}

#define isemptyslot(sl)    ((sl)->key_type == '\0')
#define setemptyslot(sl)   ((sl)->key_type = '\0')
#define tbl_slot(tb, k)    ((tb)->slot+(k))

#define TBL_SMALL 16
#define tbl_issmall(tb)    (tb->size <= TBL_SMALL)

static tbl_t tbl_compact(tbl_t tb)
{
  tbl_slot_t *slot_top;
  tbl_slot_t *slot_bot;
  
  slot_top = tb->slot;
  slot_bot = tb->slot + tb->size-1;
  
  while (slot_top < slot_bot) {
    while (slot_top < slot_bot &&  isemptyslot(slot_top))
      slot_top++;
    while (slot_top < slot_bot && !isemptyslot(slot_bot))
      slot_bot--;
    if (slot_top < slot_bot) {
      *slot_top = *slot_bot;
      setemptyslot(slot_bot);
      slot_top++;                    
      slot_bot--;                    
    }            
  }
}

tbl_t tbl_rehash(tbl_t tb, long nslots)
{
  tbl_t newtb;
  tbl_slot_t *slot;
  long ndx;
  
  nslots = roundpow2(nslots);
  
  if (!tb) return tbl_new(nslots);
  
  if (tb->count > nslots) return tb;
  
  if (nslots <= TBL_SMALL) { /* It will be a small-table */
  
     /* If it was a hash table compact slots in the upper side */
    if (tb->size > TBL_SMALL) tb = tbl_compact(tb);
      
    /* Now only the first tbl->count slots are filled (and they are less than nslots)*/
    tb = realloc(tb, nslots);
    if (!tb) utl_outofmem();
    
    if (nslots > tb->size) /* clear the newly added elemets */
      memset(tb->slot + tb->size, 0x00, (nslots-tb->size) * sizeof(tbl_slot_t));
      
    tb->size = nslots;
  }
  else { /* create a new table and fill it with existing elements */
    newtb = tbl_new(nslots);
    slot = tb->slot;
    for (ndx = 0; ndx < tb->size; ndx++, slot++) {
      if (!isemptyslot(slot))
        newtb = tbl_set(newtb, slot->key_type, slot->key,
                               slot->val_type, slot->val);
    }
    free(tb);
    tb = newtb;
  }
  return tb;
}


#define maxdist(tb) llog2(tb->size)

#define FIND_NOPLACE    (-1)
#define FIND_CANDIDATE  (-1)
#define FIND_EMPTYPLACE (-2)
#define FIND_FULLTABLE  (-3)

static long tbl_find_small(tbl_t tb, char k_type, val_u key, long *candidate)
{
  tbl_slot_t *slot;
  
  for (slot = tb->slot; slot < tb->slot + tb->count; slot++) {
    if (val_cmp(k_type, key, slot->key_type, slot->key))
      return slot - tb->slot;
  }
  if (tb->count < tb->size) {
    *candidate = tb->count;
    return FIND_EMPTYPLACE;    
  }      
  return FIND_FULLTABLE;
}

#define modsz(t,x) (((x) + (t)->size) % (t)->size)
 
static long tbl_find_hash(tbl_t tb, char k_type, val_u key, long *candidate, unsigned char *distance)
{
  long hk;  
  long h;
  long ndx;
  long d;
  long d_max;
  unsigned char cand_dist;
  tbl_slot_t *slot;
  
  d_max = maxdist(tb);
  
  if (*candidate >= 0) {
    d   = *distance + 1;
    ndx = modsz(tb, *candidate + 1);
    hk  = modsz(tb, ndx - d);
    k_type = '\0'; /* avoid checking for existing key */
  }
  else {
    *distance = d_max-1;  
    hk  = modsz(tb, val_hash(k_type, key));
    ndx = hk;
    d   = 0;
  }
  
  *candidate = -1;
    
  while (d < d_max) {
    slot = tbl_slot(tb, ndx);
    
    if (isemptyslot(slot)) { 
      *distance = d;
      *candidate = ndx;
      return FIND_EMPTYPLACE;
    }
    
    if (modsz(tb, ndx - slot->dist) == hk) { /* same hash!! */
      if (val_cmp(k_type, key, slot->key_type, slot->key)) { /* same value!! */
        *distance = d;
        *candidate = ndx;
        return ndx;
      }
    }
    else if (slot->dist <= *distance) {
      /* TODO: What's the best criteria for selecting candidate?
      **       Currently, the latest slot with lowest distance is selected.
      */
      *candidate = ndx;
      *distance = slot->dist;
    }
    
    ndx = modsz(tb, ndx + 1);
    d++;
  }
  return FIND_NOPLACE; 
}

/*
**   
**
**
**
*/

static long tbl_find(tbl_t tb, char k_type, val_u key, long *candidate, unsigned char *distance)
{
   *candidate = -1;
   *distance  = 0;
         
   if (!tb)  return -1;
   
   if (tb->size <= TBL_SMALL)
     return tbl_find_small(tb, k_type, key, candidate);
     
   return tbl_find_hash(tb, k_type, key, candidate, distance);
}


val_u tbl_get(tbl_t tb, char k_type, val_u key, char v_type, val_u def)
{
  tbl_slot_t *slot;
  long ndx;
  long cand;
  unsigned char dist;
  
  ndx = tbl_find(tb, k_type, key, &cand, &dist);
  
  if (ndx < 0) return def;
  if (tb->slot[ndx].val_type != v_type)  return def;
  
  return (tb->slot[ndx].val);    
}

tbl_t tbl_set(tbl_t tb, char k_type, val_u key, char v_type, val_u val)
{
  long ndx;
  long cand = -1;
  unsigned char dist = 0;
  
  #define swap(x,y,z) (z=x, x=y, y=z)
  val_u tmp_val;
  char  tmp_chr;
  unsigned char tmp_dst;
  
  if (!tb) {
    tb = tbl_new(2);
    tb->slot[0].key_type = k_type;
    tb->slot[0].key = key;
    tb->slot[0].val_type = v_type;
    tb->slot[0].val = val;
    tb->slot[0].dist = 0;
    tb->count++;
    return tb;
  }
  
  for(;;) {
    
    ndx = tbl_find(tb, k_type, key, &cand, &dist);
    
    if (ndx == FIND_EMPTYPLACE) {
      tb->slot[cand].key_type = k_type;
      tb->slot[cand].key      = key;
      tb->slot[cand].val_type = v_type;
      tb->slot[cand].val      = val;
      tb->slot[cand].dist     = dist;
      tb->count++;
      return tb;
    }
    
    if (ndx >= 0) {
      val_del(k_type, key);
      val_del(tb->slot[ndx].val_type, tb->slot[ndx].val);
      
      tb->slot[ndx].val_type = v_type;
      tb->slot[ndx].val      = val;
      return tb;
    }
    
    if (cand >= 0) {
      swap(k_type ,tb->slot[cand].key_type ,tmp_chr);
      swap(key    ,tb->slot[cand].key      ,tmp_val);      
      swap(v_type ,tb->slot[cand].val_type ,tmp_chr);
      swap(val    ,tb->slot[cand].val      ,tmp_val);
      swap(dist   ,tb->slot[cand].dist     ,tmp_dst);      
    }    
    else {
      tb = tbl_rehash(tb, tb->size * 2);
    }
  }
  
  return tb;
}

#if 0
tbl_t tbl_del_small(tbl_t tb, char k_type, val_u key) 
{ 
  tbl_slot_t slot;
  long ndx;
  
  ndx = tbl_find_small(tb,k_type,key);
  if (ndx >= 0) {
    slot = tb->slot[ndx];
    val_del(slot->key_type, slot->key);
    val_del(slot->val_type, slot->val);
    tb->count--;
    if (ndx != tb->count) 
      tb->slot[ndx] = tb->slot[tb->count];
    tb->slot[tb->count].key_type = 0;
  }
   
  return tb;
}


tbl_t tbl_del(tbl_t tb, char tk, val_u key)
{



}
#endif

tbl_t tbl_free(tbl_t tb)
{
  tbl_slot_t *slot;
  long ndx;

  if (tb) {
    for (slot = tb->slot; slot < tb->slot + tb->size; slot++) {
      val_del(slot->key_type, slot->key);
      val_del(slot->val_type, slot->val);
    }
    free(tb);
  }
  return NULL;
}

int main()
{
  int k;
  tbl_t tb;
  
  tblNew(tb);
  
  tblSetNS(tb,32,"hello world!");
  
  tblFree(tb);   
  return 0; 
}
