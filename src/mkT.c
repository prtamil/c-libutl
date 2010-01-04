
#include <stdio.h>
#include <time.h>
#include "libutl.h"

unsigned char T1[256];
unsigned char T2[256];

#define MAX 10000

#define swap(n,T) {unsigned char c; \
                 int i = (rand() >> 1) & 0xFF;\
                 int j = n & 0xFF;\
                 c=T[i]; T[i]=T[j]; T[j]=c;\
                }

#define P(T,k) printf("\\x%02X",T[k++])
#define print16(T) \
  { unsigned char *s;\
  printf("static unsigned char *" #T " ="); \
  for (k=0,s=T; k<256; ) {\
    printf("\n        \"");\
    P(T,k);P(T,k);P(T,k);P(T,k);P(T,k);P(T,k);P(T,k);P(T,k);\
    P(T,k);P(T,k);P(T,k);P(T,k);P(T,k);P(T,k);P(T,k);P(T,k);\
    printf("\"");\
  }\
  printf (";\n\n");\
  }
            

int main(void)
{
  int k;
  
   for (k=0;k<256;k++) {
     T1[k] = k;
     T2[k] = k;
   }
   
   srand(time(0));  
   for (k=0; k<MAX; k++) {
     swap(k,T1);
     swap(k,T2);     
   }

   print16(T1);
   print16(T2);
}
