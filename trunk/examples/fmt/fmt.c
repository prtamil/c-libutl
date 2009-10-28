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
#define T_ANY       xF0

int main(int argc, char *argv[])
{
  int k;
  FILE *f; 
  FILE *out = stdout;
  chs_t source = NULL;

  if (argc <= 1) 
    utlError(1,"Usage: fmt filename\n");
     
  f = fopen(argv[1],"r");
  
  if (f) {
    source = chsRead(source,f,'w');
    fclose(f);
    pmxScannerBegin(source)
      pmxTokSet("&K.(<+=&%>)&K(&L)",T_HEADER)
      pmxTokSet("&K.v  &N..",T_HEADER)
      pmxTokSet("<.>",T_ANY)
      
    pmxTokSwitch
    
      pmxTokCase(T_HEADER):
        k = pmxTokLen(1);
        fprintf(out,"<H%d>%.*s</H%d>\n",k,pmxTokLen(2),pmxTokStart(2),k);
        continue;
          
      default: /*fputc(*pmxTokStart(0),out);*/
               continue;
      
    pmxScannerEnd;

  }
  else utlError(2,"Unable to open input file\n");

  if (source) source = chsFree(source);
  exit(0);
}
