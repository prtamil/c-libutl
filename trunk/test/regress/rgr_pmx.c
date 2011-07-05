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
    TST("match star",ret && strncmp(pmxStartP(ret,0), "dolor" ,pmxLen(ret,0))==0);
        
    ret = pmxMatchStr(lorem,"> <+=s-u> ");
    TST("match plus",ret && strncmp(pmxStartP(ret,0), " ut " ,pmxLen(ret,0))==0);
    TSTIF_NOTOK {
      if (ret) TSTWRITE("%.*s\n",pmxLen(ret,0),pmxStartP(ret,0));
    }
        
    ret = pmxMatchStr("1abc4","(<?d>)(<*D>)(<?d>)");
    k = (ret != NULL);
    if (k)  k = (pmxStart(ret,1) == 0) && (pmxStart(ret,2) == 1) && (pmxStart(ret,3) == 4); 
    if (k)  k = (pmxLen(ret,1)   == 1) && (pmxLen(ret,2)   == 3) && (pmxLen(ret,3) == 1);     
    TST("match options (and captures)",k);
    TSTNOTE("(%.*s)(%.*s)(%.*s)",pmxLen(ret,1),pmxStartP(ret,1),pmxLen(ret,2),pmxStartP(ret,2),pmxLen(ret,3),pmxStartP(ret,3));
    
    ret = pmxMatchStr("1abc4","(<?d>((<*D>)<?d>))");
    k = (ret != NULL);
    if (k)  k = (pmxStart(ret,1) == 0) && (pmxStart(ret,2) == 1) && (pmxStart(ret,3) == 1); 
    if (k)  k = (pmxLen(ret,1)   == 5) && (pmxLen(ret,2)   == 4) && (pmxLen(ret,3) == 3);     
    TST("match options (and nested captures)",k);

    ret = pmxMatchStr("xxxx","(<?d>((<*A>)<?d>))");
    TST("Don't match emptiness",ret == NULL);
    
    ret = pmxMatchStr("01AfEX","<+x>");
    TST("Hex digits",ret && strncmp(pmxStartP(ret,0), "01AfE" ,pmxLen(ret,0))==0);
    
    ret = pmxMatchStr("0x01AfEX","<?$0x$0X><+x>");
    TST("Hex digits (and optional string)",ret && strncmp(pmxStartP(ret,0), "0x01AfE" ,pmxLen(ret,0))==0);
    
    ret = pmxMatchStr("01AfEX","<?$0x$0X><+x>");
    TST("Hex digits (no optional string)",ret && strncmp(pmxStartP(ret,0), "01AfE" ,pmxLen(ret,0))==0);
    
    k=0;    
    pmxScanStr(lorem,">&r<.>",getfirst);
    TST("scan string",strcmp(buf,"LPvAcMf") == 0);
  }
    
  TSTSECTION("pmx failall") {
    TSTGROUP("failall") {
      pmxScannerBegin("abcbdade")        
        pmxTokSet(x81, "ab&!c")
        pmxTokSet(x82, "ade")
        pmxTokSet(x83, "bda")
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
  
  TSTSECTION("pmx Goal") {
    TSTGROUP("positive look ahead") {
      ret = pmxMatchStr(lorem,"Lorem&g ipsum");
      TST("matched",ret != NULL);
      TST("look ahead", pmxLen(ret,0) == 5);
      
      ret = pmxMatchStr(lorem,"Lorem&G ipsum");
      TST("not matched",ret == NULL);
      TST("look ahead", pmxLen(ret,0) == 0);
      
      ret = pmxMatchStr(lorem,"Lorem&Gzzz");
      TST("matched",ret != NULL);
      TST("look ahead", pmxLen(ret,0) == 5);
      if (!TSTFAILED) 
         TSTNOTE("[%.*s]", pmxLen(ret,0), pmxStartP(ret,0));
      
      ret = pmxMatchStr(lorem,">&g.&k(M<+l>)");
      TST("matched",ret != NULL);
      TST("look ahead  (0 Len!)", pmxLen(ret,0) == 0);
      TST("look ahead  (>0 Start!)", pmxStart(ret,0) > 0);
      TST("look ahead  (Captured!)", pmxLen(ret,1) > 0);
      TST("look ahead  (Captured)", pmxStart(ret,1) > 0);
      if (!TSTFAILED) 
         TSTNOTE("[%.*s]", pmxLen(ret,1), pmxStartP(ret,1));
    
    }
  }
  
  TSTSECTION("Case sensitive") {
    TSTGROUP("simple") {
      ret = pmxMatchStr(lorem,"LOReM");
      TST("Not ignore case",ret == NULL);
      ret = pmxMatchStr(lorem,"&iLOReM");
      TST("Ignorecase",ret != NULL && pmxLen(ret,0)==5);
      ret = pmxMatchStr(lorem,"&iLO&IReM");
      TST("Ignore then dont (1)",ret == NULL);
      ret = pmxMatchStr(lorem,"&iLO&Irem");
      TST("Ignore then dont (2)",ret != NULL && pmxLen(ret,0)==5);
    }
  }

  TSTSECTION("escape") {
    TSTGROUP("simple") {
      ret = pmxMatchStr("'pippo'","&q");
      TST("Quoted string",ret != NULL && pmxLen(ret,0) == 7);
      ret = pmxMatchStr("'pip%'po'","&q");
      TST("Quoted string (with embedded quote)",ret != NULL && pmxLen(ret,0) == 6);
      ret = pmxMatchStr("'pip%'po'","&e%&q");
      TST("Quoted string (with escaped embedded quote)",ret != NULL && pmxLen(ret,0) == 9);
      ret = pmxMatchStr("'pip%'%'po'","&e%&q");
      TST("Quoted string (with two escaped embedded quote)",ret != NULL && pmxLen(ret,0) == 11);
    }
  }

  TSTSECTION("context") {
    TSTGROUP("simple") {
      ret = pmxMatchStr("5.3e-10xyz","&f<?[>e&f<]>x");
      TST("float exp",ret != NULL && pmxLen(ret,0) == 8);
      ret = pmxMatchStr("5.3x","&f<?[>e&f<]>x");
      TST("float exp2",ret != NULL && pmxLen(ret,0) == 4);
      if (TSTFAILED) { 
        TSTNOTE("exp2: %d %.*s\n",pmxLen(ret,0),pmxLen(ret,0),pmxStartP(ret,0));
      }
      
      ret = pmxMatchStr("123945934","<+=0-8>9");
      TST("plus",ret != NULL && pmxLen(ret,0) == 4);
      TSTNOTE("plus0: %d %.*s\n",pmxLen(ret,0),pmxLen(ret,0),pmxStartP(ret,0));
      
      ret = pmxMatchStr("123945934","<+[><+=0-8>9<]>");
      TST("plus",ret != NULL && pmxLen(ret,0) == 7);
      TSTNOTE("exp2: %d %.*s\n",pmxLen(ret,0),pmxLen(ret,0),pmxStartP(ret,0));
      
      ret = pmxMatchStr("123945934","<*[><+=0-8>9<]>");
      TST("plus",ret != NULL && pmxLen(ret,0) == 7);
      TSTNOTE("exp2: %d %.*s\n",pmxLen(ret,0),pmxLen(ret,0),pmxStartP(ret,0));
      
      ret = pmxMatchStr("1234534","<*[><+=0-8>9<]><+d>");
      TST("plus",ret != NULL && pmxLen(ret,0) == 7);
      TSTNOTE("exp2: %d %.*s\n",pmxLen(ret,0),pmxLen(ret,0),pmxStartP(ret,0));
      
    }
  }

  TSTDONE();
  
  exit(0);
}
