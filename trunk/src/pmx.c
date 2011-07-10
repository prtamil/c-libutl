/*
** .: (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php
** .. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "pmx.h"

#define mTRUE  1
#define mFALSE 0


#define  DBGMSG(...) fprintf(stderr,__VA_ARGS__)
#define xDBGMSG(...) 

/* {{ * FILE-like access function to a string **/

typedef struct {
  char *text;
  char *start;
  short eof;
} sbuf;

static short pmx_ch;

#define SB(s)          ((sbuf *)(s))
#define pmxGetc(s) \
     ((pmx_ch = *SB(s)->text++) ? pmx_ch : (SB(s)->text--,SB(s)->eof = EOF))

static int pmxEscGetc(void *text,char esc)
{
  int ch;

  while ((ch = pmxGetc(text)) == esc)
    ch = pmxGetc(text);

  return ch;
}

/*#define pmxEscGetc(s,e) \
     (((pmxGetc(s) == (e)) ? (pmxGetc(s),pmxGetc(s)) : pmx_ch),pmx_ch)
     ((pmxGetc(s) == (e)) ? (pmxGetc(s),pmxGetc(s)) : pmx_ch)*/
     
#define pmxTell(s)      (SB(s)->text - SB(s)->start)
#define pmxSeek(s,o,w)  ((SB(s)->text = SB(s)->start + (o)), SB(s)->eof = 0) 
#define pmxEof(s)       (SB(s)->eof)
#define pmxBof(s)       (SB(s)->text == SB(s)->start)
#define pmxChrAt(s,k)   ((pmx_ch = (SB(s)->start)[k]) ? pmx_ch : EOF)
#define pmxCurChar(s)   ((pmx_ch = *SB(s)->text) ? pmx_ch : EOF)


/*
static int pmxGetc(sbuf *s)
{
  short ch;
  if (!s) return EOF;
  if (!s->text || !*s->text) return (s->eof = EOF);
  ch = *s->text;
  s->nl = (s->text == s->start) ||
          (ch == '\n') ||
          (ch == '\r' && s->text[1] != '\n') ;
  s->text++;
  return ch;
}
*/

static int pmxBeginLine(sbuf *s)
{
  return ( (s->text-1 == s->start) ||
           (s->text[-2] == '\n') ||
           (s->text[-2] == '\r' && s->text[-1] != '\n'));
}

/* .%% The '|pmxMatches| structure '<matchinfo>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  The '{=pmxMatches} structure contains the following information: 
 
.v
                   0                           1
    +-----------------------------+-----------------------------+
  0 | start index of matched text | end index of matched text   |
    +-----------------------------+-----------------------------+
  1 | start index of capture 1    | end index of capture 1      | 
   ...                           ...                           ...
  8 | start index of capture 8    | end index of capture 8      |
    +-----------------------------+-----------------------------+
  9 | start index of capture 9    | end index of capture 9      |
    +=============================+=============================+
 10 | matched pattern             | token of matched pattern    |
    +-----------------------------+-----------------------------+
 11 | start offset                |          flags              |
    +-----------------------------+-----------------------------+
..
 
  Start/end index are offset with respect to the start of the string
that has been matched.

  This structure is not to be used directly, an opaque pointer
type ('{pmx_t}) is provided for passing information from a 
function to another. 

  There actually is a stack of such structures to handle call back functions; 
*/

int pmx_capt_cur = 0;

static pmxMatches capt_arr[pmxCaptStkSize];
#define capt  capt_arr[pmx_capt_cur]

size_t pmxLen(pmx_t mtc, unsigned char n)
{
  return (mtc != NULL && (n < pmxCaptMax) && ((*mtc)[n][1] > (*mtc)[n][0]))
          ? (*mtc)[n][1] - (*mtc)[n][0]
          : 0;
}

size_t pmxStart(pmx_t mtc, unsigned char n)
{
  return (mtc && n < pmxCaptMax) ? (*mtc)[n][0] : 0;
}

size_t pmxEnd(pmx_t mtc, unsigned char n)
{
  return (mtc && (n < pmxCaptMax)) ? (*mtc)[n][1] : 0;
}

char *pmxStartP(pmx_t mtc, unsigned char n)
{
  return (mtc && n < pmxCaptMax) ? (char *)0 + (*mtc)[pmxCaptMax+1][0] + (*mtc)[n][0] : NULL;
}

