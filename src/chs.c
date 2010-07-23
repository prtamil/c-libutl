/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This sofwtare is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#include "libutl.h"
#include <ctype.h>


long chsLen(chs_t s)
{
  chs_blk_t *cb;
  long l;
  cb = chs_blk(s);
  l = (s? cb->len  : 0);
  _dbgmsg("CHSLEN: %p %ld\n",s,l);
  return l;
}

chs_t chs_Free(chs_t s)
{
  if (s) free(chs_blk(s));
  return NULL;
}

long chsSize(chs_t s)
{
 return (s ? chs_blk(s)->size : 0);
}


static long fixndx(chs_t s, long n)
{
  _dbgmsg("fixndx: %p  %d -> ",s,n);
  if (s) {
    if (n < 0) n += chsLen(s);
    if (n > chsLen(s)) n = chsLen(s);
  }
  if (n < 0) n = 0;
  _dbgmsg("%d\n",n);
  
  return n;
}

chs_t chs_setsize(chs_t s, long ndx)
{
  long sz;
  chs_blk_t *cb;
  
  cb = s?  chs_blk(s) : NULL;
  sz = cb? cb->size   : 0;
    
  if (ndx >= sz) {
    sz = (ndx / chs_blk_inc) * chs_blk_inc;
    cb = realloc(cb, sizeof(chs_blk_t) + sz);
    if (!cb) utlError(8911,utlErrInternal);
    cb->size = sz + chs_blk_inc;
  }
  if (s == NULL) {  /* created a fresh string */
    cb->len    = 0;
    cb->chs[0] = '\0';
  }
  return cb->chs;  
}

chs_t chs_Set(chs_t s, long ndx, char c)
{
  chs_blk_t *cb;
  
  if (ndx >= chsLen(s)) s = chs_setsize(s,ndx+1);

  s[ndx] = c;
  cb = chs_blk(s);
  
  if (c == '\0') 
    cb->len = ndx;
  else if (ndx >= cb->len)
    cb->len = ndx+1;
    
  s[ndx+1] = '\0';
  _dbgmsg("chs_Set: [%d] = %d\n",ndx,c);
  return s;
}

chs_t chs_SetByte(chs_t s, long ndx, char c)
{
  chs_blk_t *cb;
  
  if (ndx >= chsLen(s)) s = chs_setsize(s,ndx+1);

  s[ndx] = c;
  cb = chs_blk(s);
  
  if (ndx >= cb->len) {
    cb->len = ndx+1;
    s[ndx+1] = '\0';
  }
  return s;
}

char chsChrAt(chs_t s, long ndx)
{
  ndx = fixndx(s,ndx);
  if (s && ndx < chsLen(s)) {
    return s[ndx];
  }
  return '\0';
}

chs_t chs_CpyL(chs_t dst, char *src, long len)
{
  chsSetChr(dst, len, '\0');
  _dbgmsg("chs_Cpy: %p %ld \"%s\"\n",dst, len, src?src:"(null)");
  if (src && len > 0) {
    strncpy(dst, src, len);
  }  
  return dst;
}

chs_t chs_Cpy(chs_t dst, char *src)
{
  if (src) 
    chsCpyL(dst, src, strlen(src));
  return dst;
}


chs_t chs_AddChr(chs_t dst, char c)
{
  long k = chsLen(dst);
  chsSetChr(dst, k+1, '\0');
  dst[k] = c;
  return dst;
}

chs_t chs_AddStrL(chs_t dst, char *src, long len)
{
  long k;
  if (src && *src && len > 0) {
    k = chsLen(dst);
    chsSetChr(dst, k+len, '\0');
    strncpy(dst+k, src, len);
  } 
  return dst;
}

chs_t chs_AddStr(chs_t dst, char *src)
{
  if (src && *src)
    chsAddStrL(dst, src, strlen(src)) ;
  return dst ;
}

