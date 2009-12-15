/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This sofwtare is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#include "libutl.h"
#include <assert.h> 

long tbl_i;

static unsigned long hsh_num1(unsigned long a);
static unsigned long hsh_str1(const void *data, int len);
static unsigned long hsh_ptr1(void *p);
#if 0
static unsigned long hsh_num2(unsigned long a);
static unsigned long hsh_str2(const void *data, int len);
static unsigned long hsh_ptr2(void *p);
#endif 
static unsigned short llog2(unsigned long x);


#define tblslot(tb,n)   ((tb)->slot + n)
#define slotpos(tb,sl)  (sl - (tb)->slot) 

#define properslot(sl)  ((sl)->flg[3])
#define linkedslot(sl)  ((sl)->aux.n)
#define isnotempty(sl)  tbl_keytype(sl)


tbl_t tbl_set(tbl_t tb, char tk, long nkey, void *pkey,
                        char tv, long nval, void *pval);

tbl_t tbl_new(long nslots)
{
  tbl_t tb;
  
  if (nslots < 2) nslots = 2;

  tb = calloc(1, sizeof(*tb) + (sizeof(tbl_slot_t)*(nslots-1)));
  
  if (!tb)  utlError(6911,utlErrInternal);
  
  tb->count  = 0;
  tb->size = nslots;
  tb->cur = 0;
  return tb;
}

tbl_t tbl_free(tbl_t tb, char wipe)
{
  tbl_slot_t *cur_slot;
  int k;
  if (tb) {
    cur_slot = tb->slot;
    if (wipe) {  
      for (k = 0; k< tb->size; k++, cur_slot++) {
        if (isnotempty(cur_slot)) {
          if (tbl_keytype(cur_slot) == 'S') chsFree(cur_slot->key.p);
          else if (tbl_keytype(cur_slot) == 'T') tblFree(cur_slot->key.p);
          if (tbl_valtype(cur_slot) == 'S') chsFree(cur_slot->val.p);
          else if (tbl_valtype(cur_slot) == 'T') tblFree(cur_slot->val.p);
        }
      }
    }  
    free(tb);
  }
  return NULL;
}

static int tblcmp(char atype, val_u a, char btype, val_u b)
{
  int ret;
  
  ret = atype - btype;
  if (ret == 0) {
    switch (atype) {
      case 'N' : ret = a.n - b.n; break;
      case 'S' : ret = strcmp(a.p, b.p); break;
      case 'P' :
      case 'T' : ret = (char *)(a.p) - (char *)(b.p); break;
      default  : ret = -1;
    }
  }
  return ret;
}

#define val_set(x, tv,nv,pv) ((tv == 'N') \
                                  ? (void)((x).n = (nv)) \
                                  : (void)((x).p = (pv))) 

#define val_del(tv,v) do { switch (tv) { \
                             case 'S' : chsFree((v).p); break; \
                             case 'T' : tblFree((v).p); break; \
                             case 'V' : vecFree((v).p); break; \
                             case 'P' : (v).p = NULL; \
                             case 'N' : (v).n = 0; \
                           }\
                      } while (utlZero)

#define isnotpow2(x)  ((x) & ((x)-1))

unsigned long keyhash(tbl_t tb, char tk, val_u key)
{
  switch (tk) {
    case 'N' : return (hsh_num1(key.n) % tb->size);
    
    case 'S' : return (hsh_str1(key.p, strlen(key.p)) % tb->size);
  } 
   
  return (hsh_ptr1(key.p)                % tb->size);
}

static tbl_slot_t *tbl_search(tbl_t tb, char tk, long nkey, void *pkey,
                                                              tbl_slot_t **head)
{
  tbl_slot_t *cur_slot;
  val_u key;  
  int cmp;
  unsigned long h;
 
  val_set(key,tk,nkey,pkey);
  h = keyhash(tb, tk, key);
  cur_slot = tblslot(tb,h); 
  if (head) *head = cur_slot;
  
  if (!properslot(cur_slot)) return NULL;
    
  do {
    cmp = tblcmp(tk, key, tbl_keytype(cur_slot), cur_slot->key);
    
    if (cmp == 0)                 return cur_slot;
    if (linkedslot(cur_slot) < 0) break;
    
    cur_slot = tblslot(tb, linkedslot(cur_slot));
  } while (1); 
   
  return NULL;
}