char *pmxEndP(pmx_t mtc, unsigned char n)
{
  return (mtc && (n < pmxCaptMax)) ? (char *)0 + (*mtc)[pmxCaptMax+1][0] + (*mtc)[n][1] : NULL;
}

int pmxMatched(pmx_t mtc)
{
  return mtc ? (*mtc)[pmxCaptMax][0] : 0;
}

unsigned char pmxToken(pmx_t mtc)
{
  return (unsigned char)(mtc ? (*mtc)[pmxCaptMax][1] : 0x00);
}

#define F_ALL      0xFFFF
#define F_ICASE    0x0001
#define F_FAILALL  0x0002
#define F_GOAL     0x0004
#define F_NEGGOAL  0x0008
#define F_CONTEXT  0x0010
#define F_CTFAIL   0x0020
#define F_CTREPT   0x0040
#define F_CTSKIPTO 0x0080
#define F_CTSKIP   0x0100

#define set_flag(f)  (capt[11][1] |=  (f))
#define clr_flag(f)  (capt[11][1] &= ~(f))
#define tst_flag(f)  (capt[11][1] &   (f))

/* {{ Checks on characters **/
#define ic(c) (tst_flag(F_ICASE)?tolower((int)(c)):c)

#define is_blank(x) (x == ' ' || x =='\t')
#define is_ascii(x) (x < 0x7F)
#define is_word(x)  (x == '_' || isalnum(x))
#define is_any(x)   mTRUE

static int isclass(char *p, short ch)
{
  char *q;

  while (*p && *p != '>') {
    if (*p == '&' && p[1]) p++;
    if (*p == ch) return mTRUE;
    if (p[1] == '-' && *(q=p+2))  {
      if (*q == '&' && q[1]) q++;
      if (*p <= ch && ch <= *q)
        return mTRUE;
      p = q;
    }
    ++p;
  }
  return mFALSE;
}

static int issortedclass(char *p, short ch)
{
  char *q;

  while (*p && *p != '>') {
    if (*p == '&' && p[1]) p++;
    if (*p > ch) return mFALSE;
    if (*p == ch) return mTRUE;
    if (p[1] == '-' && *(q=p+2))  {
      if (*q == '&' && q[1]) q++;
      if (ch <= *q) return mTRUE;
      p = q;
    }
    ++p;
  }
  return mFALSE;
}


/*
** "$str1$stri&$ng2>"
*/
static int hasstring(void *text, char *lst)
{
  size_t pos = pmxTell(text)-1;
  int ch = ' ';

  while (*lst && *lst != '>' && *++lst) {
    pmxSeek(text,pos,SEEK_SET);
    do {
      if (*lst == '$' || *lst == '>') return mTRUE;
      if (*lst == '&') lst++;
      ch = ic(pmxGetc(text));
      if (ch != *lst++) break;
    } while (*lst);
    if (ch == EOF) break;
    while (*lst && *lst != '$' && *lst != '>')  lst++;
    while (lst[1] == '$')  lst++;
  }
  pmxSeek(text,pos+1,SEEK_SET);
  return mFALSE;
}

static int iscapt(void *text, int cap_num)
{
  size_t pos = pmxTell(text)-1;
  size_t k = capt[cap_num][0];
  size_t n = capt[cap_num][1];
  short ch ;

  if (k >= n) return mFALSE;

  pmxSeek(text,pos,SEEK_SET);
  while (k < n && (ch = ic(pmxGetc(text)), ch == ic(pmxChrAt(text,k))))
    k++;

  if (k == n) return mTRUE;
  
  pmxSeek(text,pos+1,SEEK_SET);
  return mFALSE;
}

static int braced(void *text, int left, int right, char esc)
{
  size_t pos = pmxTell(text)-1;
  int ch = ' ';
  int op = 0;
  
  pmxSeek(text,pos,SEEK_SET);
  ch = ic(pmxGetc(text));
  if (ic(ch) == left) {
    if (left != right) {
      op = 1; /* open braces count */
      while (ch != EOF && op > 0) {
        ch = ic(pmxGetc(text));
        if (ch == right) op--;
        else if (ch == left) op++;
      }
    }
    else {
      do {
        ch = ic(pmxGetc(text));
        if (ch == esc) {
          ch = ic(pmxGetc(text));
          if (ch != EOF) ch = right+1;
        }
      } while (ch != EOF && ch != right);
    }
    if (ch != EOF) return mTRUE;
  }
  pmxSeek(text,pos,SEEK_SET);
  return mFALSE;
}

