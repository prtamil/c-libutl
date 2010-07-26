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
 
int getfirst(char *txt, pmx_t mtc)
{
  buf[k++] = txt[pmxStart(mtc,0)];
  buf[k] = '\0';
  return 0;
}

int main (void)
{ 
  pmx_t ret;
       
  TSTSECTION("pmx Basics") {
  
    ret = pmxMatchStr(lorem,"Lorem");
    TST("match literal string (1)",ret && pmxStart(ret,0)==0 && pmxLen(ret,0)==5);
    ret = pmxMatchStr(lorem,"ipsum");
    TST("match literal string (2)",!ret);
    ret = pmxMatchStr(lorem,">ipsum");
    TST("match literal string (3)",ret && pmxStart(ret,0)==6 && pmxLen(ret,0)==5);
    
    ret = pmxMatchStr(lorem,"<.><:4:l>");
    TST("match counted chars (1)",ret && pmxStart(ret,0)==0 && pmxLen(ret,0)==5);
    ret = pmxMatchStr(lorem,"<l><:4:l>");
    TST("match counted chars (2)",!ret);
    ret = pmxMatchStr(lorem,"><l><:4:l>");
    TST("match counted chars (3)",ret && pmxStart(ret,0)==6 && pmxLen(ret,0)==5);

    ret = pmxMatchStr(lorem,">d<*a>");
    TST("match star",ret && strncmp(lorem+pmxStart(ret,0), "dolor" ,pmxLen(ret,0))==0);
        
    ret = pmxMatchStr(lorem,"> <+=s-u> ");
    TST("match plus",ret && strncmp(lorem+pmxStart(ret,0), " ut " ,pmxLen(ret,0))==0);
    TSTIF_NOTOK {
      if (ret) TSTWRITE("%.*s\n",pmxLen(ret,0),lorem+pmxStart(ret,0));
    }
        
    ret = pmxMatchStr("1abc4","(<?d>)(<*D>)(<?d>)");
    k = (ret != NULL);
    if (k)  k = (pmxStart(ret,1) == 0) && (pmxStart(ret,2) == 1) && (pmxStart(ret,3) == 4); 
    if (k)  k = (pmxLen(ret,1)   == 1) && (pmxLen(ret,2)   == 3) && (pmxLen(ret,3) == 1);     
    TST("match options",k);
    k=0;    
    pmxScanStr(lorem,">&r<.>",getfirst);
    TST("scan string",strcmp(buf,"LPvAcMf") == 0);
  }
    
  TSTSECTION("pmx failall") {
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
