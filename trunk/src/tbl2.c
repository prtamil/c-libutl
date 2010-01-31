/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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

  x &= 0xFFFFFFFF;
  
  if (x==0) return 0;
  
  #ifndef UTL_NOASM
    #if defined(__POCC__) || defined(_MSC_VER) || defined (__WATCOMC__)
        /* Pelles C            MS Visual C++         OpenWatcom*/
      __asm { mov eax, [x]
              bsr ecx, eax
              mov  l, ecx
      }
    #elif defined(__GNUC__)
      l = (unsigned short) ((sizeof(long)*8 -1) - __builtin_clzl(x));
    #elif
      #define UTL_NOASM
    #endif  
  #endif
  
  #ifdef UTL_NOASM  /* Make a binary search.*/
    if (x & 0xFFFF0000) {l += 16; x >>= 16;} /* 11111111111111110000000000000000 */
    if (x & 0xFF00)     {l += 8;  x >>= 8 ;} /* 1111111100000000*/
    if (x & 0xF0)       {l += 4;  x >>= 4 ;} /* 11110000*/
    if (x & 0xC)        {l += 2;  x >>= 2 ;} /* 1100 */
    if (x & 2)          {l += 1;  }          /* 10 */
    return l;
  #endif
  
  return (unsigned short)l;
}

unsigned long lsqrt(unsigned long x)
{
  /* lsqrt(x) = 2 ^ (1/2 * lg2(x)) */
  return (x == 0) ? 0 : (1 << (llog2(x) >> 1));
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

#define val_del(tv,v) do { switch (tv) { \
                             case '\0': break; \
                             case 'S' : (v).s = val_Sfree((v).s); break; \
                             case 'P' : (v).p = NULL; break;\
                             case 'N' : (v).n = 0; break; \
                             case 'U' : (v).u = 0; break; \
                             case 'F' : (v).f = 0.0; break; \
                             case 'T' : tblFree((v).p); break; \
                             case 'M' : free((v).p); (v).p = NULL; break;\
                           }\
                      } while (0)