/* }} **********************/

/* {READ_NEXT} will be assigned to the current character
** if a new character has to be read. This allows optional
** matching and patterns that match no input that require
** that the same input character is processed again
**/
#define READ_NEXT  0x4000
#define FAILED     0x0200
#define ENDPATTERN 0x0100

static char *nullptrn="";

#define FAIL    goto failed

#define NOMATCH {if (tst_flag(F_CONTEXT)) {set_flag(F_CTFAIL); break;}\
                else FAIL;}

/* {MAX_MAX} limits the number of repetitions that are allowed
*/
#define MAX_MAX 0xFFFFFFFE

char *setminmax(char *p, unsigned long *min, unsigned long *max)
{
  *min = 0;
  *max = MAX_MAX;
  ++p;
  if (isdigit((int)*p)) {
    *min = atoi(p);
    *max = *min;
    while (*p && *p!= ',' && *p!=':' && *p!='>') p++;
  }
  if (*p == ',') {
    p++;
    *max = atoi(p);
    if (*max == 0) *max = MAX_MAX;
  }
  while (*p && *p!=':' && *p!='>') p++;
  if (*p == ':') return p;
  return NULL;
}

#define chpos(t) (pmxTell(t)-(pmxEof(t) || pmxBof(t)?0:1))

static pmx_t domatch(void *text, char *pattern, char **next)
{
  short reverse;
  int ch,left,right;
  unsigned long min,max,cnt;
  char op;
  char esc;
  char *p = pattern;
  
  size_t        ct_text = 0;
  char         *ct_patt = NULL;
  char         *ct_endp = NULL;
  //char         *ct_alt  = NULL;
  
  unsigned long ct_min = 1;
  unsigned long ct_max = 1;
  unsigned long ct_cnt = 0;
  size_t        ct_goal= 0;
   
  unsigned char capt_opn = 0;
  unsigned char capt_stk_cnt = 0;
  unsigned char capt_stk[pmxCaptMax];

  for (capt_opn = 0; capt_opn <= pmxCaptMax; capt_opn++) {
    capt[capt_opn][0] = 0;
    capt[capt_opn][1] = 0;
  }
  
  capt_opn = 0;
  capt_stk_cnt = 0;
  
  esc = '\0';
  clr_flag(F_ALL);
  
  ct_min = 1;
  ct_max = 1;
  ct_cnt = 0;
  
  if (*p == '>') p++;
  
  ch = pmxGetc(text);
  
  capt[0][0] = chpos(text);
  capt[0][1] = capt[0][0];
  
  for (*next = p; *p ; ++p) {
   *next = p;
    min = 1; max = 1;
    cnt = 0;
    
    reverse = mFALSE;
    
    switch (*p) {
      case '<' : op = *++p;
                 switch (op) {
                   case ':' : if ((p = setminmax(p,&min,&max))) goto rep;
                              else FAIL;
                   case '+' : min = 1; max = MAX_MAX;     goto rep;
                   case '*' : min = 0; max = MAX_MAX;     goto rep;
                   case '?' : min = 0; max = 1; 
                        rep : op = *++p;
                              break;
                   case '\0': FAIL;
                 }
                   
                 reverse = (isupper((int)op) ? mTRUE : mFALSE);
                 op = tolower((int)op);
                 
                 switch (op) {
                   #define xW(x,f) while(ch && ch != EOF && cnt < max && !(x) == reverse)\
                                   { ch = f; cnt++; }
                   #define  W(x) xW(x,pmxGetc(text))
                   #define eW(x) xW(x,pmxEscGetc(text,esc))
                                                                
                   case 'a' : W(isalpha(ch))  ; break;
                   case 'c' : W(iscntrl(ch))  ; break;
                   case 'd' : W(isdigit(ch))  ; break;
                   case 'g' : W(isgraph(ch))  ; break;
                   case 'i' : W(is_ascii(ch)) ; break;
                   case 'k' : W(is_blank(ch)) ; break;
                   case 'l' : W(islower(ch))  ; break;
                   case 'p' : W(ispunct(ch))  ; break;
                   case 'q' : W(isalnum(ch))  ; break;
                   case 'r' : W(isprint(ch))  ; break;
                   case 's' : W(isspace(ch))  ; break;
                   case 'u' : W(isupper(ch))  ; break;
                   case 'w' : W(is_word(ch))  ; break;
                   case 'x' : W(isxdigit(ch)) ; break;
                   case '.' : W(is_any(ch))   ; break;

                   case '!' : reverse = mTRUE;
                   case '=' : if (*++p == 0) FAIL;
                              eW(isclass(p,ch));
                              break;
                                                
                   case 'j' : if (*++p == 0) FAIL;
                              eW(issortedclass(p,ch));
                              break;
                                                
                              
                   case '$' : W(hasstring(text,p));
                              break;

                   case '1' : case '2' : case '3' :
                   case '4' : case '5' : case '6' :
                   case '7' : case '8' : case '9' :
                              op -= '0';
                              W(iscapt(text,op));     
                              break;

                   case '#' : set_flag(F_CTSKIPTO); 
                   case '@' : set_flag(F_CTSKIP); 
                              if (min != 1 || max != 1) FAIL;
                              if (*++p != '[') FAIL;
                   case '[' : if (tst_flag(F_CONTEXT)) FAIL;
                              if (*++p != '>') FAIL;
                              
                              ct_patt = p;
                              ct_endp = ct_patt;
                              while (*ct_endp && (ct_endp[0] != '<' || ct_endp[1] != ']'))
                                if (*ct_endp++ =='&' && *ct_endp) ct_endp++;
                              while(*ct_endp && ct_endp[0] != '>')
                                if (*ct_endp++ =='&' && *ct_endp) ct_endp++;
                              if (*ct_endp != '>') FAIL;
                              
                              ct_text = chpos(text);
                              ct_goal = capt[0][1];
                              ct_min = min;
                              ct_max = max;
                              ct_cnt = 0;
                              set_flag(F_CONTEXT);
                              clr_flag(F_CTFAIL | F_CTREPT);
                              cnt = min;
                              break;
                              
                   case ']' : if (!tst_flag(F_CONTEXT)) FAIL;
                              xDBGMSG("] chk %c %ld < %ld %x\n",ch,ct_cnt,ct_max,tst_flag(F_CTFAIL));
                              ct_cnt++;
                              if (ct_cnt < ct_max) {
                                set_flag(F_CTREPT);
                              }
                              else {
                                p = ct_endp;
                                if (tst_flag(F_CTSKIPTO)) {
                                  pmxSeek(text,ct_text+1,SEEK_SET);
                                  ch = READ_NEXT;      
                                }
                                clr_flag(F_CTFAIL|F_CONTEXT|F_CTSKIPTO|F_CTSKIP|F_CTREPT);
                              }
                              cnt = min;
                              xDBGMSG("] OK %s %c\n",p,ch);
                              break;
                              
                   case '\0': FAIL;
                   
                 }
                  
                 if (cnt < min) NOMATCH; /* NOTE: this may never happen if in CONTEXT! */
                 
                 if (tst_flag(F_CTREPT)) {
                   p = ct_patt;
                   ct_text = chpos(text);
                   clr_flag(F_CTREPT);
                   ct_goal = capt[0][1];
                 }
                 else {
                   while (*p && *p != '>')
                     if (*p++ =='&' && *p) p++;
                   if (*p != '>') FAIL;
                 }
                 break;

      case '>' : if (ch != EOF || p[1] != '\0') FAIL;
                 break;
      
      case '&' : cnt = 0;  
                 left = '\0'; right = '\0';
                 op = *++p;
                 switch (op) {
                   case 'G' : set_flag(F_NEGGOAL);
                   case 'g' : set_flag(F_GOAL);
                              capt[0][1] = chpos(text);
                              break;

                   case 'r' : if (!pmxBeginLine(text)) NOMATCH;
                              break;

                   case 'I' : clr_flag(F_ICASE); break;
                   case 'i' : set_flag(F_ICASE); break;

                   case 'L' : reverse = mTRUE;
                   case 'l' : while (ch && ch != EOF && ch != '\n'&& ch != '\r' ) {
                                if (ch == esc) {
                                  do {
                                    ch = pmxGetc(text);
                                  } while (is_blank(ch)); 
                                  if (ch == '\r') ch = pmxGetc(text);
                                  if (ch == '\n') ch = pmxGetc(text);
                                }
                                else ch = pmxGetc(text);
                                cnt++;
                              }
                              if (cnt == 0 && !reverse) NOMATCH;
                              break;

                   case 'N' : reverse = mTRUE;
                   case 'n' : if (ch == '\r') { ch = pmxGetc(text); cnt++;}
                              if (ch == '\n') { ch = pmxGetc(text); cnt++;}
                              if (cnt == 0 && !reverse) NOMATCH;
                              break;
                              
                   case 'D' : reverse = mTRUE;
                   case 'd' : if (ch == '-' || ch == '+') { ch = pmxGetc(text); }
                              while (isdigit(ch)) { ch = pmxGetc(text); cnt++;}
                              if (cnt == 0 && !reverse) NOMATCH;
                              break;
                              
                   case 'X' : reverse = mTRUE;
                   case 'x' : while (isxdigit(ch)) { ch = pmxGetc(text); cnt++;}
                              if (cnt == 0 && !reverse) NOMATCH;
                              break;
                              
                   case 'F' : reverse = mTRUE;
                   case 'f' : if (ch == '-' || ch == '+') { ch = pmxGetc(text); }
                              while (isdigit(ch)) { ch = pmxGetc(text); cnt++;}
                              if (ch == '.') { ch = pmxGetc(text); }
                              while (isdigit(ch)) { ch = pmxGetc(text); cnt++;}
                              if (cnt == 0 && !reverse) NOMATCH;
                              xDBGMSG("!!%c\n",ch);
                              break;
                              
                   case '!' : set_flag(F_FAILALL); break;
                   
                   case '|' : if (tst_flag(F_CONTEXT)) FAIL;
                              ch = ENDPATTERN; break;
                   
                   case 'E' : esc = '\0'; break;
                   
                   case 'e' : if ((esc=*++p)=='\0') FAIL;
                              if ((esc == '&') && ((esc=*++p)=='\0')) FAIL;
                              break;
                              
                   case 'Q' : reverse = mTRUE;
                   case 'q' : if (ch == '"' || ch == '\'') {
                                left = ch; right = ch;
                                ch = READ_NEXT;
                                if (braced(text,left,right,esc)) break;
                              }
                              if (reverse) break;
                              NOMATCH;
                              
                   case 'B' : reverse = mTRUE;
                   case 'b' : if ((left  = *++p) == '\0') FAIL;
                              if ((right = *++p) == '\0') FAIL;
                              ch = READ_NEXT;
                              if (braced(text,left,right,esc)) break;
                              if (reverse) break;
                              NOMATCH;

                   case 'K' : min = 0;
                   case 'k' : max = MAX_MAX;
                              W(is_blank(ch)) ; 
                              if (cnt >= min) break;
                              NOMATCH;
                              
                   case 'S' : min = 0;
                   case 's' : max = MAX_MAX;
                              W(isspace(ch)) ; 
                              if (cnt >= min) break;
                              NOMATCH;
                              
                   case 'W' : min = 0;
                   case 'w' : max = MAX_MAX;
                              W(is_word(ch)) ; 
                              if (cnt >= min) break;
                              NOMATCH;
                              
                   case '\0': FAIL;
                   
                   default : if (*p & 0x80) {
                               capt[pmxCaptMax][1] = *p;
                             }
                             else {
                               if (ic(ch) != ic(*p)) NOMATCH;
                               ch = READ_NEXT;
                             }
                             break;
                 }
                 break;

      case '(' : if (tst_flag(F_CONTEXT)) FAIL;
                 if (capt_opn < pmxCaptMax-1) {
                   capt_stk[capt_stk_cnt++] = ++capt_opn;
                   capt[capt_opn][0] = chpos(text);
                 }
                 break;

      case ')' : if (tst_flag(F_CONTEXT)) FAIL;
                 if (capt_stk_cnt>0) {
                   capt_stk_cnt--;
                   capt[capt_stk[capt_stk_cnt]][1] = chpos(text);
                 }
                 break;

      default  : if (ic(ch) != ic(*p)) NOMATCH;
                 ch = READ_NEXT;
                 break;
    }
    
    if (tst_flag(F_CTFAIL)) {
      if (tst_flag(F_CTSKIP)) {
        if (ch == EOF) FAIL;
        else {
          ch = READ_NEXT;
          capt[0][1] = ct_goal;
          p = ct_patt;
          ct_text = chpos(text);   
        }
      }
      else {
      
        if (ct_cnt < ct_min) FAIL;
  
        capt[0][1] = ct_goal;
        pmxSeek(text,ct_text,SEEK_SET);
        ch = READ_NEXT;      
        
        clr_flag(F_CONTEXT|F_CTSKIP|F_CTSKIPTO);
        p = ct_endp;
      }        
      clr_flag(F_CTFAIL);
      xDBGMSG("failed in the middle %ld %ld (%s) [%c]\n",ct_cnt, ct_min,p+1,ch);
    }
    
    if (ch == ENDPATTERN) break;
    if (ch == READ_NEXT && ch != EOF) ch = pmxGetc(text);
  }

  if (tst_flag(F_GOAL)) { /* manage &g and &G */
    pmxSeek(text, capt[0][1], SEEK_SET);
  }
  else {
    capt[0][1] = chpos(text);
    /* refuse to match the empty string! */
    /*if (capt[0][0] >= capt[0][1]) FAIL;*/
  }

  /*printf("*|* %s\n",p);*/

  /* MATCHED !! */
  if (!tst_flag(F_NEGGOAL)) return &capt;
  clr_flag(F_GOAL | F_NEGGOAL);

failed:  
  if (tst_flag(F_NEGGOAL)) { /* manage &G */
    pmxSeek(text, capt[0][1], SEEK_SET);
    return &capt;
  }
  
  if (tst_flag(F_FAILALL)) *next=nullptrn;
  return NULL;
}


