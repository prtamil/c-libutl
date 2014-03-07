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
char vec[512];
int k=0;
int c=0;
vec_t vv=NULL;

typedef struct {
  int x; int y;
} point;

point p1;
point p2;
point *p;

int main (int argc, char *argv[])
{

  p1.x =  1; p1.y =  2;
  p2.x = -1; p2.y = -2;

  TSTPLAN("utl unit test: vec") {
  
    TSTSECTION("vec creation") {
      TSTGROUP("vecNew()") {
        vv = vecNew(sizeof(point));
        TSTNEQPTR("Is not NULL", NULL, vv );
        TSTEQINT("Len 0", 0, vecCount(vv) );
      }
    }
    TSTSECTION("vec add") {
      TSTGROUP("vec set() 1") {
        vecSet(vv,0,&p1);
        TSTNEQPTR("Is not NULL", NULL, vv->vec );
        p = vecGet(vv,0);
        TSTEQINT("Set properly direct access", 1, p->x );
        TSTEQINT("Len 1", 1, vecCount(vv) );
      }
    }
  }
}
