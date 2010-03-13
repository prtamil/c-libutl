/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


/*
** This example is mainly to illustrate how to use the |chsSubFun()|
** function. It is derived from the <musicpad|http://l01c.ouvaton.org/musicpad-help.html>
** language (for which I hope to write a full interpreter one day or another).
**
** The general idea is that we can define a macro everywhere in a text
** with the syntax: |m$xxx(...)| and then having it replaced by using |$xxx|.
** A macro can contain other macros so that the text:
**   "m$a([$b])m$b(turpis)Curabitur $a sed massa $b."
** is expanded as:
**   "Curabitur [turpis] sed massa turpis."
**
** Macros can have "arguments": The strings $1,...,$9 
**
** In general macros can have a type (e.g. |mrnd$x($a $b)| expands as |$a| or
** as |$b| at random). Macros in this form ar recognized but not handled in
** this example.
*/

#include <stdio.h>
#include <ctype.h>

#include "libutl.h"


int tempo          = -1;
int ppqn           = -1;
int duty           = -1;
int velocity       = -1;
int globalloose_w  = -1;
int globalloose_q  = -1;
int globalvelvar_w = -1;
int globalvelvar_q = -1;
int globalguiton   = -1;

tbl_t macros  = NULL;
chs_t tmptext = NULL;
chs_t rpl     = NULL;
vec_t args    = NULL;
vec_t tracks  = NULL;

#define DO_CLEANUP 0

void usage()
{
  fprintf(stderr,"Usage: mpad filename\n" );
  exit(1);
}

void merr(char *msg)
{
  fprintf(stderr,"ERR: %s\n",msg);
  exit(1);
}


char *subargs(char *str, pmx_t capt)
{ 
  int k;
  char *r;

  k  = str[pmxStart(capt,0)+1];
  if (k == '$') return ("$");
  
  k -= '1';
  r  = vecGetS(args, k, NULL);
  
  return (r? r : utlEmptyString);
}

char *submacro(char *str, pmx_t capt)
{
  char *name;
  char *bd;
  char c;
  
  if (pmxLen(capt,1) == 0) return "";
  
  name = str+pmxStart(capt,1);
  c = name[pmxLen(capt,1)]; 
  name[pmxLen(capt,1)] = '\0';
  
  while (*name) { 
    *name = tolower((int)*name);
    name++;    
  }    
  name = str+pmxStart(capt,1);
  
  bd = tblGetSS(macros,name,NULL);
   
  if (!bd) {
    fprintf(stderr,"Unknown macro: '%s'\n",name);
    return "";
  }
  
  while (*bd && *bd++ != '$');
  chsCpy(rpl,"(");
  chsAddStr(rpl,bd);
  chsAddChr(rpl,')');
  
  name[pmxLen(capt,1)] = c;

  vecFree(args);
  if (pmxLen(capt,2)>2) {  
    name = str+pmxStart(capt,2);
    c = name[pmxLen(capt,2)]; 
    name[pmxLen(capt,2)] = '\0';
    
    args = vecSplit(name,","," \t()");
    name[pmxLen(capt,2)] = c;
  }
  
  /* replace args */
  chsSubFun(rpl,0,">$<=$1-9>",subargs);
  
  return rpl;
}

char *mulstr(char *str, pmx_t capt)
{
   int k;
   int l;
   char *s;
      
   k = atoi(str+pmxStart(capt,2));
   if (k <= 0) return " ";
   
   l=pmxLen(capt,1);
   if (l <= 0) return " ";
   
   s = str+pmxStart(capt,1);   
   
   chsCpy(tmptext,"(");
   while (k-- > 0) {
     chsAddStrL(tmptext, s, l);
     chsAddChr(tmptext,' ');
   }
   chsAddStr(tmptext,") ");
   
   return tmptext;   
}

