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
  "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. "
  "Sed libero sapien, sollicitudin consequat, tempor ut, elementum a, "
  "diam. Morbi eu risus sed felis porta fermentum. Phasellus sit amet."
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
      TST("CHS length is correct", k == strlen(uppers));
      TSTWRITE("# Next two lines should be identical\n");
      TSTWRITE("# >>  \"%s\"\n",uppers);
      TSTWRITE("# >>  \"%s\"\n",buf);
    
      chsDel(buf,'M'-'A','P'-'A');
      TST("Deleted \"MNOP\". Length is correct", k == chsLen(buf)+4);
      TSTWRITE("# Check that next lines don't have MNOP in it!\n");
      TSTWRITE("# >>  \"%s\"\n",buf);
    
      k = chsChrAt(buf,'L'-'A');
      TST("ChrAt in the middle", k == 'L');
    
      k = chsLen(buf);
      chsDel(buf, -4, -1);
      TST("Deleted \"WXYZ\" at the end. Length is correct", k == chsLen(buf)+4);
      TSTWRITE("# >>  \"%s\"\n",buf);
    
      k = chsLen(buf);
      chsDel(buf, 0, 3);
      TST("Deleted \"ABCD\" at the beginning. Length is correct", k == chsLen(buf)+4);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
    
      k = chsLen(buf);
      chsInsStr(buf, chsLen(buf), "ABCD");
      TST("Added \"ABCD\" at the end. Length is correct", k == chsLen(buf)-4);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
      
      k = chsLen(buf);
      chsInsStr(buf, 0, "WXYZ");
      TST("Added \"WXYZ\" at the beginning. Length is correct", k == chsLen(buf)-4);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);
      
      k = chsLen(buf);
      chsInsStr(buf,'M'-'A', "MNOP");
      TST("Added \"MNOP\" in the middle. Length is correct", k == chsLen(buf)-4);
      TSTWRITE("# >> [%ld]  \"%s\"\n",chsLen(buf),buf);      
    }
    
    TSTGROUP("Create/Destroy") {
      chsSubStr(buf ,0, "><=EGIKM>","++");
      TST("Replacing <=EGIKM> with '++'",1);
      TSTWRITE("# >>  \"%s\"\n",buf);
    
      chsSubStr(buf ,0, "><=PQRS>","[&0&0]");
      TST("Replacing <=PQRS> with '[&0&0]'", 4);
      TSTWRITE("# >>  \"%s\"\n",buf);
    }
      
    TSTGROUP("Destroy") {
      chsFree(buf);
      TST("CHS destroyed", buf == NULL);
    }
      
    TSTGROUP("Basic file reading") {
      f = fopen("txt.txt","r");
      if (f) { 
        chsCpyFile(buf,f);
        TSTWRITE("[[**************************\n");
        TSTWRITE("%s\n",buf);
        TSTWRITE("]]**************************\n");
        fclose(f);
        k = chsLen(buf);
        TST("File reading [1]", buf && k > 0);
      }
      else  TST("File reading [1]", 0);
      
      f = fopen("txt.txt","r");
      if (f) {
        chsAddFile(buf,f);
        TSTWRITE("[[**************************\n");
        TSTWRITE("%s\n",buf);
        TSTWRITE("]]**************************\n");
        fclose(f);
        TST("File reading [2]", buf && k *2 == chsLen(buf));
      }
      else  TST("File reading [2]", 0);
      
      f = fopen("txt.txt","r");
      if (f) {
        TSTWRITE("[[**************************\n");
        do {
          chsCpyLine(buf,f);
          if (chsLen(buf) == 0) break;
          TSTWRITE("{%s}",buf);
        } while (1);
        TSTWRITE("]]**************************\n");
        fclose(f);
        TST("File reading [3]", 1);
      } 
      else  TST("File reading [3]", 0);

      assert(buf != NULL);  
      chsFree(buf);
      assert(buf == NULL);  
    }
    
    _TSTGROUP("chs as a stream") {
      f = fopen("txt.txt","r");
      if (f) {
        chsCpyFile(buf,f);
        fclose(f);
        
      } 
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
    }
  }  
  
  chsFree(buf);
  TSTDONE();
  
  return 0;
}