#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define UTL_LIB
#include <utl.h>

utlAssume(3 != 23);

int main (int argc, char *argv[])
{
  int x = 3;
  logWarn(logStderr,"Hello");
  logFatal(logStderr,"Hello (fatal)");
  x+=4;
  { utlAssume(sizeof(short) == 2);
    utlAssume(sizeof(int) == sizeof(long));
    utlAssume(sizeof(unsigned int) == sizeof(long));
    
    x -=2;
  }
   
  printf("%d\n",sizeof(log_abbrev));
  logAssert(logStderr, x>0 );
  logAssert(logStderr, x<0 );
  
  
  exit(0);
} 
