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

#define DEFAULT_VAL -99

static int tempo          = DEFAULT_VAL;
static int ppqn           = DEFAULT_VAL;
static int duty           = DEFAULT_VAL;
static int velocity       = DEFAULT_VAL;
static int globalloose_w  = DEFAULT_VAL;
static int globalloose_q  = DEFAULT_VAL;
static int globalvelvar_w = DEFAULT_VAL;
static int globalvelvar_q = DEFAULT_VAL;
static int globalguiton   = DEFAULT_VAL;
static int globalmeter_n  = DEFAULT_VAL;
static int globalmeter_d  = DEFAULT_VAL;
static int globalmeter_c  = DEFAULT_VAL;
static int globalmeter_b  = DEFAULT_VAL;
static int key_sig        = DEFAULT_VAL;

static tbl_t macros  = NULL;
static chs_t tmptext = NULL;
static chs_t rpl     = NULL;
static vec_t args    = NULL;
static vec_t tracks  = NULL;

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


static char *subargs(char *str, pmx_t capt)
{ 
  int k;
  char *r;

  k  = str[pmxStart(capt,0)+1];
  if (k == '$') return ("$");
  
  k -= '1';
  r  = vecGetS(args, k, NULL);
  
  return (r? r : utlEmptyString);
}

static char *submacro(char *str, pmx_t capt)
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

static char *mulstr(char *str, pmx_t capt)
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

static char *mulpar(char *str, pmx_t capt)
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

static void blankit(char *str, int len)
{
  while (len-- > 0) *str++ = ' ';
}

static int blankcomment(char *str, pmx_t ret)
{
  blankit(str+pmxStart(ret,0), pmxLen(ret,0));
  return 0;
}

static int getmacro(char *str, pmx_t ret)
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

static chs_t expand(chs_t text)
{
  /* get and expand macros */
  pmxScanStr(text, "&Km(<?$rnd>)$(<+a>)&K(&b())&K(&N)", getmacro);
  chsSubFun(text, 0,"&*$(<*a>)(&B())",submacro);

  /* Multiply */  
  chsSubFun(text,0,"&*(&b())&K*&K(&d)&K",mulpar);
  chsSubFun(text,0,"&*(<+! \t*>)&K*&K(&d)&K",mulstr);
  
  /* cleanup parenthesis*/
  //chsSubStr(text,0,"<+=()>","");
  
  if (DO_CLEANUP) {
    tblFree(macros);
    vecFree(args);
  }
  
  return text;
}

