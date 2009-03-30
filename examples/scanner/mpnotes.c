/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#include "libutl.h"


#define TK_NOTE    x81
#define TK_PAUSE   x82
#define TK_DEFNOTE x83
#define TK_ABSNOTE x84
#define TK_UNKNOWN xFE

int main(int argc, char *argv[])
{
  if (argc < 2) return(1);
  
  pmxScanner(
    argv[1]
  ,
    pmxTokSet("(<?=,'>)<=a-gA-G>(<*==>)" ,TK_NOTE)
    pmxTokSet("(<?=,'>)&io(<*==>)", TK_DEFNOTE)
    pmxTokSet("&ip(<*==>)", TK_PAUSE)
    pmxTokSet("(<.>)", TK_UNKNOWN)
  , 
    pmxTokCase(TK_NOTE) :
       printf("NOTE: %.*s\n",pmxTokLen(0),pmxTokStart(0));
       continue;
                    
    pmxTokCase(TK_DEFNOTE):
       printf("DEFNOTE: %.*s\n",pmxTokLen(0),pmxTokStart(0));
       continue;
                       
    pmxTokCase(TK_PAUSE):
       printf("PAUSE: %.*s\n",pmxTokLen(0),pmxTokStart(0));
       continue;
       
    default: continue;  
  );

  return 0;
}
