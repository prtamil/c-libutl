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
      return (unsigned short)__builtin_clzl(x);
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

static void tbl_outofmem()
{ 
  if (stderr) fprintf(stderr,"OUT OF MEMORY");
  exit(1);
}

tbl_t tbl_new(long nslots)
{
  tbl_t tb = NULL;
  long sz;
  
  if (nslots & (nslots - 1)) roundpow2(nslots);
  if (nslots < 2) nslots = 2;
  sz = sizeof(tbl_table_t) + sizeof(tbl_slot_t) * (nslots-1);
  tb = calloc(1, sz);
  if (!tb) tbl_outofmem();
  tb->count = 0;
  tb->size  = nslots;
  return  tb;
}

#define tbl_isnotempty(sl) (slot->key_type)
#define tbl_setempty(sl)   (slot->key_type = '\0')
#define tbl_slot(tb,k)     (tb->slot+k)

#define TBL_SMALL 16
#define tbl_issmall(tb) (tb->size <= TBL_SMALL)

tbl_t tbl_reash(tbl_t tb, long size)
{
  tbl_slot_t slot_top;
  tbl_slot_t slot_bot;
  long ndx;
  
  if (tbl->count > size) return tb;
  
  if (size <= TBL_SMALL) {
    /* compact the table in the upper side */
    if (tbl->size > TBL_SMALL) {
      slot_top = tb->slot;
      slot_bot = tb->slot + tb->size-1;
      while (slot_top < slot_bot) {
        while (slot_top < slot_bot && slot_top->key_type != '\0')
          slot_top++;
        while (slot_top < slot_bot && slot_bot->key_type == '\0')
          slot_bot--;
        if (slot_top < slot_bot) {
          *slot_top = *slot_bot;
          *slot_bot->key_type = '\0';
        }            
         *slot_top++;                    
      }
    }
    tb = tbl_realloc(tb,size);
    if (!tb) tbl_outofmem();
    if (size > tb->size) 
      memset(tb->slot + tb->size, 0, (size - tb->size) * sizeof(tbl_slot_t));
    tb->size = size
  }
  else {
    /* HASHTABLE REASH */
  }
  return tb;
}

static tbl_t 
tbl_set_small(tbl_t tb, char k_type, val_u key, char v_type, val_u val)
{
  tbl_slot_t *slot;
  
  slot = tb->slot + tb->count;
  slot->key_type = k_type;
  slot->val_type = v_type;
  slot->key = key;
  slot->val = val;
  tb->count++;
  
  return tb;
}

tbl_t tbl_set(tbl_t tb, char k_type, val_u key, char v_type, val_u val)
{
  if (tb == NULL)  tb = tbl_new();
  
  if (tb->count >= tb->size) tb = tbl_reash(tb,tb_size * 2);

  if (tb->size <= TBL_SMALL) 
    tb = tbl_set_small(tb,k_type,key,v_type,val);
  else 
    tb = tbl_set_hash(tb,k_type,key,v_type,val);
  return tb;
}

long tbl_find_small(tbl_t tb, char k_type, val_u key)
{
  tbl_slot_t *slot;
  long ndx;
  
  if (tb) {
    ndx = 0;
    slot = tb->slot;
    while (ndx< tb->count && slot->key_type) {
      if (val_cmp(k_type, key, slot->key_type, slot->key))
        return ndx;
      ndx++; slot++;
    }
  }
  return -1;
}

val_u tbl_get_small(tbl_t tb, char k_type, val_u key,val_u def)
{
  long ndx;
  ndx = tbl_find_small(tb,k_type,key);
  if (ndx >=0)
    return (tb->slot[ndx].val);
  return def;
}

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

tbl_t tbl_free(tbl_t tb)
{
  tbl_slot_t slot;
  long ndx;

  if (tb) {
    for (ndx = 0; ndx <= tb->size; ndx++) {
      slot = tb->slot[ndx];
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
  tblFree(tb);   
  return 0; 
}
