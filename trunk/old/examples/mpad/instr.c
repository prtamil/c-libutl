/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#include <string.h>

static char *instr[] = {
  "\122leadcalliope",
  "\262htom",
  "\173birdtweet",
  "\272vibraslap",
  "\110piccolo",
  "\247handclap",
  "\265rb",
  "\065voiceoohs",
  "\060stringensemble1",
  "\111flute",
  "\051viola",
  "\076synthbrass1",
  "\101altosax",
  "\044slapbass1",
  "\031steelstringguitar",
  "\263rc",
  "\251tom1",
  "\132padpolysynth",
  "\271c2",
  "\255ltom",
  "\264tc",
  "\005epiano2",
  "\165melodictom",
  "\022rockorgan",
  "\136padhalo",
  "\314hwoodblock",
  "\254pedhihat",
  "\262t6",
  "\243abassdrum",
  "\030nylonstringguitar",
  "\010celesta",
  "\166synthdrum",
  "\177gunshot",
  "\077synthbrass2",
  "\253tom2",
  "\120leadsquare",
  "\261crashcy",
  "\316mcuica",
  "\321otriangle",
  "\103baritonesax",
  "\311sguiro",
  "\171breathnoise",
  "\275lbongo",
  "\106bassoon",
  "\021percussiveorgan",
  "\276mhconga",
  "\164taikodrum",
  "\052cello",
  "\055pizzicatostrings",
  "\172seashore",
  "\162steeldrums",
  "\134padbowed",
  "\117ocarina",
  "\317ocuica",
  "\072tuba",
  "\154kalimba",
  "\126leadfifths",
  "\246asnare",
  "\257lmidtom",
  "\161agogo",
  "\265ridebell",
  "\313claves",
  "\277ohconga",
  "\300lconga",
  "\026harmonica",
  "\104oboe",
  "\243b2",
  "\252chihat",
  "\130padnewage",
  "\254hh",
  "\037guitarharmonics",
  "\274hbongo",
  "\302ltimbale",
  "\155bagpipe",
  "\043fretlessbass",
  "\253t2",
  "\004epiano1",
  "\267sc",
  "\046synthbass1",
  "\124leadcharang",
  "\105englishhorn",
  "\075brasssection",
  "\102tenorsax",
  "\034emutedguitar",
  "\001brightacoustic",
  "\013vibraphone",
  "\150sitar",
  "\307swhistle",
  "\250esnare",
  "\163woodblock",
  "\245rs",
  "\033ecleanguitar",
  "\135padmetallic",
  "\156fiddle",
  "\063synthstrings2",
  "\144fxbrightness",
  "\142fxcrystal",
  "\041ebassfinger",
  "\125leadvoice",
  "\007clavinet",
  "\153koto",
  "\255tom3",
  "\050violin",
  "\040acousticbass",
  "\273r2",
  "\025accordion",
  "\315lwoodblock",
  "\167reversecymbal",
  "\047synthbass2",
  "\056orchestralstrings",
  "\270cb",
  "\266ta",
  "\100sopranosax",
  "\267splashcy",
  "\012musicbox",
  "\152shamisen",
  "\256oh",
  "\116whistle",
  "\257tom4",
  "\006harpsichord",
  "\304lagogo",
  "\053contrabass",
  "\303hagogo",
  "\312lguiro",
  "\170guitarfretnoise",
  "\023churchorgan",
  "\064choiraahs",
  "\003honkytonk",
  "\020drawbarorgan",
  "\000acousticgrand",
  "\032ejazzguitar",
  "\252ch",
  "\062synthstrings1",
  "\310lwhistle",
  "\157shanai",
  "\073mutedtrumpet",
  "\024reedorgan",
  "\306maracas",
  "\114blownbottle",
  "\244bd",
  "\262tom6",
  "\141fxsoundtrack",
  "\246sd",
  "\260t5",
  "\002electricgrand",
  "\015xylophon",
  "\071trombone",
  "\017dulcimer",
  "\176applause",
  "\145fxgoblins",
  "\301htimbale",
  "\107clarinet",
  "\266tambourine",
  "\146fxechoes",
  "\112recorder",
  "\175helicopter",
  "\036distortionguitar",
  "\131padwarm",
  "\247hc",
  "\245sidestick",
  "\066synthvoice",
  "\253hfloortom",
  "\127leadbasslead",
  "\035overdrivenguitar",
  "\174telephonering",
  "\255t3",
  "\256ohihat",
  "\045slapbass2",
  "\251lfloortom",
  "\140fxrain",
  "\305cabasa",
  "\014marimba",
  "\027tangoaccordion",
  "\260tom5",
  "\264chinesecy",
  "\151banjo",
  "\160tinklebell",
  "\113panflute",
  "\251t1",
  "\261cc",
  "\011glockenspiel",
  "\054tremolostrings",
  "\244bassdrum",
  "\133padchoir",
  "\042ebasspick",
  "\147fxscifi",
  "\121leadsawtooth",
  "\115skakuhachi",
  "\016tubularbells",
  "\061stringensemble2",
  "\123leadchiff",
  "\074frenchhorn",
  "\070trumpet",
  "\250s2",
  "\273ridecy2",
  "\320mtriangle",
  "\270cowbell",
  "\271crashcy2",
  "\143fxatmosphere",
  "\260hmidtom",
  "\263ridecy",
  "\067orchestrahit",
  "\137padsweep",
  "\257t4",
  "\057timpani"
};


