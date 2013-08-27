#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <utl.h>

utl_assume(3 != 23);

int main (int argc, char *argv[])
{
  int x = 3;
  
  x+=4;
  
  utl_assume(sizeof(short) == 2);
  utl_assume(sizeof(int) == sizeof(long));
  utl_assume(sizeof(unsigned int) != sizeof(long));
   
  utl_assert(x>0);
  
  
  exit(0);
} 
