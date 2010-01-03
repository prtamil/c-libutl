/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#include "libutl.h"

int main(void)
{
   vec_t t = NULL;
   int k=0;
   for (k=0; k<=10000000;k++) {
     vecSetS(t,k,"test");
   }
   vecFree(t);
   
   exit(0);
}
