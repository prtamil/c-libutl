/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#define UTL_UNITTEST
#include "libutl.h"

int main(void)
{
  long   i,k,j;
  
  TSTSECTION("fsm") {
    TSTGROUP("basics") {
       k = 0;
       
       fsmStart(test1) {
         k++;
         if (k == 10) fsmExit(test1); 
         fsmGoto(test1);
       }
       
       fsmEnd(test1);
       
       TST("Single State",k==10);
       
       fsmStart(door) {
         i = 0; k = 0; j = 0;
       }
       
         fsmState(closed) {
           if (i > 10) fsmExit(door);
           if ((i & 1) == 1) fsmGoto(open);
           i++; k++;
           fsmGoto(closed);
         } 
         
         fsmState(open) {
           if (i > 10) fsmExit(door);
           if ((i & 1) == 0) fsmGoto(closed);
           i++; j++;
           fsmGoto(open);
         }
         
       fsmEnd(door);
       
       TST("door",i==11 && k == 6 && j == 5);
       TSTWRITE("%ld %ld %ld\n",i,k,j);
    }
  }    
  
  
  TSTDONE();
  
  exit(0);
}
