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

#include "pmx.h"

#define mTRUE  1
#define mFALSE 0

/* {{ * FILE-like access function to a string **/

typedef struct {
  char *start;
  char *text;
  short eof;
} sbuf;


#define SB(s)          ((sbuf *)(s))
#define pmxGetc(s)     ((SB(s)->text && *SB(s)->text)?  *SB(s)->text++ : (SB(s)->eof = 1, EOF))
#define pmxTell(s)     (SB(s)->text - SB(s)->start)
#define pmxSeek(s,o,w) (SB(s)->text = SB(s)->start + o, SB(s)->eof = 0) 
#define pmxEof(s)      (SB(s)->eof)



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
..
 
  Start/end index are offset with respect to the start of the string
that has been matched.

  This structure is not to be used directly, an opaque pointer
type ('{pmxMatches_t}) is provided for passing information from a 
function to another. 
 
*/
int pmx_capt_cur = 0;

static pmxMatches capt_arr[8];
#define capt  capt_arr[pmx_capt_cur]

static short icase = mFALSE;

size_t pmxLen(pmxMatches_t mtc, unsigned char n)
{
  return (mtc != NULL && (n < pmxCaptMax) && ((*mtc)[n][1] > (*mtc)[n][0]))
          ? (*mtc)[n][1] - (*mtc)[n][0]
          : 0;
}

size_t pmxStart(pmxMatches_t mtc, unsigned char n)
{
  return (mtc && n < pmxCaptMax) ? (*mtc)[n][0] : 0;
}

size_t pmxEnd(pmxMatches_t mtc, unsigned char n)
{
  return (mtc && (n < pmxCaptMax)) ? (*mtc)[n][1] : 0;
}

int pmxMatched(pmxMatches_t mtc)
{
  return mtc ? (*mtc)[pmxCaptMax][0] : 0;
}

unsigned char pmxToken(pmxMatches_t mtc)
{
  return (unsigned char)(mtc ? (*mtc)[pmxCaptMax][1] : 0x00);
}

/* {{ Checks on characters **/
#define ic(c) (icase?tolower(c):c)

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

#define FAIL   goto chk_fail

/* {MAX_MAX} limits the number of repetitions that are allowed
** As a side effect this is an hard limit to the lenght of
** text that can be matched.
*/
#define MAX_MAX 0xFFFFFFFE

static pmxMatches_t domatch(void *text, char *pattern, char **next)
{
  short reverse;
  int ch,left,right;
  unsigned long min,max,cnt;
  char op;
  char esc;
  char *p = pattern;
   
  unsigned char capt_opn = 0;
  unsigned char capt_stk_cnt = 0;
  unsigned char capt_stk[pmxCaptMax];

  for (capt_opn = 0; capt_opn <= pmxCaptMax; capt_opn++) {
    capt[capt_opn][0] = 0;
    capt[capt_opn][1] = 0;
  }
  
  capt_opn = 0;
  capt_stk_cnt = 0;

  capt[0][0] = pmxTell(text);
  capt[0][1] = capt[0][0];
  
  esc = '\0';
  icase = mFALSE;
  
  if (*p == '>') p++;
  *next = p;
  for (ch = pmxGetc(text); *p && ch != EOF; ++p) {
    /*printf("*** (%d) %c %s\n",ch,ch, p);*/ 
   *next = p;
    min = 1; max = 1;
    cnt = 0;
    reverse = mFALSE;
    switch (*p) {
      case '<' : op = *++p;
                 switch (op) {
                   case '+' : min = 1; max = MAX_MAX; goto rep;
                   case '*' : min = 0; max = MAX_MAX; goto rep;
                   case '?' : min = 0; max = 1; 
                        rep : op = *++p;
                              break;
                   case '\0': return NULL;
                 }
                 reverse = (isupper(op) ? mTRUE : mFALSE);
                 op = tolower(op);
                 switch (op) {
                   #define W(x) while(ch != EOF && cnt < max && !(x) == reverse)\
                                   { ch = pmxGetc(text); cnt++; }
                                                                
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
                   case '=' : if (*++p == 0) return NULL;
                              W(isclass(p,ch));
                              break;
                                                
                   case 'j' : if (*++p == 0) return NULL;
                              W(issortedclass(p,ch));
                              break;
                                                
                   case '#' : while(ch != EOF && cnt < max) {
                                if (esc && ch == esc) {
                                  ch = pmxGetc(text); 
                                } 
                                else if (isclass(p+1,ch)) break;
                                ch = pmxGetc(text); cnt++;
                              }
                              if (ch == EOF || cnt >= max) return NULL;
                              break;
                              
                   case '$' : W(hasstring(text,p));
                              break;

                   case '\0': return NULL;
                 }
                 
                 if (cnt < min) return NULL;
                 
                 while (*p && *p != '>')
                   if (*p++ =='&' && *p) p++;
                   
                 if (*p != '>') return NULL;
                 break;

      case '>' : return NULL;
      
      case '&' : cnt = 0;  op = 0;
                 left = '\0'; right = '\0';
                 switch (*++p) {
                   case 'G' : capt[0][1] = pmxTell(text)-1;
                              break;

                   case 'I' : icase = mFALSE; break;
                   case 'i' : icase = mTRUE; break;

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
                              if (cnt == 0 && !reverse) return NULL;
                              break;

                   case 'N' : reverse = mTRUE;
                   case 'n' : if (ch == '\r') { ch = pmxGetc(text); cnt++;}
                              if (ch == '\n') { ch = pmxGetc(text); cnt++;}
                              if (cnt == 0 && !reverse) return NULL;
                              break;
                              
                   case 'D' : reverse = mTRUE;
                   case 'd' : if (ch == '-' || ch == '+') { ch = pmxGetc(text); }
                              while (isdigit(ch)) { ch = pmxGetc(text); cnt++;}
                              if (cnt == 0 && !reverse) return NULL;
                              break;
                              
                   case 'X' : reverse = mTRUE;
                   case 'x' : while (isxdigit(ch)) { ch = pmxGetc(text); cnt++;}
                              if (cnt == 0 && !reverse) return NULL;
                              break;
                              
                   case 'F' : reverse = mTRUE;
                   case 'f' : if (ch == '-' || ch == '+') { ch = pmxGetc(text); }
                              while (isdigit(ch)) { ch = pmxGetc(text); cnt++;}
                              if (ch == '.') { ch = pmxGetc(text); }
                              while (isdigit(ch)) { ch = pmxGetc(text); cnt++;}
                              if (cnt == 0 && !reverse) return NULL;
                              break;
                              
                   case '|' : ch = ENDPATTERN; break;
                   
                   case 'E' : esc = '\0'; break;
                   
                   case 'e' : if ((esc=*++p)=='\0') return NULL;
                              if ((esc == '&') && ((esc=*++p)=='\0')) return NULL;
                              break;
                              
                   case 'Q' : reverse = mTRUE;
                   case 'q' : if (ch == '"' || ch == '\'') {
                                left = ch; right = ch;
                                ch = READ_NEXT;
                                if (braced(text,left,right,esc)) break;
                              }
                              if (reverse) break;
                              return NULL;
                              
                   case 'B' : reverse = mTRUE;
                   case 'b' : if ((left  = *++p) == '\0') return NULL;
                              if ((right = *++p) == '\0') return NULL;
                              ch = READ_NEXT;
                              if (braced(text,left,right,esc)) break;
                              if (reverse) break;
                              return NULL;

                   case 'K' : min = 0;
                   case 'k' : max = MAX_MAX;
                              W(is_blank(ch)) ; 
                              if (cnt < min) return NULL;
                              break;
                              
                   case 'S' : min = 0;
                   case 's' : max = MAX_MAX;
                              W(isspace(ch)) ; 
                              if (cnt < min) return NULL;
                              break;
                              
                   case '\0': return NULL;
                   
                   default : if (*p & 0x80) {
                               capt[pmxCaptMax][1] = *p;
                             }
                             else {
                               if (ic(ch) != ic(*p)) return NULL;
                               ch = READ_NEXT;
                             }
                             break;
                 }
                 break;

      case '(' : if (capt_opn < pmxCaptMax-1) {
                   capt_stk[capt_stk_cnt++] = ++capt_opn;
                   capt[capt_opn][0] = pmxTell(text)-1;
                 }
                 break;

      case ')' : if (capt_stk_cnt>0) {
                   capt_stk_cnt--;
                   capt[capt_stk[capt_stk_cnt]][1] = pmxTell(text)-1;
                 }
                 break;

      default  : if (ic(ch) != ic(*p)) return NULL;
                 ch = READ_NEXT;
                 break;
    }
    
    if (ch == ENDPATTERN) break;
    if (ch == READ_NEXT) ch = pmxGetc(text);
  }

  if (capt[0][1] == capt[0][0]) {
    capt[0][1] = pmxTell(text);
    if (ch != EOF) capt[0][1]--;
  }
  else {
    pmxSeek(text, capt[0][1], SEEK_SET);
  }

  /* refuse to match the empty string! */
  if (capt[0][0] >= capt[0][1]) return NULL;

  /*printf("*|* %s\n",p);*/
/* {{ remove the optional elements at the end of the pattern */
  if (ch != ENDPATTERN) {
    ch = *p;
    while (ch) {
       switch (ch) {
        case '<' : if (*++p == '?' || *p == '*') {
                     while(*p && *p != '>') if (*p++ =='&' && *p) p++;
                     break;
                   }
                   return NULL;
  
        case '>' : if (!pmxEof(text)) return NULL;
                   ch='\0';
                   break;
        
        case '&' : switch (*++p) {
                     case 'B' : if (*++p) p++;
                     case 'G' : 
                     case 'F' :
                     case 'D' :
                     case 'N' :
                     case 'L' :
                     case 'Q' :
                     case 'K' :
                     case 'S' :
                     case 'i' :
                     case 'I' : break;
                     case 'e' : if (*++p == '&' && *p) p++;
                     case 'E' : break;
                     case '|' : ch = '\0'; break;
                     case '\0': if (pmxEof(text)) break;
                     default  : if ((*p & 0x80) == 0) return NULL;
                                capt[pmxCaptMax][1] = *p;
                   }
                   break;
  
        case '(' : if (capt_opn < pmxCaptMax-1) {
                     capt_stk[capt_stk_cnt++] = ++capt_opn;
                     capt[capt_opn][0] = capt[0][1];
                   }
                   break;
  
        case ')' : if (capt_stk_cnt>0) {
                     capt_stk_cnt--;
                     capt[capt_stk[capt_stk_cnt]][1] = capt[0][1];
                   }
                   break;
  
        default  : return NULL;
      }
      if (ch) ch = *p;
      if (ch) ch = *++p;
    }
  }
/* }} ****/

  return &capt;
}

/* */

pmxMatches_t pmxMatchStr(char *txt, char *ptrn)
{
  pmxMatches_t ret = NULL;
  size_t cnt;
  size_t start;
  char *next;
  int ptnum = 0;
  long ptlen;
  sbuf sb;
  sbuf *text = &sb;
  
  if (!txt || !ptrn || !*ptrn ) return NULL;
  
  sb.start = txt;
  sb.text  = txt;
  sb.eof   = 0;

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

int pmxScanStr(char *text, char *ptrn, pmxScanFun_t f)
{
  pmxMatches_t ret;
  char *cur = text;
  int f_ret;
  int k;
  int delta;

  if (!text || !ptrn || !*ptrn || f == NULL) 
    return 0;

  while (*cur) {
    ret = pmxMatchStr(cur, ptrn);
    if (ret) {
      delta = cur - text;
      for (k=0; k<pmxCaptMax; k++) {
        (*ret)[k][0] += delta;
        (*ret)[k][1] += delta;
      }
      if ((f_ret = f(text,ret))) return f_ret; 
      cur =  text+pmxEnd(ret,0);
    }
    else cur++;
  }
  return 0;
}

char *pmx_tmpstr;
char *pmx_tmpptrn;
pmxMatches_t pmx_tmpmtc;

/*******************/


