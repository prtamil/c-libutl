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


#define val_set(x, tv,nv,pv,fv) ((tv == 'N') ? (void)((x).n = (nv)) : \
                                 (tv == 'F') ? (void)((x).f = (fv)) : \
                                               (void)((x).p = (pv))) 

#define val_del(tv,v) do { switch (tv) { \
                             case 'S' : chsFree((v).p); break; \
                             case 'T' : tblFree((v).p); break; \
                             case 'V' : vecFree((v).p); break; \
                             case 'R' : recFree((v).p); break; \
                             case 'P' : (v).p = NULL; \
                             case 'N' : (v).n = 0; \
                             case 'F' : (v).f = 0.0; \
                           }\
                      } while (utlZero)

static int val_cmp(char atype, val_u a, char btype, val_u b)
{
  int ret;
  
  ret = atype - btype;
  if (ret == 0) {
    switch (atype) {
      case 'N' : ret = a.n - b.n;                                  break;
      case 'S' : ret = strcmp(a.p, b.p);                           break;
      case 'F' : ret = (a.f == b.f) ? 0 : ((a.f > b.f) ? 1 : -1);  break;
      case 'R' : ret = recCmp(a.p,b.p);                            break;
      case 'P' :
      case 'T' :
      case 'V' : ret = (char *)(a.p) - (char *)(b.p);              break;
      default  : ret = -1;
    }
  }
  return ret;
}

tbl_t tbl_set(tbl_t tb, char tk, long nkey, void *pkey, float fkey,
                        char tv, long nval, void *pval, float fdef);

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
          val_del(tbl_keytype(cur_slot),cur_slot->key);
          val_del(tbl_valtype(cur_slot),cur_slot->val);
        }
      }
    }  
    free(tb);
  }
  return NULL;
}

#define isnotpow2(x)  ((x) & ((x)-1))

unsigned long keyhash(tbl_t tb, char tk, val_u key)
{
  char  *s;
  float f;
  
  switch (tk) {
    case 'N' : return (hsh_num1(key.n) % tb->size);
    case 'R' : s = recUid(key.p);
               return (hsh_str1(s, strlen(s)) % tb->size);
    case 'F' : f = key.f + 1; /* avoid -0 */
               return (hsh_str1((char *)(&f),sizeof(f))  % tb->size);    
    case 'S' : return (hsh_str1(key.p, strlen(key.p)) % tb->size);
  } 
   
  return (hsh_ptr1(key.p)                % tb->size);
}

static tbl_slot_t *tbl_search(tbl_t tb, char tk, long nkey, void *pkey, float fkey,
                                                              tbl_slot_t **head)
{
  tbl_slot_t *cur_slot;
  val_u key;  
  int cmp;
  unsigned long h;
 
  val_set(key,tk,nkey,pkey,fkey);
  h = keyhash(tb, tk, key);
  cur_slot = tblslot(tb,h); 
  if (head) *head = cur_slot;
  
  if (!properslot(cur_slot)) return NULL;
    
  do {
    cmp = val_cmp(tk, key, tbl_keytype(cur_slot), cur_slot->key);
    
    if (cmp == 0)                 return cur_slot;
    if (linkedslot(cur_slot) < 0) break;
    
    cur_slot = tblslot(tb, linkedslot(cur_slot));
  } while (1); 
   
  return NULL;
}

val_u tbl_get(tbl_t tb, char tk, long nkey, void *pkey, float fkey,
                        char tv, long ndef, void *pdef, float fdef)
{
  tbl_slot_t *cur_slot;
  val_u val;
    
  if (tb) {
    cur_slot = tbl_search(tb,tk,nkey,pkey,fkey,NULL);
    if (cur_slot) return cur_slot->val;
  }
  val_set(val,tv,ndef,pdef,fdef);
  return val; 
}

long tbl_find(tbl_t tb, char tk, long nkey, void *pkey, float fkey)
{
  tbl_slot_t *cur_slot;
 
  cur_slot = tbl_search(tb,tk,nkey,pkey,fkey,NULL);
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
  
  _dbgmsg("SETMAX: %ld -> ",nslots);
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
         tbl_keytype(cur_slot), cur_slot->key.n, cur_slot->key.p, cur_slot->key.f,
         tbl_valtype(cur_slot), cur_slot->val.n, cur_slot->val.p, cur_slot->val.f);
    }
  }
  tb = tbl_free(tb,0);
  return newtb;
}

