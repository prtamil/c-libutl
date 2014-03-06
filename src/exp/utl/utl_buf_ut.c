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
buf_t s=NULL;

int main (int argc, char *argv[])
{

  TSTPLAN("utl unit test: buf") {
  
    TSTSECTION("buf creation") {
      TSTGROUP("bufNew()") {
        s = bufNew();
        TSTNEQPTR("Is not NULL", NULL, s );
      }
    }
    TSTSECTION("buf add") {
      TSTGROUP("buf set() 1") {
        TSTEQINT("Len 0", 0, bufLen(s) );
        bufSet(s,0,'a');
        TSTNEQPTR("Is not NULL", NULL, s );
        TSTEQINT("Set properly direct access", 'a', bufStr(s)[0] );
        TSTEQINT("Set properly (chrAt)", 'a', bufGet(s,0) );
        TSTEQINT("Len 1", 1, bufLen(s) );
      }
      TSTGROUP("buf set() 2") {
        bufSet(s,1,'b');
        TSTEQINT("Len 2", 2, bufLen(s));
        TSTEQINT("Len 2", strlen(bufStr(s)), bufLen(s));
        TSTEQINT("Set properly direct access", 0, strcmp("ab",bufStr(s)) );
        TSTFAILNOTE("str: [%s]\n",bufStr(s));
      }
    }
  }
}
