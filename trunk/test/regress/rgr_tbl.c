/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#define UTL_UNITTEST
#include "libutl.h"

int main(void)
{
  tbl_t tt = NULL;
  char *ss;
  long   ii,kk,jj;
  long mm, ll;
  tbl_slot_t *q;
  chs_t str;
  
  TSTSECTION("tbl") {
  
    TSTGROUP("Values") {
    
      tblNew(tt);
      TST("TBL created",(tt != NULL));
      tblSetNN(tt,3,4);
      
      ii = tblGetNN(tt,3,-1);
      TST("TBL set/get",ii==4);
      
      ii = tblGetNN(tt,4,-1);
      TST("TBL set/get",ii == -1);
      
      tblSetNN(tt,3,5);
      ii = tblGetNN(tt,3,-1);
      TST("TBL set/get",ii==5);
      
      _TSTBLOCK {
        for (ii=0; ii<49149; ii++) {
          tblSetNN(tt,ii,ii*2);
        }
      }
      
      tblSetSN(tt,"XX",131);
      ii = tblGetSN(tt,"XX",-1);
      TST("TBL set/get SN",ii==131);
      
      tblSetNS(tt,-3,"YY");
      ss = tblGetNS(tt,-3,"??");
      
      TST("TBL set/get NS",strcmp(ss,"YY") == 0);
      
      ll = 0;
      kk = 0;
      ii = 0; 
      jj = 0;
      tblForeach(tt,ii) {
       TSTWRITE("# %d T[%c %d] = (%c %d)\n",kk++,tblKeyType(tt,ii),tblKeyN(tt,ii),
                                                 tblValType(tt,ii),tblValN(tt,ii));
      }
      
      TSTNOTE("COUNT %ld (%ld, max: %ld) HTSIZE: %ld",tt->count,jj,ll,tt->size);
      
      for (ii=0; ii<49150; ii++) {
       kk = tblGetNN(tt,ii,-1);
       if (kk != 2 * ii) break;
      }
      
      TST("GetNN OK",kk != 2 * ii); 
      
      
      tblFree(tt);
      TST("TBL freed",(tt == NULL));
      
      _TSTBLOCK {
      
        tblNew(tt);
        tblSetNN(tt,432,431);
        ii = tblGetNN(tt,432,-1);
        tblDelN(tt,432);
        kk = tblGetNN(tt,432,-1);
        TST("Delete an element", (ii == 431 && kk == -1));
        
        tblSetSS(tt,"Pippo","Pluto");
        
        str = tblGetSS(tt,"Pippo",NULL);
        
        TST("GetSS", str && strcmp(str,"Pluto")==0);
        
        kk = tblFindS(tt,"Pippo");
        if (kk>0) {
          str = tblValS(tt,kk);
          chsInsStr(str,1,"xxxx"); 
        }
        
        str = tblGetSS(tt,"Pippo",NULL);
         
        TST("GetSS 2", str && strcmp(str,"Pxxxxluto")==0);
        str = tblValS(tt,kk);
        chsInsStr(str ,0,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"); 
        
        TSTWRITE("[%s] = %s\n",tblKeyS(tt,kk), tblValS(tt,kk));
        
        tblSetSS(tt,"",NULL);
        
        str = tblGetSS(tt,"","xx");
        TST("GetSS Empty", !str);
        
        str = tblGetSS(tt,"xx",NULL);
        TST("GetSS non existant", !str);
        
        tblFree(tt);
      }
      
    }
    
    TSTGROUP("floats")  {
      float f;
      tblNew(tt);
      for (kk = 0; kk < 1000; kk++) {
        tblSetFN(tt,2.00+(float)kk/100,kk);
      }
      f = 2.00+(float)3/100;
      TST("Float set", tblGetFN(tt,f,-1) == 3);
    }
  }    
  
  
  TSTDONE();
  
  exit(0);
}