static chs_t parseglobals(chs_t text)
{
  int val;
  
  #define T_TEMPO       x81
  #define T_RESOLUTION  x82
  #define T_PPQN        x83
  #define T_DUTY        x84
  #define T_VELOCITY    x85
  #define T_GLOOSE      x86
  #define T_GVELVAR     x87
  #define T_GGUITON     x88 
  #define T_KEY         x89 
  #define T_METER       x8A 
  #define T_SMPTE       x8B 
  #define T_IGNORE      x8F 
  
  pmxScannerBegin(text)
                       
    pmxTokSet("tempo&K(&D)",T_TEMPO)
    pmxTokSet("smpteoff<?$set>&K(&d)<?=,>(&d)<?=,>(&d)<?=,>(&d)<?=,>(&d)",T_SMPTE)
    pmxTokSet("resolution&K(&d)",T_RESOLUTION)
    pmxTokSet("ppqn&K(&d)",T_PPQN)
    pmxTokSet("duty&K(&d)",T_DUTY)
    pmxTokSet("velocity&K(&d)",T_VELOCITY)
    pmxTokSet("g<?$lobal>loose&K(&d)<?=,>(<*=0-9g>)",T_GLOOSE)
    pmxTokSet("g<?$lobal>velar&K(&d)<?=,>(<*=0-9g>)",T_GVELVAR)
    pmxTokSet("g<?$lobal>guit<?$ar>on",T_GGUITON) 
    pmxTokSet("g<?$lobal>meter&K(&d)/(&d)<?=,>(&D)<?=,>(&D)",T_METER)
    pmxTokSet("g<?$lobal>key&K(<=1-7a-g>)(<=#b+->)(<?$min$maj>)<?$or>",T_KEY)
    pmxTokSet("&s",pmxTokIGNORE) 
    pmxTokSet("<.>",pmxTokIGNORE) 
                        
  pmxScannerSwitch
 
    pmxTokCase(T_TEMPO):
      if (tempo != DEFAULT_VAL) merr("Tempo already specified");
      tempo = atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_RESOLUTION):  
      if (ppqn != DEFAULT_VAL) merr("Resolution already specified");
      val = atoi(pmxTokStart(1));
      switch (val) {
        case 0: ppqn = 96;   break; 
        case 1: ppqn = 192;  break;
        case 2: ppqn = 384;  break;
        case 3: ppqn = 1536; break;
        default : ppqn = val; 
      }
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_PPQN):        
      if (ppqn != DEFAULT_VAL) merr("ppqn already specified");
      ppqn =  atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_DUTY):        
      if (duty != DEFAULT_VAL) merr("duty already specified");
      duty =  atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_VELOCITY):    
      if (velocity != DEFAULT_VAL) merr("velocity already specified");
      velocity =  atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GLOOSE):   
      if (globalloose_w != DEFAULT_VAL) merr("globalloose already specified");
      globalloose_w = atoi(pmxTokStart(1));
      if (pmxTokLen(2) > 0 && *pmxTokStart(2) != 'g')
        globalloose_q = atoi(pmxTokStart(2));
      else 
        globalloose_q = -1;
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GVELVAR):   
      if (globalvelvar_w != DEFAULT_VAL) merr("globalvelvar already specified");
      globalvelvar_w = atoi(pmxTokStart(1));
      if (pmxTokLen(2) > 0 && *pmxTokStart(2) != 'g')
        globalvelvar_q = atoi(pmxTokStart(2));
      else 
        globalvelvar_q = -1;
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GGUITON):
      if (globalguiton != DEFAULT_VAL) merr("globalguiton already specified");
      globalguiton = 1;
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_METER):
      if (globalmeter_n != DEFAULT_VAL) merr("Meter already specified");
      globalmeter_n = atoi(pmxTokStart(1));
      globalmeter_d = atoi(pmxTokStart(2));
      
      if (pmxTokLen(3) > 0)
        globalmeter_c = atoi(pmxTokStart(3));
      else 
        globalmeter_c = 24;
        
      if (pmxTokLen(4) > 0)
        globalmeter_b = atoi(pmxTokStart(4));
      else 
        globalmeter_c = 8;
        
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(pmxTokIGNORE):
      continue;

    default: merr("Internal error");
      break; 
     
  pmxScannerEnd;

  /* cleanup spaces */
  //chsSubStr(text,0,"&s"," ");
  
  if (tempo          == DEFAULT_VAL )  tempo          = 120;
  if (ppqn           == DEFAULT_VAL )  ppqn           = 192;
  if (duty           == DEFAULT_VAL )  duty           = 98;
  if (velocity       == DEFAULT_VAL )  velocity       = 100;
  if (globalloose_w  == DEFAULT_VAL )  globalloose_w  = 0;
  if (globalvelvar_w == DEFAULT_VAL )  globalvelvar_w = 0;
  if (globalguiton   == DEFAULT_VAL )  globalguiton   = 0;
  if (key_sig        == DEFAULT_VAL )  key_sig        = 0;

  return text;
}


static void checktrackstart(chs_t text)
{
  /* It assumes there's a "|" at the beginning. See the {loadmp()} function */
  char *s = text+1;
  while(isspace((int)(*s))) s++;
  if (*s == '|') *text = ' ';
}

static int gettrack(char *str, pmx_t capt)
{
  static int cur_track = -1;
  int len;
  chs_t trk;
  
  len = pmxLen(capt,2);
  
  if (len >0) {
    if (pmxLen(capt,1)>0) 
      cur_track = atoi(str + pmxStart(capt,1));
    else cur_track++;
     
    trk = vecGetZS(tracks, cur_track, NULL); 
    chsAddChr(trk,' ');
    chsAddStrL(trk, str+pmxStart(capt ,2), len);
    vecSetZH(tracks, cur_track, trk); 
    //fprintf(stderr, "**%s\n",trk);  
  }
    
  return 0;
}

/*
    pmxTokSet("key&K(<=1-7a-g>)(<=#b+->)(<?$min$maj>)<?$or>",T_KEY)
    pmxTokSet("meter&K(&d)/(&d)<?=,>(&D)<?=,>(&D)",T_METER)

*/