chs_t chs_InsChr(chs_t dst, long ndx, char c)
{
  if (!dst) chsNew(dst);
  ndx = fixndx(dst,ndx);
  chsAddChr(dst,c);
  if (ndx < chsLen(dst)-1) 
    memmove(dst+ndx+1, dst+ndx, chsLen(dst)-1 - ndx );
  dst[ndx] = c;
  return dst;
}

chs_t chs_InsStrL(chs_t dst, long ndx, char *src, long len)
{
  long k;
  if (src && len > 0) {
    if (!dst) chsNew(dst);
    ndx = fixndx(dst,ndx);
    if (ndx >= chsLen(dst)) {
      chsAddStrL(dst, src, strlen(src)) ;
    }
    else {
      k = chsLen(dst);
      chsSetChr(dst, chsLen(dst)+len, '\0');
      memmove(dst+ndx+len, dst+ndx, k - ndx );
      strncpy(dst+ndx,src,len);
      /*chs_blk(dst)->len += len;*/
    }
  }
  return dst;
}

chs_t chs_InsStr(chs_t dst, long ndx, char *src)
{
  if (src && *src) {
    chsInsStrL(dst, ndx, src, strlen(src));
  }
  return dst;
}

chs_t chs_Del(chs_t dst, long from, long to)
{
  long len = chsLen(dst);
  if (len > 0) {
    from = fixndx(dst, from);
    to = fixndx(dst, to);
    if (to > len) to = len;
    if (to >= from) { 
      if (to == len) {
        chs_blk(dst)->len -= (to-from);   
      }
      else {
        memmove(dst+from, dst+to+1, len - to);
        chs_blk(dst)->len -= (to+1-from);   
      }
      dst[chs_blk(dst)->len] = '\0';
    }   
  }
  return dst;
}

chs_t chs_Trim(chs_t st,char *left, char *right) 
{
  char *p ;
  
  if (!(st && *st)) return st;
  
  if (right && *right) {
    p = st + chsLen(st);
    while (p > st && strchr(right,*--p)) {
      *p = '\0'; 
      chs_blk(st)->len -= 1;
    }   
  }
  if (left && *left) {
    p = st;
    while (*p && strchr(left,*p)) p++;
    if (p>st) chsDel(st,0,p-st-1);
  }
  return st;
}

chs_t chs_read(chs_t dst, FILE *f, char how, char what)
{
  int k = 0;
  char chs_buf[chs_buf_size];
  
  _dbgmsg("READ = %p,%p,%c,%c\n",dst,f,how,what);

  if (!dst) chsNew(dst);
  else if (tolower((int)how) != 'a')  chsCpy(dst,"") ;
  
  if (what == 'A') { /* read rest of the file */
    while ((k = fread(chs_buf,1,chs_buf_size,f)) > 0) {
      chsAddStrL(dst, chs_buf,k);
      _dbgmsg("READBLK %ld\n",chsLen(dst));
    }
    dst = chs_Set(dst, chsLen(dst), '\0');
  }
  else { /* read line */
    what = '\0';
    while (1) {
      chs_buf[0] = '\0';
      if (!fgets(chs_buf,chs_buf_size,f)  || chs_buf[0] == '\0') break;
      chs_buf[chs_buf_size-1] = '\0';
      k=0;
      while (k < chs_buf_size-1  &&  chs_buf[k]  &&  chs_buf[k] != '\n')
        k++; 
      if (chs_buf[k] == '\0') {
        chsAddStrL(dst, chs_buf,k);
        what = 'L';
        continue;
      } 
      if (chs_buf[k] == '\n') {
        chsAddStrL(dst, chs_buf,k+1);
        break;
      }
      utlError(8313,utlErrInternal);
    }
    if (what == 'L' && chsChrAt(dst,-1) != '\n')
      chsAddChr(dst, '\n');
  }  
  _dbgmsg("READ: [%ld,%p]%s\n",chsLen(dst),dst,dst);
  return dst;
}

