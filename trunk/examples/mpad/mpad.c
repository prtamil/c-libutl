/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#include <stdio.h>
#include <ctype.h>

#include "libutl.h"

lutBeginSN(instr)
   {   "abassdrum",                    (0x80 |  35) },
   {   "accordion",                    21  },
   {   "acousticbass",                 32  },
   {   "acousticgrand",                 0  },
   {   "agogo",                       113  },
   {   "altosax",                      65  },
   {   "applause",                    126  },
   {   "asnare",                       (0x80 |  38) },
   {   "b2",                           (0x80 |  35) },
   {   "bagpipe",                     109  },
   {   "banjo",                       105  },
   {   "baritonesax",                  67  },
   {   "bassdrum",                     (0x80 |  36) },
   {   "bassoon",                      70  },
   {   "bd",                           (0x80 |  36) },
   {   "birdtweet",                   123  },
   {   "blownbottle",                  76  },
   {   "brasssection",                 61  },
   {   "breathnoise",                 121  },
   {   "brightacoustic",                1  },
   {   "c2",                           (0x80 |  57) },
   {   "cabasa",                       (0x80 |  69) },
   {   "cb",                           (0x80 |  56) },
   {   "cc",                           (0x80 |  49) },
   {   "celesta",                       8  },
   {   "cello",                        42  },
   {   "ch",                           (0x80 |  42) },
   {   "chihat",                       (0x80 |  42) },
   {   "chinesecy",                    (0x80 |  52) },
   {   "choiraahs",                    52  },
   {   "churchorgan",                  19  },
   {   "clarinet",                     71  },
   {   "claves",                       (0x80 |  75) },
   {   "clavinet",                      7  },
   {   "contrabass",                   43  },
   {   "cowbell",                      (0x80 |  56) },
   {   "crashcy",                      (0x80 |  49) },
   {   "crashcy2",                     (0x80 |  57) },
   {   "distortionguitar",             30  },
   {   "drawbarorgan",                 16  },
   {   "dulcimer",                     15  },
   {   "ebassfinger",                  33  },
   {   "ebasspick",                    34  },
   {   "ecleanguitar",                 27  },
   {   "ejazzguitar",                  26  },
   {   "electricgrand",                 2  },
   {   "emutedguitar",                 28  },
   {   "englishhorn",                  69  },
   {   "epiano1",                       4  },
   {   "epiano2",                       5  },
   {   "esnare",                       (0x80 |  40) },
   {   "fiddle",                      110  },
   {   "flute",                        73  },
   {   "frenchhorn",                   60  },
   {   "fretlessbass",                 35  },
   {   "fxatmosphere",                 99  },
   {   "fxbrightness",                100  },
   {   "fxcrystal",                    98  },
   {   "fxechoes",                    102  },
   {   "fxgoblins",                   101  },
   {   "fxrain",                       96  },
   {   "fxscifi",                     103  },
   {   "fxsoundtrack",                 97  },
   {   "glockenspiel",                  9  },
   {   "guitarfretnoise",             120  },
   {   "guitarharmonics",              31  },
   {   "gunshot",                     127  },
   {   "hagogo",                       (0x80 |  67) },
   {   "handclap",                     (0x80 |  39) },
   {   "harmonica",                    22  },
   {   "harpsichord",                   6  },
   {   "hbongo",                       (0x80 |  60) },
   {   "hc",                           (0x80 |  39) },
   {   "helicopter",                  125  },
   {   "hfloortom",                    (0x80 |  43) },
   {   "hh",                           (0x80 |  44) },
   {   "hmidtom",                      (0x80 |  48) },
   {   "honkytonk",                     3  },
   {   "htimbale",                     (0x80 |  65) },
   {   "htom",                         (0x80 |  50) },
   {   "hwoodblock",                   (0x80 |  76) },
   {   "kalimba",                     108  },
   {   "koto",                        107  },
   {   "lagogo",                       (0x80 |  68) },
   {   "lbongo",                       (0x80 |  61) },
   {   "lconga",                       (0x80 |  64) },
   {   "leadbasslead",                 87  },
   {   "leadcalliope",                 82  },
   {   "leadcharang",                  84  },
   {   "leadchiff",                    83  },
   {   "leadfifths",                   86  },
   {   "leadsawtooth",                 81  },
   {   "leadsquare",                   80  },
   {   "leadvoice",                    85  },
   {   "lfloortom",                    (0x80 |  41) },
   {   "lguiro",                       (0x80 |  74) },
   {   "lmidtom",                      (0x80 |  47) },
   {   "ltimbale",                     (0x80 |  66) },
   {   "ltom",                         (0x80 |  45) },
   {   "lwhistle",                     (0x80 |  72) },
   {   "lwoodblock",                   (0x80 |  77) },
   {   "maracas",                      (0x80 |  70) },
   {   "marimba",                      12  },
   {   "mcuica",                       (0x80 |  78) },
   {   "melodictom",                  117  },
   {   "mhconga",                      (0x80 |  62) },
   {   "mtriangle",                    (0x80 |  80) },
   {   "musicbox",                     10  },
   {   "mutedtrumpet",                 59  },
   {   "nylonstringguitar",            24  },
   {   "oboe",                         68  },
   {   "ocarina",                      79  },
   {   "ocuica",                       (0x80 |  79) },
   {   "oh",                           (0x80 |  46) },
   {   "ohconga",                      (0x80 |  63) },
   {   "ohihat",                       (0x80 |  46) },
   {   "orchestrahit",                 55  },
   {   "orchestralstrings",            46  },
   {   "otriangle",                    (0x80 |  81) },
   {   "overdrivenguitar",             29  },
   {   "padbowed",                     92  },
   {   "padchoir",                     91  },
   {   "padhalo",                      94  },
   {   "padmetallic",                  93  },
   {   "padnewage",                    88  },
   {   "padpolysynth",                 90  },
   {   "padsweep",                     95  },
   {   "padwarm",                      89  },
   {   "panflute",                     75  },
   {   "pedhihat",                     (0x80 |  44) },
   {   "percussiveorgan",              17  },
   {   "piccolo",                      72  },
   {   "pizzicatostrings",             45  },
   {   "r2",                           (0x80 |  59) },
   {   "rb",                           (0x80 |  53) },
   {   "rc",                           (0x80 |  51) },
   {   "recorder",                     74  },
   {   "reedorgan",                    20  },
   {   "reversecymbal",               119  },
   {   "ridebell",                     (0x80 |  53) },
   {   "ridecy",                       (0x80 |  51) },
   {   "ridecy2",                      (0x80 |  59) },
   {   "rockorgan",                    18  },
   {   "rs",                           (0x80 |  37) },
   {   "s2",                           (0x80 |  40) },
   {   "sc",                           (0x80 |  55) },
   {   "sd",                           (0x80 |  38) },
   {   "seashore",                    122  },
   {   "sguiro",                       (0x80 |  73) },
   {   "shamisen",                    106  },
   {   "shanai",                      111  },
   {   "sidestick",                    (0x80 |  37) },
   {   "sitar",                       104  },
   {   "skakuhachi",                   77  },
   {   "slapbass1",                    36  },
   {   "slapbass2",                    37  },
   {   "sopranosax",                   64  },
   {   "splashcy",                     (0x80 |  55) },
   {   "steeldrums",                  114  },
   {   "steelstringguitar",            25  },
   {   "stringensemble1",              48  },
   {   "stringensemble2",              49  },
   {   "swhistle",                     (0x80 |  71) },
   {   "synthbass1",                   38  },
   {   "synthbass2",                   39  },
   {   "synthbrass1",                  62  },
   {   "synthbrass2",                  63  },
   {   "synthdrum",                   118  },
   {   "synthstrings1",                50  },
   {   "synthstrings2",                51  },
   {   "synthvoice",                   54  },
   {   "t1",                           (0x80 |  41) },
   {   "t2",                           (0x80 |  43) },
   {   "t3",                           (0x80 |  45) },
   {   "t4",                           (0x80 |  47) },
   {   "t5",                           (0x80 |  48) },
   {   "t6",                           (0x80 |  50) },
   {   "ta",                           (0x80 |  54) },
   {   "taikodrum",                   116  },
   {   "tambourine",                   (0x80 |  54) },
   {   "tangoaccordion",               23  },
   {   "tc",                           (0x80 |  52) },
   {   "telephonering",               124  },
   {   "tenorsax",                     66  },
   {   "timpani",                      47  },
   {   "tinklebell",                  112  },
   {   "tom1",                         (0x80 |  41) },
   {   "tom2",                         (0x80 |  43) },
   {   "tom3",                         (0x80 |  45) },
   {   "tom4",                         (0x80 |  47) },
   {   "tom5",                         (0x80 |  48) },
   {   "tom6",                         (0x80 |  50) },
   {   "tremolostrings",               44  },
   {   "trombone",                     57  },
   {   "trumpet",                      56  },
   {   "tuba",                         58  },
   {   "tubularbells",                 14  },
   {   "vibraphone",                   11  },
   {   "vibraslap",                    (0x80 |  58) },
   {   "viola",                        41  },
   {   "violin",                       40  },
   {   "voiceoohs",                    53  },
   {   "whistle",                      78  },
   {   "woodblock",                   115  },
   {   "xylophone",                    13  },
