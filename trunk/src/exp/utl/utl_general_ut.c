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
  TSTTITLE("utl unit test: general");
  
  TSTSECTION("General use constants") {
    TSTGROUP("utlEmptyFun()") {
      TST("Is not NULL", utlEmptyFun != NULL);
      TST("Can be called", utlEmptyFun() == 0);
    }

    TSTGROUP("utlEmptyString") {
      TST("Is not NULL", utlEmptyString != NULL);
      TST("Is empty", utlEmptyString[0] == '\0');
    }

    TSTGROUP("utlZero") {
      TST("Is zero", utlZero == 0);
    }
  }
  
  TSTSECTION("Output file") {
    /* We cannot play to much as the TST macros themselves use '{utl_output} */
    TSTGROUP("Defaults (stderr)") {
      TST("Defaults to NULL", utl_output == NULL);
      TST("Actually to stderr", utlOut == stderr);
    }
    
    TSTGROUP("Diverted") {
    
      TSTNOTE("");
      TSTNOTE("Result of next text will be diverted!");
  
      utlSetOutput("TSTOUT.tmp");
      
      TST("utl_output not null", utl_output != NULL);
      TST("utlOut not stderr", utlOut != stderr);
      TST("utlOut equals utl_output", utlOut == utl_output);
      
      utlSetOutput(NULL);
      TSTBLOCK {
        TSTNOTE("Read them back!");
        f = fopen("TSTOUT.tmp","r");
        if (f) {
          while (fgets(buf,512,f))
            fputs(buf,utlOut);
        }
        TST("Able to read it back",f != NULL);
      }
      if (f) {fclose(f); f = NULL;}
      TST("Back to default (NULL)", utl_output == NULL);
      TST("Back to default (stderr)", utlOut == stderr);
      
    }
  }
  
 
  TSTDONE();
}