chs_t parsetrack(chs_t trk)
{
  chs_t new_trk = NULL;
  int cur_duty     = duty;
  int cur_velocity = velocity;
  int cur_loose_w  = globalloose_w;
  int cur_loose_q  = globalloose_q;
  int cur_velvar_w = globalvelvar_w;
  int cur_velvar_q = globalvelvar_q;
  int cur_guiton   = globalguiton;

  unsigned long cur_tick = 0;
  char  cur_octave        = 5;
  char  cur_note          = 'c';
  char  cur_acc           = ' ';
  short cur_notelen       = 4;
  
  int  d;
  char n;
  char o;
  
  #define T_NOTE        x91
  #define T_STRESS      x92
  #define T_SOFT        x93
  #define T_PAUSE       x94
  #define T_SPACE       x95
  #define T_DEFAULT     x96
  #define T_XNOTE       x97
  #define T_XPAUSE      x98
  #define T_ERROR       x9F
  
  pmxScannerBegin(trk)
                       
    pmxTokSet("(<?=,'>)(<=a-gx><?=#b+&->)(<*=0-9>)<?=/>(<*=0-9>)&K(<*==>)",T_NOTE)
    pmxTokSet("(o)(<?=a-g><?=#b+&->)(<*=0-9>)<?=/>(<*=0-9>)",T_NOTE)
    pmxTokSet("(<?=,'>)(x)()<?=/>(<*=0-9>)&K(<*==>)",T_XNOTE)
    pmxTokSet("p<?=/>(<*=0-9>)&K(<*==&->)",T_PAUSE)
    pmxTokSet("-()(<*==&->)",T_PAUSE)
    pmxTokSet("&s",pmxTokIGNORE) 
    pmxTokSet("<.>",T_ERROR) 
                        
  pmxScannerSwitch
 
    pmxTokCase(T_NOTE):
      if (pmxTokLen(2) > 0 && pmxTokStart(2)[0] != 'x')  {
        cur_note = pmxTokStart(2)[0];
        if ((pmxTokLen(2) > 1)) {
          switch(pmxTokStart(2)[1] ) {
            case '#' : case '+' : cur_acc = '#'; break;
            case 'b' : case '-' : cur_acc = 'b'; break;
             default :            cur_acc = ' ';
          }
        }  
      }
      if (pmxTokLen(3) > 0)  cur_octave  = atoi(pmxTokStart(3));
      if (pmxTokLen(4) > 0)  cur_notelen = atoi(pmxTokStart(4));
        
      if (pmxTokLen(1) > 0) {
        if (*pmxTokStart(1) == 'o') continue; 
        /* Handle stress and soft!! */
      }
      
      d = (1+pmxTokLen(5));
      chsAddFmt(new_trk,"%08lx note %c%c %d %d/%d\n", 
                       cur_tick, cur_note, cur_acc, cur_octave, d, cur_notelen);
      cur_tick += (ppqn / cur_notelen) * d;
      continue;

    pmxTokCase(T_PAUSE):
      if (pmxTokLen(1) > 0)  cur_notelen = atoi(pmxTokStart(1));
        
      d = (1+pmxTokLen(2));
      chsAddFmt(new_trk,"%08lx pause %d/%d\n", 
                       cur_tick,  d, cur_notelen);
      cur_tick += (ppqn / cur_notelen) * d;
      continue;

    pmxTokCase(pmxTokIGNORE):
      continue;
      
    pmxTokCase(T_ERROR):
      merr("Syntax error");
      break;

    default: merr("Internal error");
      break; 
     
  pmxScannerEnd;
  
  chsAddFmt(new_trk,"%08lx end\n",cur_tick);
  
  chsFree(trk);
  return new_trk;
}

vec_t mp_tracks(FILE *f)
{
  chs_t text = NULL;
  int k;
  chs_t trk;
  
  chsCpy(text,"| ");
  chsAddFile(text, f);
  chsAddChr(text,'\n');
  
  /* Case insensitiveness */  
  chsLower(text);
  
  pmxScanStr(text, "&k#&l&n", blankcomment);

  text = parseglobals(text);
  text = expand(text);
  
  /* Ensure there's a "|" at the beginning */
  checktrackstart(text);
  
  /* split tracks */
  pmxScanStr(text,"|(&D)&K(<*!|>)",gettrack);

  for (k=0; k< vecCount(tracks); k++) {
    trk = vecGetZS(tracks, k, NULL); 
    if (trk != NULL) { 
      trk = parsetrack(trk);
      vecSetZH(tracks, k, trk);
    }
  }

  if (DO_CLEANUP) {
    chsFree(text);
    chsFree(tmptext);
  }
  
  return tracks;
}

vec_t mp_tracks_free(vec_t tracks)
{
  if (DO_CLEANUP) {
    vecFree(tracks);
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  FILE *f;
  char *fname;
  int k;
  char *trk;
  vec_t tracks = NULL;

  if (argc < 2) fname="mm.txt";
  else fname=argv[1];
   
  f = fopen(fname,"r");
  
  if (!f) merr("Unable to open file");
  
  tracks = mp_tracks(f);
   
  if (f != stdin) fclose(f);

  for (k=0; k< vecCount(tracks); k++) {
    trk = vecGetS(tracks, k, NULL);
    if (trk != NULL) 
       fprintf(stdout,"|%d %s\n",k,trk);
  }  
  
  tracks = mp_tracks_free(tracks);
  
  exit(0);
}