static tbl_slot_t *nextfreeslot(tbl_t tb, unsigned long h)
{
  tbl_slot_t *free_slot;
  
  do {
    if (++h >= (unsigned long)tb->size) h = 0;
    free_slot = tblslot(tb,h);
  } while (isnotempty(free_slot));

  return free_slot;
}

tbl_t tbl_set(tbl_t tb, char tk, long nkey, void *pkey, float fkey,
                        char tv, long nval, void *pval, float fdef)
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
  tbl_keytype(&ins) = tk; val_set(ins.key,tk,nkey,pkey,fkey); 
  tbl_valtype(&ins) = tv; val_set(ins.val,tv,nval,pval,fdef);
  linkedslot(&ins) = -1;
  properslot(&ins) = 0; 

  cur_slot = tbl_search(tb,tk,nkey,pkey,fkey,&head_slot);

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

tbl_t tbl_del(tbl_t tb, char tk, long nkey, void *pkey, float fkey)
{
  tbl_slot_t *cur_slot, *parent_slot;
  
  cur_slot = tbl_search(tb, tk, nkey, pkey, fkey, &parent_slot);
  
  if (cur_slot) {
    if (cur_slot != parent_slot) {
      while (tblslot(tb, linkedslot(parent_slot)) != cur_slot) 
        parent_slot = tblslot(tb, linkedslot(parent_slot));
      linkedslot(parent_slot) = linkedslot(cur_slot);      
    }
    
    val_del(tbl_keytype(cur_slot),cur_slot->key);
    val_del(tbl_valtype(cur_slot),cur_slot->val);
    
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
    #if defined(__POCC__) || defined(_MSC_VER) || defined (__WATCOMC__)
        /* Pelles C            MS Visual C++         OpenWatcom*/
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

vec_t vec_SetCount(vec_t vt, long max)
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
  vt = vec_SetCount(NULL, nslots);
  vt->count = 0;
  return vt;
}

vec_t vec_set(vec_t vt, long nkey, char tv, long nval, void *pval, float fval)
{
  vec_slot_t *slot;
  
  _dbgmsg("vec_set: %ld %c\n",nkey,tv);
  nkey = fixndx(vt,nkey);
  
  if (!vt || vt->size <= nkey)
    vecSetCount(vt, nkey);
  
  slot = vt->slot + nkey;
  val_del(vec_valtype(slot),slot->val);

  vec_valtype(slot) = tv;
  
  if (tv == 'N') 
    slot->val.n = nval;
  else if (tv == 'F') 
    slot->val.f = fval;
  else
    slot->val.p = pval;
    
  if (nkey >= vt->count) vt->count = nkey+1;
  
  return vt;
}

vec_t vec_ins(vec_t vt, long nkey, char tv, long nval, void *pval, float fval)
{
  vec_slot_t slot;
  int k;
  
  nkey = fixndx(vt,nkey);
  k = vecCount(vt);
  
  if (nkey >= k) 
    return vt = vec_set(vt, nkey, tv, nval, pval,fval);
    
  vt = vec_set(vt, k, tv, nval, pval,fval);
  
  if (nkey < vt->count-1) {
    slot = vt->slot[vt->count-1];
    memmove(vt->slot+nkey+1,vt->slot+nkey,((vt->count-1)-nkey)*sizeof(vec_slot_t));
    vt->slot[nkey] = slot ; 
  }
  
  return vt;
}

val_u vec_get(vec_t vt, long nkey, char tv, long ndef, void *pdef, float fdef)
{
  val_u v;
  
  nkey = fixndx(vt,nkey);
  if (nkey >= vecCount(vt)) {
    if      (tv == 'N') v.n = ndef; 
    else if (tv == 'F') v.f = fdef; 
    else                v.p = pdef;
    return v;
  }
  return vt->slot[nkey].val;
}

vec_t vec_Del(vec_t vt, long kfrom, long kto)
{ 
  int k; 
  vec_slot_t *slot;

  if (!vt || vt->count == 0) return vt;
  
  kfrom = fixndx(vt,kfrom);
  kto = fixndx(vt,kto);
  
  if (kto >= vt->count) kto = vt->count -1;
  if (kfrom >= vt->count || kfrom > kto) return vt;
  
  for (k=kfrom, slot = vt->slot+kfrom; k<=kto; k++, slot++)
    val_del(vec_valtype(slot),slot->val);
  
  if (kto < vt->count-1)
    memmove(vt->slot+kfrom, vt->slot+(kto+1), ((vt->count-1)-kto)*sizeof(vec_slot_t));

  vt->count -= (kto - kfrom) +1;
  return vt;
}

vec_t vec_free(vec_t vt, char wipe)
{
  int k = 0;
  vec_slot_t *slot;

  if (vt) {
    if (wipe) {  
      for (k = 0, slot = vt->slot; k < vt->count; k++, slot++) {
        val_del(vec_valtype(slot),slot->val);
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
       t = vec_set(t, k++, 'S', 0, chsDupL(q, pp-q),0.0);
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
  return val_cmp(vec_valtype(va),va->val,vec_valtype(vb),vb->val);
}



/*****************/
static unsigned char *T1 =
        "\xF2\x47\x6F\xFC\x43\xE1\x54\x31\x7A\x67\xE8\xBE\x92\xF0\x85\xA9"
        "\x87\x34\x7C\xDF\x1E\xB1\xFE\x59\xFF\x7D\xD0\x83\x6E\x12\x3E\x8E"
        "\x22\x91\x81\x58\x86\x93\x30\x6C\x80\x7E\x75\x42\xDA\xF1\x20\xB0"
        "\x37\x6A\xEE\xDC\xED\x04\x38\xE9\x62\x97\xF7\x2F\x17\x0D\x3C\x2D"
        "\x49\xA6\x66\x0F\x5A\xDD\x44\x28\x39\x4E\x8C\xF6\xFD\xD5\xDB\x70"
        "\xEF\xFB\xB6\x63\x77\xD7\xBA\x3D\x36\x95\xB5\x53\x06\x2A\xC9\x9F"
        "\x9C\x6D\x4C\x23\xD1\xC5\x3F\x72\x52\xC7\x48\x8B\x46\xAE\xBB\x33"
        "\xAA\xF5\x05\xC1\x1F\xE4\xCA\x15\xE7\xB9\x9E\xCC\xE3\x71\xB3\x4F"
        "\xFA\xA7\x4B\x79\xA3\x45\xD9\x03\x35\xD6\x0B\xAC\x6B\x5E\x73\xA0"
        "\x41\x74\x10\x64\xA8\x65\x0E\xAF\x8F\x24\x13\x25\x90\x26\x08\x88"
        "\x8D\x5C\xF4\xF9\xEC\x9D\x57\x2E\xE5\x01\xCF\xA1\x5F\x76\x1D\xB2"
        "\x69\x27\xB7\x16\xD2\xB8\xAB\x09\xCE\x2C\xCD\x94\xF3\x14\xE6\x21"
        "\x40\xC2\x18\xF8\xC3\x1B\x7B\x7F\xA4\x9B\x5D\xDE\x98\xE0\x4D\xC4"
        "\x68\x2B\xEA\x8A\xB4\x0C\x19\x84\x32\x11\xC0\xBC\x4A\x3A\x89\xD4"
        "\xD8\x1C\xBD\x51\x00\x29\xA2\xCB\x1A\xD3\x9A\xBF\xC6\xEB\x5B\x78"
        "\x55\x96\x99\xA5\x50\xE2\x61\x60\xC8\x56\x0A\x82\x02\x07\x3B\xAD";

static unsigned char *T2 =
        "\xE9\x43\xDF\x60\x86\x1F\x4B\xBA\x40\xE5\xC4\xA5\x98\xAE\x93\x82"
        "\x0E\x10\x3E\xC1\x35\xA1\x69\xF1\x00\x65\x18\xE7\xA6\xD1\x81\x8D"
        "\x97\xE3\x9B\xFC\xCE\xF5\x1E\xB0\x83\x88\x2D\xC9\xB2\x85\x75\xF9"
        "\x4F\xBE\xB8\x67\xA3\x4A\xCB\xCA\x90\x12\xEA\x8F\x13\x27\x1D\xD2"
        "\x6F\x77\x61\x79\x74\x7C\x9F\x06\x04\x73\x6C\x6A\x0B\x08\xDA\x99"
        "\x51\xD5\x22\xDD\xF4\xCF\xA2\x42\xAA\xAF\x59\xED\x23\xAC\xC2\xDE"
        "\x4E\xA7\x5B\x92\xF0\x84\x02\x07\xCC\xB5\xDB\xFF\xC6\x9E\x7D\xE1"
        "\x58\x49\x1A\xC7\x21\x5C\x39\x94\x9C\xB3\x87\x3A\x11\x72\xFB\xC3"
        "\x2F\x16\xE0\xE6\xBF\x0F\x26\x41\x7F\x6E\x01\x8E\x14\x7B\xF8\x3F"
        "\x64\x57\x62\x55\x80\x76\x96\x25\xD3\x09\x52\x45\xD0\x0C\x4C\x0D"
        "\xF3\xAB\x50\x6D\x4D\xA8\x5E\x78\xF2\x0A\x30\x5F\x8C\xC8\x03\x7A"
        "\x38\xE8\x71\x44\xE2\x95\x1B\x15\xA0\x24\xDC\x19\xEC\x1C\x5A\xA4"
        "\x70\x05\xD9\x33\x28\xF6\xD4\x2C\xF7\xEB\x53\x6B\x56\x3B\xD7\xB1"
        "\x9D\xAD\x31\xBD\xBC\xA9\x5D\x34\x2A\x37\xFD\x3D\x8B\x29\xB7\xEF"
        "\xFE\xC0\x91\x36\xE4\x2E\xB4\xC5\x20\xBB\xCD\x8A\x63\x48\x54\xFA"
        "\x89\x47\x9A\x17\xB9\x46\x68\x3C\xB6\x7E\xEE\xD8\x32\x66\xD6\x2B";


static int tbt_cmp(tbt_node_t *a, tbt_node_t *b)
{
  int ret;
  
  ret = a->pri - b->pri;
  if (ret == 0) {
    ret = val_cmp(tbt_keytype(a),a->key,tbt_keytype(b),b->key);
  }
  return ret;
}

static uint16_t keypri(void *key,int len)
{
  unsigned char *s=key;
  unsigned char pri1=0, pri2=0;
  
  if (len > 0) {
     while (len--) {
       pri1 = T1[*s ^ pri1];
       pri2 = T2[*s ^ pri2];
       s++;
     }
  }
  else {
     while (*s) {
       pri1 = T1[*s ^ pri1];
       pri2 = T2[*s ^ pri2];
       s++;
     }
  }
  return ((pri2<<8) | pri1);
}

static tbt_node_t *tbt_newnode()
{
   tbt_node_t *node;
   
   node = malloc(sizeof(*node));
   if (node) {
     node->left = NULL;
     node->right = NULL;
     tbt_keytype(node) = '\0';
     tbt_valtype(node) = '\0';
   }
   return node;
}

#define tbt_keypri(t,n,p,f) \
  ((t) == 'S'? keypri(p,0) :\
   (t) == 'F'? keypri(&f,sizeof(float)) :\
   (t) == 'N'? keypri(&n,sizeof(int)) :\
   (t) == 'R'? keypri(recUid(p),0) :\
               keypri(&p,sizeof(void *)))

static tbt_node_t *tbt_search(tbt_node_t *tb, char tk, long nkey, void *pkey, float fkey,
                                                              tbt_node_t **parent. int *lr)
{
  int cmp;
  val_u key;
  uint16_t pri;
  tbt_node_t *par;
  
  val_set(key, tk, nkey, pkey, fkey);
  
  pri = tbt_keypri(tk, nkey, pkey, fkey);
  *parent = NULL;  
  while (tb) {
    cmp = tb->pri - pri;
    if (lr) *lr = cmp; 
    if (cmp == 0) 
      cmp = val_cmp(tbt_keytype(tb),tb->key,tk,key);
      
    if (cmp == 0) break;
     
    par = tb;
    tb = (cmp < 0) ? tb->left : tb->right;
  }
  if (parent) *parent = par;
  return tb;
}

val_u tbt_get(tbt_t tb, char tk, long nkey, void *pkey, float fkey,
                        char tv, long ndef, void *pdef, float fdef)
{
  tbt_node_t *cur_node;
  val_u val;
    
  if (tb && tb->root) {
    cur_node = tbt_search(tb->root,tk,nkey,pkey,fkey,NULL,NULL);
    if (cur_node) return cur_node->val;
  }
  val_set(val,tv,ndef,pdef,fdef);
  return val; 
}

tbt_t tbt_set(tbt_t tb, char tk, long nkey, void *pkey, float fkey,
                        char tv, long nval, void *pval, float fdef)
{
  tbt_node_t *curnode, *parent;
  int lr;
  
  if (!tb) tb = tbt_new(); 
  
  curnode = tbt_search(tb->root,tk,nkey,pkey,fkey,&parent,&lr);

  if (curnode) {
  }
  else {
    curnode =  tbt_newnode();
    val_set(curnode->key,tk,nkey,pkey,fkey);
    val_set(curnode->val,tv,nval,pval,fval);    
    if (lr<0) parent->left = curnode;
    else parent->right = curnode;
    tb->count++;
  }
  
  return tb;
}
