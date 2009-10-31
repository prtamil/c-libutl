/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#include <stdio.h>
#include "libutl.h"

#define T_HEADER    x81
#define T_VERBATIM  x82
#define T_NL        x83
#define T_ANY       xF0


#define MAX_SEC_NEST 20

int section[MAX_SEC_NEST];
int sec_curlvl=0;

int curline=0;

int main(int argc, char *argv[])
{
  int k;
  FILE *f; 
  FILE *out = stdout;
  chs_t source = NULL;
  char *curchar;

  if (argc <= 1) 
    utlError(1,"Usage: fmt filename\n");
     
  f = fopen(argv[1],"r");
  
  if (f) {
    source = chsNew();
    source = chsRead(source,f,'a');
    fclose(f);
    
    curchar = source;
    
    FSM {
      STATE(linestart):
          pmxSwitch (curchar,
            pmxTokSet("&K.(<+=&%>)&K(&L)&N",T_HEADER)
          ) {
            pmxTokCase(T_HEADER):
                  k = pmxTokLen(1);
                  fprintf(out,"<h%d>%.*s</h%d>\n",k,pmxTokLen(2),pmxTokStart(2),k);
                  GOTO(linestart);
            
             pmxTokCase(pmxTokNONE) : GOTO(midline);
                  
             pmxTokCase(pmxTokEOF)  : GOTO(done);
          }
          fprintf(stderr,"EEEKK\n");      
      
      STATE(midline) :  
          pmxSwitch (curchar,
            pmxTokSet("&n",T_NL)
            pmxTokSet("<.>",T_ANY)
          ) {
            pmxTokCase(T_NL):
                  GOTO(linestart);
            
             pmxTokCase(T_ANY): /*fputc(*pmxTokStart(0),out);*/
                  GOTO(midline);
                  
             pmxTokCase(pmxTokEOF) : GOTO(done);
          }
          fprintf(stderr,"EEEKK2\n");
          
       STATE(done) :
         break;
     }
  }
  else utlError(2,"Unable to open input file\n");

  if (source) source = chsFree(source);
  exit(0);
}
