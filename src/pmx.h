/* 
** .: (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php
**
** ..
*/


#ifndef PMX_H
#define PMX_H

#include <stddef.h>

/*
.v
                __ __  __ __ __ ___  ___ 
               |  '_ \|  '  '  |\  \/  / 
               |  |_) |  |  |  | /    /  
               |  ___/|__/__/__|/__/\__\ 
               |  |
               |__)
..
  
*/
#define pmxCaptMax 10

typedef size_t pmxMatches[pmxCaptMax+1][2];
typedef pmxMatches *pmx_t;

extern int pmx_capt_cur;

#define pmxCaptStkSize 8
#define pmxMatchesPush()  (pmx_capt_cur = (pmx_capt_cur +1) & 0x07)
#define pmxMatchesPop()   (pmx_capt_cur = (pmx_capt_cur + pmxCaptStkSize -1) & 0x07)

pmx_t pmx_matchstr(char *txt, char *ptrn, size_t offset);
#define pmxMatchStr(t, p) pmx_matchstr(t,p,0)

int           pmxMatched (pmx_t mtc);

size_t        pmxLen     (pmx_t mtc, unsigned char n);
size_t        pmxStart   (pmx_t mtc, unsigned char n);
size_t        pmxEnd     (pmx_t mtc, unsigned char n);

unsigned char pmxToken(pmx_t mtc);
#define pmxTokStart(x) (pmx_tmpstr+pmxStart(pmx_tmpmtc,x))
#define pmxTokEnd(x)   (pmx_tmpstr+pmxEnd(pmx_tmpmtc,x))
#define pmxTokLen(x)   pmxLen(pmx_tmpmtc,x)

#define pmxTokSet(x,y) "&|" x pmxTok_defstr(&\y)

#define pmxTokEOF  x7F
#define pmxTokNONE x00

#define pmxTok_defcase(y) 0##y 
#define pmxTok_defstr(y)  #y 
#define pmxTokCase(y) case pmxTok_defcase(y)

#define pmxSwitch(s,p) \
    switch ( ((pmx_tmpstr = s) && *s ) \
                 ? (pmx_tmpmtc = pmxMatchStr(pmx_tmpstr,p), \
                           s += pmxLen(pmx_tmpmtc,0), pmxToken(pmx_tmpmtc))\
                 : 0x7F )
             

typedef int (*pmxScanFun_t)(char *txt, pmx_t mtc);

int pmxScanStr(char* text, char *ptrn, pmxScanFun_t f);

extern char *pmx_tmpstr;
extern char *pmx_tmpptrn;
extern pmx_t pmx_tmpmtc;

#define pmxScannerBegin(s) do {\
    for (pmx_tmpstr = s, pmx_tmpptrn =  
    
#define pmxScannerSwitch  , \
                       pmx_tmpmtc = pmxMatchStr(pmx_tmpstr, pmx_tmpptrn); \
         *pmx_tmpstr && pmx_tmpmtc; \
         pmx_tmpstr += pmxLen(pmx_tmpmtc,0), \
                       pmx_tmpmtc = pmxMatchStr(pmx_tmpstr, pmx_tmpptrn)) \
    { switch (pmxToken(pmx_tmpmtc)) { 
    
#define pmxScannerEnd } ; break; } \
    pmx_tmpstr = ""; \
  } while (pmx_tmpstr == NULL)


#define pmxScanner(s,p,c) do {\
    for (pmx_tmpstr = s, pmx_tmpptrn =  p, \
                       pmx_tmpmtc = pmxMatchStr(pmx_tmpstr, pmx_tmpptrn); \
         *pmx_tmpstr && pmx_tmpmtc; \
         pmx_tmpstr += pmxLen(pmx_tmpmtc,0), \
                       pmx_tmpmtc = pmxMatchStr(pmx_tmpstr, pmx_tmpptrn)) \
    { switch (pmxToken(pmx_tmpmtc)) { c } ; break; } \
    pmx_tmpstr = ""; \
  } while (pmx_tmpstr == NULL)


#endif
