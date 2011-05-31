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
  tbl_t t2 = NULL;
  char *ss;
  long   ii,kk,jj;
  long mm, ll;
  tbl_slot_t *q;
  chs_t str;
  /* Test for table of tables (and strings etc) */
  TSTSECTION("tbl") {
    TSTGROUP("CHS") {
      tblNew(tt);
      TST("TBL created",(tt != NULL));
      
      tblSetNS(tt,13,"pippo");
      
      kk = tblFindN(tt,13);
      TST("Found",(kk > 0));
      if (kk > 0) {
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
        chsAddStr(tblValS(tt,kk)," & pluto");
      }
      ss = tblGetNS(tt,13,"(none)");
      if (kk > 0) {
        for (jj=0;jj<10000;jj++)
          chsAddStr(tblValS(tt,kk)," & pluto");
      }
      str = tblGetNS(tt,13,"(none)");
      TST("Changed",(ss != str));
    }
    TSTGROUP("CHS") {
      tblNew(t2);
      tblSetNS(t2,5,"topoplino");
      tblSetNT(tt,3,t2);
      kk=tblFindN(tt,3);
      TST("found2:", (kk > 0));
      if (kk>0) {
        TST("type: ",(tblValType(tt,kk) == 'T'));
        t2 = tblValT(tt,kk);
        TST("Tbl retrieved", t2 != NULL);
        if (t2) {
          TSTNOTE("t2[5]     -> %s",tblGetNS(t2,5,NULL));
          TSTNOTE("tt[t2][5] -> %s",tblGetNS(tblValT(tt,kk),5,NULL));
          jj = tblFindN(t2,5);
          if (jj>0) {
            chsAddStr(tblValS(tblValT(tt,kk),jj),"xxx");
            TSTNOTE("tt[t2][5] -> %s",tblGetNS(tblValT(tt,kk),5,NULL));
          }
        } 
      }
    }    
    
  }    
  
    
  TSTDONE();
  
  exit(0);
}
