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

int main (int argc, char *argv[])
{

  TSTPLAN("utl unit test: general") {
  
    TSTSECTION("General use constants") {
      TSTGROUP("utlEmptyFun()") {
        TSTNEQPTR("Is not NULL", NULL, utlEmptyFun );
        TSTEQINT("Can be called", 0,utlEmptyFun());
      }
  
      TSTGROUP("utlEmptyString") {
        TSTNEQPTR("Is not NULL", NULL,utlEmptyString);
        TSTEQINT("Is empty", '\0', utlEmptyString[0]);
      }
  
      TSTGROUP("utlZero") {
        TSTEQINT("Is zero", 0, utlZero);
      }
    }
    
    TSTSECTION("Output file") {
      /* We cannot play to much as the TST macros themselves use '{utl_output} */
      TSTGROUP("Defaults (stderr)") {
        TSTEQPTR("Defaults to NULL", NULL,utl_output);
        TSTEQPTR("Actually to stderr", stderr , utlOut);
      }
      
      TSTGROUP("Diverted") {
      
        TSTNOTE("");
        TSTNOTE("Result of next text will be diverted!");
    
        utlSetOutput("TSTOUT.tmp");
        
        TSTNEQPTR("utl_output not null", NULL,utl_output );
        TSTNEQPTR("utlOut not stderr", stderr,utlOut );
        TSTEQPTR("utlOut equals utl_output", utl_output,utlOut);
        
        utlSetOutput(NULL);
        TSTCODE {
          f = fopen("TSTOUT.tmp","r");
        } TSTNEQPTR("Able to read it back",NULL,f);
        if (!TSTFAILED) {
          TSTNOTE("Check the number order!");
          while (fgets(buf,512,f)) fputs(buf,utlOut);
          fclose(f); f = NULL;
        }
        TSTEQPTR("Back to default (NULL)", NULL,utl_output);
        TSTEQPTR("Back to default (stderr)", stderr,utlOut);
        
      }
    }
  }
   
}