lutEndSN(instr)


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

int instrbyname(char *name, int len)
{
  char buf[32];
  if (len>30) len=30;
  strncpy(buf,name,len);
  buf[len] = '\0';
  return lutGetSN(instr,buf,0);
}

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
  char  cur_instr         = 0;
  
  unsigned char cur_channel        = 0;
  
  int  d;
  char n;
  char o;
  char *t;
     
  chsCpy(new_trk,"track\n");  
  
  #define T_NOTE        x91
  #define T_STRESS      x92
  #define T_SOFT        x93
  #define T_PAUSE       x94
  #define T_SPACE       x95
  #define T_DEFAULT     x96
  #define T_XNOTE       x97
  #define T_XPAUSE      x98
  #define T_CHANNEL     x99
  #define T_INSTR       x9A
  #define T_ERROR       x9F
  
  pmxScannerBegin(trk)
                       
    pmxTokSet("ch&K(&d)",T_CHANNEL)
    pmxTokSet("i&K(&d)()",T_INSTR)
    pmxTokSet("i&K()(<+q>)",T_INSTR)
    pmxTokSet("(<?=,'>)(<=a-g><?=#b+&->)(<*=0-9>)<?=/>(<*=0-9>)&K(<*==>)",T_NOTE)
    pmxTokSet("(<?=,'>)(x)()<?=/>(<*=0-9>)&K(<*==>)",T_NOTE)
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
      chsAddFmt(new_trk,"note %c%c %d %d/%d\n", cur_note, cur_acc, cur_octave, d, cur_notelen);
      continue;

    pmxTokCase(T_PAUSE):
      if (pmxTokLen(1) > 0)  cur_notelen = atoi(pmxTokStart(1));
        
      d = (1+pmxTokLen(2));
      chsAddFmt(new_trk,"pause %d/%d\n", d, cur_notelen);
      continue;

    pmxTokCase(T_CHANNEL):
      d = atoi(pmxTokStart(1)) -1;
      if (0 <= d && d <= 15 ) {
        cur_channel = d;
        chsAddFmt(new_trk,"ch %d\n",cur_channel);
      }
      continue;
      
    pmxTokCase(T_INSTR):
      if (pmxTokLen(2)>0) {
        d = instrbyname(pmxTokStart(2), pmxTokLen(2));
        if (d & 0x80) {
          if (cur_channel != 9) {
            chsAddStr(new_trk,"ch 9\n");
            cur_channel = 9;
          }
          d &= 0x7F;
          t = "c c#d d#e f f#g g#a a#b "+(d % 12);
          cur_note = t[0]; cur_acc = t[1];
          cur_octave = d / 12;
          continue;
        }
      }
      else {
        d = atoi(pmxTokStart(1))-1;
      }
      if (d < 0 || d > 127 ) d = 0;
      if (d != cur_instr) {
        chsAddFmt(new_trk,"instr %d\n",d);
        cur_instr = d;
      }
      continue;
      
    pmxTokCase(pmxTokIGNORE):
      continue;
      
    pmxTokCase(T_ERROR):
      merr("Syntax error");
      break;

    default: merr("Internal error");
      break; 
     
  pmxScannerEnd;
  
  chsAddStr(new_trk,"end\n");
  
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
