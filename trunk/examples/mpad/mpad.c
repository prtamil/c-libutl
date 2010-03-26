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
    lutItem("abassdrum",            (0x80 |  35))
    lutItem("accordion",                      21)
    lutItem("acousticbass",                   32)
    lutItem("acousticgrand",                   0)
    lutItem("agogo",                         113)
    lutItem("altosax",                        65)
    lutItem("applause",                      126)
    lutItem("asnare",               (0x80 |  38))
    lutItem("b2",                   (0x80 |  35))
    lutItem("bagpipe",                       109)
    lutItem("banjo",                         105)
    lutItem("baritonesax",                    67)
    lutItem("bassdrum",             (0x80 |  36))
    lutItem("bassoon",                        70)
    lutItem("bd",                   (0x80 |  36))
    lutItem("birdtweet",                     123)
    lutItem("blownbottle",                    76)
    lutItem("brasssection",                   61)
    lutItem("breathnoise",                   121)
    lutItem("brightacoustic",                  1)
    lutItem("c2",                   (0x80 |  57))
    lutItem("cabasa",               (0x80 |  69))
    lutItem("cb",                   (0x80 |  56))
    lutItem("cc",                   (0x80 |  49))
    lutItem("celesta",                         8)
    lutItem("cello",                          42)
    lutItem("ch",                   (0x80 |  42))
    lutItem("chihat",               (0x80 |  42))
    lutItem("chinesecy",            (0x80 |  52))
    lutItem("choiraahs",                      52)
    lutItem("churchorgan",                    19)
    lutItem("clarinet",                       71)
    lutItem("claves",               (0x80 |  75))
    lutItem("clavinet",                        7)
    lutItem("contrabass",                     43)
    lutItem("cowbell",              (0x80 |  56))
    lutItem("crashcy",              (0x80 |  49))
    lutItem("crashcy2",             (0x80 |  57))
    lutItem("distortionguitar",               30)
    lutItem("drawbarorgan",                   16)
    lutItem("dulcimer",                       15)
    lutItem("ebassfinger",                    33)
    lutItem("ebasspick",                      34)
    lutItem("ecleanguitar",                   27)
    lutItem("ejazzguitar",                    26)
    lutItem("electricgrand",                   2)
    lutItem("emutedguitar",                   28)
    lutItem("englishhorn",                    69)
    lutItem("epiano1",                         4)
    lutItem("epiano2",                         5)
    lutItem("esnare",               (0x80 |  40))
    lutItem("fiddle",                        110)
    lutItem("flute",                          73)
    lutItem("frenchhorn",                     60)
    lutItem("fretlessbass",                   35)
    lutItem("fxatmosphere",                   99)
    lutItem("fxbrightness",                  100)
    lutItem("fxcrystal",                      98)
    lutItem("fxechoes",                      102)
    lutItem("fxgoblins",                     101)
    lutItem("fxrain",                         96)
    lutItem("fxscifi",                       103)
    lutItem("fxsoundtrack",                   97)
    lutItem("glockenspiel",                    9)
    lutItem("guitarfretnoise",               120)
    lutItem("guitarharmonics",                31)
    lutItem("gunshot",                       127)
    lutItem("hagogo",               (0x80 |  67))
    lutItem("handclap",             (0x80 |  39))
    lutItem("harmonica",                      22)
    lutItem("harpsichord",                     6)
    lutItem("hbongo",               (0x80 |  60))
    lutItem("hc",                   (0x80 |  39))
    lutItem("helicopter",                    125)
    lutItem("hfloortom",            (0x80 |  43))
    lutItem("hh",                   (0x80 |  44))
    lutItem("hmidtom",              (0x80 |  48))
    lutItem("honkytonk",                       3)
    lutItem("htimbale",             (0x80 |  65))
    lutItem("htom",                 (0x80 |  50))
    lutItem("hwoodblock",           (0x80 |  76))
    lutItem("kalimba",                       108)
    lutItem("koto",                          107)
    lutItem("lagogo",               (0x80 |  68))
    lutItem("lbongo",               (0x80 |  61))
    lutItem("lconga",               (0x80 |  64))
    lutItem("leadbasslead",                   87)
    lutItem("leadcalliope",                   82)
    lutItem("leadcharang",                    84)
    lutItem("leadchiff",                      83)
    lutItem("leadfifths",                     86)
    lutItem("leadsawtooth",                   81)
    lutItem("leadsquare",                     80)
    lutItem("leadvoice",                      85)
    lutItem("lfloortom",            (0x80 |  41))
    lutItem("lguiro",               (0x80 |  74))
    lutItem("lmidtom",              (0x80 |  47))
    lutItem("ltimbale",             (0x80 |  66))
    lutItem("ltom",                 (0x80 |  45))
    lutItem("lwhistle",             (0x80 |  72))
    lutItem("lwoodblock",           (0x80 |  77))
    lutItem("maracas",              (0x80 |  70))
    lutItem("marimba",                        12)
    lutItem("mcuica",               (0x80 |  78))
    lutItem("melodictom",                    117)
    lutItem("mhconga",              (0x80 |  62))
    lutItem("mtriangle",            (0x80 |  80))
    lutItem("musicbox",                       10)
    lutItem("mutedtrumpet",                   59)
    lutItem("nylonstringguitar",              24)
    lutItem("oboe",                           68)
    lutItem("ocarina",                        79)
    lutItem("ocuica",               (0x80 |  79))
    lutItem("oh",                   (0x80 |  46))
    lutItem("ohconga",              (0x80 |  63))
    lutItem("ohihat",               (0x80 |  46))
    lutItem("orchestrahit",                   55)
    lutItem("orchestralstrings",              46)
    lutItem("otriangle",            (0x80 |  81))
    lutItem("overdrivenguitar",               29)
    lutItem("padbowed",                       92)
    lutItem("padchoir",                       91)
    lutItem("padhalo",                        94)
    lutItem("padmetallic",                    93)
    lutItem("padnewage",                      88)
    lutItem("padpolysynth",                   90)
    lutItem("padsweep",                       95)
    lutItem("padwarm",                        89)
    lutItem("panflute",                       75)
    lutItem("pedhihat",             (0x80 |  44))
    lutItem("percussiveorgan",                17)
    lutItem("piccolo",                        72)
    lutItem("pizzicatostrings",               45)
    lutItem("r2",                   (0x80 |  59))
    lutItem("rb",                   (0x80 |  53))
    lutItem("rc",                   (0x80 |  51))
    lutItem("recorder",                       74)
    lutItem("reedorgan",                      20)
    lutItem("reversecymbal",                 119)
    lutItem("ridebell",             (0x80 |  53))
    lutItem("ridecy",               (0x80 |  51))
    lutItem("ridecy2",              (0x80 |  59))
    lutItem("rockorgan",                      18)
    lutItem("rs",                   (0x80 |  37))
    lutItem("s2",                   (0x80 |  40))
    lutItem("sc",                   (0x80 |  55))
    lutItem("sd",                   (0x80 |  38))
    lutItem("seashore",                      122)
    lutItem("sguiro",               (0x80 |  73))
    lutItem("shamisen",                      106)
    lutItem("shanai",                        111)
    lutItem("sidestick",            (0x80 |  37))
    lutItem("sitar",                         104)
    lutItem("skakuhachi",                     77)
    lutItem("slapbass1",                      36)
    lutItem("slapbass2",                      37)
    lutItem("sopranosax",                     64)
    lutItem("splashcy",             (0x80 |  55))
    lutItem("steeldrums",                    114)
    lutItem("steelstringguitar",              25)
    lutItem("stringensemble1",                48)
    lutItem("stringensemble2",                49)
    lutItem("swhistle",             (0x80 |  71))
    lutItem("synthbass1",                     38)
    lutItem("synthbass2",                     39)
    lutItem("synthbrass1",                    62)
    lutItem("synthbrass2",                    63)
    lutItem("synthdrum",                     118)
    lutItem("synthstrings1",                  50)
    lutItem("synthstrings2",                  51)
    lutItem("synthvoice",                     54)
    lutItem("t1",                   (0x80 |  41))
    lutItem("t2",                   (0x80 |  43))
    lutItem("t3",                   (0x80 |  45))
    lutItem("t4",                   (0x80 |  47))
    lutItem("t5",                   (0x80 |  48))
    lutItem("t6",                   (0x80 |  50))
    lutItem("ta",                   (0x80 |  54))
    lutItem("taikodrum",                     116)
    lutItem("tambourine",           (0x80 |  54))
    lutItem("tangoaccordion",                 23)
    lutItem("tc",                   (0x80 |  52))
    lutItem("telephonering",                 124)
    lutItem("tenorsax",                       66)
    lutItem("timpani",                        47)
    lutItem("tinklebell",                    112)
    lutItem("tom1",                 (0x80 |  41))
    lutItem("tom2",                 (0x80 |  43))
    lutItem("tom3",                 (0x80 |  45))
    lutItem("tom4",                 (0x80 |  47))
    lutItem("tom5",                 (0x80 |  48))
    lutItem("tom6",                 (0x80 |  50))
    lutItem("tremolostrings",                 44)
    lutItem("trombone",                       57)
    lutItem("trumpet",                        56)
    lutItem("tuba",                           58)
    lutItem("tubularbells",                   14)
    lutItem("vibraphone",                     11)
    lutItem("vibraslap",            (0x80 |  58))
    lutItem("viola",                          41)
    lutItem("violin",                         40)
    lutItem("voiceoohs",                      53)
    lutItem("whistle",                        78)
    lutItem("woodblock",                     115)
    lutItem("xylophone",                      13)
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
fprintf(stderr,"{{%.*s}}\n",len,str);
  while (len-- > 0) *str++ = ' ';
}

