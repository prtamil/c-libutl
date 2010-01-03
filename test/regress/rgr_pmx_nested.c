/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#define UTL_UNITTEST
#include "libutl.h"

int k=0;
int scan1(char *txt, pmx_t mtc)
{
  pmx_t m2;
  m2 = pmxMatchStr(txt+pmxStart(mtc,0),"<.><.>");
  if (m2) {
    TSTNOTE("scan0: %p %.*s",m2, pmxLen(m2,0),txt+pmxStart(mtc,0)+pmxStart(m2,0));
  }
   
  TSTNOTE("scan1: %p %c, %d",mtc, txt[pmxStart(mtc,0)],k++);
  return 0;
}

int main(void)
{
  pmx_t pp;
  
  TSTSECTION("pmx nested") {
  
    TSTGROUP("Values") {
       pp = pmxMatchStr("cc","<.>");
       TSTNOTE("ret=%p",pp);
       TST("r1",pp!=NULL);
       pp = pmxMatchStr("cc","<.>");
       TSTNOTE("ret=%p",pp);
       TST("r2",pp!=NULL);
       pmxScanStr("abc","<.>",scan1);
    }
    
  }    
  
  TSTDONE();
  
  exit(0);
}
