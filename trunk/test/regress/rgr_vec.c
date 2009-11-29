/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#define UTL_UNITTEST
#include "libutl.h"
#include <time.h>

int main(void)
{
  vec_t vt = NULL;
  char *ss;
  long   ii,kk,jj;
  long mm, ll;
 
  chs_t str;
                                     
 
  srand(time(0));

  TSTSECTION("vec Basics") {
 
    TSTGROUP("Create") {
      vt = vecNew();
      TST("VEC created",(vt != NULL));
    }
    
    TSTGROUP("Values") {
    
      jj = vecGetN(vt,0,-1);
      TST();
      jj = 0;                                
      for (kk=0; kk<100; kk++) {
       ii = rand() & 0x3FF;
       _dbgmsg("index: [%ld] = %ld\n",ii,kk);
       if (jj < ii) jj = ii;
       vt = vecSetN(vt,ii,vecGetN(vt,ii,0)+1);
      }
      TSTNOTE("max ndx: [%ld] count: %ld\n",jj,vecCount(vt));
      TST("Integer values inserted", vecCount(vt) -1 == jj);
      ii = 0;
      for (kk = 0; kk < vecCount(vt); kk++) {
        ii += vecGetN(vt,kk,0); 
      }
      TST("sum matched", ii == 100);
      
    }      
    
    TSTGROUP("Dispose") {
      vt = vecFree(vt);
      TST("VEC destroyed",(vt == NULL));
    }
  }
  
  TSTDONE();

  exit(0);
}
