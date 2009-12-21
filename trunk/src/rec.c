/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#include "libutl.h"

void *rec_cpy(rec_t a, rec_t b) 
{
  if (b != a) { 
    if (!b)  recFree(a);
    else {
      if (!a) a = malloc(recSize(b));
      if (!a) utlError(8912,utlErrInternal);
      memcpy(a,b,recSize(b));
      b->rec_f->cpy((void *)a,(void *)b);
    }
  }
  return a;
}

int rec_cmp(rec_t a, rec_t b)
{
   if (a == b) return 0;
   if (!a) return 1;
   if (!b) return -1;
   if (a->rec_f != b->rec_f) return (recPtrCmp(a->rec_f,b->rec_f));
   return (a->rec_f->cmp(a,b));
}
