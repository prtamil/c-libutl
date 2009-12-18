/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This sofwtare is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#include "libutl.h"

#define CODE    1
#define COMMENT 2

int state = CODE;

chs_t ln;
pmx_t ret;

int main(int argc, char *argv[])
{
  FILE *inf = stdin;
  FILE *outf = stdout;
  FILE *tmpf;
  char *cur;
  char *fname = "(stdin)";
  int switch_num=0, case_num=0, c;
  
  tmpf = tmpfile();
  if (!tmpf) utlError(202,"Unable to open temp file");

  if (argc > 1) { 
    fname = argv[1];
    inf = fopen(argv[1],"r");
  }
  if (!inf) utlError(203,"Unable to open input file");

  if (argc > 2)
    outf = fopen(argv[2],"w");
  if (!outf) utlError(204,"Unable to open output file");

  for (chsReadln(ln, inf, 'w'); chsLen(ln) > 0; chsReadln(ln, inf, 'w')) {
    cur = ln;
    _dbgmsg("LINE: %s\n",cur);
    while (*cur) {
      switch (state) {
        case CODE :
              if ((ret = pmxMatchStr(cur,"/*"))) {
                state = COMMENT;
                fprintf(tmpf,"%.*s", pmxLen(ret,0), cur);
                cur += pmxLen(ret,0);
              }
              else if ((ret = pmxMatchStr(cur,"&e\\&q"))) {
                fprintf(tmpf,"%.*s", pmxLen(ret,0), cur);
                cur += pmxLen(ret,0);
              }
              else if ((ret = pmxMatchStr(cur,"switch<+s>pmx<*s>(&b())"))) {
                switch_num++;
                case_num = 0;
                fprintf(tmpf,"pmx_switch(%.*s,pmx_%d)", pmxLen(ret,1)-2,
                                             cur+pmxStart(ret,1)+1,switch_num);
                cur += pmxLen(ret,0);
              }
              else if ((ret = pmxMatchStr(cur,"case<+s>&e\\(&b\"\")"))) {
                if (case_num == 0) 
                  fprintf(outf,";\nstatic char *pmx_%d = \n",switch_num);
                else 
                  fprintf(outf,"\"&|\"\n");
                case_num++;
                fprintf(outf,"  %.*s",pmxLen(ret,1),cur+pmxStart(ret,1));
                fprintf(tmpf,"case %d", case_num);
                cur += pmxLen(ret,0);
              }
              else {
                fprintf(tmpf,"%c", *cur);
                cur++;
              }
              break;
        
        case COMMENT :
              if ((ret = pmxMatchStr(cur,"*/"))) {
                state = CODE;
                fprintf(tmpf,"%.*s", pmxLen(ret,0), cur);
                cur += pmxLen(ret,0);
              }
              else {
                fprintf(tmpf,"%c", *cur);
                cur++;
              }
              break;
      
      }
    }
  }
  
  fprintf(outf,";\n\n");
  fprintf(outf, 
    "#define pmx_switch(s,n) "
    "switch ((pmx_cur=s, (pmx_ret=pmxMatchStr(s,n)), (s)+=pmxLen(pmx_ret,0), pmxMatched(pmx_ret)))\n");

  fprintf(outf,"\n");
  fprintf(outf, "#define pmx_Start(x) pmx_cur+pmxStart(pmx_ret,x)\n");
  fprintf(outf, "#define pmx_End(x) pmx_cur+pmxEnd(pmx_ret,x)\n");
  fprintf(outf, "#define pmx_Len(x) pmxLen(pmx_ret,x)\n");
  fprintf(outf, "#define pmx(w,n)  pmx_##w(n)\n");  

  fprintf(outf,"\n");
  fprintf(outf,"static void *pmx_ret;\n");
  fprintf(outf,"static char *pmx_cur;\n");
    
  fprintf(outf,"\n");
  fprintf(outf,"#line 1 \"%s\"\n",fname);
  
  fseek(tmpf,SEEK_SET,0);
  while ((c = fgetc(tmpf)) != EOF) 
    fputc(c,outf);
  
  if (outf != stdout) fclose(outf);
  if (inf  != stdin)  fclose(inf);
  fclose(tmpf);
  exit (0);  
}
