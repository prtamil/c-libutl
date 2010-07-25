/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#define UTL_UNITTEST
#include "libutl.h" 

char *lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n"
              "Praesent hendrerit, magna ut congue blandit, lectus metus\n"
              "vehicula mi, sit amet interdum mauris sapien eget tellus.\n"
              "Aliquam bibendum luctus ornare. Lorem ipsum dolor sit amet,\n"
              "consectetur adipiscing elit. Mauris ut pretium orci.\n"
              "Mauris dolor ante, semper vitae aliquam sit amet, vehicula\n"
              "fermentum diam. Nam lobortis hendrerit commodo.\n"; 

char *simp = "ab\ncd\r\nef\n";
 
char buf[32];
int k = 0;
 
int printfirst(char *txt, pmx_t mtc)
{
  buf[k++] = txt[pmxStart(mtc,0)];
  buf[k] = '\0';
  return 0;
}

int main (void)
{ 
     
  TSTSECTION("pmx Basics") {
    TSTGROUP("scan") {
      pmxScanStr(lorem,">&r<.>",printfirst);
      TST("scan",strcmp(buf,"LPvAcMf") == 0);
    }
    
    TSTGROUP("failall") {
      pmxScannerBegin("abcbdade")        
        pmxTokSet("ab&!c", x81)
        pmxTokSet("ade", x82)
        pmxTokSet("bda", x83)
      pmxScannerSwitch
      
        pmxTokCase(x81) : printf("ABC"); continue;
        pmxTokCase(x82) : printf("ADE"); continue;
        pmxTokCase(x83) : printf("BDA"); continue;
          
        default: break;
                
      pmxScannerEnd;
      printf("\n");  
      TST("failall",1);
    }
  }
  TSTDONE();
  
  exit(0);
}