val_u tbl_get(tbl_t tb, char tk, long nkey, void *pkey,
                        char tv, long ndef, void *pdef)
{
  tbl_slot_t *cur_slot;
  val_u val;
    
  if (tb) {
    cur_slot = tbl_search(tb,tk,nkey,pkey,NULL);
    if (cur_slot) return cur_slot->val;
  }
  val_set(val,tv,ndef,pdef);
  return val; 
}

long tbl_find(tbl_t tb, char tk, long nkey, void *pkey)
{
  tbl_slot_t *cur_slot;
 
  cur_slot = tbl_search(tb,tk,nkey,pkey,NULL);
  if (cur_slot) return slotpos(tb,cur_slot)+1;
  
  return 0; 
}

long tblNext(tbl_t tb, long cur)
{
  if (cur >= 0) {
    while (cur < tb->size) {
      if (isnotempty(tb->slot + cur++)) return cur;
    } 
  }
  return -1; 
}

#define two_raised(n) (1<<(n))
#define div_by_two(n) ((n)>>1)
                
tbl_t tbl_MaxSlot(tbl_t tb, long nslots)
{
  unsigned short lg;
  long n;
  tbl_t tt;
  
  dbgmsg("SETMAX: %ld -> ",nslots);
  if (nslots < 4) nslots = 4;
  lg = two_raised(llog2(nslots));
  
  n = (3 * lg) / 2;
  if (n < nslots) n = lg * 2;
  
  _dbgmsg("Actually: %ld (%ld)\n",n,lg);
  
  if (n <= tb->size) return tb;
  
  tt = realloc(tb,sizeof(*tb) + (sizeof(tbl_slot_t)*(n-1)));
  if (!tt) return tb;
  
  memset(tt->slot + tt->size, 0, (n - tt->size) * sizeof(tbl_slot_t));
  
  tt->size = n; 
  return tt; 
}
                        
static tbl_t rehash(tbl_t tb, char resize)
{
  tbl_t newtb;
  tbl_slot_t *cur_slot;
  long k;
  long sz;
  
  sz = tb->size;
  
  if (resize == '+') { /* Expand */ 
    sz = isnotpow2(sz) ? ((sz / 3) * 4) : ((sz / 2) * 3);
  }
  else if (resize == '-') { /* Shrink */
    sz = isnotpow2(sz) ? (sz / 3) : (sz / 2);
  } 
  else return tb;
  
  if (sz < 4) sz = 4;
  if (sz <= tb->count) return tb; 
  
  newtb = tbl_new(sz);
    
  _dbgmsg("REHASH: %d -> %d\n",tb->size,newtb->size);

  cur_slot = tb->slot;
  for (k = 0; k < tb->size; k++, cur_slot++) {
    if (isnotempty(cur_slot)) {
      newtb = tbl_set(newtb, 
         tbl_keytype(cur_slot), cur_slot->key.n, cur_slot->key.p,
         tbl_valtype(cur_slot), cur_slot->val.n, cur_slot->val.p);
    }
  }
  tb = tbl_free(tb,0);
  return newtb;
}

static tbl_slot_t *nextfreeslot(tbl_t tb, unsigned long h)
{
  tbl_slot_t *free_slot;
  
  do {
    if (++h >= tb->size) h = 0;
    free_slot = tblslot(tb,h);
  } while (isnotempty(free_slot));

  return free_slot;
}

