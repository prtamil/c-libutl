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
  tbl_t tt;
  char *ss;
  long   ii,kk,jj;
  long mm, ll;
  tbl_slot_t *q;
  chs_t str;
  
  TSTSECTION("tbl") {
  
    TSTGROUP("Values");
    
    tt = tblNew();
    TST("TBL created",(tt != NULL));
    #if 0
    tt = tblSetNN(tt,3,4);
    
    ii = tblGetNN(tt,3,-1);
    TST("TBL set/get",ii==4);
    
    ii = tblGetNN(tt,4,-1);
    TST("TBL set/get",ii == -1);
    
    tt = tblSetNN(tt,3,5);
    ii = tblGetNN(tt,3,-1);
    TST("TBL set/get",ii==5);
    #endif
    tt = tblMaxSlot(tt,50000);
    
    for (ii=0; ii<49149; ii++) {
     tt = tblSetNN(tt,ii,ii*2);
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
    #if 0 
     TSTWRITE("# %d T[%c %d] = (%c %d)\n",kk++,tblKeyType(tt,ii),tblKeyN(tt,ii),
                                               tblValType(tt,ii),tblValN(tt,ii));
    #endif
     q = &tblSlot(tt,ii);
     if (q->flg[3]) jj++;
     else {
      mm = 1;
      while (q->aux.n >= 0) {
        mm++;
        q = &tblSlot(tt,q->aux.n+1);
      }
      if (mm > ll) ll = mm;
     } 
    }
    
    TSTNOTE("COUNT %ld (%ld, max: %ld) HTSIZE: %ld",tt->count,jj,ll,tt->size);
    
    for (ii=0; ii<49150; ii++) {
     kk = tblGetNN(tt,ii,-1);
     if (kk != 2 * ii) break;
    }
    
    TST("GetNN OK",kk != 2 * ii); 
    
    
    tt = tblFree(tt);
    TST("TBL freed",(tt == NULL));
    #if 1
    
    tt = tblNew();
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
     tblValS(tt,kk) = chsInsStr(tblValS(tt,kk),1,"xxxx"); 
    }
    
    str = tblGetSS(tt,"Pippo",NULL);
    
    TST("GetSS 2", str && strcmp(str,"Pxxxxluto")==0);
    
    tblValS(tt,kk) = chsInsStr(tblValS(tt,kk),0,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"); 
    
    TSTWRITE("[%s] = %s\n",tblKeyS(tt,kk), tblValS(tt,kk));
    
    tt = tblSetSS(tt,"",NULL);
    
    str = tblGetSS(tt,"","xx");
    TST("GetSS Empty", !str);
    
    str = tblGetSS(tt,"xx",NULL);
    TST("GetSS non existant", !str);
    
    tt = tblFree(tt);
    
    #endif
    
    tt = tblNew();
    tt = tblMaxSlot(tt,120);
    TST("MAX size", tt && tt->size >= 120);
    
    tt = tblMaxSlot(tt,130);
    TST("MAX size", tt && tt->size >= 130);
    tt = tblFree(tt);
  }    
  TSTDONE();
  
  exit(0);
}
