/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#include "libutl.h"

#define CODE    1
#define COMMENT 2 

#define T_COMMENT x81
#define T_SKIP    x82
#define T_SKIP2   x92
#define T_EMPTY   x83

int state = CODE;

chs_t ln = NULL;

int main(void)
{
  FILE *inf = stdin;
  int startline;
  char *cur;
   
  chsForLines(ln,inf) {
    cur = ln; 
    startline = 1; 
    while (*cur) {
      switch (state) {
        case CODE :    pmxSwitch (cur,
                         pmxTokSet("&K&n",         T_EMPTY)
                         pmxTokSet("&s",           T_SKIP)
                         pmxTokSet("&e\\&b\"\"",   T_SKIP)
                         pmxTokSet("/*",           T_COMMENT)
                         pmxTokSet("/",            T_SKIP)
                         pmxTokSet("<+!/\t\r\n>", T_SKIP)
                       ) { 
                         pmxTokCase(T_COMMENT):
                           state = COMMENT;
                           startline = 2;
                           break;
                           
                         pmxTokCase(T_SKIP):
                           printf("%.*s",pmxTokLen(0),pmxTokStart(0));
                           break;
                           
                         pmxTokCase(T_EMPTY):
                           if (startline <= 0) putchar('\n');
                           break;
                           
                        pmxTokCase(pmxTokEOF) :
                           cur = utlEmptyString;
                           break;
                       }
                       pmxSwitchEnd;
                       break;

        case COMMENT : pmxSwitch (cur,
                         pmxTokSet("&K*/&K",    T_COMMENT)
                         pmxTokSet("*",         T_SKIP)
                         pmxTokSet("&K(&n)",    T_SKIP)
                         pmxTokSet("<+!*\n\r>", T_SKIP)
                       ) {
                         pmxTokCase(T_COMMENT):
                           state = CODE;
                           break;
                           
                         pmxTokCase(T_SKIP):
                           if (pmxTokLen(1) != 0)  putchar('\n');
                           break;
                           
                        pmxTokCase(pmxTokEOF) :
                           cur = utlEmptyString;
                           break;
                       }
                       pmxSwitchEnd;
                       break;
      }
      startline--;
    }
  }
  
  chsFree(ln);
  return (0);  
}
