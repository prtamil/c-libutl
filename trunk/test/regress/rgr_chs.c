/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This sofwtare is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#define UTL_UNITTEST
#include "libutl.h"

#include <assert.h>
#include <ctype.h>

char *lorem =
  "Lorem ipsum dolor sit amet, consectetuer adipiscing elit.\n"
  "Sed libero sapien, sollicitudin consequat, tempor ut, elementum a,\n"
  "diam. Morbi eu risus sed felis porta fermentum. Phasellus sit amet.\n"
#if 0  
  "Diam in gravida. Nunc et arcu vel turpis porttitor semper. Nulla "
  "facilisi. Integer lobortis urna in dolor. Nam eu nisl ac nibh "
  "elementum molestie. Proin eros. Cras ornare aliquam risus. Nulla sem "
  "tortor, pulvinar ac, elementum et, convallis a, velit. Proin mollis "
  "elit non augue. Ut laoreet nunc. Etiam imperdiet iaculis nibh. Donec "
  "nec eros. Vivamus posuere gravida sapien. Donec eros. Praesent ut "
  "pede at leo laoreet consequat. Sed in sem. "
#endif
   ;

char *uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(void)
{
  int k = 0;
  chs_t buf = NULL;
  FILE *f;
  /*char ln[256];*/
 
  TSTTITLE("");
  
  TSTSECTION("char strings (chs)") {
  
    TSTGROUP("Create/Destroy") {
     
      chsNew(buf);
      TST("String created", buf != NULL);
      TST("Size is one slot", chsSize(buf) == chs_blk_inc);
      TST("Length is 0", chsLen(buf) == 0);
      
      chsCpy(buf, uppers);
      k = chsLen(buf);
      TST("CHS length is correct", k == (int)strlen(uppers));
      TSTWRITE("# Next two lines should be identical\n");
      TSTWRITE("# >>  \"%s\"\n",uppers);
      TSTWRITE("# >>  \"%s\"\n",buf);
    
      chsDel(buf,'M'-'A','P'-'A');
      TST("Deleted \"MNOP\". Length is correct", k == chsLen(buf)+4);
      TST("Deleted \"MNOP\". ", strcmp(buf,"ABCDEFGHIJKLQRSTUVWXYZ") == 0);
      TSTWRITE("# Check that next lines don't have MNOP in it!\n");
      TSTWRITE("# >>  \"%s\"\n",buf);
    
      k = chsChrAt(buf,'L'-'A');
      TST("ChrAt in the middle", k == 'L');
    
      k = chsChrAt(buf,chsLen(buf)+100);
      TST("ChrAt past the end", k == '\0');
    
      k = chsLen(buf);
      chsDel(buf, -4, -1);
      TST("Deleted \"WXYZ\" at the end. Length is correct", k == chsLen(buf)+4);
      TST("Deleted \"WXYZ\" at the end. ", strcmp(buf,"ABCDEFGHIJKLQRSTUV") == 0);
      TSTWRITE("# >>  \"%s\"\n",buf);
    
      k = chsLen(buf);
      chsDel(buf, 0, 3);
      TST("Deleted \"ABCD\" at the beginning. Length is correct", k == chsLen(buf)+4);
      TST("Deleted \"ABCD\" at the beginning. ", strcmp(buf,"EFGHIJKLQRSTUV") == 0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
    
      k = chsLen(buf);
      chsInsStr(buf, chsLen(buf), "ABCD");
      TST("Added \"ABCD\" at the end. Length is correct", k == chsLen(buf)-4);
      TST("Added \"ABCD\" at the end. ", strcmp(buf,"EFGHIJKLQRSTUVABCD") == 0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
      
      k = chsLen(buf);
      chsInsStr(buf, 0, "WXYZ");
      TST("Added \"WXYZ\" at the beginning. Length is correct", k == chsLen(buf)-4);
      TST("Added \"WXYZ\" at the beginning. ", strcmp(buf,"WXYZEFGHIJKLQRSTUVABCD") == 0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
      
      k = chsLen(buf);
      chsInsStr(buf,'M'-'A', "MNOP");
      TST("Added \"MNOP\" in the middle. Length is correct", k == chsLen(buf)-4);
      TST("Added \"MNOP\" in the middle. ", strcmp(buf,"WXYZEFGHIJKLMNOPQRSTUVABCD") == 0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
            
    }
    
    TSTGROUP("Replace") {
      chsSubStr(buf ,0, "<=EGIKM>","++");
      TST("Replacing <=EGIKM> with '++'",strcmp(buf,"WXYZ++F++H++J++L++NOPQRSTUVABCD") == 0);
      TSTWRITE("# >>  \"%s\"\n",buf);
    
      chsSubStr(buf ,0, "<=PQRS>","[&0&0]");
      TST("Replacing <=PQRS> with '[&0&0]'",strcmp(buf,"WXYZ++F++H++J++L++NO[PP][QQ][RR][SS]TUVABCD") == 0);
      TSTWRITE("# >>  \"%s\"\n",buf);    
    }
      
    TSTGROUP ("Replace arr") {
      char *ra[] = {"A","B",NULL};
      char *rb[] = {"#&1#","$&2$&1$",NULL};
      char *rc[] = {"b","B",NULL};
      char *rd[] = {"&A","&B",NULL};
      
      chsCpy(buf,"xabc");
      chsSubArr(buf,0,"a&|b",ra);
      TST("repl arr1",strcmp(buf,"xABc")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
      
      chsCpy(buf,"xabc");
      chsSubArr(buf ,0, "a&|b",rd);
      TST("repl arr1",strcmp(buf,"xABc")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
    
      chsCpy(buf,"_123_x34_y_34z12");
      chsSubArr(buf,0,"(&d)&|(<l>)(&d)",rb);
      TST("repl arr1",strcmp(buf,"_#123#_$34$x$_y_#34#$12$z$")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
    
      chsCpy(buf,"xabc");
      chsSubArr(buf ,0, "&*a&|b",rc);
      TST("repl arr1",strcmp(buf,"xBBc")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
    
      chsSubStr(buf ,0, "B","Z");
      TST("repl arr1",strcmp(buf,"xZZc")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
    
      chsSubStr(buf ,0, "&rZ","B");
      TST("repl arr1",strcmp(buf,"xZZc")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
    
      chsSubStr(buf ,0, "&rx","z");
      TST("repl arr1",strcmp(buf,"zZZc")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
    
    }
    
    TSTGROUP("Insert") {
      chsCpy(buf,"xabc");
      chsInsChr(buf,2,'1');
      TST("Insert char",strcmp(buf,"xa1bc")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
    }
    
    TSTGROUP("Delete") {
      chsCpy(buf,"xZabc");
      chsDel(buf, 1, 1);
      TST("Deleted 1 char in the middle. ", strcmp(buf,"xabc") == 0);
      
      chsDel(buf, -1, -1);
      TST("Deleted 1 char at the end. ", strcmp(buf,"xab") == 0);
      
      chsDel(buf, 0, 0);
      TST("Deleted 1 char at the beginning. ", strcmp(buf,"ab") == 0);
    }
    
    TSTGROUP("Destroy") {
      chsFree(buf);
      TST("CHS destroyed", buf == NULL);
    }
      
    f = fopen("txt.txt","w");
    if (f) {
      fprintf(f,lorem);
      fclose(f);
    
      TSTGROUP("Basic file reading") {
        f = fopen("txt.txt","r");
        if (f) { 
          chsCpyFile(buf,f);
          TSTWRITE("[[**************************\n");
          TSTWRITE("%s\n",buf);
          TSTWRITE("]]**************************\n");
          fclose(f);
          k = chsLen(buf);
          TST("File reading [1]", buf && (strcmp(buf, lorem) == 0));
        }
        else  TST("File reading [1]", 0);
        
        f = fopen("txt.txt","r");
        if (f) {
          chsAddFile(buf,f);
          TSTWRITE("[[**************************\n");
          TSTWRITE("%s\n",buf);
          TSTWRITE("]]**************************\n");
          fclose(f);
          TST("File reading [2]", buf && k *2 == chsLen(buf) && strncmp(buf,buf+k,k) == 0);
        }
        else  TST("File reading [2]", 0);
        
        f = fopen("txt.txt","r");
        if (f) {
          chsCpy(buf,"");
          k = 0;
          TSTWRITE("[[**************************\n");
          do {
            chsAddLine(buf,f);
            if (k == chsLen(buf)) break;
            k = chsLen(buf);
          } while (1);
          TSTWRITE("%s\n",buf);
          TSTWRITE("]]**************************\n");
          fclose(f);
          TST("File reading [3]" , buf && (strcmp(buf, lorem) == 0));
        } 
        else  TST("File reading [3]", 0);
  
        assert(buf != NULL);  
        chsFree(buf);
        assert(buf == NULL);  
      } 
    }
    else  {
      TST("Create text file",0);
    }
        
    TSTGROUP("Upper/Lower/Reverse") {
      chsCpy(buf,"abc");
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);      
      chsUpper(buf);
      TST("Upper",strcmp(buf,"ABC")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);      
      chsLower(buf);
      TST("Lower",strcmp(buf,"abc")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);      
      chsReverse(buf);
      TST("Reverse",strcmp(buf,"cba")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);      
    } 
    
    TSTGROUP("Delete") {
      chsCpy(buf,"012345678");
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
      chsDel(buf,4,4) ;     
      TST("Del 4,4",strcmp(buf,"01235678")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
      chsDel(buf,2,3) ;     
      TST("Del 2,3",strcmp(buf,"015678")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
      chsDel(buf,4,-1);      
      TST("Del 4,-1",strcmp(buf,"0156")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
      chsDel(buf,0,1);      
      TST("Del 0,1",strcmp(buf,"56")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
      chsDel(buf,0,-1);      
      TST("Del 0,-1",*buf == '\0');
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
    }
        
    TSTGROUP("Trim") {
      chscpy(buf,"xxyxxabcxxyxx");
      TSTWRITE("# >> [%2ld]  \"%s\"\n",chslen(buf),buf);
      k=chslen(buf);
      chstrim(buf,"x",NULL);
      TST("trim x left", k == chslen(buf)+2);
      TSTWRITE("# >> [%2ld]  \"%s\"\n",chslen(buf),buf);
      k=chslen(buf);
      chstrim(buf,NULL,"x");
      TST("trim x right", k == chslen(buf)+2);
      TSTWRITE("# >> [%2ld]  \"%s\"\n",chslen(buf),buf);
      k=chslen(buf);
      chstrim(buf,"xy","xy");
      TST("trim xy right and left", k == chslen(buf)+6);
      TSTWRITE("# >> [%2ld]  \"%s\"\n",chslen(buf),buf);
    }
    
    TSTGROUP ("Formatting") {
      chscpyf(buf,"x:%d, y:%d, d:%c",3,4,'N');
      TST("Format 1",strcmp(buf,"x:3, y:4, d:N")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);

      chscpyf(buf,"x:%02d, y:%05.2f, d:%s",3,4.3,"NE");
      TST("Format 2",strcmp(buf,"x:03, y:04.30, d:NE")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
      
      chsCpy(buf,"[[]]");
      chsInsFmt(buf,2,"%04X",23147);
      TST("Format 3",strcmp(buf,"[[5A6B]]")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
      
      chsAddFmt(buf,"%04X",23147);
      TST("Format 4",strcmp(buf,"[[5A6B]]5A6B")==0);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
    }
    
  }  
  
  chsFree(buf);
  TSTDONE();
  
  return 0;
}