char *mulpar(char *str, pmx_t capt)
{
   int k;
   int l;
   char *s;
      
   k = atoi(str+pmxStart(capt,2));
   if (k <= 0) return " ";
   
   l=pmxLen(capt,1)-2;
   if (l <= 0) return " ";
   
   s = str+pmxStart(capt,1)+1;   
   
   chsCpy(tmptext,"(");
   while (k-- > 0) {
     chsAddStrL(tmptext, s, l);
     chsAddChr(tmptext,' ');
   }
   chsAddStr(tmptext,") ");
   
   return tmptext;   
}

void blankit(char *str, int len)
{
  while (len-- > 0) *str++ = ' ';
}

int blankcomment(char *str, pmx_t ret)
{
  blankit(str+pmxStart(ret,0), pmxLen(ret,0));
  return 0;
}

int getmacro(char *str, pmx_t ret)
{
  chs_t body = NULL;
    
  str[pmxEnd(ret,2) ]  = '\0';
  str[pmxEnd(ret,3)-1] = '\0';  
  
  chsCpy(body,"$");
  chsAddStrL(body, str+pmxStart(ret,3)+1, pmxLen(ret,3));
     
  tblSetSH(macros, str+pmxStart(ret,2), body);
  blankit(str+pmxStart(ret,0), pmxLen(ret,0));

  return 0;
}

chs_t expand(chs_t text)
{
  /* get and expand macros */
  pmxScanStr(text, ">&Km(<?$rnd>)$(<+a>)&K(&b())&K(&N)", getmacro);
  chsSubFun(text, 0,"&*$(<*a>)(&B())",submacro);

  /* Multiply */  
  chsSubFun(text,0,"&*(&b())&K*&K(&d)&K",mulpar);
  chsSubFun(text,0,"&*(<+! \t*>)&K*&K(&d)&K",mulstr);
  
  /* cleanup parenthesis*/
  chsSubStr(text,0,"<+=()>","");
  
  if (DO_CLEANUP) {
    tblFree(macros);
    vecFree(args);
  }
  
  return text;
}

chs_t parseglobals(chs_t text)
{

  #define T_TEMPO       x81
  #define T_RESOLUTION  x82
  #define T_PPQN        x83
  #define T_DUTY        x84
  #define T_VELOCITY    x85
  #define T_GLOOSE      x86
  #define T_GVELVAR     x87
  #define T_GGUITON     x88 
  #define T_ANY         x89 
  
  pmxScannerBegin(text)
                       
    pmxTokSet("tempo&K(&D)",T_TEMPO)
    pmxTokSet("resolution&K(&D)",T_RESOLUTION)
    pmxTokSet("ppqn&K(&D)",T_PPQN)
    pmxTokSet("duty&K(&D)",T_DUTY)
    pmxTokSet("velocity&K(&D)",T_VELOCITY)
    pmxTokSet("g<?$lobal>loose&K(&d)&K,&K(<+=0-9g>)",T_GLOOSE)
    pmxTokSet("g<?$lobal>loose&K(&d)",T_GLOOSE)
    pmxTokSet("g<?$lobal>velar&K(&d)&K,&K(<+=0-9g>)",T_GVELVAR)
    pmxTokSet("g<?$lobal>velar&K(&d)",T_GVELVAR)
    pmxTokSet("g<?$lobal>guiton",T_GGUITON) 
    pmxTokSet("<.>",T_ANY) 
                        
  pmxScannerSwitch
 
    pmxTokCase(T_TEMPO):
      if (pmxTokLen(1) == 0) merr("Invalid tempo");
      if (tempo >= 0) merr("Tempo already specified");
      tempo = atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_RESOLUTION):  
      if (pmxTokLen(1) == 0) merr("Invalid resolution");
      if (ppqn >= 0) merr("Resolution already specified");
      switch (atoi(pmxTokStart(1))) {
        case 0: ppqn = 96;  break; 
        case 1: ppqn = 192;
        case 2: ppqn = 384;
        case 3: ppqn = 1536;
        default : merr("Invalid resolution");
      }
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_PPQN):        
      if (pmxTokLen(1) == 0) merr("Invalid ppqn");
      if (ppqn >= 0) merr("ppqn already specified");
      ppqn =  atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_DUTY):        
      if (pmxTokLen(1) == 0) merr("Invalid duty");
      if (duty >= 0) merr("duty already specified");
      duty =  atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_VELOCITY):    
      if (pmxTokLen(1) == 0) merr("Invalid velocity");
      if (velocity >= 0) merr("velocity already specified");
      velocity =  atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GLOOSE):   
      if (globalloose_w >= 0) merr("globalloose already specified");
      globalloose_w = atoi(pmxTokStart(1));
      if (pmxTokLen(2) > 0 && *pmxTokStart(2) != 'g')
        globalloose_q = atoi(pmxTokStart(2));
      else 
        globalloose_q = -1;
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GVELVAR):   
      if (globalvelvar_w >= 0) merr("globalvelvar already specified");
      globalvelvar_w = atoi(pmxTokStart(1));
      if (pmxTokLen(2) > 0 && *pmxTokStart(2) != 'g')
        globalvelvar_q = atoi(pmxTokStart(2));
      else 
        globalvelvar_q = -1;
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GGUITON):
      if (pmxTokLen(1) == 0) merr("Invalid globalguiton");
      if (globalguiton >= 0) merr("globalguiton already specified");
      globalguiton =  1;
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_ANY):
      continue;

    default: merr("Internal error");
      break; 
     
  pmxScannerEnd;

  /* cleanup spaces */
  chsSubStr(text,0,"&s"," ");
  
  return text;
}


