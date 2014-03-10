/*
**  (C) by Remo Dentato (rdentato@gmail.com)
**
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php
*/


#include <stdio.h>
#include "libutl.h"

#define T_HEADER     x81
#define T_HDR_MARK   x81
#define T_HDR_CLASS  x82
#define T_HDR_TITLE  x83
#define T_HDR_END    x84

#define T_VERBATIM  x82
#define T_VRB_MARK  x81
#define T_VRB_FMT   x82
#define T_VRB_END   x84
#define T_VRB_BODY  x85
#define T_VRB_LINE  x85

#define T_ESCAPED   x93
#define T_REF       x94
#define T_MONOSP    x95
#define T_MATH      x96
#define T_BOLD      x97
#define T_ITALIC    x98
#define T_ULINE     x99
#define T_NOTE      x9A
#define T_VAR       x9B
#define T_TICK      x9C

#define T_REF_END       xA4
#define T_MONOSP_END    xA5
#define T_MATH_END      xA6
#define T_BOLD_END      xA7
#define T_ITALIC_END    xA8
#define T_ULINE_END     xA9
#define T_NOTE_END      xAA
#define T_VAR_END       xAB


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

unsigned short style;

int curln;
char *cur;

FILE *out;

chs_t tmpstr[16];
int   tmpint[16];

#define header_title tmpstr[0]   
#define header_class tmpstr[1]   
#define header_mark  tmpstr[2]
#define header_level tmpint[0]
#define header_line  tmpint[1]   


void fmterr(int errnum, char *msg)
{
  fprintf(stderr,"** %d: ",curln) ;
  utlError(errnum,msg);
}

chs_t htmlesc(chs_t s)
{
  chsSubStr(s,0,"&&","&&amp;");
  chsSubStr(s,0,"&>","&&gt;");
  chsSubStr(s,0,"&<","&&lt;");
  return s;
} 

chs_t setstyle(chs_t s)
{
  chsSubStr(s,0,"'|(&e`<*!|>)|","<tt>&1</tt>");
  chsSubStr(s,0,"'/(&e`<*!/>)/","<i>&1</i>");
  chsSubStr(s,0,"'*(&e`<*!*>)*","<b>&1</b>");
  chsSubStr(s,0,"`(<.>)","&1");
  return s;
}

void text()
{
  int k;
  FSM {
    STATE (text) {     
         pmxSwitch (cur,
           pmxTokSet("&r&K.v<?$erb><?$atim>", T_VERBATIM)
           pmxTokSet("&r&K.(<+=%>)&K",  T_HEADER)
           pmxTokSet("(&L)&n",  T_ANY)
         ) {
           pmxTokCase(T_HEADER):
                 header_level = pmxTokLen(1);
                 header_line = curln;
                 chsCpy(header_title,"");
                 chsCpy(header_class,"");
                 chsCpy(header_mark,"");
                 GOTO(header);

           pmxTokCase(T_VERBATIM):
                 fprintf(out,"<v ln=\"%d\"",curln);                  
                 verb_end[0] = '.'; verb_end[1] = '.'; verb_end[2] = '\0';
                 GOTO(verbatim);

           pmxTokCase(T_ANY) : 
                 fprintf(out,"%.*s\n",pmxTokLen(1),pmxTokStart(1));
                 curln++;
                 GOTO(text);
                 
           pmxTokCase(pmxTokNONE) : 
           pmxTokCase(pmxTokEOF)  : GOTO(done);
         }
         fprintf(stderr,"EEEKK\n"); break;
    }
   
    STATE (verbatim) {
         pmxSwitch (cur,
           pmxTokSet("&K<?='>&<(<*!&>>)&>",  T_VRB_MARK)
           pmxTokSet("&K:(<*S>)",       T_VRB_FMT)
           pmxTokSet("&K(<+S>)",        T_VRB_END)
           pmxTokSet("<*!\n\r>&n",      T_VRB_BODY)
         ) {
           pmxTokCase(T_VRB_BODY):
                 fprintf(out,">\n");
                 curln++;
                 GOTO(verb_text);

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

           pmxTokCase(pmxTokNONE) :
           pmxTokCase(pmxTokEOF)  : GOTO(done);
         }
         fprintf(stderr,"EEEKK3\n"); break;
    }
    
    STATE (verb_text) {
          pmxSwitch (cur,
            pmxTokSet("(&L)&n",T_VRB_LINE)
          ) {
            pmxTokCase(T_VRB_LINE):
                  curln++;
                  if (strncmp(pmxTokStart(1),verb_end,pmxTokLen(1)) == 0) {
                    fprintf(out,"</v>\n");
                    GOTO(text);
                  }
                  fprintf(out,"%.*s",pmxTokLen(0),pmxTokStart(0));
                  GOTO(verb_text);

            pmxTokCase(pmxTokNONE) : 
            pmxTokCase(pmxTokEOF)  :
                  utlError(5,"File ended within a verbatim section\n");
                  GOTO(done);
          }
          fprintf(stderr,"EEEKK3\n"); break;
    }
    
    STATE (header) {
          pmxSwitch (cur,
            pmxTokSet("&K:&K(<*S>)",T_HDR_CLASS)
            pmxTokSet("&K<?='>&<(<*!&>>)&>",T_HDR_MARK)
            pmxTokSet("&K(&e`<+!\r\n<>)",T_HDR_TITLE)
            pmxTokSet("&K&n&K<*='\"~&-=>&K(&N)",T_HDR_END)
          ) {
            pmxTokCase(T_HDR_CLASS):
                  chsCpyL(header_class,pmxTokStart(1), pmxTokLen(1));
                  chsTrim(header_class," \t"," \t");
                  GOTO(header);

            pmxTokCase(T_HDR_MARK):
                  chsCpyL(header_mark,pmxTokStart(1), pmxTokLen(1));
                  chsTrim(header_mark," \t"," \t");
                  GOTO(header);

            pmxTokCase(T_HDR_TITLE):
                  chsCpyL(header_title,pmxTokStart(1),pmxTokLen(1));
                  chsTrim(header_title,NULL," \t");
                  GOTO(header);
                  
            pmxTokCase(T_HDR_END):
                  curln += (pmxTokLen(1) > 0 ? 2 : 1);
                  if (header_mark[0]) fprintf(out,"<a name=\"%s\"/>",header_mark);
                  fprintf(out,"<h%d",header_level);
                  if (header_class[0]) {
                    fprintf(out," class=\"%s\"",header_class);
                    if (!header_title[0]) chsCpy(header_title,header_class);
                  }
                  header_title = htmlesc(header_title);
                  header_title = setstyle(header_title);
                  fprintf(out,">%s</h%d>\n",header_title,header_level);
                  GOTO(text);

            pmxTokCase(pmxTokNONE) : 
            pmxTokCase(pmxTokEOF)  : GOTO(done);
          }
          fprintf(stderr,"EEEKK3\n"); break;
    
    }
    
    STATE (done) {
       BREAK;
    }
  }
}

int main(int argc, char *argv[])
{
  FILE *f;
  chs_t source = NULL;

  chs_t tmps=NULL;

  if (argc <= 1)
    utlError(1,"Usage: fmt filename\n");

  f = fopen(argv[1],"r");

  if (f) {
    chsCpyFile(source,f);
    fclose(f);

    chsAddChr(source,'\n');
    
    style = 0;
    curln = 1;
    cur = source;
    out = stdout;
    text();

  }
  else utlError(2,"Unable to open input file\n");

  if (source) chsFree(source);
  if (tmps) chsFree(tmps);
  
  exit(0);
}
