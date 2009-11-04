/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#include <stdio.h>
#include "libutl.h"

#define T_HEADER    x81
#define T_HDR_MARK  x81
#define T_HDR_CLASS x82
#define T_HDR_TITLE x83

#define T_VERBATIM  x82
#define T_VRB_MARK  x81
#define T_VRB_FMT   x82
#define T_VRB_END   x84
#define T_VRB_BODY  x85
#define T_VRB_LINE  x85

#define T_NL        x83

#define T_ANY       xF0


#define MAX_SEC_NEST 20

int section[MAX_SEC_NEST];
int sec_curlvl=0;

char verb_end[16];

#define BOLD    0x0001
#define ITALIC  0x0002
#define MONOSP  0x0004
#define NOTE    0x0008
#define REF     0x0010
#define MATH    0x0020
#define VAR     0x0040
#define ULINE   0x0080

unsigned short env;

int main(int argc, char *argv[])
{
  int k;
  FILE *f; 
  FILE *out = stdout;
  chs_t source = NULL;
  char *curchar;

  if (argc <= 1) 
    utlError(1,"Usage: fmt filename\n");
     
  f = fopen(argv[1],"r");
  
  if (f) {
    source = chsNew();
    source = chsRead(source,f,'a');
    fclose(f);
    
    chsAddChr(source,'\n');
    
    curchar = source;
    
    env = 0;
    
    FSM {
      STATE(linestart):
          pmxSwitch (curchar,
            pmxTokSet("&K.(<+=%>)",  T_HEADER)
            pmxTokSet("&K.v<?$erb><?$atim>", T_VERBATIM)
          ) {
            pmxTokCase(T_HEADER):
                  fprintf(out,"<h lvl=\"%d\"",pmxTokLen(1));
                  GOTO(header);
            
            pmxTokCase(T_VERBATIM):
                  fprintf(out,"<v");
                  verb_end[0] = '.'; verb_end[1] = '.'; verb_end[2] = '\0';
                  k=2;   
                  GOTO(verbatim);
            
            pmxTokCase(pmxTokNONE) : GOTO(midline);
                  
            pmxTokCase(pmxTokEOF)  : GOTO(done);
          }
          fprintf(stderr,"EEEKK\n"); break;      

      STATE(verbatim) :
          pmxSwitch (curchar,
            pmxTokSet("&K&<(<*!&>>)&>",  T_VRB_MARK)
            pmxTokSet("&K:&K(<*S>)",     T_VRB_FMT)
            pmxTokSet("&K(<+S>)",       T_VRB_END)
            pmxTokSet("<*!\n\r>&n",      T_VRB_BODY)
          ) {
            pmxTokCase(T_VRB_BODY):
                  fprintf(out,">");
                  GOTO(verb_body);
                  
            pmxTokCase(T_VRB_FMT):
                  fprintf(out," fmt=\"%.*s\"",pmxTokLen(1),pmxTokStart(1));
                  GOTO(verbatim);
            
            pmxTokCase(T_VRB_MARK):
                  fprintf(out," mark=\"%.*s\"",pmxTokLen(1),pmxTokStart(1));
                  GOTO(verbatim);

            pmxTokCase(T_VRB_END): 
                  k = pmxTokLen(1); if (k>15) k=15;
                  strncpy(verb_end,pmxTokStart(1),k);
                  verb_end[k] = '\0';
                  GOTO(verbatim);
                  
            pmxTokCase(pmxTokNONE) : GOTO(midline);
                  
            pmxTokCase(pmxTokEOF)  : GOTO(done);
          }
          fprintf(stderr,"EEEKK3\n"); break;      

      STATE(verb_body) :
          pmxSwitch (curchar,
            pmxTokSet("&L&n",T_VRB_LINE)
          ) {
            pmxTokCase(T_VRB_LINE):
                  if (strncmp(pmxTokStart(0),verb_end,k) == 0) {
                    fprintf(out,"</v>\n");
                    GOTO(linestart);                  
                  }
                  fprintf(out,"%.*s",pmxTokLen(0),pmxTokStart(0));
                  GOTO(verb_body);
                  
            pmxTokCase(pmxTokNONE) : GOTO(verb_body);
                  
            pmxTokCase(pmxTokEOF)  :
                  utlError(5,"File ended within a verbatim section\n");
                  GOTO(done);
          }
          fprintf(stderr,"EEEKK3\n"); break;      
      
      STATE(header) :
          pmxSwitch (curchar,
            pmxTokSet("&K:&K(<*S>)",T_HDR_CLASS)
            pmxTokSet("&K&<(<*!&>>)&>",T_HDR_MARK)
            pmxTokSet("&K(&L)&n",T_HDR_TITLE)
          ) {
            pmxTokCase(T_HDR_CLASS):
                  fprintf(out," class=\"%.*s\"",pmxTokLen(1),pmxTokStart(1));
                  k = 1;
                  GOTO(header);
                  
            pmxTokCase(T_HDR_MARK):
                  fprintf(out," mark=\"%.*s\"",pmxTokLen(1),pmxTokStart(1));
                  GOTO(header);

            pmxTokCase(T_HDR_TITLE):
                  fprintf(out,">%.*s</h>\n",pmxTokLen(1),pmxTokStart(1));
                  GOTO(linestart);
                  
            pmxTokCase(pmxTokNONE) : GOTO(midline);
                  
            pmxTokCase(pmxTokEOF)  : GOTO(done);
          }
          fprintf(stderr,"EEEKK3\n"); break;      
      
      STATE(midline) :  
          pmxSwitch (curchar,
            pmxTokSet("&n",  T_NL)
            pmxTokSet("<.>", T_ANY)
            pmxTokSet("`.",  T_ESCAPED)
            pmxTokSet("'<",  T_REF)
            pmxTokSet("'|",  T_MONOSP)
            pmxTokSet("'$",  T_MATH)
            pmxTokSet("'*",  T_BOLD)
            pmxTokSet("'/",  T_ITALIC)
            pmxTokSet("'_",  T_ULINE)
            pmxTokSet("'(",  T_NOTE)
            pmxTokSet("'{",  T_VAR)
            
          ) {
            pmxTokCase(T_NL):
                  GOTO(linestart);
            
            pmxTokCase(T_ANY): /*fputc(*pmxTokStart(0),out);*/
                  GOTO(midline);
                  
            pmxTokCase(pmxTokEOF) : GOTO(done);
          }
          fprintf(stderr,"EEEKK2\n"); break;      
          
       STATE(done) :
         break;
     }
  }
  else utlError(2,"Unable to open input file\n");

  if (source) source = chsFree(source);
  exit(0);
}
