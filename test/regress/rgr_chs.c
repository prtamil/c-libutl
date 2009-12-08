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
  int k;
  chs_t buf = NULL;
  FILE *f;
  size_t pos;
  char ln[256];
 
  TSTTITLE("");
  
  TSTSECTION("char strings (chs)") {
  
    TSTGROUP("Create/Destroy") {
     
      chsNew(buf);
      TST("String created", buf != NULL);
      TST("Size is one slot", chsSize(buf) == chs_blk_inc);
      TST("Length is 0", chsLen(buf) == 0);
      TST("Cur is 0", chsCur(buf) == 0);
      
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
    
      k = chsGetChr(buf);
      TST("Cur char is Q", k == 'Q');
      
      k = chsChrAt(buf,'L'-'A');
      TST("ChrAt in the middle", k == 'L');
      k = chsGetChr(buf);
      TST("GetChr after ChrAt ", k == 'Q');
    
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
      
      chsSubStr(buf ,0, "><=EGIKM>","++");
      TST("Replacing <=EGIKM> with '++'",1);
      TSTWRITE("# >>  \"%s\"\n",buf);
    
      chsSubStr(buf ,0, "><=PQRS>","[&0&0]");
      TST("Replacing <=PQRS> with '[&0&0]'", 4);
      TSTWRITE("# >>  \"%s\"\n",buf);
      
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
    
  }  
  TSTDONE();
  
  return 0;
}