char *val_Sdup(char *s)
{
  char *str = NULL;
  int k;
  if (s) {
    k = strlen(s)+1;
    str = malloc(k);
    if (str) memcpy(str, s, k);
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
      case 'S' : ret = strcmp(a.s, b.s);                           break;
      case 'N' : ret = a.n - b.n;                                  break;
      case 'U' : ret = (a.u == b.u) ? 0 : ((a.u > b.u) ? 1 : -1);  break;
      case 'F' : ret = (a.f == b.f) ? 0 : ((a.f > b.f) ? 1 : -1);  break;
      default  : ret = (char *)(a.p) - (char *)(b.p);              break;
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

static unsigned long hash_num(unsigned long a)
{
   /* Thomas Wang */
  a = ~a + (a << 15); /* a = (a << 15) - a - 1; */
  a =  a ^ (a >> 12);
  a =  a + (a << 2);
  a =  a ^ (a >> 4);
  a =  a * 2057;
  a =  a ^ (a >> 16);
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
    case 'S' : h = hash_djb((unsigned char *)key.s);  break;
    case 'N' : h = hash_num((unsigned long)key.n);    break;
    case 'U' : h = hash_num(key.u);                   break;
    case 'F' : h = hash_float(key.f);                 break;
    default  : h = hash_ptr(key.p);                   break;
  } 
   
  return (long)(h & 0x7FFFFFFF);
}

/******************************************************************/

#define slot_val_type(s) ((s)->info[0])
#define slot_key_type(s) ((s)->info[1])
#define slot_dist(s)     ((s)->info[2])
#define slot_val(s)      ((s)->val)
#define slot_key(s)      ((s)->key)

#define slot_isempty(sl)    (slot_val_type(sl) == '\0')
#define slot_setempty(sl)   (slot_val_type(sl) =  '\0')
#define slot_ptr(tb, k)     ((tb)->slot+(k))

#define TBL_SMALL 4
#define tbl_issmall(tb)    (tb->size <= TBL_SMALL)

#define MAX_DIST(tb) (llog2(tb->size) + 2)

void tbl_print(tbl_t tb)
{
  long ndx;
  tbl_slot_t *slot;
  
  if (!tb) return ;
  
  for (ndx = 0; ndx < tb->size; ndx++) {
    slot = &tb->slot[ndx];
    if (slot_isempty(slot))
      fprintf(stderr,"[%04ld] X X <0,0> (0)\n",ndx);
    else
      fprintf(stderr,"[%04ld] %c %c <%ld,%ld> (%d)\n",ndx, 
                slot_key_type(slot) ? slot_key_type(slot) :'X',
                slot_val_type(slot) ? slot_val_type(slot) :'X',
                slot_key(slot).n,slot_val(slot).n,
                slot_dist(slot));
  }
}


tbl_t tbl_new(long nslots)
{
  tbl_t tb = NULL;
  long sz;
  
  if (nslots & (nslots - 1)) roundpow2(nslots);
  if (nslots < 2) nslots = 2;
  sz = sizeof(tbl_table_t) + sizeof(tbl_slot_t) * (nslots-1);
  tb = calloc(1, sz);
  if (!tb) utl_outofmem();
  
  tb->count    = 0;
  tb->size     = nslots;
  tb->max_dist = MAX_DIST(tb);
  return  tb;
}

static void tbl_compact(tbl_t tb)
{
  tbl_slot_t *slot_top;
  tbl_slot_t *slot_bot;
  
  slot_top = tb->slot;
  slot_bot = tb->slot + tb->size-1;
  
  while (slot_top < slot_bot) {
    while ((slot_top < slot_bot) && !slot_isempty(slot_top))
      slot_top++;
    while ((slot_top < slot_bot) &&  slot_isempty(slot_bot))
      slot_bot--;
    if (slot_top < slot_bot) {
      *slot_top = *slot_bot;
      slot_setempty(slot_bot);
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
  long sz;
  
  if (!tb) return tbl_new(nslots);
  
  /* fprintf(stderr, "REASH: %d/%d\n",tb->count,tb->size);
  tbl_print(tb);
  */
  if (tb->count > nslots) return tb;
  
  if (nslots <= TBL_SMALL) { /* It will be a small-table */
  
     /* If it was a hash table compact slots in the upper side */
    if (tb->size > TBL_SMALL) tbl_compact(tb);
      
    /* Now only the first tbl->count slots are filled (and they are less than nslots)*/
    sz = sizeof(tbl_table_t) + sizeof(tbl_slot_t) * (nslots-1);
    tb = realloc(tb, sz);
    if (!tb) utl_outofmem();
    
    if (nslots > tb->size) /* clear the newly added elemets */
      memset(tb->slot + tb->size, 0x00, (nslots-tb->size) * sizeof(tbl_slot_t));
      
    tb->size     = nslots;
    tb->max_dist = MAX_DIST(tb);
  }
  else { /* create a new table and fill it with existing elements */
    newtb = tbl_new(nslots);
    slot = tb->slot;
    for (ndx = 0; ndx < tb->size; ndx++, slot++) {
      if (!slot_isempty(slot))
        newtb = tbl_set(newtb, slot_key_type(slot), slot_key(slot),
                               slot_val_type(slot), slot_val(slot));
    }
    free(tb);
    tb = newtb;
  }
  return tb;
}

#define FIND_NOPLACE    (-1)
#define FIND_NONE       (-1)
#define FIND_EMPTY      (-2)

static long tbl_search_small(tbl_t tb, char k_type, val_u key, long *candidate)
{
  tbl_slot_t *slot;
  
  for (slot = tb->slot; slot < tb->slot + tb->count; slot++) {
    if (val_cmp(k_type, key, slot_key_type(slot), slot_key(slot)) == 0)
      return slot - tb->slot;
  }
  if (tb->count < tb->size) {
    *candidate =  tb->count ;
    return FIND_EMPTY;
  }
  
  *candidate = FIND_NONE;
  return FIND_NONE;
}

#define modsz(t,x)  (((x) + (t)->size) & ((t)->size - 1))
#define MAX_ATTEMPT 2

static long tbl_search_hash(tbl_t tb, char k_type, val_u key,
                                       long *candidate, unsigned char *distance)
{
  long hk;  
  long ndx;
  long d;
  long d_max;
  tbl_slot_t *slot;
  
  d_max = tb->max_dist;
  
  if (*candidate >= 0) {
    hk  = modsz(tb, *candidate - *distance);
    d   = *distance + 1;
    ndx = modsz(tb, *candidate + 1);
    k_type = '\0'; /* avoid checking for existing key */
  }
  else {
    hk  = modsz(tb, val_hash(k_type, key));
    ndx = hk;
    d   = 0;
  }
  
  *candidate = FIND_NONE;
  *distance = d_max-1;  
    
  while (d < d_max) {
    slot = slot_ptr(tb, ndx);
    
    if (slot_isempty(slot)) { 
      *distance  = d;
      *candidate = ndx;
      return FIND_EMPTY;
    }
    
    if (modsz(tb, ndx - slot_dist(slot)) == hk) { /* same hash!! */
      if (val_cmp(k_type, key, slot_val_type(slot), slot_key(slot)) == 0) { /* same value!! */
        *distance  = d;
        *candidate = ndx;
        return ndx;
      }
    }
    else if (slot_dist(slot) <= *distance) {
      /* TODO: What's the best criteria for selecting candidate?
      **       Currently, the latest slot with lowest distance is selected.
      */
      *distance = d;
      *candidate = ndx;
    }
    
    ndx = modsz(tb, ndx + 1);
    d++;
  }
  if (tb->count >= tb->size)  *candidate = FIND_NONE;
  return FIND_NONE; 
}

static long tbl_search(tbl_t tb, char k_type, val_u key, long *candidate, unsigned char *distance)
{         
   if (!tb)  { *candidate = FIND_NONE;  return FIND_NOPLACE; }
      
   if (tb->size <= TBL_SMALL)
     return tbl_search_small(tb, k_type, key, candidate);
     
   return tbl_search_hash(tb, k_type, key, candidate, distance);
}

val_u tbl_get(tbl_t tb, char k_type, val_u key, char v_type, val_u def)
{
  long ndx;
  long cand = FIND_NONE;
  unsigned char dist = 0;
  
  ndx = tbl_search(tb, k_type, key, &cand, &dist);
  
  if (ndx < 0  || slot_val_type(slot_ptr(tb,ndx)) != v_type)
    return def;
  
  return slot_val(slot_ptr(tb,ndx));    
}

val_u valP(void *val)         {val_u v; v.p = val; return v;}
val_u valS(char *val)         {val_u v; v.s = val; return v;}
val_u valN(long val)          {val_u v; v.n = val; return v;}
val_u valU(unsigned long val) {val_u v; v.u = val; return v;}
val_u valF(float val)         {val_u v; v.f = val; return v;}

tbl_t tbl_set(tbl_t tb, char k_type, val_u key, char v_type, val_u val)
{
  long ndx;
  long cand = FIND_NONE;
  unsigned char dist = 0;
  int attempt;
  tbl_slot_t *slot;
  
  #define swap(x,y,z) (z=x, x=y, y=z)
  val_u tmp_val;
  char  tmp_chr;
  unsigned char tmp_dst;
  
  if (!tb) {
    tb = tbl_new(2);
    slot = slot_ptr(tb,0);
    
    slot_key_type(slot) = k_type;
    slot_key(slot)      = key;
    slot_val_type(slot) = v_type;
    slot_val(slot)      = val;
    slot_dist(slot)     = 0;
    
    tb->count++;
    return tb;
  }
  
  for(attempt = 0; ;attempt++) {
    
    if (attempt >= MAX_ATTEMPT) {
      tb = tbl_rehash(tb, tb->size * 2);
      attempt = 0;
      cand = FIND_NONE;
    }
    
    ndx = tbl_search(tb, k_type, key, &cand, &dist);

    if (ndx >= 0) {
      if (k_type == 'S')  val_del(k_type, key);
      slot = slot_ptr(tb,ndx);
      
      val_del(slot_val_type(slot), slot_val(slot));
      slot_val_type(slot) = v_type;
      slot_val(slot)      = val;      
      
      return tb;
    }
    
    if (ndx == FIND_EMPTY) {
      slot = slot_ptr(tb,cand);
      
      slot_key_type(slot) = k_type;
      slot_key(slot)      = key;
      slot_val_type(slot) = v_type;
      slot_val(slot)      = val;
      slot_dist(slot)     = dist;
      
      tb->count++;
      return tb;
    }
    
    if (cand >= 0 ) {
      slot = slot_ptr(tb,cand);
      
      swap(k_type ,slot_key_type(slot) ,tmp_chr);
      swap(key    ,slot_key(slot)      ,tmp_val);      
      swap(v_type ,slot_val_type(slot) ,tmp_chr);
      swap(val    ,slot_val(slot)      ,tmp_val);
      swap(dist   ,slot_dist(slot)     ,tmp_dst); 
    }
    else 
      attempt = MAX_ATTEMPT;
  }
  
  return tb;
}

static tbl_t fillhole_small(tbl_t tb, long ndx)
{
  if (ndx != tb->count) { 
    tb->slot[ndx] = tb->slot[tb->count];
    slot_setempty(slot_ptr(tb,tb->count));
  }
  return tb;
}

static tbl_t fillhole_hash(tbl_t tb, long ndx)
{
  int d=1;
  long cand;
  
  while (d < tb->max_dist) { 
    cand = modsz(tb,ndx + d);
    if (slot_dist(slot_ptr(tb,cand)) >= d)  {
      tb->slot[ndx] = tb->slot[cand];
      slot_dist(slot_ptr(tb,ndx)) -= d;
      slot_setempty(slot_ptr(tb,cand));
      ndx = cand;
      d = 0;
    }
    d++;
  }
  if (tb->count <= (tb->size / 4))
    tb = tbl_rehash(tb,tb->size / 2);
    
  return tb;
}

tbl_t tbl_del(tbl_t tb, char k_type, val_u key)
{
  tbl_slot_t *slot;
  long ndx;
  long cand = FIND_NONE;
  unsigned char dist = 0;
  
  ndx = tbl_search(tb, k_type, key, &cand, &dist);
  
  if (ndx >= 0) {
    slot = slot_ptr(tb, ndx);
      
    val_del(slot_key_type(slot), slot_key(slot));
    val_del(slot_val_type(slot), slot_val(slot));
    slot_setempty(slot);
    tb->count--;
    if (tb->size <= TBL_SMALL)
      tb = fillhole_small(tb,ndx);   
    else 
      tb = fillhole_hash(tb,ndx); 
  }
  return tb;    
}

tbl_t tbl_free(tbl_t tb)
{
  tbl_slot_t *slot;

  if (tb) {
    for (slot = tb->slot; slot < tb->slot + tb->size; slot++) {
      val_del(slot_key_type(slot), slot_key(slot));
      val_del(slot_val_type(slot), slot_val(slot));
    }
    free(tb);
  }
  return NULL;
}

tblptr_t tblNext(tbl_t tb, tblptr_t ndx)
{  
  while (0 <= ndx && ndx < tb->size) {
    if (slot_key_type(slot_ptr(tb,ndx++)) != '\0') return ndx;
  }
  return (tblptr_t)0;
}

char tblKeyType(tbl_t tb, tblptr_t ndx)
{
   return (0 < ndx && ndx <= tb->size) ? slot_key_type(slot_ptr(tb,ndx-1)) : '\0';
}

char tblValType(tbl_t tb, tblptr_t ndx)
{
   return (0 < ndx && ndx <= tb->size) ? slot_val_type(slot_ptr(tb,ndx-1)) : '\0';
}

val_u tbl_key(tbl_t tb, tblptr_t ndx)
{
  val_u def; def.n = 0;
  return (0 < ndx && ndx <= tb->size) ? slot_key(slot_ptr(tb,ndx-1)) : def;
}

val_u tbl_val(tbl_t tb, tblptr_t ndx)
{
  val_u def; def.n = 0;
  return (0 < ndx && ndx <= tb->size) ? slot_val(slot_ptr(tb,ndx-1)) : def;
}

tblptr_t tbl_find(tbl_t tb, char k_type, val_u key)
{
  tblptr_t ndx;
  long cand = FIND_NONE;
  unsigned char dist = 0;
  
  ndx = tbl_search(tb, k_type, key, &cand, &dist);
  return (ndx < 0 || ndx != cand) ? 0 : ndx +1;  
}


/*******************************************/


vec_t vec_setsize(vec_t vt, long nslots)
{
  long sz;
  
  if (nslots < 2) nslots = 2;
  
  sz = sizeof(vec_vector_t) + sizeof(vec_slot_t) * (nslots-1);
  
  if (!vt) {
    vt = calloc(1,sz);
    if (!vt) utl_outofmem();
    vt->size  = 0;
    vt->count = 0;
    vt->cur   = 0 ;
    return vt;
  }

  vt = realloc(vt,sz);
  if (!vt) utl_outofmem();

  if (nslots > vt->size)
    memset(vt->slot+vt->size, 0, (nslots - vt->size) * sizeof(vec_slot_t));

  vt->size = nslots;
  if (vt->count > vt->size) vt->count = vt->size;

  return vt;
}

vec_t vec_free(vec_t vt)
{
  vec_slot_t *slot;
  long ndx;
  
  if (vt) {
    for (ndx = 0, slot=slot_ptr(vt,0); ndx < vt->size ; ndx++, slot++) {
      val_del(slot_val_type(slot), slot_val(slot));
    }
  }
  free(vt);
  return NULL;  
}

static long fixndx(vec_t vt, long n)
{
  
  if (n < 0 && vt) n += vt->count;
  if (n < 0) n = 0;
  
  return n;
}

long vecSize(vec_t vt)
{
  return vt? vt->size : 0;
}

long vecCount(vec_t vt)
{
  return vt? vt->count : 0;
}
vec_t vec_set(vec_t vt, long ndx, char v_type, val_u val)
{
  long sz;
  vec_slot_t *slot;
  
  ndx = fixndx(vt,ndx);
  
  if ( ndx >= vecSize(vt) )
    vt = vec_setsize( vt, (ndx+1) + lsqrt(ndx+1) );
  
  slot = slot_ptr(vt,ndx);
  slot_val_type(slot) = v_type;
  slot_val(slot)      = val;
 
  if (ndx >= vt->count) vt->count = ndx+1;
  
  return vt;
}

vec_t vec_move(vec_t vt, long from, long to)
{
  long n;
  vec_slot_t *slot_from;
  vec_slot_t *slot_to;
  
  if (vt && vt->count) {
    if (from < vt->count) {
      if (to > from) { /* make room */
        n = vt->count - from;
        if (vt->count + n >= vec->size) {
          vt = vec_setsize(vt, vt->count + n + lsqrt(vt->count+n));
        }
        slot_from = slot_ptr(vt,from);
        memmove(slot_ptr(vt,to), slot_from, n * sizeof(vec_slot_t));
        memset(slot_from, 0, (to-from) * sizeof(vec_slot_t));
      }
      else if (to < from) {
        n = from - to;
        slot_to = slot_ptr(vt,to;
        while (n-- > 0) {
          val_del(slot_val_type(slot_to), slot_val(slot_to));
          slot_to++;
        }
      }
    }
  }  
  return vt;
}

vec_t vec_ins(vec_t vt, long ndx, char v_type, val_u val)
{
  
  vec_slot_t *slot;
  
  ndx = fixndx(vt,ndx);
  
  if (!vt || ndx >= vt->count )
    return vec_set(vt, ndx, v_type, val);
    
  vt = vec_move(vt,ndx,ndx+1);
  
  slot = slot_ptr(vt,ndx);
  
  slot_val_type(slot) = v_type;
  slot_val(slot)      = val;
  
  vt->count++;
  return vt;
}

vec_t vec_del(vec_t vt, long from, long to)
{
  vec_slot_t *slot;
  long sq;
  
  from = fixndx(vt,ndx);
  to = fixndx(vt,to);
  
  if (vt && ndx < vt->count) {
    slot = slot_ptr(vt,ndx);
  
    val_del(slot_val_type(slot), slot_val(slot));
 
    if (ndx < vec->count-1) 
      memmove(slot, slot+1, (vt->count - ndx - 1) * sizeof(vec_slot_t));

    vt->count--:
    sq = lsqrt(vt->size);
    if (vt->count + (2 * sq) < vt->size) 
      vt = vec_setsize(vt, vt->count + sq + 1);
  }
  return vt;  
}

val_u vec_get(vec_t vt, long ndx, char v_type, val_u def)
{
  vec_slot_t *slot;
  
  if (vt) {
    ndx = fixndx(vt,ndx);
    if (ndx < vt->count) {
      slot = slot_ptr(vt,ndx);
      if (slot_val_type(slot) == v_type)
        return slot_val(slot);
    }
  }
  return def;
}


char vecType(vec_t vt, long ndx)
{
  if (!vt || vt->count == 0) return '\0';
  ndx = fixndx(vt,ndx);
  return (ndx < vt->count) ? slot_val_type(slot_ptr(vt,ndx)) : '\0';
}


/*******************************************/

int main()
{
  
  vec_t vt = NULL;
  
  vecSetS(vt,15,"Hi there!");
  vecFree(vt);
  
  
#if 0
  tbl_t tb;
  tblptr_t ndx; 
    
  tblNew(tb);
  
  tblSetNN(tb,101,201);
  tblSetNN(tb,102,202);
  tblSetNN(tb,103,203);
  tblSetNN(tb,104,204);
  
  tblSetNN(tb,555,205);
  tblSetNN(tb,666,206);
  
  ndx = tblFindN(tb,104);
  if (ndx) printf("found: %c\n",tblKeyType(tb,ndx));  
  else printf("not found\n");  
    
  ndx = tblFindN(tb,109);
  if (ndx) printf("found: %c\n",tblKeyType(tb,ndx));  
  else printf("not found\n");  
    
  tbl_print(tb);  

  tblDelN(tb,101);
  tbl_print(tb);  

  tblDelN(tb,103);
  tbl_print(tb);
    
  tblDelN(tb,104);
  tbl_print(tb);  

  tblDelN(tb,555);
  tbl_print(tb);
    
#if 0
  for (k=0; k< 120; k++)  
    tblSetNN(tb,k,-k);
  
  tbl_print(tb);  
  for (k=0; k< 120; k++)  
    if (tblGetNN(tb,k,k+1) != -k) 
      fprintf(stderr,"ARGH: %d\n",k);
#endif
      
  tblFree(tb);   
#endif

  return 0; 
}