tbl_t tbl_set(tbl_t tb, char tk, long nkey, void *pkey,
                        char tv, long nval, void *pval)
{
  tbl_slot_t *cur_slot, *head_slot;
  tbl_slot_t *new_slot, *parent_slot;
  tbl_slot_t  ins;
  unsigned long h;
  
  if (!tb)
    tb = tbl_new(4); 
  
  /* limit load factor to max 75% */
  if (tb->count >= ((tb->size * 3) / 4) )  
    tb = rehash(tb,'+');
  
  _dbgmsg("TBL SET: T[%c %ld %p] = (%c %ld %p)\n",tk, nkey,pkey,tv,nval,pval);
  tbl_keytype(&ins) = tk; val_set(ins.key,tk,nkey,pkey); 
  tbl_valtype(&ins) = tv; val_set(ins.val,tv,nval,pval);
  linkedslot(&ins) = -1;
  properslot(&ins) = 0; 

  cur_slot = tbl_search(tb,tk,nkey,pkey,&head_slot);

  if (cur_slot) {                      /* Key already present: replace value */
    if (tbl_keytype(&ins) == 'S')
      chsFree(ins.key.p);
    if (tbl_valtype(cur_slot) == 'S' && (tv != 'S' || cur_slot->val.p != pval)) 
      chsFree(cur_slot->val.p);
    tbl_valtype(cur_slot) = tbl_valtype(&ins);
    cur_slot->val = ins.val;
    tb->count--; /* Not a new element */                
  }
  
  else if (!isnotempty(head_slot)) {                /* An empty slot: insert */
    properslot(&ins) = 1; 
   *head_slot = ins;
  }

  else if (properslot(head_slot)) { /* A true collision: append to the chain */
    new_slot = nextfreeslot(tb,slotpos(tb, head_slot));
   *new_slot = ins;
    linkedslot(new_slot) = linkedslot(head_slot);      
    linkedslot(head_slot) = slotpos(tb, new_slot);      
  }
  
  else  {   /* Slot used by another chain: move it somewhere else and insert */
    new_slot = nextfreeslot(tb,slotpos(tb, head_slot));
   *new_slot = *head_slot;

    /* restore the link */      
    h = keyhash(tb, tbl_keytype(head_slot), head_slot->key);
    parent_slot = tblslot(tb, h);
    while (tblslot(tb, linkedslot(parent_slot)) != head_slot) 
      parent_slot = tblslot(tb, linkedslot(parent_slot));
    linkedslot(parent_slot) = slotpos(tb, new_slot);

    properslot(&ins) = 1; 
   *head_slot = ins;   
  }
  
  tb->count++;
  return tb;
}

tbl_t tbl_del(tbl_t tb, char tk, long nkey, void *pkey)
{
  tbl_slot_t *cur_slot, *parent_slot;
  
  cur_slot = tbl_search(tb, tk, nkey, pkey, &parent_slot);
  
  if (cur_slot) {
    if (cur_slot != parent_slot) {
      while (tblslot(tb, linkedslot(parent_slot)) != cur_slot) 
        parent_slot = tblslot(tb, linkedslot(parent_slot));
      linkedslot(parent_slot) = linkedslot(cur_slot);      
    }
    
    val_del(tbl_keytype(cur_slot),cur_slot->key);
/*
    switch (tbl_keytype(cur_slot)) {
      case 'S' : chsFree(cur_slot->key.p); break;
      case 'T' : tblFree(cur_slot->key.p); break;
      case 'V' : vecFree(cur_slot->key.p); break;
    }
*/    
    val_del(tbl_valtype(cur_slot),cur_slot->val);
/*    
    switch (tbl_valtype(cur_slot)) {
      case 'S' : chsFree(cur_slot->val.p); break;
      case 'T' : tblFree(cur_slot->val.p); break;
      case 'V' : vecFree(cur_slot->val.p); break;
    }
*/
    isnotempty(cur_slot) = 0;
    properslot(cur_slot) = 0;
    
    tb->count--;
  }
   
  return tb;
}

/** HASH FUNCTIONS *******************/

/*
** by Paul Hsie
*/
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const unsigned short *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((unsigned long)(((const unsigned char *)(d))[1])) << 8)\
                       +(unsigned long)(((const unsigned char *)(d))[0]) )
#endif

