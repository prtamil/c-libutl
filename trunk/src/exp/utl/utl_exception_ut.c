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


void functhrow(int e)
{
    utlThrow(e);
    TST("Returned to main",0); /* it's an error to be executed! */
}

int main (int argc, char *argv[])
{

  TSTPLAN("utl unit test: try/catch") {
  
    TSTSECTION("Simple catch") {
      TSTGROUP("catch 1") {
        TSTCODE {
          k = 0;
          utlTry      { utlThrow(1); }
          utlCatch(1) { k = 1; }
          utlCatch(2) { k = 2; }
          utlCatchAny { k = 9; }
          
        } TST("Exception 1 caught", k==1);
      }
     
      TSTGROUP("catch 2") {
        TSTCODE {
          k = 0;
          utlTry      { utlThrow(2); }
          utlCatch(1) { k = 1; }
          utlCatch(2) { k = 2; }
          utlCatchAny { k = 9; }
        } TST("Exception 2 caught", k==2);
      }
      
      TSTGROUP("catch default") {
        TSTCODE {
          k = 0;
          utlTry { utlThrow(3);  }
          utlCatch(1) { k = 1; }
          utlCatch(2) { k = 2; }
          utlCatchAny { k = 9; }
        } TST("Exception not caught", k==9);
      }

    }

    TSTSECTION("Different syntax") {
      TSTGROUP("catch 1") {
        TSTCODE {
          k = 0;
          utlTry       utlThrow(1);
          utlCatch(1)  k = 1;
          utlCatch(2)  k = 2;
          utlCatchAny  k = 9;
        } TST("Exception 1 caught", k==1);
      }
      
      TSTGROUP("catch 2") {
        TSTCODE {
          k = 0;
          utlTry       utlThrow(2);
          utlCatch(1)  k = 1;
          utlCatch(2)  k = 2;
          utlCatchAny  k = 9;
        } TST("Exception 2 caught", k==2);
      }
      
      TSTGROUP("catch default") {
        TSTCODE {
          k = 0;
          utlTry       utlThrow(3);
          utlCatch(1)  k = 1;
          utlCatch(2)  k = 2;
          utlCatchAny  k = 9;
        } TST("Exception not caught", k==9);
      }
    }
    
    TSTSECTION("Catch exceptions from functions") {
      TSTGROUP("catch 1") {
        TSTCODE {
          k = 0;
          utlTry       functhrow(1);
          utlCatch(1)  k = 1;
          utlCatch(2)  k = 2;
        } TST("Exception 1 caught", k==1);
      }
      
      TSTGROUP("catch 2") {
        TSTCODE {
          k = 0;
          utlTry       functhrow(2);
          utlCatch(1)  k = 1;
          utlCatch(2)  k = 2;
        }
        TST("Exception 2 caught", k==2);
      }
      
      TSTGROUP("catch default") {
        TSTCODE {
          k = 0;
          utlTry       functhrow(3);
          utlCatch(1)  k = 1;
          utlCatch(2)  k = 2;
          utlCatchAny  k = 9;
        }
        TST("Exception not caught", k==9);
        TSTFAILNOTE("Expected: %d got: %d",9,k);
      }
    }

    TSTSECTION("Nested") {
      TSTGROUP("2 levels") {
        TSTCODE {
          k = 0;
          utlTry      {
            utlTry      { functhrow(20); }
            utlCatch(10) {k += 10;}
            utlCatch(20) {k += 20;}
          }
          utlCatch(1) {k += 1;}
          utlCatch(2) {k += 2;}
        }
        TST("Exception 20 caught", k==20);
        
        TSTCODE {
          k = 0;
          utlTry {
            utlTry      { functhrow(2); }
            utlCatch(10) {k += 10;}
            utlCatch(20) {k += 20;}
          }
          utlCatch(1) {k += 1;}
          utlCatch(2) {k += 2;}
        }
        TST("Exception 2 caught", k==2);
      }
      
      TSTGROUP("Visibility") {
        TSTCODE {
          k = 0;
          utlTry {
            utlTry      { functhrow(2); }
            utlCatch(10) {k += 10;}
            utlCatch(20) {k += 20;}
          }
          utlCatch(1) {k += 1;}
          utlCatch(2) {k += 2; functhrow(10);}
          utlCatchAny {k += 100;}
        }
        TST("Inner try are invisible", k==102);
        TSTEXPECTED("%d",102,"%d",k);
      }

    }
    
    TSTSECTION("Multiple throw") {
      TSTGROUP("Same try") {
        TSTCODE {
          k = 0;
          utlTry      { utlThrow(2); }
          utlCatch(1) { k += 1; }
          utlCatch(2) { k += 2; functhrow(1);}
          utlCatchAny { k += 9; }
        } TST("Exception 2 then 1 caught", k==3);
      }
        
      TSTGROUP("Nested try") {
        TSTCODE {
          k = 0;
          utlTry      {
            utlTry      { functhrow(20); }
            utlCatch(10) {k += 10; functhrow(2);}
            utlCatch(20) {k += 20; utlThrow(10);}
          }
          utlCatch(1) {k += 1;}
          utlCatch(2) {k += 2;}
          
        }  TST("Exception 10,20,2 caught", k==32);
        
        TSTCODE {
          k = 0;
          utlTry      {
            utlTry      { functhrow(20); }
            utlCatch(10) {k += 10; functhrow(2);}
            utlCatch(20) {k += 20; utlThrow(10);}
          }
          utlCatch(1) {k += 1;}
          utlCatch(2) {k += 2; functhrow(3);}
          utlCatchAny {k += 100; }
        }  TST("Exception 10,20,2,3 caught", k==132);
      }
    }
    
  }
}