static int blankcomment(char *str, pmx_t ret)
{
  blankit(str+pmxStart(ret,0),  pmxLen(ret,0));
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

char *notename(int note)
{
  return "c c#d d#e f f#g g#a a#b "+(note % 12) * 2;
}

int noteoctave(int note)
{
  int octave = note / 12;
  if (octave < 0) octave = 0;
  else if (octave > 10) octave = 10;
  return octave;
}

int notenorm(int num)
{
  int n = (num %12);
  if (n<0) n+=12; 
  num = n + 12*noteoctave(num);
  if (num > 128) num -= 12;
  return num;
}

int notenum(char note, char acc, char octave)
{                
  int num = "\011\013\000\002\004\005\007"[note-'a'] + 12 * octave;
  
  if (acc == '#' || acc == '+') num++;
  else if (acc == 'b' || acc == '-') num--;
    
  return notenorm(num);
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
  
  unsigned char cur_channel = 0;
  
  int  d;
  int n;
  int o;
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
  #define T_NUMNOTE     x9B
  #define T_ERROR       x9F
  
  pmxScannerBegin(trk)
                       
    pmxTokSet("ch&K(&d)",T_CHANNEL)
    pmxTokSet("i&K(&d)()",T_INSTR)
    pmxTokSet("i&K()(<+q>)",T_INSTR)
    pmxTokSet("(<?=,'>)n(<?=t>)(<?=+&->)(&d)<?=/>(<*=0-9>)&K(<*==>)",T_NUMNOTE)
    pmxTokSet("(<?=,'>)(<=a-g><?=#b+&->)(<*=0-9>)<?=/>(<*=0-9>)&K(<*==>)",T_NOTE)
    pmxTokSet("(<?=,'>)(x)()<?=/>(<*=0-9>)&K(<*==>)",T_NOTE)
    pmxTokSet("(o)(<?=a-g><?=#b+&->)(<*=0-9>)<?=/>(<*=0-9>)",T_NOTE)
    pmxTokSet("(<?=,'>)(x)()<?=/>(<*=0-9>)&K(<*==>)",T_XNOTE)
    pmxTokSet("p<?=/>(<*=0-9>)&K(<*==&->)",T_PAUSE)
    pmxTokSet("-()(<*==&->)",T_PAUSE)
    pmxTokSet("&s",pmxTokIGNORE) 
    pmxTokSet("<.>",T_ERROR) 
                        
  pmxScannerSwitch

    pmxTokCase(T_NUMNOTE):
    
      n=atoi(pmxTokStart(4)); 
      if (pmxTokLen(3) > 0) {
        if (*pmxTokStart(3) == '-') n = -n;
        n += notenum(cur_note, cur_acc, cur_octave);
      }
      n = notenorm(n);
      o = noteoctave(n);
      t = notename(n);
      chsAddFmt(new_trk,"note %c%c %d ", t[0], t[1], o);
      d = cur_notelen;
      if (pmxTokLen(5)>0) d = atoi(pmxTokStart(5));
      
      chsAddFmt(new_trk,"%d/%d\n",(1+pmxTokLen(6)), d);
      if (pmxTokLen(2) == 0) {
        cur_note = t[0]; cur_acc = t[1];
        cur_octave = o; cur_notelen = d;
      }       
      continue;
 
    pmxTokCase(T_NOTE):
      if (pmxTokLen(2) > 0 && pmxTokStart(2)[0] != 'x')  {
        cur_note = pmxTokStart(2)[0];
        cur_acc = ' ';
        if ((pmxTokLen(2) > 1)) {
          switch(pmxTokStart(2)[1] ) {
            case '#' : case '+' : cur_acc = '#'; break;
            case 'b' : case '-' : cur_acc = 'b'; break;
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
          t = notename(d);
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
      fprintf(stderr,"<<...%.*s...>>\n",30,pmxTokStart(0));
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
  
  pmxScanStr(text, "&s#&L", blankcomment);
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
