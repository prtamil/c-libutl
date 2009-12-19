/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

//#define UTL_UNITTEST
#include "libutl.h"

rec(point,
 int x; int y;
);

recFunCpy(point,a,b) { }
recFunCmp(point,a,b) { return ((char *)a-(char *)b);}
recFunNew(point,a) { }
recFunFree(point,a) { }

int main (int argc, char *argv[])
{
  int p;
  point *r = NULL;
     
  recNew(point, r);
  r->x = 3;
  r->y = 5;
  
  recFree(r);
  exit(0);
}
