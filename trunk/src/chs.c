/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This sofwtare is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#include "libutl.h"
#include <ctype.h>

chs_blk_t *chs_blk_;
chs_t   chs_tmp_;

char chs_buf[chs_buf_size];

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

static chs_t chs_setsize(chs_t s, long ndx)
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
    cb->cur    = 0;
    cb->len    = 0;
    cb->chs[0] = '\0';
  }
  return cb->chs;  
}

chs_t chsNew()
{
  return chs_setsize(NULL,0);
}

chs_t chsSet(chs_t s, long ndx, char c)
{
  chs_blk_t *cb;

  s = chs_setsize(s,ndx+1);
  s[ndx] = c;
  cb = chs_blk(s);
  cb->cur = ndx;
  
  if (c == '\0') 
    cb->len = ndx;
  else if (ndx >= cb->len)
    cb->len = ndx+1;
    
  s[ndx+1] = '\0';
  _dbgmsg("chsSet: [%d] = %d\n",ndx,c);
  return s;
}

char chsChrAt(chs_t s, long ndx)
{
  ndx = fixndx(s,ndx);
  if (s && ndx < chsLen(s)) {
    chs_blk(s)->cur = ndx+1;
    return s[ndx];
  }
  return '\0';
}

int chsGetChr(chs_t s)
{
  chs_blk_t *cb;
  
  if (!s) return EOF;

  cb = chs_blk(s);

  if (cb->cur == EOF) return EOF;
  if (cb->cur >= cb->len) return (cb->cur = EOF);
  return s[cb->cur++];  
}

int chsEof(chs_t s)
{
  return (s? chs_blk(s)->cur == EOF : 1);
}

int chsSeek(chs_t dst, long pos, int whence)
{
  if (dst) {
    switch (whence) {
      case SEEK_END : pos += chsLen(dst); break;
      case SEEK_CUR : pos += chsCur(dst) ; break; 
      case SEEK_SET : 
           default  : break;
    }
    _dbgmsg("\tpos:%d\n",pos);
    if (pos > chsLen(dst)) pos = chsLen(dst);
    if (pos < 0) pos = 0;
    chs_blk(dst)->cur = pos;
  }
  return 0;
}

size_t chsTell(chs_t dst)
{
  return (size_t)chsCur(dst);
}

chs_t chsCpyL(chs_t dst, char *src, long len)
{
  dst = chsSet(dst, len, '\0');
  if (src && len > 0) {
    _dbgmsg("chsCpy: %d \"%s\"\n",len, src);
    strncpy(dst, src, len);
  }  
  chs_blk(dst)->cur = len; 
  return dst;
}

chs_t chsCpy(chs_t dst, char *src)
{
  if (src) 
    dst = chsCpyL(dst, src, strlen(src));
  return dst;
}

chs_t chsDup(char *src)
{
  chs_t dst = NULL; 
  if (src) {
    dst = chsCpyL(chsNew(), src, strlen(src));
  }
  return dst;
}

chs_t chsAddChr(chs_t dst, char c)
{
  long k = chsLen(dst);
  dst = chsSet(dst, k+1, '\0');
  dst[k] = c;
  chs_blk(dst)->cur = k+1;
  return dst;
}

chs_t chsAddStrL(chs_t dst, char *src, long len)
{
  long k;
  if (src && *src && len > 0) {
    k = chsLen(dst);
    dst = chsSet(dst, k+len, '\0');
    strncpy(dst+k, src, len);
    chs_blk(dst)->cur = chs_blk(dst)->len;
  } 
  return dst;
}

chs_t chsAddStr(chs_t dst, char *src)
{
  if (src && *src)
    dst = chsAddStrL(dst, src, strlen(src)) ;
  return dst ;
}

chs_t chsInsChr(chs_t dst, long ndx, char c)
{
  if (!dst) dst=chsNew();
  ndx = fixndx(dst,ndx);
  dst = chsAddChr(dst,c);
  if (ndx < chsLen(dst)-1) 
    memmove(dst+ndx+1, dst+ndx, chsLen(dst)-1 - ndx );
  dst[ndx] = c;
  chs_blk(dst)->cur = ndx+1;
  return dst;
}

chs_t chsInsStrL(chs_t dst, long ndx, char *src, long len)
{
  long k;
  if (src && len > 0) {
    if (!dst) dst=chsNew();
    ndx = fixndx(dst,ndx);
    if (ndx >= chsLen(dst)) {
      dst = chsAddStrL(dst, src, strlen(src)) ;
    }
    else {
      k = chsLen(dst);
      dst = chsSet(dst, chsLen(dst)+len, '\0');
      memmove(dst+ndx+len, dst+ndx, k - ndx );
      strncpy(dst+ndx,src,len);
      /*chs_blk(dst)->len += len;*/
      chs_blk(dst)->cur = ndx+len;
    }
  }
  return dst;
}

chs_t chsInsStr(chs_t dst, long ndx, char *src)
{
  if (src && *src) {
    dst = chsInsStrL(dst, ndx, src, strlen(src));
  }
  return dst;
}

chs_t chsDel(chs_t dst, long from, long to)
{
  if (dst) {
    from = fixndx(dst, from);
    to = fixndx(dst, to);
    if (from == 0 && to >= chsLen(dst)) {
      chs_blk(dst)->len = 0;   
      chs_blk(dst)->cur = 0;   
    }
    else if (to >= from) {
      memmove(dst+from, dst+to+1, chsLen(dst) - to);
      chs_blk(dst)->len -= (to+1 - from);   
      chs_blk(dst)->cur  = from;   
    }
  }
  return dst;
}