/*
  This is the perfect hash function generated with Bob Jenkins tool:
  
  http://burtleburtle.net/bob/hash/perfect.html
  
*/

static unsigned char tab[] = {
  253,113,131,184,40,0,0,0,125,0,40,183,131,131,0,0,
  85,183,0,0,0,85,183,0,120,0,0,113,125,7,125,183,
  135,113,0,124,0,0,0,113,7,131,183,0,0,0,7,0,
  0,131,116,0,183,124,0,82,0,220,168,85,146,125,233,131,
  113,82,113,120,131,113,51,190,30,220,0,0,220,0,74,183,
  0,235,235,0,24,145,183,7,220,131,220,42,40,214,217,0,
  0,165,220,184,0,0,0,125,145,88,135,232,42,184,0,145,
  201,59,0,74,231,78,229,34,120,183,221,17,0,235,227,0,
};

#define mix(a,b,c) \
{ \
  a -= b; a -= c; a ^= (c>>13); \
  b -= c; b -= a; b ^= (a<<8); \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12);  \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5); \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}

static unsigned long  int lookup(unsigned char *k, unsigned long  int  length, unsigned long  int level)
{
   register unsigned long  int a,b,c,len;

   /* Set up the internal state */
   len = length;
   a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
   c = level;           /* the previous hash value */

   /*---------------------------------------- handle most of the key */
   while (len >= 12)
   {
      a += (k[0] +((unsigned long  int)k[1]<<8) +((unsigned long  int)k[2]<<16) +((unsigned long  int)k[3]<<24));
      b += (k[4] +((unsigned long  int)k[5]<<8) +((unsigned long  int)k[6]<<16) +((unsigned long  int)k[7]<<24));
      c += (k[8] +((unsigned long  int)k[9]<<8) +((unsigned long  int)k[10]<<16)+((unsigned long  int)k[11]<<24));
      mix(a,b,c);
      k += 12; len -= 12;
   }

   /*------------------------------------- handle the last 11 bytes */
   c += length;
   switch(len)              /* all the case statements fall through */
   {
   case 11: c+=((unsigned long  int)k[10]<<24);
   case 10: c+=((unsigned long  int)k[9]<<16);
   case 9 : c+=((unsigned long  int)k[8]<<8);
      /* the first byte of c is reserved for the length */
   case 8 : b+=((unsigned long  int)k[7]<<24);
   case 7 : b+=((unsigned long  int)k[6]<<16);
   case 6 : b+=((unsigned long  int)k[5]<<8);
   case 5 : b+=k[4];
   case 4 : a+=((unsigned long  int)k[3]<<24);
   case 3 : a+=((unsigned long  int)k[2]<<16);
   case 2 : a+=((unsigned long  int)k[1]<<8);
   case 1 : a+=k[0];
     /* case 0: nothing left to add */
   }
   mix(a,b,c);
   /*-------------------------------------------- report the result */
   return c;
}


static unsigned long int phash(char *key, int   len)
{
  unsigned long int  rsl, val;
  val = lookup((unsigned char *)key, len, 0xb54cda56);
  rsl = ((val>>25)^tab[val&0x7f]);
  return rsl;
}

unsigned char instr_name(char *name, int len)
{
  unsigned long int n= phash(name,len);
  if (strncmp(name,instr[n]+1,len) == 0) return instr[n][0];  
  return 0;
}
