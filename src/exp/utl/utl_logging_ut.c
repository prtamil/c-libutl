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

int main (int argc, char *argv[])
{
  TSTPLAN("utl unit test: logging") {
    
    TSTSECTION("Enabled") {
      TSTGROUP("Enabled") {
        #ifdef UTL_NOLOGGING
          enabled = 0;
        #endif
        if (!TST("Logging enabled", enabled))
          TSTBAILOUT( "Logging is not enabled.");
      }
    }
    
  #ifndef UTL_NOLOGGING
    
    TSTSECTION("Defaults") {
        TST("log_file is NULL ", log_file == NULL);
        TST("logFile is stderr", logFile == stderr);
        TST("Level is OFF", log_level == log_Off);
    }
    
    TSTSECTION("Logging") {
      TSTGROUP("Change level") {
        TSTCODE {
          logLevel(Warn);
          k = 0;
          logIf(Info)  { k++; } /* If level is at least INFO  */
          logIf(Warn)  { k++; } /* If level is at least WARN  */
          logIf(Error) { k++; } /* If level is at least ERROR */
        } TST("logLevel() and logIf()", k == 2);
        TSTFAILNOTE("Failed with %d instead of 2",k); 
      }
  
      TSTGROUP("Log File") {
        TSTCODE
          logOpen("TSTOUT.tmp","w");
        TST("Log file opened",logFile != stderr);
        
        TSTCODE
          logClose();
        TST("Log file closed",logFile == stderr);
        
        TSTCODE  /* Log file should be empty */
          f = fopen("TSTOUT.tmp","r");
        TST("Able to read log file",f != NULL);
        
        TSTSKIP(TSTFAILED,"Unable to read log file") {
          TSTCODE {
            k = 0;
            while ((c=fgetc(f)) != EOF) k++;
            fclose(f);
            f=NULL;
          } TST("Log file empty",k == 0);
        }      
  
        TSTCODE
          logOpen("TSTOUT.tmp","w");
        TST("Log file opened",logFile != stderr);
        
        TSTCODE {
          k=0;
          logInfo("%d - This will never make it!",k++); /* shouldn't be executed */
          logWarn("%d - This warning will make it!",k++);
          logError("%d - That's too important!",k++);
        } TST("Log level respected",k == 2);

        TSTCODE
          logClose();
        TST("Log file closed",logFile == stderr);
        
        TSTCODE { /* Log file has only 3 lines */
          f = fopen("TSTOUT.tmp","r");
        } TST("Able to read log file",f != NULL);
          
        TSTSKIP(TSTFAILED,"Unable to read log") {
          TSTCODE {
            k = 0;
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
          } TST("Rest of log file is empty",k == 3);
        }
        
        TSTCODE
          logOpen("TSTOUT.tmp","a");
        TST("Log file opened (append)",logFile != stderr);
        
        TSTCODE {
          k=10;
          logInfo("%d - This will never make it!",k++); /* shouldn't be executed */
          logWarn("%d - This warning will make it!",k++);
          logError("%d - That's too important!",k++);
        } TST("Log level respected",k == 12);
        
        TSTCODE
          logClose();
        TST("Log file closed",logFile == stderr && log_file == NULL);
  
        TSTCODE { /* Log file has 5 lines */
          k = 0;
          f = fopen("TSTOUT.tmp","r");
        } TST("Able to read log file",f != NULL);
        
        TSTSKIP(TSTFAILED,"Unable to read log") {
          TSTCODE {
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
          } TST("Rest of log file is empty",k == 5);
          TSTNOTE("Also check the log file visually to ensure everything is ok!");
        }
  
      }
  
    }
#endif
  }
}