chs_t chs_read(chs_t dst, FILE *f, char how, char what)
{
  int k = chs_buf_size;
  
  _dbgmsg("READ = %p,%p,%c,%c",dst,f,how,what);

  if (!dst) dst=chsNew();

  if (tolower(how) != 'a') 
    chs_blk(dst)->len = 0 ;
       
  chs_blk(dst)->cur = chs_blk(dst)->len ;
  
  if (what == 'A') { /* read rest of the file */
    while ((k = fread(chs_buf,1,chs_buf_size,f)) > 0) {
      dst = chsAddStrL(dst, chs_buf,k);
      _dbgmsg("READBLK %d\n",chsLen(dst));
    }
//    dst = chsSet(dst, chsLen(dst), '\0');
  }
  else { /* read line */
    what = '\0';
    while (1) {
      chs_buf[0]='\0';
      if (!fgets(chs_buf,chs_buf_size,f)  ||  chs_buf[0] == '\0') break;
      k=0;
      while (k < chs_buf_size  &&  chs_buf[k]  &&  chs_buf[k] != '\n')
        k++; 
      if (chs_buf[k] == '\0') {
        dst = chsAddStrL(dst, chs_buf,k);
        what = 'L';
        continue;
      } 
      if (chs_buf[k] == '\n') {
        dst = chsAddStrL(dst, chs_buf,k+1);
        break;
      }
      utlError(8313,utlErrInternal);
    }
    if (what == 'L'  &&  chsChrAt(dst,-1) != '\n')
      dst = chsAddChr(dst, '\n');
  }  
  _dbgmsg("READ: %s\n",dst);
  return dst;
}

pmxMatches_t chsMatch(chs_t s, long from, char *pat)
{
  pmxMatches_t ret;
  int k;
  
  if (!pat || !*pat || !s || chsLen(s) == 0) return NULL;
  from = fixndx(s,from);
  if (from >= chsLen(s)) return NULL;
  
  ret = pmxMatchStr(s+from, pat);
  if (ret) {
    for (k = 0; k<pmxCaptMax; k++) {
      (*ret)[k][0] += from; (*ret)[k][1] += from;
    }
    chs_blk(s)->cur = from+pmxStart(ret,0);    
  }
  return ret;
}

chs_t chsSubFun(chs_t s, size_t pos, char *pat, chsSubF_t f)
{
  chs_t  mtc = NULL;
  char  *rpl;
  long   l = 0;
  int    repeat = 0;
  pmxMatches_t  ret;
  
  pos = fixndx(s,pos);
  
  if (!s || pos >= chsLen(s) || !pat)
    return s;
    
  if (pat[0] == '&' && pat[1] == '*') {
    repeat = 1;
    pat += 2;
  }
    
  if (!*pat) return s;

  /* We might be in a  another '|chsSubFun| handle, hence we need to preserve
     the previous matching result if we want to call another pmx function
  */
  pmxMatchesPush();
    
  while ((ret = chsMatch(s, pos, pat))) {
    pos =  pmxStart(ret,0);
    rpl = f(s,ret);
    if (rpl) {
      s = chsDel(s, pos, pmxEnd(ret,0)-1);
      l = strlen(rpl);
      if (l>0)
        s = chsInsStrL(s, pos, rpl, l);

      if (repeat)
        l = 0;
    }
    else  l = pmxLen(ret,0);
    pos += l;
  }

  mtc = chsFree(mtc);

  pmxMatchesPop();

  return s;  
}


static char  *rpl_str;
static chs_t  rpl_chs;
static char  *rpl_fun(char *mtc, pmxMatches_t cpt)
{
  char *r, *t;
  long l;
  
  rpl_chs = chsCpy(rpl_chs, utlEmptyString);
  if (rpl_str && *rpl_str) {
    r = rpl_str;
    while (*r) {
      l = 0;
      t = r;
      while (*t && *t != '&') { t++; l++; }
      rpl_chs = chsAddStrL(rpl_chs, r, l);
      if (*t == '&') {
        if (t[1] &&  0 <= *++t && *t <= '9') { 
           l = pmxLen(cpt, *t - '0');
           rpl_chs = chsAddStrL(rpl_chs, mtc + pmxStart(cpt,*t - '0'), l);
           _dbgmsg("\tlen: %ld\n",l);
        }
        else
          rpl_chs = chsAddChr(rpl_chs, *t);
        r = t+1;
      }
      else r=t;
    }
  }
  return (char *)rpl_chs;
}

chs_t chsSubStr(chs_t s, size_t pos, char *pat, char *rpl)
{ 
  rpl_str = rpl;
  rpl_chs = NULL;
  s = chsSubFun(s, pos, pat, rpl_fun);
  rpl_chs = chsFree(rpl_chs);
  
  return s;
}

#if 0
static tbl_t rpl_tbl=NULL;

chs_t chsSubTbl(chs_t s, size_t pos, char *pat, tbl_t rpl)
{ 
  rpl_tbl = rpl;
  rpl_chs = NULL;
  s = chsSubFun(s, pos, pat, rpltbl_fun);
  rpl_chs = chsFree(rpl_chs);
  
  return s;
}
#endif