static unsigned long SuperFastHash (const char *data, int len, unsigned long hash)
{
unsigned long tmp;
int rem;

    if (data == NULL) return 1;
    if (len <= 0)     return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (;len > 0; len--) {
        hash  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        data  += 2*sizeof (unsigned short);
        hash  += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
        case 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= data[sizeof (unsigned short)] << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += *data;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;
    
    return hash;
}

/*
** by Bob Jenkins 
*/
static unsigned long hsh_num1 ( unsigned long a)
{
    a = (a+0x7ed55d16) + (a<<12);
    a = (a^0xc761c23c) ^ (a>>19);
    a = (a+0x165667b1) + (a<<5);
    a = (a+0xd3a2646c) ^ (a<<9);
    a = (a+0xfd7046c5) + (a<<3);
    a = (a^0xb55a4f09) ^ (a>>16);
    return a;
}

#if 0
/*
** by Thomas Wang
*/
static unsigned long hsh_num2( unsigned long a)
{
    a = (a ^ 61) ^ (a >> 16);
    a =  a + (a << 3);
    a =  a ^ (a >> 4);
    a =  a * 0x27d4eb2d;
    a =  a ^ (a >> 15);
    return a;
}
#endif 

/*********/
static unsigned long hsh_str1(const void *data, int len)
{
  return SuperFastHash(data, len, 0x165667b1);
} 
#if 0
static unsigned long hsh_str2(const void *data, int len)
{
  return SuperFastHash(data, len, 0x27d4eb2d);
} 
#endif

static unsigned long hsh_ptr1(void *p)
{
  return hsh_num1((unsigned long)p);
}

#if 0
static unsigned long hsh_ptr2(void *p)
{
  return hsh_num2((unsigned long)p);
}
#endif
/************************/

/*
** Integer log base 2 of uint32 integer values.
**   llog2(0) == llog2(1) == 0
*/
static unsigned short llog2(unsigned long x)
{
  long l;

  l=0;

  #ifndef UTL_NOASM   /* Use inline assembly instructions! */
    #if defined(__POCC__) || defined(_MSC_VER)
      /* Pelles C & MS Visual C++*/
      __asm { mov eax, [x]
              cmp eax, 0
              je  z
              bsr ecx, eax
              mov  l, ecx
         z:
      }
    #elif defined(__GNUC__)
      /* GCC */
      __asm__( "bsrl %1,%0" :"=r" (l) :"r" (x));
    #else
      /* fallback to the C version */
      #define UTL_NOASM
    #endif
  #endif

  #ifdef UTL_NOASM  /* Make a binary search.*/
  _dbgmsg("Standard llog\n");
  if (x & 0xFFFF0000) {l += 16; x >>= 16;} /* 11111111111111110000000000000000 */
  if (x & 0xFF00)     {l += 8;  x >>= 8 ;} /* 1111111100000000*/
  if (x & 0xF0)       {l += 4;  x >>= 4 ;} /* 11110000*/
  if (x & 0xC)        {l += 2;  x >>= 2 ;} /* 1100 */
  if (x & 2)          {l += 1;  }          /* 10 */
  #endif

  return (unsigned short)l;
}

/** VEC *********************/

vec_t vec_tmp;


long vecCount(vec_t vt)
{
  return (vt ? vt->count: 0);
}

static long fixndx(vec_t s, long n)
{
  if (n < 0) n += vecCount(s);
  if (n < 0) n = 0;
  
  return n;
}

vec_t vecSetCount(vec_t vt, long max)
{
  long nslots;
  unsigned long lg;
  long sz = vecCount(vt);
  
  if (max < 2)
    nslots = 2;
  else {
    lg = two_raised(llog2(max));  
    nslots = (3 * lg) / 2;
    if (nslots <= max) nslots = lg * 2;
  }
  
  vt = realloc(vt,sizeof(*vt) + (sizeof(vec_slot_t)*(nslots-1)));
  if (!vt)  utlError(6815,utlErrInternal);
  if (nslots > sz) {
    memset(vt->slot+sz, 0, (nslots-sz)*sizeof(vec_slot_t));
  }
  
  vt->size = nslots;
  vt->count = max;
  vt->cur = 0;
  
  return vt;
}

vec_t vec_new(long nslots)
{ 
  vec_t vt;
  vt = vecSetCount(NULL, nslots);
  vt->count = 0;
  return vt;
}

vec_t vec_set(vec_t vt, long nkey, char tv, long nval, void *pval)
{
  vec_slot_t *slot;
  
  _dbgmsg("vec_set: %ld %c\n",nkey,tv);
  nkey = fixndx(vt,nkey);
  
  if (!vt || vt->size <= nkey)
    vt = vecSetCount(vt, nkey);
  
  slot = vt->slot + nkey;
  vec_valtype(slot) = tv;
  if (tv == 'N') 
    slot->val.n = nval;
  else
    slot->val.p = pval;
    
  if (nkey >= vt->count) vt->count = nkey+1;
  
  return vt;
}

vec_t vec_ins(vec_t vt, long nkey, char tv, long nval, void *pval)
{
  vec_slot_t slot;
  int k;
  
  nkey = fixndx(vt,nkey);
  k = vecCount(vt);
  
  if (nkey >= k) 
    return vt = vec_set(vt, nkey, tv, nval, pval);
    
  vt = vec_set(vt, k, tv, nval, pval);
  
  if (nkey < vt->count-1) {
    slot = vt->slot[vt->count-1];
    memmove(vt->slot+nkey+1,vt->slot+nkey,((vt->count-1)-nkey)*sizeof(vec_slot_t));
    vt->slot[nkey] = slot ; 
  }
  
  return vt;
}

val_u vec_get(vec_t vt, long nkey, char tv, long ndef, void *pdef)
{
  val_u v;
  
  nkey = fixndx(vt,nkey);
  if (nkey >= vecCount(vt)) {
    if (tv == 'N') v.n = ndef; 
    else           v.p = pdef;
    return v;
  }
  return vt->slot[nkey].val;
}

vec_t vecDel(vec_t vt, long kfrom, long kto)
{  
  if (!vt || vt->count == 0) return vt;
  
  kfrom = fixndx(vt,kfrom);
  kto = fixndx(vt,kto);
  
  if (kto >= vt->count) kto = vt->count -1;
  if (kfrom >= vt->count || kfrom > kto) return vt;
  
  val_del(vec_valtype(vt->slot+kfrom),vt->slot[kfrom].val);
/*
  switch(vec_valtype(vt->slot+kfrom)) {
    case 'S': chsFree(vt->slot[kfrom].val.p); break;
    case 'T': tblFree(vt->slot[kfrom].val.p); break;
    case 'V': vecFree(vt->slot[kfrom].val.p); break;
  }
*/  
  if (kto < vt->count-1)
    memmove(vt->slot+kfrom, vt->slot+(kto+1), ((vt->count-1)-kto)*sizeof(vec_slot_t));

  vt->count -= (kto - kfrom) +1;
  return vt;
}

vec_t vec_free(vec_t vt, char wipe)
{
  int k = 0;

  if (vt) {
    if (wipe) {  
      for (k = 0; k < vt->count; k++) {
        switch(vec_valtype(vt->slot+k)) {
          case 'S': chsFree(vt->slot[k].val.p);  break;
          case 'T': tblFree(vt->slot[k].val.p);  break;
          case 'V': vecFree(vt->slot[k].val.p);  break;
        }
      }
    }  
    free(vt);
  }
  return NULL;
}


vec_t vecMove(vec_t vt, long kfrom, long kto)
{
  vec_slot_t slot;
  
  if (vecCount(vt) < 2) return vt;
  
  kfrom = fixndx(vt,kfrom);
  kto = fixndx(vt,kto);
  
  if (kfrom == kto) return vt;
  
  slot = vt->slot[kfrom];

  if (kfrom > kto) {
    memmove(vt->slot+(kto+1), vt->slot+kto, (kfrom-kto)*sizeof(vec_slot_t));  
  }
  else { /* kto > kfrom */
    memmove(vt->slot+kfrom, vt->slot+(kfrom+1), (kto-kfrom)*sizeof(vec_slot_t));  
  }
  vt->slot[kto] = slot;
  return vt;
}

vec_t vec_split(char *s, char *sep,char *trim, int dup)
{
   char *p,*q,*pp;
   vec_t t = NULL;
   int k = 0;
   
   if (!s || !*s) return t;
 
   p = s; 
   while (*p) {
     if (trim)
       while (strchr(trim,*p)) ++p;
     q = p;
     while (*p && !strchr(sep,*p)) ++p;
     pp = p;
     if (trim)
       while (pp > q  &&  strchr(trim,pp[-1])) --pp;
       
     if (dup) {
       t = vec_set(t, k++, 'S', 0, chsDupL(q, pp-q));
       /*fprintf(stderr,"[%s]\n",vecGetS(t,k-1,"??"));*/
     }
     else {
       vecSetP(t, k++, q);
       vecSetP(t, k++, pp);
     }
     
     if (*p) p++;
   }
    
   return t;  
}

int vec_cmp (const void *a, const void *b)
{
  const vec_slot_t *va = a;
  const vec_slot_t *vb = b;
 
  int c;
  
  _dbgmsg("CMP: %c %c\n",vec_valtype(va) , vec_valtype(vb));
  c = vec_valtype(va) - vec_valtype(vb);
  
  if (c != 0) return c;
  
  switch(vec_valtype(va)) {
    case 'N' : return (va->val.n - vb->val.n);
    case 'S' : _dbgmsg("[%s],[%s]\n",va->val.p, vb->val.p);
               return strcmp(va->val.p, vb->val.p);
  }
  return ((char *)(va->val.p) - (char *)(vb->val.p));
}



/*****************/
