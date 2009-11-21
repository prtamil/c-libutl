/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#include "libutl.h"

int main(int argc, char *argv[])
{
   tbl_t t = NULL;
   int k=0;
   for (k=0; k<=1000000;k++) {
     t = tblSetNS(t,k,"test");
   }
   t = tblFree(t);
   
   exit(0);
}