static pmx_t match_multi(void *text, char *ptrn)
{
  pmx_t ret = NULL;
  size_t cnt;
  size_t start;
  char *next;
  int ptnum = 0;
  long ptlen;

  start = pmxTell(text);
  
  if (*ptrn == '&' && ptrn[1] == '|') ptrn+=2;  

  while (*ptrn) {
    cnt = start;
    if (*ptrn == '&' && ptrn[1] == ':') {
      ptlen = ptrn[2]; ptrn+=2;
      if (*ptrn) ptrn++;
    }
    else ptlen = 0;
    ptnum++;
    
    while (!(ret = domatch(text, ptrn, &next)) && (*ptrn == '>') && !pmxEof(text)) {
      pmxSeek(text, ++cnt, SEEK_SET);
    }    
    if (ret) {
      (*ret)[pmxCaptMax][0] = ptnum;
      break;
    }
    
    if (ptlen) ptrn += ptlen;
    else ptrn = next;
    if (*ptrn) {
      do {
        if (*ptrn++ == '&' && *ptrn++ == '|') break;  
      } while (*ptrn);
    } 
    if (*ptrn)
      pmxSeek(text, start, SEEK_SET);    
  }
  
  return ret;
}

/* */

pmx_t pmx_matchstr(char *txt, char *ptrn, size_t offset)
{
  sbuf sb;
  pmx_t ret;
    
  assert(sizeof(size_t) >= 4);
  
  if (!txt || !ptrn || !*ptrn ) return NULL;
  
  sb.start = txt;
  sb.text  = txt+offset;
  sb.eof   = 0;
  
  ret = match_multi(&sb,ptrn);
  if (ret) {
    (*ret)[pmxCaptMax+1][0] = txt - (char *)0;
  }

  return ret;  
}

int pmxScanStr(char *text, char *ptrn, pmxScanFun_t f)
{
  pmx_t ret;
  char *cur = text;
  int f_ret;

  if (ptrn && *ptrn == '>') ptrn++;
  
  if (!text || !ptrn || !*ptrn || f == NULL) 
    return 0;

  while (*cur) {
    ret = pmx_matchstr(text, ptrn, cur-text);
    if (ret) {
      pmxMatchesPush();
      f_ret = f(text,ret);
      pmxMatchesPop();
      if (f_ret) return f_ret; 
      cur =  text+pmxEnd(ret,0);
    }
    else cur++;
  }
  return 0;
}

/*******************/


