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

void fmterr(int errnum, char *msg)
{
  fprintf(stderr,"** %d: ",curln) ;
  utlError(errnum,msg);
}

int main(int argc, char *argv[])
{
  int k;
  FILE *f;
  FILE *out = stdout;
  chs_t source = NULL;
  char *curchar;  

  chs_t tmps=NULL;

  if (argc <= 1)
    utlError(1,"Usage: fmt filename\n");

  f = fopen(argv[1],"r");

  if (f) {
    chsCpyFile(source,f);
    fclose(f);

    chsAddChr(source,'\n');

    curchar = source;

    style = 0;
    curln = 0;

    FSM {
      STATE(linestart) {
          curln++;
          pmxSwitch (curchar,
            pmxTokSet("&K.(<+=%>)",  T_HEADER)
            pmxTokSet("&K.v<?$erb><?$atim>", T_VERBATIM)
          ) {
            pmxTokCase(T_HEADER):
                  fprintf(out,"<h lvl=\"%d\" ln=\"%d\"",pmxTokLen(1),curln);
                  GOTO(header);

            pmxTokCase(T_VERBATIM):
                  fprintf(out,"<v ln=\"%d\"",curln);                  
                  verb_end[0] = '.'; verb_end[1] = '.'; verb_end[2] = '\0';
                  k=2;
                  GOTO(verbatim);

            pmxTokCase(pmxTokNONE) : GOTO(midline);

            pmxTokCase(pmxTokEOF)  : GOTO(done);
          }
          fprintf(stderr,"EEEKK\n"); break;
      }
      
      STATE(verbatim) {
          pmxSwitch (curchar,
            pmxTokSet("&K&<(<*!&>>)&>",  T_VRB_MARK)
            pmxTokSet("&K:(<*S>)",       T_VRB_FMT)
            pmxTokSet("&K(<+S>)",        T_VRB_END)
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
      }
      
      STATE(verb_body) {
          pmxSwitch (curchar,
            pmxTokSet("&L&n",T_VRB_LINE)
          ) {
            pmxTokCase(T_VRB_LINE):
                  curln++;
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
      }
      
      STATE(header) {
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
          
      }
      STATE(midline) {
          pmxSwitch (curchar,
            pmxTokSet("&n",   T_NL)
            pmxTokSet("`&n",  T_TICK)
            pmxTokSet("`<.>", T_ESCAPED)
            pmxTokSet("'&<",  T_REF)
            pmxTokSet("'|",   T_MONOSP)
            pmxTokSet("'$",   T_MATH)
            pmxTokSet("'*",   T_BOLD)
            pmxTokSet("'/",   T_ITALIC)
            pmxTokSet("'_",   T_ULINE)
            pmxTokSet("'&(",  T_NOTE)
            pmxTokSet("'{",   T_VAR)
            pmxTokSet("&>",   T_REF_END)
            pmxTokSet("|",    T_MONOSP_END)
            pmxTokSet("$",    T_MATH_END)
            pmxTokSet("*",    T_BOLD_END)
            pmxTokSet("/",    T_ITALIC_END)
            pmxTokSet("_",    T_ULINE_END)
            pmxTokSet(")",    T_NOTE_END)
            pmxTokSet("}",    T_VAR_END)
            pmxTokSet("<.>",  T_ANY)
          ) {

            pmxTokCase(T_TICK):     fputc('`',out); GOTO(midline);
            pmxTokCase(T_ESCAPED):  fputc(*pmxTokStart(0)+1,out); GOTO(midline);

            pmxTokCase(T_REF):            

            pmxTokCase(T_BOLD):
                 if (style & BOLD) fmterr(11, "Bold already enabled.");
                 style |= BOLD; fprintf(out,"<b>");
                 GOTO(midline);

            pmxTokCase(T_BOLD_END):
                 if (style & BOLD) { style &= ~BOLD; fprintf(out,"</b>"); }
                 else putc('*',out);
                 GOTO(midline);

            pmxTokCase(T_ITALIC):
                 if (style & ITALIC) fmterr(12, "Italic already enabled.");
                 style |= ITALIC; fprintf(out,"<i>");
                 GOTO(midline);

            pmxTokCase(T_ITALIC_END):
                 if (style & ITALIC) { style &= ~ITALIC; fprintf(out,"</i>"); }
                 else fputc('/',out);
                 GOTO(midline);

            pmxTokCase(T_MONOSP):
                 if (style & MONOSP) fmterr(13, "Monospace already enabled.");
                 style |= MONOSP; fprintf(out,"<tt>");
                 GOTO(midline);

            pmxTokCase(T_MONOSP_END):
                 if (style & MONOSP) { style &= ~MONOSP; fprintf(out,"</tt>"); }
                 else fputc('|',out);
                 GOTO(midline);

            pmxTokCase(T_MATH):
                 if (style & MATH) fmterr(14, "Math mode already enabled.");
                 style |= MATH; fprintf(out,"<m style=\"inline\">");
                 GOTO(midline);

            pmxTokCase(T_MATH_END):
                 if (style & MATH) { style &= ~MATH; fprintf(out,"</m>"); }
                 else fputc('$',out);
                 GOTO(midline);

            pmxTokCase(T_ULINE):
                 if (style & ULINE) fmterr(15, "Underline mode already enabled.");
                 style |= ULINE; fprintf(out,"<u>");
                 GOTO(midline);

            pmxTokCase(T_ULINE_END):
                 if (style & ULINE) { style &= ~ULINE; fprintf(out,"</u>"); }
                 else fputc('_',out);
                 GOTO(midline);

            pmxTokCase(T_NOTE):
                 if (style & NOTE) fmterr(16, "Footnote mode already enabled.");
                 style |= NOTE; fprintf(out,"<note>");
                 GOTO(midline);

            pmxTokCase(T_NOTE_END):
                 if (style & NOTE) { style &= ~NOTE; fprintf(out,"</note>"); }
                 else fputc(')',out);
                 GOTO(midline);

            pmxTokCase(T_NL):
                  GOTO(linestart);

            pmxTokCase(T_ANY): /*fputc(*pmxTokStart(0),out);*/
                  GOTO(midline);

            pmxTokCase(pmxTokEOF) : GOTO(done);
          }
          fprintf(stderr,"EEEKKX %d\n", pmxToken(pmx_tmpmtc));break;
       }
       STATE(done) {
         break;
       }
     }
  }
  else utlError(2,"Unable to open input file\n");

  if (source) chsFree(source);
  if (tmps) chsFree(tmps);
  
  exit(0);
}
