/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This sofwtare is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#ifndef CHS_H
#define CHS_H


/*
.v
                     __        
                    |  |        
                 ___|  |__  ____ 
                /  _|  __ \/ ___)
               (  (_|  || |\___ \
                \____)_||_(_____/
..



*/

#define chsBlksz 32

typedef struct {
  long size;
  long len;
  long cur;
  char chs[chsBlksz];
} chsBlk;

typedef char *chs_t ;

extern chsBlk *chs_blk_;
extern chs_t   chs_tmp_;

#define chs_blk(s) ((chsBlk *)(((char*)(s)) - offsetof(chsBlk,chs)))

#define chsLen(s)  ((chs_tmp_=(s))? chs_blk(chs_tmp_)->len : 0)
#define chsSize(s) ((chs_tmp_=(s))? chs_blk(chs_tmp_)->size  : 0)
#define chsCur(s)  ((chs_tmp_=(s))? chs_blk(chs_tmp_)->cur : 0)

#define chsFree(s) ((chs_tmp_=(s))? (free(chs_blk(chs_tmp_)),NULL) : NULL)

chs_t  chsNew() ;

int    chsSeek (chs_t dst, long pos, int whence) ;
size_t chsTell (chs_t dst) ;
int    chsEof  (chs_t s) ;

chs_t chsSet    (chs_t s, long ndx, char c) ;
char  chsChrAt  (chs_t s, long ndx) ;
int   chsGetChr (chs_t s) ;

chs_t chsCpyL (chs_t dst, char *src, long len) ;
chs_t chsCpy  (chs_t dst, char *src) ;
chs_t chsDup  (char *src);

chs_t chsAddChr  (chs_t dst, char c) ;
chs_t chsAddStrL (chs_t dst, char *src, long len) ;
chs_t chsAddStr  (chs_t dst, char *src) ;

chs_t chsInsChr  (chs_t dst, long ndx, char c) ;
chs_t chsInsStrL (chs_t dst, long ndx, char *src, long len) ;
chs_t chsInsStr  (chs_t dst, long ndx, char *src) ;

chs_t chsDel (chs_t dst, long from, long to) ;

chs_t chs_read(chs_t dst, FILE *f, char how, char what);

#define chsRead(s,f,h)   chs_read(s,f,h,'A')
#define chsReadln(s,f,h) chs_read(s,f,h,'L')

#define chsForLines(l,f)  for (l=chsReadln(l,f, 'w'); chsLen(l) > 0;\
                                                     l = chsReadln(l,f,'w'))

pmxMatches_t chsMatch(chs_t s, long from, char *pat) ;

typedef char *(*chsSubF_t)(char *mtc, pmxMatches_t cpt);

chs_t chsSubStr(chs_t s, size_t pos, char *pat, char *rpl) ;
chs_t chsSubFun(chs_t s, size_t pos, char *pat, chsSubF_t f);

#endif  /* CHS_H */
