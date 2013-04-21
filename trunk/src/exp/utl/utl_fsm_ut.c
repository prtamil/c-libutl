/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This sofwtare is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#define UTL_C
#define UTL_UNITTEST

#include "utl.h"

FILE *f = NULL;
char buf[512];
int k=0;
int c=0;

#define START fsmSTART
#define OTHER 1 

int main (int argc, char *argv[])
{

  TSTPLAN("utl fsm test") {
    TSTSECTION("Simple FSM") {
      TSTGROUP("Start state") {
        TSTCODE {
          fsm {
            fsmState START: k = 1;
          } fsmEnd;
        } TSTEQINT("Start executed", 1,k);
        TSTCODE {
          k = 0;
          fsm {
            fsmState OTHER : k = 1;
          } fsmEnd;
        } TSTEQINT("No start state", 0,k);
        TSTCODE {
          k = 0;
          fsm {
            fsmState OTHER : k = 2;
            fsmState START : k = 1;
            fsmState     2 : k = 3;
          } fsmEnd;
        } TSTEQINT("Start is not the first", 1,k);
        TSTCODE {
          fsm {
            fsmState START : k = 1;
            fsmState OTHER : k += 2;
          } fsmEnd;
        } TSTEQINT("No fallthrough",1,k);
      }
    }
    
    TSTSECTION("Nested FSM") {
      TSTGROUP("Start state") {
        TSTCODE {
          k = 0;
          fsm {
            fsmState 0: k = 1; fsmGoto(1);
            fsmState 2: k = 3;
            fsmState 1: k += 10;
                        fsm {
                           fsmState 0: k += 100; fsmGoto(2);
                           fsmState 2: k += 1000; break;
                        } fsmEnd;
          } fsmEnd;
        } TSTEQINT("Nested",1112,k);
      }
    }
  } 
}
