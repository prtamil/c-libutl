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

  TSTSECTION("vec_basics") {
 
    _TSTGROUP("Create") {
      vt = vecNew();
      TST("VEC created",(vt != NULL));
    }
    
    TSTGROUP("Values") {
      jj = 0;            
      for (kk=0; kk<100; kk++) {
       ii = rand() & 0x3FF;
       _dbgmsg("index: [%ld] = %ld\n",ii,kk);
       if (jj < ii) jj = ii;
       vt = vecSetN(vt,ii,kk);
      }
      TSTWRITE("max ndx: [%ld] count: %ld\n",jj,vecCount(vt));
      TST("100 values added",(vecCount(vt) -1 == jj));
      
      vt = vecFree(vt);
      TST("VEC destroyed",(vt == NULL));
    }
  }
  TSTDONE();

  exit(0);
}
