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
int enabled=1;
logger lg = NULL;

int main (int argc, char *argv[])
{
  TSTPLAN("utl unit test: logging") {
    
    TSTSECTION("Enabled") {
        #ifdef UTL_NOLOGGING
          enabled = 0;
        #endif
        if (!TST("Logging enabled", enabled))
          TSTBAILOUT( "Logging is not enabled.");
    }
    
    TSTSECTION("NULL logger") {
      TSTEQPTR("logger is NULL", NULL,lg);
      TSTEQINT("logLevel is Warn", log_W , logLevel(lg,"") );
      TSTEQPTR("file is stderr", stderr, log_file(lg) );
      TSTCODE {
        logLevel(lg,"MSG");
      } TSTEQINT("NULL logger level can't be changed", log_W, logLevel(lg,"") );
    }
    
    TSTSECTION("Not NULL logger") {
    
      TSTCODE {
        logOpen(lg,"stdout","a");
      } 
      TSTNEQPTR("logger is not NULL", NULL,lg);
      TSTEQINT("logLevel is Warn", log_W, logLevel(lg,"") );
      TSTEQPTR("file is stdout", stdout, log_file(lg) );

      TSTCODE {
        logLevel(lg,"Msg");
      } TSTEQINT("Log level changed", log_M, logLevel(lg,"") );
      
      TSTCODE {
        k = 0;
        logIf(lg,"Info")  { k+=1; } /* If level is at least INFO  */
        logIf(lg,"Warn")  { k+=10; } /* If level is at least WARN  */
        logIf(lg,"Error") { k+=100; } /* If level is at least ERROR */
      } TSTEQINT("logLevel() and logIf()", 110, k );
      
      TSTCODE {
        logClose(lg);
      }
      TSTEQPTR("logger is NULL", NULL,lg);
      TSTEQINT("logLevel is Warn", log_W, logLevel(lg,"") );
      TSTEQPTR("file is stderr", stderr, log_file(lg) );
    }
  }
}
