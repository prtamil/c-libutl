/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#define UTL_UNITTEST
#include "libutl.h"

rec(point,
 int x; int y;
);
 
recFunCmp(point,a,b) { return (recPtrCmp(a,b)); }
recFunCpy(point,a,b) { }
recFunUid(point,a)   { return (recPtrUid(a)); }
recFunFree(point,a)  { }
recFunNew(point,a)   { }

int main (int argc, char *argv[])
{
  point *r = NULL;
  point *s = NULL;
      
  TSTSECTION("rec Basics") {
 
    TSTGROUP("Create") {
      recNew(point, r);
      TST("Create", recIs(point,r));
      r->x = 3;
      r->y = 5;
      TST("Set values", r->x == 3 && r->y == 5);
    }
    
    TSTGROUP("Copy") {
      recCpy(s,r);
      TST("Copy record", r != s && r->x == s->x && r->y == s->y);
    }
    
    TSTGROUP("Set to vec") {
      vec_t vt = NULL;
      vecSetR(vt,4,r);
      TST("Add record to V", (point *)vecGetR(vt,4,NULL) == r);      
    }
    
    TSTGROUP("Destroy") {
      TSTNOTE("Destroying: %s", recName(r));
      recFree(r);
      recFree(s);
    }

  }
  exit(0);
}
