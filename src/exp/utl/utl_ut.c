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
  TSTTITLE("Unit test for utl.h");
  
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
  
  TSTSECTION("Logging") {
    TSTGROUP("Enabled") {
      #ifndef UTL_NOLOGGING
        TST("Logging is enabled", logFile == stderr);
      #else
        TST("Logging not enabled", 1>0);
      #endif
    }
    
    #ifndef UTL_NOLOGGING
    
    TSTGROUP("Defaults") {
      TST("log_file is NULL ", log_file == NULL);
      TST("logFile is stderr", logFile == stderr);
      TST("Level is OFF", log_level == log_Off);
    }
    
    TSTGROUP("Change level") {
      logLevel(Warn);
      k = 0;
      logIf(Info)  { k++; } /* If level is at least INFO  */
      logIf(Warn)  { k++; } /* If level is at least WARN  */
      logIf(Error) { k++; } /* If level is at least ERROR */
      
      TST("logLevel() and logIf()", k == 2);
      TSTIF_NOTOK { /* If last test failed */ 
        TSTNOTE("Failed with %d instead of 2",k); 
      }
    }

    TSTGROUP("Log File") {
      logOpen("TSTOUT.tmp","w");
      TST("Log file opened",logFile != stderr);
      logClose();
      TST("Log file closed",logFile == stderr);
      
      TSTBLOCK { /* Log file should be empty */
        k = 0;
        f = fopen("TSTOUT.tmp","r");
        TST("Able to read log file",f != NULL);
        if (f) {
          while ((c=fgetc(f)) != EOF) k++;
          fclose(f);
          f=NULL;
        } 
        TST("Log file empty",k == 0);
      }      

      logOpen("TSTOUT.tmp","w");
      TST("Log file opened",logFile != stderr);
      k=0;
      logInfo("%d - This will never make it!",k++); /* shouldn't be executed */
      logWarn("%d - This warning will make it!",k++);
      logError("%d - That's too important!",k++);
      TST("Log level respected",k == 2);
      logClose();
      TST("Log file closed",logFile == stderr);
      
      TSTBLOCK { /* Log file has only 3 lines */
        k = 0;
        f = fopen("TSTOUT.tmp","r");
        TST("Able to read log file",f != NULL);
        if (f) {
          while (fgets(buf,512,f)) {
            switch (k) {
               case 0 : TST("1st line is empty",buf[0] == '\n');
                        break;
               case 1 : TST("2nd line is warning",buf[20] == 'W');
                        break;
               case 2 : TST("3rd line is error",buf[20] == 'E');
                        break;
            }
            k++;
          }
          fclose(f);
          f=NULL;
        } 
        TST("Rest of log file is empty",k == 3);
      }
      
      logOpen("TSTOUT.tmp","a");
      TST("Log file opened (append)",logFile != stderr);
      k=10;
      logInfo("%d - This will never make it!",k++); /* shouldn't be executed */
      logWarn("%d - This warning will make it!",k++);
      logError("%d - That's too important!",k++);
      TST("Log level respected",k == 12);
      logClose();
      TST("Log file closed",logFile == stderr);

      TSTBLOCK { /* Log file has 5 lines */
        k = 0;
        f = fopen("TSTOUT.tmp","r");
        TST("Able to read log file",f != NULL);
        if (f) {
          while (fgets(buf,512,f)) {
            switch (k) {
               case 0 : TST("1st line is empty",buf[0] == '\n');
                        break;
               case 1 : TST("2nd line is warning",buf[20] == 'W');
                        break;
               case 2 : TST("3rd line is error",buf[20] == 'E');
                        break;
               case 3 : TST("4th line is warning",buf[20] == 'W');
                        break;
               case 4 : TST("5th line is error",buf[20] == 'E');
                        break;
            }
            k++;
          }
          fclose(f);
          f=NULL;
        } 
        TST("Rest of log file is empty",k == 5);
      }

    }

    #endif
  }
  
  TSTDONE();
}
