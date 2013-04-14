/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This sofwtare is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#define UTL_C
#define UTL_MEMCHECK
#define UTL_UNITTEST

#include "utl.h"

int main (int argc, char *argv[])
{
  char *ptr_a;
  char *ptr_b;
  int valid;
  
  TSTPLAN("utl unit test: memory check") {
    logLevel(Info);
    logOpen("memory.info","w");

    TSTSECTION("malloc") {
      TSTGROUP("malloc") {
        TSTCODE {
           ptr_a = malloc(32);
        }
        TST("Check Valid after malloc()",utlMemCheck(ptr_a) == utlMemValid);
        TST("Allocated memory is 32",utlMemAllocated == 32);
        
        TSTCODE {
           free(ptr_a);
        }
        TST("Check invalid after free",utlMemCheck(ptr_a) < utlMemValid);
        TST("Allocated memory is 0",utlMemAllocated == 0);
        TSTCODE {
           free(ptr_a);
        }
        TST("Check invalid again",utlMemCheck(ptr_a) < utlMemValid);
      }
      TSTGROUP("malloc (overrun memory)") {
        TSTCODE {
           ptr_a = malloc(16);
        }
        TST("Check Valid after malloc()",utlMemCheck(ptr_a) == utlMemValid);
        TST("Allocated memory is 16",utlMemAllocated == 16);
        TSTCODE {
           ptr_a[16] = '\0';
        }
        TST("Check invalid after overrun",utlMemCheck(ptr_a) == utlMemOverflow);
      
      }
    }
    TSTNOTE("Check the file 'memory.info' to see the log of traced allocations");
  }
  
  logClose();
}