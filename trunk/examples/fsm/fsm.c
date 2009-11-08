/*
**  (C) by Remo Dentato (rdentato@gmail.com)
**
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php
*/


#include <stdio.h>
#include "libutl.h"


int main(int argc, char *argv[])
{
  chs_t str = NULL;

 
  str = chsCpyFmt(str,"value: %f %s 0x%04X\n",1.4,"LLLo",124);
  str = chsAddFmt(str,"and so %-10d on\n",34);

  printf("%s",str);
  exit(0);
}