pmx_t chsMatch(chs_t s, long from, char *pat)
{
  pmx_t ret;
  int k;
  
  if (!pat || !*pat || !s || chsLen(s) == 0) return NULL;
  from = fixndx(s,from);
  if (from >= chsLen(s)) return NULL;
  
  ret = pmxMatchStr(s+from, pat);
  if (ret) {
    for (k = 0; k<pmxCaptMax; k++) {
      (*ret)[k][0] += from; (*ret)[k][1] += from;
    }
  }
  return ret;
}

chs_t chs_SubFun(chs_t s, long pos, char *pat, chsSubF_t f)
{
  char  *rpl;
  long   l = 0;
  int    repeat = 0;
  int    once = 0;
  pmx_t  ret;
  
  pos = fixndx(s,pos);
  
  if (!s || !*s || !pat || pos >= chsLen(s))
    return s;
    
  while (pat[0] == '&') {
    if (pat[1] == '*') {
      repeat = 1;
      pat += 2;
    }
    else if (pat[1] == 'r') {
      once = 1;
      pat += 2;
    }
    else
      break;
  }
    
  if (!*pat) return s;
    
  while ( pos < chsLen(s)) {
    if ((ret = chsMatch(s, pos, pat))) { 
      pos =  pmxStart(ret,0);
      pmxMatchesPush();
      rpl = f(s,ret);
      pmxMatchesPop();
  
      if (rpl) {
        chsDel(s, pos, pmxEnd(ret,0)-1);
        l = strlen(rpl);
        if (l>0) chsInsStrL(s, pos, rpl, l);
  
        if (repeat) l = 0;
      }
      else
        l = pmxLen(ret,0);
    }
    else l = 1;
    if ( once && l>0) break;
    pos += l;
  } 

  return s;  
}


static char **rpl_arr;
static int    rpl_num;
static chs_t  rpl_chs = NULL;
static char  *rpl_fun(char *mtc, pmx_t cpt)
{
  char *r, *t;
  long l;
  
  chsCpy(rpl_chs, utlEmptyString);
  if (rpl_arr) {
    r = NULL;
    l = pmxMatched(cpt);
    if (l<=rpl_num) r = rpl_arr[l-1];
    if (!r) return NULL;
    while (*r) {
      l = 0;
      t = r;
      while (*t && *t != '&') { t++; l++; }
      chsAddStrL(rpl_chs, r, l);
      if (*t == '&') {
        if (*++t &&  '0' <= *t && *t <= '9') { 
           l = pmxLen(cpt, *t - '0');
           chsAddStrL(rpl_chs, mtc + pmxStart(cpt,*t - '0'), l);
           _dbgmsg("\tlen: %ld %s\n",l,rpl_chs);
        }
        else 
          chsAddChr(rpl_chs, (*t? *t :'&'));
        r = t+1;
      }
      else r=t;
    }
  }
  _dbgmsg("\tret:%s\n",rpl_chs);
  return (char *)rpl_chs;
}

chs_t chs_SubStr(chs_t s, long pos, char *pat, char *rpl)
{ 
  if (rpl) {
    rpl_arr = &rpl;
    rpl_num = 1;
    chsSubFun(s, pos, pat, rpl_fun);
    chsFree(rpl_chs);
  }
  return s;
}

chs_t chs_SubArr(chs_t s, long pos, char *pat, char **arr)
{ 
  if (arr) {
    rpl_arr = arr;
    rpl_num = 0;
    while (arr[rpl_num]) rpl_num++;
    chsSubFun(s, pos, pat, rpl_fun);
    chsFree(rpl_chs);
  }  
  return s;
}

#if 0
static tbl_t rpl_tbl=NULL;

chs_t chs_SubTbl(chs_t s, long pos, char *pat, tbl_t rpl)
{ 
  rpl_tbl = rpl;
  rpl_chs = NULL;
  chsSubFun(s, pos, pat, rpltbl_fun);
  chsFree(rpl_chs);
  
  return s;
}
#endif