void checktrackstart(chs_t text)
{
  /* It assumes there's a "|" at the beginning.
     See the {loadmp()} function */
  char *s = text+1;
  while(isspace((int)(*s))) s++;
  if (*s == '|') *text = ' ';
}

int gettrack(char *str, pmx_t capt)
{
  static int cur_track = -1;
  int len;
  chs_t trk;
  
  len = pmxLen(capt,2);
  
  if (len >0) {
    if (pmxLen(capt,1)>0) 
      cur_track = atoi(str + pmxStart(capt,1));
    else cur_track++;
     
    trk = vecGetS(tracks,cur_track,NULL);   
    chsAddChr(trk,' ');
    chsAddStrL(trk, str+pmxStart(capt ,2), len);
    vecSetH(tracks, cur_track, trk);   
  }
    
  return 0;
}

chs_t loadmp(char *fname)
{
  FILE *f;
  chs_t text = NULL;
  f = fopen(fname,"r");
  
  if (!f) merr("Unable to open file");
  
  /* Load text into the buffer */
  chsCpy(text,"| ");
  chsAddFile(text, f);
  chsAddChr(text,'\n');
  
  /* Case insensitiveness */  
  chsLower(text);

  if (f != stdin) fclose(f);
  
  return text;
}


vec_t mp_tracks(char *fname)
{
  chs_t text = NULL;
  
  text = loadmp(fname);
  
  pmxScanStr(text, ">&k#&l&n", blankcomment);

  text = parseglobals(text);
  text = expand(text);
  
  /* Ensure there's a "|" at the beginning */
  checktrackstart(text);
  
  /* split tracks */
  pmxScanStr(text,">|&K(&D)&K(<*!|>)",gettrack);


  fprintf(stdout,"%s\n\n",text);

  if (DO_CLEANUP) {
    chsFree(text);
    chsFree(tmptext);
  }
  return tracks;
}

vec_t mp_tracks_free(vec_t tracks)
{
  int k;
  
  if (DO_CLEANUP) {
    vecFree(tracks);
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  char *fname;
  int docleanup = 0;
  int k;
  char *trk;
  vec_t tracks;
  
  if (argc < 2) fname="mm.txt";
  else fname=argv[1]; 

  tracks = mp_tracks(fname);
  
  for (k=0; k< vecCount(tracks); k++) {
    trk = vecGetP(tracks, k, NULL);
    if (trk != NULL) 
       fprintf(stdout,"|%d %s\n",k,trk);
  }  
  
  tracks = mp_tracks_free(tracks);
  
  exit(0);
}
