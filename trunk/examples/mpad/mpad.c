/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#include <stdio.h>
#include <ctype.h>

#include <time.h>

#include "libutl.h"

lutBegin(SN,instr)
    lutItem("abassdrum",            (0x80 |  35) )
    lutItem("accordion",                      21 )
    lutItem("acousticbass",                   32 )
    lutItem("acousticgrand",                   0 )
    lutItem("agogo",                         113 )
    lutItem("altosax",                        65 )
    lutItem("applause",                      126 )
    lutItem("asnare",               (0x80 |  38) )
    lutItem("b2",                   (0x80 |  35) )
    lutItem("bagpipe",                       109 )
    lutItem("banjo",                         105 )
    lutItem("baritonesax",                    67 )
    lutItem("bassdrum",             (0x80 |  36) )
    lutItem("bassoon",                        70 )
    lutItem("bd",                   (0x80 |  36) )
    lutItem("birdtweet",                     123 )
    lutItem("blownbottle",                    76 )
    lutItem("brasssection",                   61 )
    lutItem("breathnoise",                   121 )
    lutItem("brightacoustic",                  1 )
    lutItem("c2",                   (0x80 |  57) )
    lutItem("cabasa",               (0x80 |  69) )
    lutItem("cb",                   (0x80 |  56) )
    lutItem("cc",                   (0x80 |  49) )
    lutItem("celesta",                         8 )
    lutItem("cello",                          42 )
    lutItem("ch",                   (0x80 |  42) )
    lutItem("chihat",               (0x80 |  42) )
    lutItem("chinesecy",            (0x80 |  52) )
    lutItem("choiraahs",                      52 )
    lutItem("churchorgan",                    19 )
    lutItem("clarinet",                       71 )
    lutItem("claves",               (0x80 |  75) )
    lutItem("clavinet",                        7 )
    lutItem("contrabass",                     43 )
    lutItem("cowbell",              (0x80 |  56) )
    lutItem("crashcy",              (0x80 |  49) )
    lutItem("crashcy2",             (0x80 |  57) )
    lutItem("distortionguitar",               30 )
    lutItem("drawbarorgan",                   16 )
    lutItem("dulcimer",                       15 )
    lutItem("ebassfinger",                    33 )
    lutItem("ebasspick",                      34 )
    lutItem("ecleanguitar",                   27 )
    lutItem("ejazzguitar",                    26 )
    lutItem("electricgrand",                   2 )
    lutItem("emutedguitar",                   28 )
    lutItem("englishhorn",                    69 )
    lutItem("epiano1",                         4 )
    lutItem("epiano2",                         5 )
    lutItem("esnare",               (0x80 |  40) )
    lutItem("fiddle",                        110 )
    lutItem("flute",                          73 )
    lutItem("frenchhorn",                     60 )
    lutItem("fretlessbass",                   35 )
    lutItem("fxatmosphere",                   99 )
    lutItem("fxbrightness",                  100 )
    lutItem("fxcrystal",                      98 )
    lutItem("fxechoes",                      102 )
    lutItem("fxgoblins",                     101 )
    lutItem("fxrain",                         96 )
    lutItem("fxscifi",                       103 )
    lutItem("fxsoundtrack",                   97 )
    lutItem("glockenspiel",                    9 )
    lutItem("guitarfretnoise",               120 )
    lutItem("guitarharmonics",                31 )
    lutItem("gunshot",                       127 )
    lutItem("hagogo",               (0x80 |  67) )
    lutItem("handclap",             (0x80 |  39) )
    lutItem("harmonica",                      22 )
    lutItem("harpsichord",                     6 )
    lutItem("hbongo",               (0x80 |  60) )
    lutItem("hc",                   (0x80 |  39) )
    lutItem("helicopter",                    125 )
    lutItem("hfloortom",            (0x80 |  43) )
    lutItem("hh",                   (0x80 |  44) )
    lutItem("hmidtom",              (0x80 |  48) )
    lutItem("honkytonk",                       3 )
    lutItem("htimbale",             (0x80 |  65) )
    lutItem("htom",                 (0x80 |  50) )
    lutItem("hwoodblock",           (0x80 |  76) )
    lutItem("kalimba",                       108 )
    lutItem("koto",                          107 )
    lutItem("lagogo",               (0x80 |  68) )
    lutItem("lbongo",               (0x80 |  61) )
    lutItem("lconga",               (0x80 |  64) )
    lutItem("leadbasslead",                   87 )
    lutItem("leadcalliope",                   82 )
    lutItem("leadcharang",                    84 )
    lutItem("leadchiff",                      83 )
    lutItem("leadfifths",                     86 )
    lutItem("leadsawtooth",                   81 )
    lutItem("leadsquare",                     80 )
    lutItem("leadvoice",                      85 )
    lutItem("lfloortom",            (0x80 |  41) )
    lutItem("lguiro",               (0x80 |  74) )
    lutItem("lmidtom",              (0x80 |  47) )
    lutItem("ltimbale",             (0x80 |  66) )
    lutItem("ltom",                 (0x80 |  45) )
    lutItem("lwhistle",             (0x80 |  72) )
    lutItem("lwoodblock",           (0x80 |  77) )
    lutItem("maracas",              (0x80 |  70) )
    lutItem("marimba",                        12 )
    lutItem("mcuica",               (0x80 |  78) )
    lutItem("melodictom",                    117 )
    lutItem("mhconga",              (0x80 |  62) )
    lutItem("mtriangle",            (0x80 |  80) )
    lutItem("musicbox",                       10 )
    lutItem("mutedtrumpet",                   59 )
    lutItem("nylonstringguitar",              24 )
    lutItem("oboe",                           68 )
    lutItem("ocarina",                        79 )
    lutItem("ocuica",               (0x80 |  79) )
    lutItem("oh",                   (0x80 |  46) )
    lutItem("ohconga",              (0x80 |  63) )
    lutItem("ohihat",               (0x80 |  46) )
    lutItem("orchestrahit",                   55 )
    lutItem("orchestralstrings",              46 )
    lutItem("otriangle",            (0x80 |  81) )
    lutItem("overdrivenguitar",               29 )
    lutItem("padbowed",                       92 )
    lutItem("padchoir",                       91 )
    lutItem("padhalo",                        94 )
    lutItem("padmetallic",                    93 )
    lutItem("padnewage",                      88 )
    lutItem("padpolysynth",                   90 )
    lutItem("padsweep",                       95 )
    lutItem("padwarm",                        89 )
    lutItem("panflute",                       75 )
    lutItem("pedhihat",             (0x80 |  44) )
    lutItem("percussiveorgan",                17 )
    lutItem("piccolo",                        72 )
    lutItem("pizzicatostrings",               45 )
    lutItem("r2",                   (0x80 |  59) )
    lutItem("rb",                   (0x80 |  53) )
    lutItem("rc",                   (0x80 |  51) )
    lutItem("recorder",                       74 )
    lutItem("reedorgan",                      20 )
    lutItem("reversecymbal",                 119 )
    lutItem("ridebell",             (0x80 |  53) )
    lutItem("ridecy",               (0x80 |  51) )
    lutItem("ridecy2",              (0x80 |  59) )
    lutItem("rockorgan",                      18 )
    lutItem("rs",                   (0x80 |  37) )
    lutItem("s2",                   (0x80 |  40) )
    lutItem("sc",                   (0x80 |  55) )
    lutItem("sd",                   (0x80 |  38) )
    lutItem("seashore",                      122 )
    lutItem("sguiro",               (0x80 |  73) )
    lutItem("shamisen",                      106 )
    lutItem("shanai",                        111 )
    lutItem("sidestick",            (0x80 |  37) )
    lutItem("sitar",                         104 )
    lutItem("skakuhachi",                     77 )
    lutItem("slapbass1",                      36 )
    lutItem("slapbass2",                      37 )
    lutItem("sopranosax",                     64 )
    lutItem("splashcy",             (0x80 |  55) )
    lutItem("steeldrums",                    114 )
    lutItem("steelstringguitar",              25 )
    lutItem("stringensemble1",                48 )
    lutItem("stringensemble2",                49 )
    lutItem("swhistle",             (0x80 |  71) )
    lutItem("synthbass1",                     38 )
    lutItem("synthbass2",                     39 )
    lutItem("synthbrass1",                    62 )
    lutItem("synthbrass2",                    63 )
    lutItem("synthdrum",                     118 )
    lutItem("synthstrings1",                  50 )
    lutItem("synthstrings2",                  51 )
    lutItem("synthvoice",                     54 )
    lutItem("t1",                   (0x80 |  41) )
    lutItem("t2",                   (0x80 |  43) )
    lutItem("t3",                   (0x80 |  45) )
    lutItem("t4",                   (0x80 |  47) )
    lutItem("t5",                   (0x80 |  48) )
    lutItem("t6",                   (0x80 |  50) )
    lutItem("ta",                   (0x80 |  54) )
    lutItem("taikodrum",                     116 )
    lutItem("tambourine",           (0x80 |  54) )
    lutItem("tangoaccordion",                 23 )
    lutItem("tc",                   (0x80 |  52) )
    lutItem("telephonering",                 124 )
    lutItem("tenorsax",                       66 )
    lutItem("timpani",                        47 )
    lutItem("tinklebell",                    112 )
    lutItem("tom1",                 (0x80 |  41) )
    lutItem("tom2",                 (0x80 |  43) )
    lutItem("tom3",                 (0x80 |  45) )
    lutItem("tom4",                 (0x80 |  47) )
    lutItem("tom5",                 (0x80 |  48) )
    lutItem("tom6",                 (0x80 |  50) )
    lutItem("tremolostrings",                 44 )
    lutItem("trombone",                       57 )
    lutItem("trumpet",                        56 )
    lutItem("tuba",                           58 )
    lutItem("tubularbells",                   14 )
    lutItem("vibraphone",                     11 )
    lutItem("vibraslap",            (0x80 |  58) )
    lutItem("viola",                          41 )
    lutItem("violin",                         40 )
    lutItem("voiceoohs",                      53 )
    lutItem("whistle",                        78 )
    lutItem("woodblock",                     115 )
    lutItem("xylophone",                      13 )
lutEnd(instr)

lutBegin(SN,ctrl)
    lutItem("allnotesoff"              ,        123 )
    lutItem("allsoundoff"              ,        120 )
    lutItem("attacktime"               ,         73 )
    lutItem("balance"                  ,          8 )
    lutItem("balancelsb"               ,         40 )
    lutItem("bankselect"               ,          0 )
    lutItem("bankselectlsb"            ,         32 )
    lutItem("breathcontroller"         ,          2 )
    lutItem("breathcontrollerlsb"      ,         34 )
    lutItem("brightness"               ,         74 )
    lutItem("channelcoarsetuning"      ,        130 )
    lutItem("channelfinetuning"        ,        129 )
    lutItem("channelvolume"            ,          7 )
    lutItem("channelvolumelsb"         ,         39 )
    lutItem("chorussend"               ,         93 )
    lutItem("damperpedal"              ,         64 )
    lutItem("datadecrement"            ,         97 )
    lutItem("dataentry"                ,          6 )
    lutItem("dataentrylsb"             ,         38 )
    lutItem("dataincrement"            ,         96 )
    lutItem("decaytime"                ,         75 )
    lutItem("detune"                   ,         94 )
    lutItem("effectcontrol1"           ,         12 )
    lutItem("effectcontrol1lsb"        ,         44 )
    lutItem("effectcontrol2"           ,         13 )
    lutItem("effectcontrol2lsb"        ,         45 )
    lutItem("expressioncontroller"     ,         11 )
    lutItem("expressioncontrollerlsb"  ,         43 )
    lutItem("footcontroller"           ,          4 )
    lutItem("footcontrollerlsb"        ,         36 )
    lutItem("harmonicintensity"        ,         71 )
    lutItem("hold2"                    ,         69 )
    lutItem("legato"                   ,         68 )
    lutItem("localcontrol"             ,        122 )
    lutItem("modulationdepthrange"     ,        133 )
    lutItem("modulationwheel"          ,          1 )
    lutItem("modulationwheellsb"       ,         33 )
    lutItem("monomodeoff"              ,        127 )
    lutItem("monomodeon"               ,        126 )
    lutItem("nonregisterednumber"      ,         99 )
    lutItem("nonregisterednumberlsb"   ,         98 )
    lutItem("omnimodeoff"              ,        124 )
    lutItem("omnimodeon"               ,        125 )
    lutItem("pan"                      ,         10 )
    lutItem("panlsb"                   ,         42 )
    lutItem("phaserdepth"              ,         95 )
    lutItem("pitchbendsensitivity"     ,        128 )
    lutItem("polymodeoff"              ,        126 )
    lutItem("polymodeon"               ,        127 )
    lutItem("portamento"               ,         65 )
    lutItem("portamentocontrol"        ,         84 )
    lutItem("portamentolsb"            ,         37 )
    lutItem("portamentotime"           ,          5 )
    lutItem("registerednumber"         ,        101 )
    lutItem("registerednumberlsb"      ,        100 )
    lutItem("releasetime"              ,         72 )
    lutItem("resetallcontrollers"      ,        121 )
    lutItem("reverbsend"               ,         91 )
    lutItem("rpnreset"                 ,        255 )
    lutItem("softpedal"                ,         67 )
    lutItem("sostenuto"                ,         66 )
    lutItem("soundvariation"           ,         70 )
    lutItem("timbreintensity"          ,         71 )
    lutItem("tremolodepth"             ,         92 )
    lutItem("tuningbank"               ,        132 )
    lutItem("tuningprogram"            ,        131 )
    lutItem("vibratodelay"             ,         78 )
    lutItem("vibratodepth"             ,         77 )
    lutItem("vibratorate"              ,         76 )
lutEnd(ctrl)
                                        
lutBegin(SN,keys)
    lutItem("ja"  ,    3)
    lutItem("jab" ,   -4)
    lutItem("jb"  ,    5)
    lutItem("jbb" ,   -2)
    lutItem("jc"  ,    0)
    lutItem("jc#" ,    7)
    lutItem("jcb" ,   -7)
    lutItem("jd"  ,    2)
    lutItem("jdb" ,   -5)
    lutItem("je"  ,    4)
    lutItem("jeb" ,   -3)
    lutItem("jf"  ,   -1)
    lutItem("jf#" ,    6)
    lutItem("jg"  ,    1)
    lutItem("jgb" ,   -6)
    lutItem("na"  ,  100)
    lutItem("na#" ,  107)
    lutItem("nab" , -107)
    lutItem("nb"  ,  102)
    lutItem("nbb" , -105)
    lutItem("nc"  , -103)
    lutItem("nc#" ,  104)
    lutItem("nd"  , -101)
    lutItem("nd#" ,  106)
    lutItem("ne"  ,  101)
    lutItem("neb" , -106)
    lutItem("nf"  , -104)
    lutItem("nf#" ,  103)
    lutItem("ng"  , -102)
    lutItem("ng#" ,  105)
lutEnd(keys)

lutBegin(SS,chords)
    lutItem("11"              ,"0,4,7,10,14,17"    )
    lutItem("11:1"            ,"0,4,7,10,14,5"     )
    lutItem("11:2"            ,"12,4,7,10,14,17"   )
    lutItem("11:3"            ,"0,4,7,10,2,5"      )
    lutItem("11:4"            ,"0,4,7,-12,2,5"     )
    lutItem("11:5"            ,"0,4,-15,-12,2,5"   )
    lutItem("5"               ,"0,7"               )
    lutItem("5:1"             ,"0,-15"             )
    lutItem("5:2"             ,"12,7"              )
    lutItem("6"               ,"0,4,7,9"           )
    lutItem("6/9"             ,"0,4,7,9,14"        )
    lutItem("6:1"             ,"0,4,7,-13"         )
    lutItem("6:2"             ,"12,4,7,9"          )
    lutItem("6:3"             ,"0,4,-15,-13"       )
    lutItem("7"               ,"0,4,7,10"          )
    lutItem("7:1"             ,"0,4,7,-12"         )
    lutItem("7:2"             ,"12,4,7,10"         )
    lutItem("7:3"             ,"0,4,-15,-12"       )
    lutItem("7sus"            ,"0,5,7,10"          )
    lutItem("7sus9"           ,"0,2,7,10"          )
    lutItem("7sus9:1"         ,"0,2,7,-12"         )
    lutItem("7sus9:2"         ,"12,2,7,10"         )
    lutItem("7sus9:3"         ,"0,2,-15,-12"       )
    lutItem("7sus:1"          ,"0,5,7,-12"         )
    lutItem("7sus:2"          ,"12,5,7,10"         )
    lutItem("7sus:3"          ,"0,5,-15,-12"       )
    lutItem("7{5b}"           ,"0,4,6,10"          )
    lutItem("7{5b}:1"         ,"0,4,6,-12"         )
    lutItem("7{5b}:2"         ,"12,4,6,10"         )
    lutItem("7{5b}:3"         ,"0,4,-16,-12"       )
    lutItem("9"               ,"0,4,7,10,14"       )
    lutItem("9:1"             ,"0,4,7,10,2"        )
    lutItem("9:2"             ,"12,4,7,10,14"      )
    lutItem("9:3"             ,"0,4,7,-12,2"       )
    lutItem("9:4"             ,"0,4,-15,-12,2"     )
    lutItem("aug"             ,"0,3,8"             )
    lutItem("aug7"            ,"0,4,8,11"          )
    lutItem("aug7:1"          ,"0,4,8,-11"         )
    lutItem("aug7:2"          ,"12,4,8,11"         )
    lutItem("aug7:3"          ,"0,4,-14,-11"       )
    lutItem("aug:1"           ,"0,3,-14"           )
    lutItem("aug:2"           ,"12,3,8"            )
    lutItem("dim"             ,"0,3,6"             )
    lutItem("dim7"            ,"0,3,6,9"           )
    lutItem("dim7:1"          ,"0,3,6,-13"         )
    lutItem("dim7:2"          ,"12,3,6,9"          )
    lutItem("dim7:3"          ,"0,3,-16,-13"       )
    lutItem("dim9"            ,"0,4,7,10,13"       )
    lutItem("dim9:1"          ,"0,4,7,10,1"        )
    lutItem("dim9:2"          ,"12,4,7,10,13"      )
    lutItem("dim9:3"          ,"0,4,7,-12,1"       )
    lutItem("dim9:4"          ,"0,4,-15,-12,1"     )
    lutItem("dim:1"           ,"0,3,-16"           )
    lutItem("dim:2"           ,"12,3,6"            )
    lutItem("maj"             ,"0,4,7"             )
    lutItem("maj7"            ,"0,3,7,11"          )
    lutItem("maj7:1"          ,"0,3,7,-11"         )
    lutItem("maj7:2"          ,"12,3,7,11"         )
    lutItem("maj7:3"          ,"0,3,-15,-11"       )
    lutItem("maj9"            ,"0,4,7,11,14"       )
    lutItem("maj9:1"          ,"0,4,7,11,2"        )
    lutItem("maj9:2"          ,"12,4,7,11,14"      )
    lutItem("maj9:3"          ,"0,4,7,-11,2"       )
    lutItem("maj9:4"          ,"0,4,-15,-11,2"     )
    lutItem("maj:1"           ,"0,4,-15"           )
    lutItem("maj:2"           ,"12,4,7"            )
    lutItem("min"             ,"0,3,7"             )
    lutItem("min6"            ,"0,3,7,9"           )
    lutItem("min6:1"          ,"0,3,7,-13"         )
    lutItem("min6:2"          ,"12,3,7,9"          )
    lutItem("min6:3"          ,"0,3,-15,-13"       )
    lutItem("min7"            ,"0,3,7,10"          )
    lutItem("min7:1"          ,"0,3,7,-12"         )
    lutItem("min7:2"          ,"12,3,7,10"         )
    lutItem("min7:3"          ,"0,3,-15,-12"       )
    lutItem("min7{5b}"        ,"0,3,6,10"          )
    lutItem("min7{5b}:1"      ,"0,3,6,-12"         )
    lutItem("min7{5b}:2"      ,"12,3,6,10"         )
    lutItem("min7{5b}:3"      ,"0,3,-16,-12"       )
    lutItem("min9"            ,"0,3,7,10,14"       )
    lutItem("min9:1"          ,"0,3,7,10,2"        )
    lutItem("min9:2"          ,"12,3,7,10,14"      )
    lutItem("min9:3"          ,"0,3,7,-12,2"       )
    lutItem("min9:4"          ,"0,3,-15,-12,2"     )
    lutItem("min:1"           ,"0,3,-15"           )
    lutItem("min:2"           ,"12,3,7"            )
    lutItem("sus"             ,"0,5,7"             )
    lutItem("sus9"            ,"0,7,14"            )
    lutItem("sus9:1"          ,"0,7,2"             )
    lutItem("sus9:2"          ,"12,7,14"           )
    lutItem("sus:1"           ,"0,5,-15"           )
    lutItem("sus:2"           ,"12,5,7"            )
    lutItem("{4}"             ,"0,4,7,17"          )
    lutItem("{4}:1"           ,"0,4,5,7"           )
    lutItem("{4}:2"           ,"12,4,7,17"         )
    lutItem("{4}:3"           ,"0,4,-15,5"         )
    lutItem("{9}"             ,"0,4,7,14"          )
    lutItem("{9}:1"           ,"0,4,7,2"           )
    lutItem("{9}:2"           ,"12,4,7,14"         )
    lutItem("{9}:3"           ,"0,4,-15,2"         )
lutEnd(chords)

lutBegin(SS,gchords)
    lutItem( "a/ab"         ,    "-,0,2,1,2,0"      )
    lutItem( "a/b"          ,    "0,0,2,4,2,0"      )
    lutItem( "a/b:1"        ,    "-,0,7,6,0,0"      )
    lutItem( "a/d"          ,    "-,0,0,2,2,0"      )
    lutItem( "a/d:1"        ,    "-,-,0,2,2,0"      )
    lutItem( "a/d:2"        ,    "-,-,0,6,5,5"      )
    lutItem( "a/d:3"        ,    "-,-,0,9,10,9"     )
    lutItem( "a/g"          ,    "3,-,2,2,2,0"      )
    lutItem( "a/g:1"        ,    "-,0,2,0,2,0"      )
    lutItem( "a/g:2"        ,    "-,0,2,2,2,3"      )
    lutItem( "a/gb"         ,    "0,0,2,2,2,2"      )
    lutItem( "a/gb:1"       ,    "0,-,4,2,2,0"      )
    lutItem( "a/gb:2"       ,    "2,-,2,2,2,0"      )
    lutItem( "a/gb:3"       ,    "-,0,4,2,2,0"      )
    lutItem( "a/gb:4"       ,    "-,-,2,2,2,2"      )
    lutItem( "a5"           ,    "5,7,7,-,-,5"      )
    lutItem( "a5:1"         ,    "-,0,2,2,-,0"      )
    lutItem( "a5:2"         ,    "5,7,7,-,-,0"      )
    lutItem( "a6"           ,    "0,0,2,2,2,2"      )
    lutItem( "a6/7"         ,    "0,0,2,0,2,2"      )
    lutItem( "a6/7:1"       ,    "5,5,4,0,3,0"      )
    lutItem( "a6/7:2"       ,    "-,0,2,0,3,2"      )
    lutItem( "a6:1"         ,    "0,-,4,2,2,0"      )
    lutItem( "a6:2"         ,    "2,-,2,2,2,0"      )
    lutItem( "a6:3"         ,    "-,0,4,2,2,0"      )
    lutItem( "a6:4"         ,    "-,-,2,2,2,2"      )
    lutItem( "a7"           ,    "3,-,2,2,2,0"      )
    lutItem( "a7/add11"     ,    "-,0,0,0,2,0"      )
    lutItem( "a7:1"         ,    "-,0,2,0,2,0"      )
    lutItem( "a7:2"         ,    "-,0,2,2,2,3"      )
    lutItem( "a7sus4"       ,    "-,0,2,0,3,0"      )
    lutItem( "a7sus4:1"     ,    "-,0,2,0,3,3"      )
    lutItem( "a7sus4:2"     ,    "-,0,2,2,3,3"      )
    lutItem( "a7sus4:3"     ,    "5,-,0,0,3,0"      )
    lutItem( "a7sus4:4"     ,    "-,0,0,0,-,0"      )
    lutItem( "a7{#5}"       ,    "1,0,3,0,2,1"      )
    lutItem( "aadd9"        ,    "0,0,2,4,2,0"      )
    lutItem( "aadd9:1"      ,    "-,0,7,6,0,0"      )
    lutItem( "aaug"         ,    "-,0,3,2,2,1"      )
    lutItem( "aaug/d"       ,    "-,-,0,2,2,1"      )
    lutItem( "aaug/g"       ,    "1,0,3,0,2,1"      )
    lutItem( "aaug:1"       ,    "-,0,-,2,2,1"      )
    lutItem( "ab/a"         ,    "-,-,1,2,1,4"      )
    lutItem( "ab/f"         ,    "-,8,10,8,9,8"     )
    lutItem( "ab/f:1"       ,    "-,-,1,1,1,1"      )
    lutItem( "ab/gb"        ,    "-,-,1,1,1,2"      )
    lutItem( "ab/gb:1"      ,    "-,-,4,5,4,4"      )
    lutItem( "ab5"          ,    "4,6,6,-,-,4"      )
    lutItem( "ab6"          ,    "-,8,10,8,9,8"     )
    lutItem( "ab6:1"        ,    "-,-,1,1,1,1"      )
    lutItem( "ab7"          ,    "-,-,1,1,1,2"      )
    lutItem( "ab7:1"        ,    "-,-,4,5,4,4"      )
    lutItem( "abaug"        ,    "-,3,2,1,1,0"      )
    lutItem( "abdim/e"      ,    "0,2,0,1,0,0"      )
    lutItem( "abdim/e:1"    ,    "0,2,2,1,3,0"      )
    lutItem( "abdim/e:2"    ,    "-,2,0,1,3,0"      )
    lutItem( "abdim/e:3"    ,    "-,-,0,1,0,0"      )
    lutItem( "abdim/eb"     ,    "-,-,0,4,4,4"      )
    lutItem( "abdim/f"      ,    "-,2,0,1,0,1"      )
    lutItem( "abdim/f:1"    ,    "-,-,0,1,0,1"      )
    lutItem( "abdim/f:2"    ,    "-,-,3,4,3,4"      )
    lutItem( "abdimin7"     ,    "-,2,0,1,0,1"      )
    lutItem( "abdimin7:1"   ,    "-,-,0,1,0,1"      )
    lutItem( "abdimin7:2"   ,    "-,-,3,4,3,4"      )
    lutItem( "abmaj"        ,    "4,6,6,5,4,4"      )
    lutItem( "abmin"        ,    "-,-,6,4,4,4"      )
    lutItem( "abmin/d"      ,    "-,-,0,4,4,4"      )
    lutItem( "abmin/e"      ,    "0,2,1,1,0,0"      )
    lutItem( "abmin/e:1"    ,    "0,-,6,4,4,0"      )
    lutItem( "abmin/e:2"    ,    "-,-,1,1,0,0"      )
    lutItem( "abmin/gb"     ,    "-,-,4,4,4,4"      )
    lutItem( "abmin7"       ,    "-,-,4,4,4,4"      )
    lutItem( "absus"        ,    "-,-,6,6,4,4"      )
    lutItem( "absus2/f"     ,    "-,1,3,1,4,1"      )
    lutItem( "adim/ab"      ,    "-,-,1,2,1,4"      )
    lutItem( "adim/e"       ,    "0,3,-,2,4,0"      )
    lutItem( "adim/f"       ,    "-,-,1,2,1,1"      )
    lutItem( "adim/f:1"     ,    "-,-,3,5,4,5"      )
    lutItem( "adim/g"       ,    "-,-,1,2,1,3"      )
    lutItem( "adim/gb"      ,    "-,-,1,2,1,2"      )
    lutItem( "adimin7"      ,    "-,-,1,2,1,2"      )
    lutItem( "am6"          ,    "-,0,2,2,1,2"      )
    lutItem( "am6:1"        ,    "-,-,2,2,1,2"      )
    lutItem( "amaj"         ,    "0,0,2,2,2,0"      )
    lutItem( "amaj7"        ,    "-,0,2,1,2,0"      )
    lutItem( "amaj:1"       ,    "0,4,-,2,5,0"      )
    lutItem( "amaj:2"       ,    "5,7,7,6,5,5"      )
    lutItem( "amaj:3"       ,    "-,0,2,2,2,0"      )
    lutItem( "amaj:4"       ,    "-,4,7,-,-,5"      )
    lutItem( "amin"         ,    "-,0,2,2,1,0"      )
    lutItem( "amin/b"       ,    "0,0,7,5,0,0"      )
    lutItem( "amin/b:1"     ,    "-,3,2,2,0,0"      )
    lutItem( "amin/d"       ,    "-,-,0,2,1,0"      )
    lutItem( "amin/d:1"     ,    "-,-,0,5,5,5"      )
    lutItem( "amin/eb"      ,    "0,3,-,2,4,0"      )
    lutItem( "amin/f"       ,    "0,0,3,2,1,0"      )
    lutItem( "amin/f:1"     ,    "1,3,3,2,1,0"      )
    lutItem( "amin/f:2"     ,    "1,-,2,2,1,0"      )
    lutItem( "amin/f:3"     ,    "-,-,2,2,1,1"      )
    lutItem( "amin/f:4"     ,    "-,-,3,2,1,0"      )
    lutItem( "amin/g"       ,    "0,0,2,0,1,3"      )
    lutItem( "amin/g:1"     ,    "-,0,2,0,1,0"      )
    lutItem( "amin/g:2"     ,    "-,0,2,2,1,3"      )
    lutItem( "amin/g:3"     ,    "-,0,5,5,5,8"      )
    lutItem( "amin/gb"      ,    "-,0,2,2,1,2"      )
    lutItem( "amin/gb:1"    ,    "-,-,2,2,1,2"      )
    lutItem( "amin/maj9"    ,    "-,0,6,5,5,7"      )
    lutItem( "amin7"        ,    "0,0,2,0,1,3"      )
    lutItem( "amin7/add11"  ,    "-,5,7,5,8,0"      )
    lutItem( "amin7:1"      ,    "-,0,2,0,1,0"      )
    lutItem( "amin7:2"      ,    "-,0,2,2,1,3"      )
    lutItem( "amin7:3"      ,    "-,0,5,5,5,8"      )
    lutItem( "amin7{b5}"    ,    "-,-,1,2,1,3"      )
    lutItem( "amin:1"       ,    "-,0,7,5,5,5"      )
    lutItem( "amin:2"       ,    "-,3,2,2,1,0"      )
    lutItem( "amin:3"       ,    "8,12,-,-,-,0"     )
    lutItem( "asus"         ,    "0,0,2,2,3,0"      )
    lutItem( "asus2"        ,    "0,0,2,2,0,0"      )
    lutItem( "asus2/ab"     ,    "-,0,2,1,0,0"      )
    lutItem( "asus2/c"      ,    "0,0,7,5,0,0"      )
    lutItem( "asus2/c:1"    ,    "-,3,2,2,0,0"      )
    lutItem( "asus2/d"      ,    "0,2,0,2,0,0"      )
    lutItem( "asus2/d:1"    ,    "-,2,0,2,3,0"      )
    lutItem( "asus2/db"     ,    "0,0,2,4,2,0"      )
    lutItem( "asus2/db:1"   ,    "-,0,7,6,0,0"      )
    lutItem( "asus2/eb"     ,    "-,2,1,2,0,0"      )
    lutItem( "asus2/f"      ,    "0,0,3,2,0,0"      )
    lutItem( "asus2/g"      ,    "3,-,2,2,0,0"      )
    lutItem( "asus2/g:1"    ,    "-,0,2,0,0,0"      )
    lutItem( "asus2/g:2"    ,    "-,0,5,4,5,0"      )
    lutItem( "asus2/gb"     ,    "-,0,4,4,0,0"      )
    lutItem( "asus2/gb:1"   ,    "-,2,4,2,5,2"      )
    lutItem( "asus2:1"      ,    "0,0,2,4,0,0"      )
    lutItem( "asus2:2"      ,    "0,2,2,2,0,0"      )
    lutItem( "asus2:3"      ,    "-,0,2,2,0,0"      )
    lutItem( "asus2:4"      ,    "-,-,2,2,0,0"      )
    lutItem( "asus4/ab"     ,    "4,-,0,2,3,0"      )
    lutItem( "asus4/b"      ,    "0,2,0,2,0,0"      )
    lutItem( "asus4/bb"     ,    "0,1,-,2,3,0"      )
    lutItem( "asus4/c"      ,    "-,-,0,2,1,0"      )
    lutItem( "asus4/c:1"    ,    "-,-,0,5,5,5"      )
    lutItem( "asus4/db"     ,    "-,0,0,2,2,0"      )
    lutItem( "asus4/db:1"   ,    "-,-,0,2,2,0"      )
    lutItem( "asus4/db:2"   ,    "-,-,0,6,5,5"      )
    lutItem( "asus4/db:3"   ,    "-,-,0,9,10,9"     )
    lutItem( "asus4/f"      ,    "-,-,7,7,6,0"      )
    lutItem( "asus4/g"      ,    "-,0,2,0,3,0"      )
    lutItem( "asus4/g:1"    ,    "-,0,2,0,3,3"      )
    lutItem( "asus4/g:2"    ,    "-,0,2,2,3,3"      )
    lutItem( "asus4/g:3"    ,    "-,0,0,0,-,0"      )
    lutItem( "asus4/gb"     ,    "0,0,0,2,3,2"      )
    lutItem( "asus4/gb:1"   ,    "0,0,4,2,3,0"      )
    lutItem( "asus4/gb:2"   ,    "2,-,0,2,3,0"      )
    lutItem( "asus4/gb:3"   ,    "-,0,2,2,3,2"      )
    lutItem( "asus4/gb:4"   ,    "-,-,2,2,3,2"      )
    lutItem( "asus4/gb:5"   ,    "-,5,4,2,3,0"      )
    lutItem( "asus4/gb:6"   ,    "-,9,7,7,-,0"      )
    lutItem( "asus:1"       ,    "-,0,2,2,3,0"      )
    lutItem( "asus:2"       ,    "5,5,7,7,-,0"      )
    lutItem( "asus:3"       ,    "-,0,0,2,3,0"      )
    lutItem( "b/a"          ,    "2,-,1,2,0,2"      )
    lutItem( "b/a:1"        ,    "-,0,1,2,0,2"      )
    lutItem( "b/a:2"        ,    "-,2,1,2,0,2"      )
    lutItem( "b/a:3"        ,    "-,2,4,2,4,2"      )
    lutItem( "b/ab"         ,    "-,-,4,4,4,4"      )
    lutItem( "b/e"          ,    "-,2,2,4,4,2"      )
    lutItem( "b/e:1"        ,    "-,-,4,4,4,0"      )
    lutItem( "b5"           ,    "7,9,9,-,-,2"      )
    lutItem( "b5:1"         ,    "-,2,4,4,-,2"      )
    lutItem( "b6"           ,    "-,-,4,4,4,4"      )
    lutItem( "b7"           ,    "2,-,1,2,0,2"      )
    lutItem( "b7/add11"     ,    "0,0,4,4,4,0"      )
    lutItem( "b7/add11:1"   ,    "0,2,1,2,0,2"      )
    lutItem( "b7:1"         ,    "-,0,1,2,0,2"      )
    lutItem( "b7:2"         ,    "-,2,1,2,0,2"      )
    lutItem( "b7:3"         ,    "-,2,4,2,4,2"      )
    lutItem( "b7sus4"       ,    "-,0,4,4,0,0"      )
    lutItem( "b7sus4:1"     ,    "-,2,4,2,5,2"      )
    lutItem( "baug"         ,    "3,2,1,0,0,3"      )
    lutItem( "baug/e"       ,    "3,-,1,0,0,0"      )
    lutItem( "baug/e:1"     ,    "-,-,1,0,0,0"      )
    lutItem( "baug:1"       ,    "3,-,1,0,0,3"      )
    lutItem( "bb"           ,    "-,-,0,3,-,0"      )
    lutItem( "bb/a"         ,    "1,1,3,2,3,1"      )
    lutItem( "bb/ab"        ,    "-,1,3,1,3,1"      )
    lutItem( "bb/ab:1"      ,    "-,-,3,3,3,4"      )
    lutItem( "bb/db"        ,    "-,-,0,6,6,6"      )
    lutItem( "bb/e"         ,    "-,1,3,3,3,0"      )
    lutItem( "bb/g"         ,    "3,5,3,3,3,3"      )
    lutItem( "bb/g:1"       ,    "-,-,3,3,3,3"      )
    lutItem( "bb5"          ,    "6,8,8,-,-,6"      )
    lutItem( "bb5:1"        ,    "-,1,3,3,-,6"      )
    lutItem( "bb6"          ,    "3,5,3,3,3,3"      )
    lutItem( "bb6/add9"     ,    "-,3,3,3,3,3"      )
    lutItem( "bb6:1"        ,    "-,-,3,3,3,3"      )
    lutItem( "bb7"          ,    "-,1,3,1,3,1"      )
    lutItem( "bb7:1"        ,    "-,-,3,3,3,4"      )
    lutItem( "bb7sus4"      ,    "-,1,3,1,4,1"      )
    lutItem( "bbadd#11"     ,    "-,1,3,3,3,0"      )
    lutItem( "bbaug"        ,    "-,-,0,3,3,2"      )
    lutItem( "bbaug/e"      ,    "2,-,4,3,3,0"      )
    lutItem( "bbdim/c"      ,    "-,3,-,3,2,0"      )
    lutItem( "bbdim/d"      ,    "-,-,0,3,2,0"      )
    lutItem( "bbdim/g"      ,    "-,1,2,0,2,0"      )
    lutItem( "bbdim/g:1"    ,    "-,-,2,3,2,3"      )
    lutItem( "bbdim/gb"     ,    "2,4,2,3,2,2"      )
    lutItem( "bbdim/gb:1"   ,    "-,-,4,3,2,0"      )
    lutItem( "bbdimin7"     ,    "-,1,2,0,2,0"      )
    lutItem( "bbdimin7:1"   ,    "-,-,2,3,2,3"      )
    lutItem( "bbmaj"        ,    "1,1,3,3,3,1"      )
    lutItem( "bbmaj7"       ,    "1,1,3,2,3,1"      )
    lutItem( "bbmaj9"       ,    "-,3,3,3,3,5"      )
    lutItem( "bbmaj:1"      ,    "-,1,3,3,3,1"      )
    lutItem( "bbmaj:2"      ,    "-,-,0,3,3,1"      )
    lutItem( "bbmin"        ,    "1,1,3,3,2,1"      )
    lutItem( "bbmin/ab"     ,    "-,1,3,1,2,1"      )
    lutItem( "bbmin/d"      ,    "-,-,0,6,6,6"      )
    lutItem( "bbmin/gb"     ,    "-,-,3,3,2,2"      )
    lutItem( "bbmin7"       ,    "-,1,3,1,2,1"      )
    lutItem( "bbsus2"       ,    "-,-,3,3,1,1"      )
    lutItem( "bbsus2/g"     ,    "-,3,5,3,6,3"      )
    lutItem( "bbsus4/ab"    ,    "-,1,3,1,4,1"      )
    lutItem( "bdim/a"       ,    "1,2,3,2,3,1"      )
    lutItem( "bdim/a:1"     ,    "-,2,0,2,0,1"      )
    lutItem( "bdim/a:2"     ,    "-,-,0,2,0,1"      )
    lutItem( "bdim/ab"      ,    "-,2,0,1,0,1"      )
    lutItem( "bdim/ab:1"    ,    "-,-,0,1,0,1"      )
    lutItem( "bdim/ab:2"    ,    "-,-,3,4,3,4"      )
    lutItem( "bdim/g"       ,    "1,-,0,0,0,3"      )
    lutItem( "bdim/g:1"     ,    "3,2,0,0,0,1"      )
    lutItem( "bdim/g:2"     ,    "-,-,0,0,0,1"      )
    lutItem( "bdimin7"      ,    "-,2,0,1,0,1"      )
    lutItem( "bdimin7:1"    ,    "-,-,0,1,0,1"      )
    lutItem( "bdimin7:2"    ,    "-,-,3,4,3,4"      )
    lutItem( "bmaj"         ,    "-,2,4,4,4,2"      )
    lutItem( "bmaj7/#11"    ,    "-,2,3,3,4,2"      )
    lutItem( "bmin"         ,    "2,2,4,4,3,2"      )
    lutItem( "bmin/a"       ,    "-,0,4,4,3,2"      )
    lutItem( "bmin/a:1"     ,    "-,2,0,2,0,2"      )
    lutItem( "bmin/a:2"     ,    "-,2,0,2,3,2"      )
    lutItem( "bmin/a:3"     ,    "-,2,4,2,3,2"      )
    lutItem( "bmin/a:4"     ,    "-,-,0,2,0,2"      )
    lutItem( "bmin/g"       ,    "2,2,0,0,0,3"      )
    lutItem( "bmin/g:1"     ,    "2,2,0,0,3,3"      )
    lutItem( "bmin/g:2"     ,    "3,2,0,0,0,2"      )
    lutItem( "bmin/g:3"     ,    "-,-,4,4,3,3"      )
    lutItem( "bmin7"        ,    "-,0,4,4,3,2"      )
    lutItem( "bmin7/add11"  ,    "0,0,2,4,3,2"      )
    lutItem( "bmin7/add11:1",    "0,2,0,2,0,2"      )
    lutItem( "bmin7:1"      ,    "-,2,0,2,0,2"      )
    lutItem( "bmin7:2"      ,    "-,2,0,2,3,2"      )
    lutItem( "bmin7:3"      ,    "-,2,4,2,3,2"      )
    lutItem( "bmin7:4"      ,    "-,-,0,2,0,2"      )
    lutItem( "bmin7{b5}"    ,    "1,2,3,2,3,1"      )
    lutItem( "bmin7{b5}:1"  ,    "-,2,0,2,0,1"      )
    lutItem( "bmin7{b5}:2"  ,    "-,-,0,2,0,1"      )
    lutItem( "bmin:1"       ,    "-,2,4,4,3,2"      )
    lutItem( "bmin:2"       ,    "-,-,0,4,3,2"      )
    lutItem( "bsus"         ,    "7,9,9,-,-,0"      )
    lutItem( "bsus2"        ,    "-,4,4,4,-,2"      )
    lutItem( "bsus2/e"      ,    "-,4,4,4,-,0"      )
    lutItem( "bsus2:1"      ,    "-,-,4,4,2,2"      )
    lutItem( "bsus4/a"      ,    "-,0,4,4,0,0"      )
    lutItem( "bsus4/a:1"    ,    "-,2,4,2,5,2"      )
    lutItem( "bsus4/ab"     ,    "0,2,2,1,0,2"      )
    lutItem( "bsus4/ab:1"   ,    "0,-,4,1,0,0"      )
    lutItem( "bsus4/ab:2"   ,    "2,2,2,1,0,0"      )
    lutItem( "bsus4/db"     ,    "-,4,4,4,-,0"      )
    lutItem( "bsus4/eb"     ,    "-,2,2,4,4,2"      )
    lutItem( "bsus4/eb:1"   ,    "-,-,4,4,4,0"      )
    lutItem( "bsus4/g"      ,    "0,2,2,0,0,2"      )
    lutItem( "bsus4/g:1"    ,    "0,2,4,0,0,0"      )
    lutItem( "bsus4/g:2"    ,    "0,-,4,0,0,0"      )
    lutItem( "bsus4/g:3"    ,    "2,2,2,0,0,0"      )
    lutItem( "bsus:1"       ,    "-,2,4,4,-,0"      )
    lutItem( "c/a"          ,    "0,0,2,0,1,3"      )
    lutItem( "c/a:1"        ,    "-,0,2,0,1,0"      )
    lutItem( "c/a:2"        ,    "-,0,2,2,1,3"      )
    lutItem( "c/a:3"        ,    "-,0,5,5,5,8"      )
    lutItem( "c/b"          ,    "0,3,2,0,0,0"      )
    lutItem( "c/b:1"        ,    "-,2,2,0,1,0"      )
    lutItem( "c/b:2"        ,    "-,3,5,4,5,3"      )
    lutItem( "c/bb"         ,    "-,3,5,3,5,3"      )
    lutItem( "c/d"          ,    "3,-,0,0,1,0"      )
    lutItem( "c/d:1"        ,    "-,3,0,0,1,0"      )
    lutItem( "c/d:2"        ,    "-,3,2,0,3,0"      )
    lutItem( "c/d:3"        ,    "-,3,2,0,3,3"      )
    lutItem( "c/d:4"        ,    "-,-,0,0,1,0"      )
    lutItem( "c/d:5"        ,    "-,-,0,5,5,3"      )
    lutItem( "c/d:6"        ,    "-,10,12,12,13,0"  )
    lutItem( "c/d:7"        ,    "-,5,5,5,-,0"      )
    lutItem( "c/f"          ,    "-,3,3,0,1,0"      )
    lutItem( "c/f:1"        ,    "-,-,3,0,1,0"      )
    lutItem( "c5"           ,    "-,3,5,5,-,3"      )
    lutItem( "c6"           ,    "0,0,2,0,1,3"      )
    lutItem( "c6/add9"      ,    "-,5,7,5,8,0"      )
    lutItem( "c6:1"         ,    "-,0,2,0,1,0"      )
    lutItem( "c6:2"         ,    "-,0,2,2,1,3"      )
    lutItem( "c6:3"         ,    "-,0,5,5,5,8"      )
    lutItem( "c7"           ,    "-,3,5,3,5,3"      )
    lutItem( "c7sus4"       ,    "-,3,5,3,6,3"      )
    lutItem( "c9{b5}"       ,    "0,3,-,3,3,2"      )
    lutItem( "cadd9"        ,    "3,-,0,0,1,0"      )
    lutItem( "cadd9:1"      ,    "-,3,0,0,1,0"      )
    lutItem( "cadd9:2"      ,    "-,3,2,0,3,0"      )
    lutItem( "cadd9:3"      ,    "-,3,2,0,3,3"      )
    lutItem( "cadd9:4"      ,    "-,-,0,0,1,0"      )
    lutItem( "cadd9:5"      ,    "-,-,0,5,5,3"      )
    lutItem( "cadd9:6"      ,    "-,10,12,12,13,0"  )
    lutItem( "cadd9:7"      ,    "-,3,2,0,3,0"      )
    lutItem( "cadd9:8"      ,    "-,5,5,5,-,0"      )
    lutItem( "caug"         ,    "-,-,4,5,-,0"      )
    lutItem( "caug:1"       ,    "-,3,2,1,1,0"      )
    lutItem( "cdim/a"       ,    "-,-,1,2,1,2"      )
    lutItem( "cdim/ab"      ,    "-,-,1,1,1,2"      )
    lutItem( "cdim/ab:1"    ,    "-,-,4,5,4,4"      )
    lutItem( "cdim/d"       ,    "-,5,4,5,4,2"      )
    lutItem( "cdimin7"      ,    "-,-,1,2,1,2"      )
    lutItem( "cm6"          ,    "-,-,1,2,1,3"      )
    lutItem( "cmaj"         ,    "-,3,2,0,1,0"      )
    lutItem( "cmaj7"        ,    "0,3,2,0,0,0"      )
    lutItem( "cmaj7:1"      ,    "-,2,2,0,1,0"      )
    lutItem( "cmaj7:2"      ,    "-,3,5,4,5,3"      )
    lutItem( "cmaj9"        ,    "-,3,0,0,0,0"      )
    lutItem( "cmaj:1"       ,    "0,3,5,5,5,3"      )
    lutItem( "cmaj:2"       ,    "3,3,2,0,1,0"      )
    lutItem( "cmaj:3"       ,    "3,-,2,0,1,0"      )
    lutItem( "cmaj:4"       ,    "0,3,2,0,1,0"      )
    lutItem( "cmaj:5"       ,    "-,3,5,5,5,0"      )
    lutItem( "cmin"         ,    "-,3,5,5,4,3"      )
    lutItem( "cmin/a"       ,    "-,-,1,2,1,3"      )
    lutItem( "cmin/bb"      ,    "-,3,5,3,4,3"      )
    lutItem( "cmin7"        ,    "-,3,5,3,4,3"      )
    lutItem( "cmin:1"       ,    "-,-,5,5,4,3"      )
    lutItem( "csus"         ,    "-,3,3,0,1,1"      )
    lutItem( "csus2"        ,    "-,10,12,12,13,3"  )
    lutItem( "csus2/a"      ,    "-,5,7,5,8,3"      )
    lutItem( "csus2/a:1"    ,    "-,-,0,2,1,3"      )
    lutItem( "csus2/b"      ,    "3,3,0,0,0,3"      )
    lutItem( "csus2/b:1"    ,    "-,3,0,0,0,3"      )
    lutItem( "csus2/e"      ,    "3,-,0,0,1,0"      )
    lutItem( "csus2/e:1"    ,    "-,3,0,0,1,0"      )
    lutItem( "csus2/e:2"    ,    "-,3,2,0,3,0"      )
    lutItem( "csus2/e:3"    ,    "-,3,2,0,3,3"      )
    lutItem( "csus2/e:4"    ,    "-,-,0,0,1,0"      )
    lutItem( "csus2/e:5"    ,    "-,-,0,5,5,3"      )
    lutItem( "csus2/e:6"    ,    "-,10,12,12,13,0"  )
    lutItem( "csus2/e:7"    ,    "-,5,5,5,-,0"      )
    lutItem( "csus2/f"      ,    "3,3,0,0,1,1"      )
    lutItem( "csus2:1"      ,    "-,5,5,5,-,3"      )
    lutItem( "csus2:2"      ,    "-,3,0,0,3,3"      )
    lutItem( "csus2:3"      ,    "-,3,5,5,3,3"      )
    lutItem( "csus4/a"      ,    "3,-,3,2,1,1"      )
    lutItem( "csus4/a:1"    ,    "-,-,3,2,1,3"      )
    lutItem( "csus4/b"      ,    "-,3,3,0,0,3"      )
    lutItem( "csus4/bb"     ,    "-,3,5,3,6,3"      )
    lutItem( "csus4/d"      ,    "3,3,0,0,1,1"      )
    lutItem( "csus4/e"      ,    "-,3,3,0,1,0"      )
    lutItem( "csus4/e:1"    ,    "-,-,3,0,1,0"      )
    lutItem( "csus:1"       ,    "-,-,3,0,1,1"      )
    lutItem( "d/b"          ,    "-,0,4,4,3,2"      )
    lutItem( "d/b:1"        ,    "-,2,0,2,0,2"      )
    lutItem( "d/b:2"        ,    "-,2,0,2,3,2"      )
    lutItem( "d/b:3"        ,    "-,2,4,2,3,2"      )
    lutItem( "d/b:4"        ,    "-,-,0,2,0,2"      )
    lutItem( "d/c"          ,    "-,5,7,5,7,2"      )
    lutItem( "d/c:1"        ,    "-,0,0,2,1,2"      )
    lutItem( "d/c:2"        ,    "-,3,-,2,3,2"      )
    lutItem( "d/c:3"        ,    "-,5,7,5,7,5"      )
    lutItem( "d/db"         ,    "-,-,0,14,14,14"   )
    lutItem( "d/db:1"       ,    "-,-,0,2,2,2"      )
    lutItem( "d/e"          ,    "0,0,0,2,3,2"      )
    lutItem( "d/e:1"        ,    "0,0,4,2,3,0"      )
    lutItem( "d/e:2"        ,    "2,-,0,2,3,0"      )
    lutItem( "d/e:3"        ,    "-,0,2,2,3,2"      )
    lutItem( "d/e:4"        ,    "-,-,2,2,3,2"      )
    lutItem( "d/e:5"        ,    "-,5,4,2,3,0"      )
    lutItem( "d/e:6"        ,    "-,9,7,7,-,0"      )
    lutItem( "d/g"          ,    "5,-,4,0,3,5"      )
    lutItem( "d/g:1"        ,    "3,-,0,2,3,2"      )
    lutItem( "d5"           ,    "5,5,7,7,-,5"      )
    lutItem( "d5:1"         ,    "-,0,0,2,3,5"      )
    lutItem( "d6"           ,    "-,0,4,4,3,2"      )
    lutItem( "d6/add9"      ,    "0,0,2,4,3,2"      )
    lutItem( "d6/add9:1"    ,    "0,2,0,2,0,2"      )
    lutItem( "d6:1"         ,    "-,2,0,2,0,2"      )
    lutItem( "d6:2"         ,    "-,2,0,2,3,2"      )
    lutItem( "d6:3"         ,    "-,2,4,2,3,2"      )
    lutItem( "d6:4"         ,    "-,-,0,2,0,2"      )
    lutItem( "d7"           ,    "-,5,7,5,7,2"      )
    lutItem( "d7:1"         ,    "-,0,0,2,1,2"      )
    lutItem( "d7:2"         ,    "-,3,-,2,3,2"      )
    lutItem( "d7:3"         ,    "-,5,7,5,7,5"      )
    lutItem( "d7sus4"       ,    "-,5,7,5,8,3"      )
    lutItem( "d7sus4:1"     ,    "-,-,0,2,1,3"      )
    lutItem( "d9"           ,    "0,0,0,2,1,2"      )
    lutItem( "d9:1"         ,    "2,-,0,2,1,0"      )
    lutItem( "d9:2"         ,    "-,5,7,5,7,0"      )
    lutItem( "d9{#5}"       ,    "0,3,-,3,3,2"      )
    lutItem( "dadd9"        ,    "0,0,0,2,3,2"      )
    lutItem( "dadd9:1"      ,    "0,0,4,2,3,0"      )
    lutItem( "dadd9:2"      ,    "2,-,0,2,3,0"      )
    lutItem( "dadd9:3"      ,    "-,0,2,2,3,2"      )
    lutItem( "dadd9:4"      ,    "-,-,2,2,3,2"      )
    lutItem( "dadd9:5"      ,    "-,5,4,2,3,0"      )
    lutItem( "dadd9:6"      ,    "-,9,7,7,-,0"      )
    lutItem( "daug"         ,    "-,-,0,3,3,2"      )
    lutItem( "daug/e"       ,    "2,-,4,3,3,0"      )
    lutItem( "db/b"         ,    "-,4,3,4,0,4"      )
    lutItem( "db/bb"        ,    "-,1,3,1,2,1"      )
    lutItem( "db/c"         ,    "-,3,3,1,2,1"      )
    lutItem( "db/c:1"       ,    "-,4,6,5,6,4"      )
    lutItem( "db5"          ,    "-,4,6,6,-,4"      )
    lutItem( "db6"          ,    "-,1,3,1,2,1"      )
    lutItem( "db7"          ,    "-,4,3,4,0,4"      )
    lutItem( "dbaug"        ,    "-,-,3,0,2,1"      )
    lutItem( "dbaug/d"      ,    "-,-,0,2,2,1"      )
    lutItem( "dbaug/g"      ,    "1,0,3,0,2,1"      )
    lutItem( "dbaug:1"      ,    "-,0,3,2,2,1"      )
    lutItem( "dbaug:2"      ,    "-,0,-,2,2,1"      )
    lutItem( "dbdim/a"      ,    "3,-,2,2,2,0"      )
    lutItem( "dbdim/a:1"    ,    "-,0,2,0,2,0"      )
    lutItem( "dbdim/a:2"    ,    "-,0,2,2,2,3"      )
    lutItem( "dbdim/b"      ,    "0,2,2,0,2,0"      )
    lutItem( "dbdim/bb"     ,    "-,1,2,0,2,0"      )
    lutItem( "dbdim/bb:1"   ,    "-,-,2,3,2,3"      )
    lutItem( "dbdim/d"      ,    "3,-,0,0,2,0"      )
    lutItem( "dbdim/d:1"    ,    "-,-,0,0,2,0"      )
    lutItem( "dbdimin7"     ,    "-,1,2,0,2,0"      )
    lutItem( "dbdimin7:1"   ,    "-,-,2,3,2,3"      )
    lutItem( "dbmaj"        ,    "4,4,6,6,6,4"      )
    lutItem( "dbmaj7"       ,    "-,3,3,1,2,1"      )
    lutItem( "dbmaj7:1"     ,    "-,4,6,5,6,4"      )
    lutItem( "dbmaj:1"      ,    "-,4,3,1,2,1"      )
    lutItem( "dbmaj:2"      ,    "-,4,6,6,6,4"      )
    lutItem( "dbmaj:3"      ,    "-,-,3,1,2,1"      )
    lutItem( "dbmaj:4"      ,    "-,-,6,6,6,4"      )
    lutItem( "dbmin"        ,    "-,4,6,6,5,4"      )
    lutItem( "dbmin/a"      ,    "-,0,2,1,2,0"      )
    lutItem( "dbmin/b"      ,    "0,2,2,1,2,0"      )
    lutItem( "dbmin/b:1"    ,    "-,4,6,4,5,4"      )
    lutItem( "dbmin7"       ,    "0,2,2,1,2,0"      )
    lutItem( "dbmin7:1"     ,    "-,4,6,4,5,4"      )
    lutItem( "dbmin7{b5}"   ,    "0,2,2,0,2,0"      )
    lutItem( "dbmin:1"      ,    "-,-,2,1,2,0"      )
    lutItem( "dbmin:2"      ,    "-,4,6,6,-,0"      )
    lutItem( "dbsus2"       ,    "-,-,6,6,4,4"      )
    lutItem( "dbsus4/bb"    ,    "-,-,4,3,2,4"      )
    lutItem( "ddim/b"       ,    "-,2,0,1,0,1"      )
    lutItem( "ddim/b:1"     ,    "-,-,0,1,0,1"      )
    lutItem( "ddim/b:2"     ,    "-,-,3,4,3,4"      )
    lutItem( "ddim/bb"      ,    "-,1,3,1,3,1"      )
    lutItem( "ddim/bb:1"    ,    "-,-,3,3,3,4"      )
    lutItem( "ddim/c"       ,    "-,-,0,1,1,1"      )
    lutItem( "ddimin7"      ,    "-,2,0,1,0,1"      )
    lutItem( "ddimin7:1"    ,    "-,-,0,1,0,1"      )
    lutItem( "ddimin7:2"    ,    "-,-,3,4,3,4"      )
    lutItem( "dm6"          ,    "1,2,3,2,3,1"      )
    lutItem( "dm6:1"        ,    "-,2,0,2,0,1"      )
    lutItem( "dm6:2"        ,    "-,-,0,2,0,1"      )
    lutItem( "dmaj"         ,    "-,5,4,2,3,2"      )
    lutItem( "dmaj7"        ,    "-,-,0,14,14,14"   )
    lutItem( "dmaj7:1"      ,    "-,-,0,2,2,2"      )
    lutItem( "dmaj:1"       ,    "-,9,7,7,-,2"      )
    lutItem( "dmaj:2"       ,    "2,0,0,2,3,2"      )
    lutItem( "dmaj:3"       ,    "-,0,0,2,3,2"      )
    lutItem( "dmaj:4"       ,    "-,0,4,2,3,2"      )
    lutItem( "dmaj:5"       ,    "-,-,0,2,3,2"      )
    lutItem( "dmaj:6"       ,    "-,-,0,7,7,5"      )
    lutItem( "dmin"         ,    "-,0,0,2,3,1"      )
    lutItem( "dmin/b"       ,    "1,2,3,2,3,1"      )
    lutItem( "dmin/b:1"     ,    "-,2,0,2,0,1"      )
    lutItem( "dmin/b:2"     ,    "-,-,0,2,0,1"      )
    lutItem( "dmin/bb"      ,    "1,1,3,2,3,1"      )
    lutItem( "dmin/c"       ,    "-,5,7,5,6,5"      )
    lutItem( "dmin/c:1"     ,    "-,-,0,2,1,1"      )
    lutItem( "dmin/c:2"     ,    "-,-,0,5,6,5"      )
    lutItem( "dmin/db"      ,    "-,-,0,2,2,1"      )
    lutItem( "dmin/e"       ,    "-,-,7,7,6,0"      )
    lutItem( "dmin/maj7"    ,    "-,-,0,2,2,1"      )
    lutItem( "dmin7"        ,    "-,5,7,5,6,5"      )
    lutItem( "dmin7/add11"  ,    "3,-,0,2,1,1"      )
    lutItem( "dmin7:1"      ,    "-,-,0,2,1,1"      )
    lutItem( "dmin7:2"      ,    "-,-,0,5,6,5"      )
    lutItem( "dmin7{b5}"    ,    "-,-,0,1,1,1"      )
    lutItem( "dsus"         ,    "5,-,0,0,3,5"      )
    lutItem( "dsus2"        ,    "5,5,7,7,-,0"      )
    lutItem( "dsus2/ab"     ,    "4,-,0,2,3,0"      )
    lutItem( "dsus2/b"      ,    "0,2,0,2,0,0"      )
    lutItem( "dsus2/b:1"    ,    "-,2,0,2,3,0"      )
    lutItem( "dsus2/bb"     ,    "0,1,-,2,3,0"      )
    lutItem( "dsus2/c"      ,    "-,-,0,2,1,0"      )
    lutItem( "dsus2/c:1"    ,    "-,-,0,5,5,5"      )
    lutItem( "dsus2/db"     ,    "-,0,0,2,2,0"      )
    lutItem( "dsus2/db:1"   ,    "-,-,0,2,2,0"      )
    lutItem( "dsus2/db:2"   ,    "-,-,0,6,5,5"      )
    lutItem( "dsus2/db:3"   ,    "-,-,0,9,10,9"     )
    lutItem( "dsus2/f"      ,    "-,-,7,7,6,0"      )
    lutItem( "dsus2/g"      ,    "-,0,2,0,3,0"      )
    lutItem( "dsus2/g:1"    ,    "-,0,2,0,3,3"      )
    lutItem( "dsus2/g:2"    ,    "-,0,2,2,3,3"      )
    lutItem( "dsus2/g:3"    ,    "5,-,0,0,3,0"      )
    lutItem( "dsus2/g:4"    ,    "-,0,0,0,-,0"      )
    lutItem( "dsus2/gb"     ,    "0,0,0,2,3,2"      )
    lutItem( "dsus2/gb:1"   ,    "0,0,4,2,3,0"      )
    lutItem( "dsus2/gb:2"   ,    "2,-,0,2,3,0"      )
    lutItem( "dsus2/gb:3"   ,    "-,0,2,2,3,2"      )
    lutItem( "dsus2/gb:4"   ,    "-,-,2,2,3,2"      )
    lutItem( "dsus2/gb:5"   ,    "-,5,4,2,3,0"      )
    lutItem( "dsus2/gb:6"   ,    "-,9,7,7,-,0"      )
    lutItem( "dsus2:1"      ,    "-,0,0,2,3,0"      )
    lutItem( "dsus2:2"      ,    "0,0,2,2,3,0"      )
    lutItem( "dsus2:3"      ,    "-,0,2,2,3,0"      )
    lutItem( "dsus2:4"      ,    "-,-,0,2,3,0"      )
    lutItem( "dsus4/b"      ,    "3,0,0,0,0,3"      )
    lutItem( "dsus4/b:1"    ,    "3,2,0,2,0,3"      )
    lutItem( "dsus4/c"      ,    "-,5,7,5,8,3"      )
    lutItem( "dsus4/c:1"    ,    "-,-,0,2,1,3"      )
    lutItem( "dsus4/e"      ,    "-,0,2,0,3,0"      )
    lutItem( "dsus4/e:1"    ,    "-,0,2,0,3,3"      )
    lutItem( "dsus4/e:2"    ,    "-,0,2,2,3,3"      )
    lutItem( "dsus4/e:3"    ,    "5,-,0,0,3,0"      )
    lutItem( "dsus4/e:4"    ,    "-,0,0,0,-,0"      )
    lutItem( "dsus4/gb"     ,    "5,-,4,0,3,5"      )
    lutItem( "dsus4/gb:1"   ,    "3,-,0,2,3,2"      )
    lutItem( "dsus:1"       ,    "3,0,0,0,3,3"      )
    lutItem( "dsus:2"       ,    "-,0,0,0,3,3"      )
    lutItem( "dsus:3"       ,    "-,-,0,2,3,3"      )
    lutItem( "e/a"          ,    "-,0,2,1,0,0"      )
    lutItem( "e/d"          ,    "0,2,0,1,0,0"      )
    lutItem( "e/d:1"        ,    "0,2,2,1,3,0"      )
    lutItem( "e/d:2"        ,    "-,2,0,1,3,0"      )
    lutItem( "e/d:3"        ,    "-,-,0,1,0,0"      )
    lutItem( "e/db"         ,    "0,2,2,1,2,0"      )
    lutItem( "e/db:1"       ,    "-,4,6,4,5,4"      )
    lutItem( "e/eb"         ,    "0,2,1,1,0,0"      )
    lutItem( "e/eb:1"       ,    "0,-,6,4,4,0"      )
    lutItem( "e/eb:2"       ,    "-,-,1,1,0,0"      )
    lutItem( "e/gb"         ,    "0,2,2,1,0,2"      )
    lutItem( "e/gb:1"       ,    "0,-,4,1,0,0"      )
    lutItem( "e/gb:2"       ,    "2,2,2,1,0,0"      )
    lutItem( "e11/b9"       ,    "0,0,3,4,3,4"      )
    lutItem( "e5"           ,    "0,2,-,-,-,0"      )
    lutItem( "e5:1"         ,    "-,7,9,9,-,0"      )
    lutItem( "e6"           ,    "0,2,2,1,2,0"      )
    lutItem( "e6:1"         ,    "-,4,6,4,5,4"      )
    lutItem( "e7"           ,    "0,2,0,1,0,0"      )
    lutItem( "e7/add11"     ,    "-,0,0,1,0,0"      )
    lutItem( "e7/b9{b5}"    ,    "0,1,3,1,3,1"      )
    lutItem( "e7:1"         ,    "0,2,2,1,3,0"      )
    lutItem( "e7:2"         ,    "-,2,0,1,3,0"      )
    lutItem( "e7:3"         ,    "-,-,0,1,0,0"      )
    lutItem( "e7sus4"       ,    "0,2,0,2,0,0"      )
    lutItem( "e9"           ,    "0,2,0,1,0,2"      )
    lutItem( "e9:1"         ,    "2,2,0,1,0,0"      )
    lutItem( "eadd9"        ,    "0,2,2,1,0,2"      )
    lutItem( "eadd9:1"      ,    "0,-,4,1,0,0"      )
    lutItem( "eadd9:2"      ,    "2,2,2,1,0,0"      )
    lutItem( "eaug"         ,    "-,3,2,1,1,0"      )
    lutItem( "eb/c"         ,    "-,3,5,3,4,3"      )
    lutItem( "eb/d"         ,    "-,6,8,7,8,6"      )
    lutItem( "eb/db"        ,    "-,1,1,3,2,3"      )
    lutItem( "eb/db:1"      ,    "-,6,8,6,8,6"      )
    lutItem( "eb/db:2"      ,    "-,-,1,3,2,3"      )
    lutItem( "eb/e"         ,    "-,-,5,3,4,0"      )
    lutItem( "eb5"          ,    "-,6,8,8,-,6"      )
    lutItem( "eb6"          ,    "-,3,5,3,4,3"      )
    lutItem( "eb7"          ,    "-,1,1,3,2,3"      )
    lutItem( "eb7:1"        ,    "-,6,8,6,8,6"      )
    lutItem( "eb7:2"        ,    "-,-,1,3,2,3"      )
    lutItem( "ebaug"        ,    "3,2,1,0,0,3"      )
    lutItem( "ebaug/e"      ,    "3,-,1,0,0,0"      )
    lutItem( "ebaug/e:1"    ,    "-,-,1,0,0,0"      )
    lutItem( "ebaug:1"      ,    "3,-,1,0,0,3"      )
    lutItem( "ebdim/b"      ,    "2,-,1,2,0,2"      )
    lutItem( "ebdim/b:1"    ,    "-,0,1,2,0,2"      )
    lutItem( "ebdim/b:2"    ,    "-,2,1,2,0,2"      )
    lutItem( "ebdim/b:3"    ,    "-,2,4,2,4,2"      )
    lutItem( "ebdim/c"      ,    "-,-,1,2,1,2"      )
    lutItem( "ebdimin7"     ,    "-,-,1,2,1,2"      )
    lutItem( "ebmaj"        ,    "-,1,1,3,4,3"      )
    lutItem( "ebmaj7"       ,    "-,6,8,7,8,6"      )
    lutItem( "ebmaj:1"      ,    "-,-,1,3,4,3"      )
    lutItem( "ebmaj:2"      ,    "-,-,5,3,4,3"      )
    lutItem( "ebmin"        ,    "-,-,4,3,4,2"      )
    lutItem( "ebmin/db"     ,    "-,-,1,3,2,2"      )
    lutItem( "ebmin7"       ,    "-,-,1,3,2,2"      )
    lutItem( "ebsus2/ab"    ,    "-,1,3,1,4,1"      )
    lutItem( "ebsus4/f"     ,    "-,1,3,1,4,1"      )
    lutItem( "edim/c"       ,    "-,3,5,3,5,3"      )
    lutItem( "edim/d"       ,    "3,-,0,3,3,0"      )
    lutItem( "edim/db"      ,    "-,1,2,0,2,0"      )
    lutItem( "edim/db:1"    ,    "-,-,2,3,2,3"      )
    lutItem( "edim/eb"      ,    "-,-,5,3,4,0"      )
    lutItem( "edimin7"      ,    "-,1,2,0,2,0"      )
    lutItem( "edimin7:1"    ,    "-,-,2,3,2,3"      )
    lutItem( "em6"          ,    "0,2,2,0,2,0"      )
    lutItem( "em9"          ,    "0,2,0,0,0,2"      )
    lutItem( "em9:1"        ,    "0,2,0,0,3,2"      )
    lutItem( "em9:2"        ,    "2,2,0,0,0,0"      )
    lutItem( "emaj"         ,    "0,2,2,1,0,0"      )
    lutItem( "emaj7"        ,    "0,2,1,1,0,0"      )
    lutItem( "emaj7:1"      ,    "0,-,6,4,4,0"      )
    lutItem( "emaj7:2"      ,    "-,-,1,1,0,0"      )
    lutItem( "emaj9"        ,    "0,2,1,1,0,2"      )
    lutItem( "emaj9:1"      ,    "4,-,4,4,4,0"      )
    lutItem( "emaj:1"       ,    "-,7,6,4,5,0"      )
    lutItem( "emin"         ,    "0,2,2,0,0,0"      )
    lutItem( "emin/a"       ,    "3,-,2,2,0,0"      )
    lutItem( "emin/a:1"     ,    "-,0,2,0,0,0"      )
    lutItem( "emin/a:2"     ,    "-,0,5,4,5,0"      )
    lutItem( "emin/c"       ,    "0,3,2,0,0,0"      )
    lutItem( "emin/c:1"     ,    "-,2,2,0,1,0"      )
    lutItem( "emin/c:2"     ,    "-,3,5,4,5,3"      )
    lutItem( "emin/d"       ,    "0,2,0,0,0,0"      )
    lutItem( "emin/d:1"     ,    "0,2,0,0,3,0"      )
    lutItem( "emin/d:2"     ,    "0,2,2,0,3,0"      )
    lutItem( "emin/d:3"     ,    "0,2,2,0,3,3"      )
    lutItem( "emin/d:4"     ,    "-,-,0,12,12,12"   )
    lutItem( "emin/d:5"     ,    "-,-,0,9,8,7"      )
    lutItem( "emin/d:6"     ,    "-,-,2,4,3,3"      )
    lutItem( "emin/d:7"     ,    "0,-,0,0,0,0"      )
    lutItem( "emin/d:8"     ,    "-,10,12,12,12,0"  )
    lutItem( "emin/db"      ,    "0,2,2,0,2,0"      )
    lutItem( "emin/eb"      ,    "3,-,1,0,0,0"      )
    lutItem( "emin/eb:1"    ,    "-,-,1,0,0,0"      )
    lutItem( "emin/gb"      ,    "0,2,2,0,0,2"      )
    lutItem( "emin/gb:1"    ,    "0,2,4,0,0,0"      )
    lutItem( "emin/gb:2"    ,    "0,-,4,0,0,0"      )
    lutItem( "emin/gb:3"    ,    "2,2,2,0,0,0"      )
    lutItem( "emin/maj7"    ,    "3,-,1,0,0,0"      )
    lutItem( "emin/maj7:1"  ,    "-,-,1,0,0,0"      )
    lutItem( "emin/maj9"    ,    "0,6,4,0,0,0"      )
    lutItem( "emin7"        ,    "0,2,0,0,0,0"      )
    lutItem( "emin7/add11"  ,    "0,0,0,0,0,0"      )
    lutItem( "emin7/add11:1",    "0,0,0,0,0,3"      )
    lutItem( "emin7/add11:2",    "3,-,0,2,0,0"      )
    lutItem( "emin7:1"      ,    "0,2,0,0,3,0"      )
    lutItem( "emin7:2"      ,    "0,2,2,0,3,0"      )
    lutItem( "emin7:3"      ,    "0,2,2,0,3,3"      )
    lutItem( "emin7:4"      ,    "-,-,0,0,0,0"      )
    lutItem( "emin7:5"      ,    "-,-,0,12,12,12"   )
    lutItem( "emin7:6"      ,    "-,-,0,9,8,7"      )
    lutItem( "emin7:7"      ,    "-,-,2,4,3,3"      )
    lutItem( "emin7:8"      ,    "0,-,0,0,0,0"      )
    lutItem( "emin7:9"      ,    "-,10,12,12,12,0"  )
    lutItem( "emin7{b5}"    ,    "3,-,0,3,3,0"      )
    lutItem( "emin:1"       ,    "3,-,2,0,0,0"      )
    lutItem( "emin:2"       ,    "-,2,5,-,-,0"      )
    lutItem( "esus"         ,    "0,0,2,2,0,0"      )
    lutItem( "esus2"        ,    "7,9,9,-,-,0"      )
    lutItem( "esus2/a"      ,    "-,0,4,4,0,0"      )
    lutItem( "esus2/a:1"    ,    "-,2,4,2,5,2"      )
    lutItem( "esus2/ab"     ,    "0,2,2,1,0,2"      )
    lutItem( "esus2/ab:1"   ,    "0,-,4,1,0,0"      )
    lutItem( "esus2/ab:2"   ,    "2,2,2,1,0,0"      )
    lutItem( "esus2/db"     ,    "-,4,4,4,-,0"      )
    lutItem( "esus2/eb"     ,    "-,2,2,4,4,2"      )
    lutItem( "esus2/eb:1"   ,    "-,-,4,4,4,0"      )
    lutItem( "esus2/g"      ,    "0,2,2,0,0,2"      )
    lutItem( "esus2/g:1"    ,    "0,2,4,0,0,0"      )
    lutItem( "esus2/g:2"    ,    "0,-,4,0,0,0"      )
    lutItem( "esus2/g:3"    ,    "2,2,2,0,0,0"      )
    lutItem( "esus2:1"      ,    "-,2,4,4,-,0"      )
    lutItem( "esus4/ab"     ,    "-,0,2,1,0,0"      )
    lutItem( "esus4/c"      ,    "0,0,7,5,0,0"      )
    lutItem( "esus4/c:1"    ,    "-,3,2,2,0,0"      )
    lutItem( "esus4/d"      ,    "0,2,0,2,0,0"      )
    lutItem( "esus4/d:1"    ,    "-,2,0,2,3,0"      )
    lutItem( "esus4/db"     ,    "0,0,2,4,2,0"      )
    lutItem( "esus4/db:1"   ,    "-,0,7,6,0,0"      )
    lutItem( "esus4/eb"     ,    "-,2,1,2,0,0"      )
    lutItem( "esus4/f"      ,    "0,0,3,2,0,0"      )
    lutItem( "esus4/g"      ,    "3,-,2,2,0,0"      )
    lutItem( "esus4/g:1"    ,    "-,0,2,0,0,0"      )
    lutItem( "esus4/g:2"    ,    "-,0,5,4,5,0"      )
    lutItem( "esus4/gb"     ,    "-,0,4,4,0,0"      )
    lutItem( "esus4/gb:1"   ,    "-,2,4,2,5,2"      )
    lutItem( "esus:1"       ,    "0,0,2,4,0,0"      )
    lutItem( "esus:2"       ,    "0,2,2,2,0,0"      )
    lutItem( "esus:3"       ,    "-,0,2,2,0,0"      )
    lutItem( "esus:4"       ,    "-,-,2,2,0,0"      )
    lutItem( "f/d"          ,    "-,5,7,5,6,5"      )
    lutItem( "f/d:1"        ,    "-,-,0,2,1,1"      )
    lutItem( "f/d:2"        ,    "-,-,0,5,6,5"      )
    lutItem( "f/e"          ,    "0,0,3,2,1,0"      )
    lutItem( "f/e:1"        ,    "1,3,3,2,1,0"      )
    lutItem( "f/e:2"        ,    "1,-,2,2,1,0"      )
    lutItem( "f/e:3"        ,    "-,-,2,2,1,1"      )
    lutItem( "f/e:4"        ,    "-,-,3,2,1,0"      )
    lutItem( "f/eb"         ,    "-,-,1,2,1,1"      )
    lutItem( "f/eb:1"       ,    "-,-,3,5,4,5"      )
    lutItem( "f/g"          ,    "3,-,3,2,1,1"      )
    lutItem( "f/g:1"        ,    "-,-,3,2,1,3"      )
    lutItem( "f5"           ,    "1,3,3,-,-,1"      )
    lutItem( "f5:1"         ,    "-,8,10,-,-,1"     )
    lutItem( "f6"           ,    "-,5,7,5,6,5"      )
    lutItem( "f6/add9"      ,    "3,-,0,2,1,1"      )
    lutItem( "f6:1"         ,    "-,-,0,2,1,1"      )
    lutItem( "f6:2"         ,    "-,-,0,5,6,5"      )
    lutItem( "f7"           ,    "-,-,1,2,1,1"      )
    lutItem( "f7:1"         ,    "-,-,3,5,4,5"      )
    lutItem( "fadd9"        ,    "3,-,3,2,1,1"      )
    lutItem( "fadd9:1"      ,    "-,-,3,2,1,3"      )
    lutItem( "faug"         ,    "-,0,3,2,2,1"      )
    lutItem( "faug/d"       ,    "-,-,0,2,2,1"      )
    lutItem( "faug/g"       ,    "1,0,3,0,2,1"      )
    lutItem( "faug:1"       ,    "-,0,-,2,2,1"      )
    lutItem( "fdim/d"       ,    "-,2,0,1,0,1"      )
    lutItem( "fdim/d:1"     ,    "-,-,0,1,0,1"      )
    lutItem( "fdim/d:2"     ,    "-,-,3,4,3,4"      )
    lutItem( "fdim/db"      ,    "-,4,3,4,0,4"      )
    lutItem( "fdimin7"      ,    "-,2,0,1,0,1"      )
    lutItem( "fdimin7:1"    ,    "-,-,0,1,0,1"      )
    lutItem( "fdimin7:2"    ,    "-,-,3,4,3,4"      )
    lutItem( "fm6"          ,    "-,-,0,1,1,1"      )
    lutItem( "fmaj"         ,    "1,3,3,2,1,1"      )
    lutItem( "fmaj7"        ,    "0,0,3,2,1,0"      )
    lutItem( "fmaj7/#11"    ,    "0,2,3,2,1,0"      )
    lutItem( "fmaj7/#11:1"  ,    "1,3,3,2,0,0"      )
    lutItem( "fmaj7:1"      ,    "1,3,3,2,1,0"      )
    lutItem( "fmaj7:2"      ,    "1,-,2,2,1,0"      )
    lutItem( "fmaj7:3"      ,    "-,-,2,2,1,1"      )
    lutItem( "fmaj7:4"      ,    "-,-,3,2,1,0"      )
    lutItem( "fmaj9"        ,    "0,0,3,0,1,3"      )
    lutItem( "fmaj:1"       ,    "-,0,3,2,1,1"      )
    lutItem( "fmaj:2"       ,    "-,3,3,2,1,1"      )
    lutItem( "fmaj:3"       ,    "-,-,3,2,1,1"      )
    lutItem( "fmin"         ,    "-,3,3,1,1,1"      )
    lutItem( "fmin/d"       ,    "-,-,0,1,1,1"      )
    lutItem( "fmin/db"      ,    "-,3,3,1,2,1"      )
    lutItem( "fmin/db:1"    ,    "-,4,6,5,6,4"      )
    lutItem( "fmin/eb"      ,    "-,8,10,8,9,8"     )
    lutItem( "fmin/eb:1"    ,    "-,-,1,1,1,1"      )
    lutItem( "fmin7"        ,    "-,8,10,8,9,8"     )
    lutItem( "fmin7:1"      ,    "-,-,1,1,1,1"      )
    lutItem( "fmin:1"       ,    "-,-,3,1,1,1"      )
    lutItem( "fsus"         ,    "-,-,3,3,1,1"      )
    lutItem( "fsus2"        ,    "-,3,3,0,1,1"      )
    lutItem( "fsus2/a"      ,    "3,-,3,2,1,1"      )
    lutItem( "fsus2/a:1"    ,    "-,-,3,2,1,3"      )
    lutItem( "fsus2/b"      ,    "-,3,3,0,0,3"      )
    lutItem( "fsus2/bb"     ,    "-,3,5,3,6,3"      )
    lutItem( "fsus2/d"      ,    "3,3,0,0,1,1"      )
    lutItem( "fsus2/e"      ,    "-,3,3,0,1,0"      )
    lutItem( "fsus2/e:1"    ,    "-,-,3,0,1,0"      )
    lutItem( "fsus2:1"      ,    "-,-,3,0,1,1"      )
    lutItem( "fsus4/g"      ,    "-,3,5,3,6,3"      )
    lutItem( "g/a"          ,    "3,0,0,0,0,3"      )
    lutItem( "g/a:1"        ,    "3,2,0,2,0,3"      )
    lutItem( "g/c"          ,    "3,3,0,0,0,3"      )
    lutItem( "g/c:1"        ,    "-,3,0,0,0,3"      )
    lutItem( "g/e"          ,    "0,2,0,0,0,0"      )
    lutItem( "g/e:1"        ,    "0,2,0,0,3,0"      )
    lutItem( "g/e:2"        ,    "0,2,2,0,3,0"      )
    lutItem( "g/e:3"        ,    "0,2,2,0,3,3"      )
    lutItem( "g/e:4"        ,    "-,-,0,12,12,12"   )
    lutItem( "g/e:5"        ,    "-,-,0,9,8,7"      )
    lutItem( "g/e:6"        ,    "-,-,2,4,3,3"      )
    lutItem( "g/e:7"        ,    "0,-,0,0,0,0"      )
    lutItem( "g/e:8"        ,    "-,10,12,12,12,0"  )
    lutItem( "g/f"          ,    "1,-,0,0,0,3"      )
    lutItem( "g/f:1"        ,    "3,2,0,0,0,1"      )
    lutItem( "g/f:2"        ,    "-,-,0,0,0,1"      )
    lutItem( "g/gb"         ,    "2,2,0,0,0,3"      )
    lutItem( "g/gb:1"       ,    "2,2,0,0,3,3"      )
    lutItem( "g/gb:2"       ,    "3,2,0,0,0,2"      )
    lutItem( "g/gb:3"       ,    "-,-,4,4,3,3"      )
    lutItem( "g5"           ,    "3,5,5,-,-,3"      )
    lutItem( "g5:1"         ,    "3,-,0,0,3,3"      )
    lutItem( "g6"           ,    "0,2,0,0,0,0"      )
    lutItem( "g6/add9"      ,    "0,0,0,0,0,0"      )
    lutItem( "g6/add9:1"    ,    "0,0,0,0,0,3"      )
    lutItem( "g6/add9:2"    ,    "3,-,0,2,0,0"      )
    lutItem( "g6:1"         ,    "0,2,0,0,3,0"      )
    lutItem( "g6:2"         ,    "0,2,2,0,3,0"      )
    lutItem( "g6:3"         ,    "0,2,2,0,3,3"      )
    lutItem( "g6:4"         ,    "-,-,0,12,12,12"   )
    lutItem( "g6:5"         ,    "-,-,0,9,8,7"      )
    lutItem( "g6:6"         ,    "-,-,2,4,3,3"      )
    lutItem( "g6:7"         ,    "0,-,0,0,0,0"      )
    lutItem( "g6:8"         ,    "-,10,12,12,12,0"  )
    lutItem( "g7"           ,    "1,-,0,0,0,3"      )
    lutItem( "g7/add11"     ,    "-,3,0,0,0,1"      )
    lutItem( "g7:1"         ,    "3,2,0,0,0,1"      )
    lutItem( "g7:2"         ,    "-,-,0,0,0,1"      )
    lutItem( "g7sus4"       ,    "3,3,0,0,1,1"      )
    lutItem( "g9"           ,    "-,0,0,0,0,1"      )
    lutItem( "g9:1"         ,    "-,2,3,2,3,3"      )
    lutItem( "gadd9"        ,    "3,0,0,0,0,3"      )
    lutItem( "gadd9:1"      ,    "3,2,0,2,0,3"      )
    lutItem( "gaug"         ,    "3,2,1,0,0,3"      )
    lutItem( "gaug/e"       ,    "3,-,1,0,0,0"      )
    lutItem( "gaug/e:1"     ,    "-,-,1,0,0,0"      )
    lutItem( "gaug:1"       ,    "3,-,1,0,0,3"      )
    lutItem( "gb/ab"        ,    "-,-,4,3,2,4"      )
    lutItem( "gb/e"         ,    "2,4,2,3,2,2"      )
    lutItem( "gb/e:1"       ,    "-,-,4,3,2,0"      )
    lutItem( "gb/eb"        ,    "-,-,1,3,2,2"      )
    lutItem( "gb/f"         ,    "-,-,3,3,2,2"      )
    lutItem( "gb6"          ,    "-,-,1,3,2,2"      )
    lutItem( "gb7"          ,    "2,4,2,3,2,2"      )
    lutItem( "gb7/#9"       ,    "-,0,4,3,2,0"      )
    lutItem( "gb7:1"        ,    "-,-,4,3,2,0"      )
    lutItem( "gb7sus4"      ,    "-,4,4,4,-,0"      )
    lutItem( "gb7{#5}"      ,    "2,-,4,3,3,0"      )
    lutItem( "gbadd9"       ,    "-,-,4,3,2,4"      )
    lutItem( "gbaug"        ,    "-,-,0,3,3,2"      )
    lutItem( "gbaug/e"      ,    "2,-,4,3,3,0"      )
    lutItem( "gbdim/d"      ,    "-,5,7,5,7,2"      )
    lutItem( "gbdim/d:1"    ,    "-,0,0,2,1,2"      )
    lutItem( "gbdim/d:2"    ,    "-,3,-,2,3,2"      )
    lutItem( "gbdim/d:3"    ,    "-,5,7,5,7,5"      )
    lutItem( "gbdim/e"      ,    "-,0,2,2,1,2"      )
    lutItem( "gbdim/e:1"    ,    "-,-,2,2,1,2"      )
    lutItem( "gbdim/eb"     ,    "-,-,1,2,1,2"      )
    lutItem( "gbdimin7"     ,    "-,-,1,2,1,2"      )
    lutItem( "gbmaj"        ,     "2,4,4,3,2,2"     )
    lutItem( "gbmaj7"       ,     "-,-,3,3,2,2"     )
    lutItem( "gbmaj:1"      ,     "-,4,4,3,2,2"     )
    lutItem( "gbmaj:2"      ,     "-,-,4,3,2,2"     )
    lutItem( "gbmin"        ,    "2,4,4,2,2,2"      )
    lutItem( "gbmin/d"      ,    "-,-,0,2,2,2"      )
    lutItem( "gbmin/d:1"    ,    "-,-,0,14,14,14"   )
    lutItem( "gbmin/e"      ,    "0,0,2,2,2,2"      )
    lutItem( "gbmin/e:1"    ,    "0,-,4,2,2,0"      )
    lutItem( "gbmin/e:2"    ,    "2,-,2,2,2,0"      )
    lutItem( "gbmin/e:3"    ,     "-,0,4,2,2,0"     )
    lutItem( "gbmin/e:4"    ,     "-,-,2,2,2,2"     )
    lutItem( "gbmin7"       ,     "0,0,2,2,2,2"     )
    lutItem( "gbmin7/b9"    ,     "0,0,2,0,2,2"     )
    lutItem( "gbmin7:1"     ,     "0,-,4,2,2,0"     )
    lutItem( "gbmin7:2"     ,     "2,-,2,2,2,0"     )
    lutItem( "gbmin7:3"     ,     "-,0,4,2,2,0"     )
    lutItem( "gbmin7:4"     ,     "-,-,2,2,2,2"     )
    lutItem( "gbmin7{b5}"   ,     "-,0,2,2,1,2"     )
    lutItem( "gbmin7{b5}:1" ,     "-,-,2,2,1,2"     )
    lutItem( "gbmin:1"      ,    "-,4,4,2,2,2"      )
    lutItem( "gbmin:2"      ,    "-,-,4,2,2,2"      )
    lutItem( "gbsus"        ,     "-,4,4,4,2,2"     )
    lutItem( "gbsus2/bb"    ,     "-,-,4,3,2,4"     )
    lutItem( "gbsus4/e"     ,     "-,4,4,4,-,0"     )
    lutItem( "gdim/e"       ,    "-,1,2,0,2,0"      )
    lutItem( "gdim/e:1"     ,    "-,-,2,3,2,3"      )
    lutItem( "gdim/eb"      ,    "-,1,1,3,2,3"      )
    lutItem( "gdim/eb:1"    ,    "-,6,8,6,8,6"      )
    lutItem( "gdim/eb:2"    ,    "-,-,1,3,2,3"      )
    lutItem( "gdimin7"      ,    "-,1,2,0,2,0"      )
    lutItem( "gdimin7:1"    ,    "-,-,2,3,2,3"      )
    lutItem( "gm13"         ,    "0,0,3,3,3,3"      )
    lutItem( "gm6"          ,    "3,-,0,3,3,0"      )
    lutItem( "gm9"          ,    "3,5,3,3,3,5"      )
    lutItem( "gmaj"         ,     "3,2,0,0,0,3"     )
    lutItem( "gmaj7"        ,    "2,2,0,0,0,3"      )
    lutItem( "gmaj7:1"      ,    "2,2,0,0,3,3"      )
    lutItem( "gmaj7:2"      ,    "3,2,0,0,0,2"      )
    lutItem( "gmaj7:3"      ,    "-,-,4,4,3,3"      )
    lutItem( "gmaj:1"       ,     "3,2,0,0,3,3"     )
    lutItem( "gmaj:2"       ,     "3,5,5,4,3,3"     )
    lutItem( "gmaj:3"       ,     "3,-,0,0,0,3"     )
    lutItem( "gmaj:4"       ,     "-,5,5,4,3,3"     )
    lutItem( "gmaj:5"       ,     "-,-,0,4,3,3"     )
    lutItem( "gmaj:6"       ,     "-,-,0,7,8,7"     )
    lutItem( "gmaj:7"       ,   "-,10,12,12,12,10"  )
    lutItem( "gmin"         ,    "3,5,5,3,3,3"      )
    lutItem( "gmin/e"       ,    "3,-,0,3,3,0"      )
    lutItem( "gmin/eb"      ,    "-,6,8,7,8,6"      )
    lutItem( "gmin/f"       ,    "3,5,3,3,3,3"      )
    lutItem( "gmin/f:1"     ,    "-,-,3,3,3,3"      )
    lutItem( "gmin7"        ,    "3,5,3,3,3,3"      )
    lutItem( "gmin7/add11"  ,    "-,3,3,3,3,3"      )
    lutItem( "gmin7:1"      ,    "-,-,3,3,3,3"      )
    lutItem( "gmin:1"       ,    "-,-,0,3,3,3"      )
    lutItem( "gsus"         ,    "-,10,12,12,13,3"  )
    lutItem( "gsus2"        ,    "5,-,0,0,3,5"      )
    lutItem( "gsus2/b"      ,    "3,0,0,0,0,3"      )
    lutItem( "gsus2/b:1"    ,    "3,2,0,2,0,3"      )
    lutItem( "gsus2/c"      ,    "-,5,7,5,8,3"      )
    lutItem( "gsus2/c:1"    ,    "-,-,0,2,1,3"      )
    lutItem( "gsus2/e"      ,    "-,0,2,0,3,0"      )
    lutItem( "gsus2/e:1"    ,    "-,0,2,0,3,3"      )
    lutItem( "gsus2/e:2"    ,    "-,0,2,2,3,3"      )
    lutItem( "gsus2/e:3"    ,    "5,0,0,0,3,0"      )
    lutItem( "gsus2/gb"     ,    "5,-,4,0,3,5"      )
    lutItem( "gsus2/gb:1"   ,    "3,-,0,2,3,2"      )
    lutItem( "gsus2:1"      ,    "3,0,0,0,3,3"      )
    lutItem( "gsus2:2"      ,    "-,0,0,0,3,3"      )
    lutItem( "gsus2:3"      ,    "-,-,0,2,3,3"      )
    lutItem( "gsus4/a"      ,    "-,5,7,5,8,3"      )
    lutItem( "gsus4/a:1"    ,    "-,-,0,2,1,3"      )
    lutItem( "gsus4/b"      ,    "3,3,0,0,0,3"      )
    lutItem( "gsus4/b:1"    ,    "-,3,0,0,0,3"      )
    lutItem( "gsus4/e"      ,    "3,-,0,0,1,0"      )
    lutItem( "gsus4/e:1"    ,    "-,3,0,0,1,0"      )
    lutItem( "gsus4/e:2"    ,    "-,3,2,0,3,0"      )
    lutItem( "gsus4/e:3"    ,    "-,3,2,0,3,3"      )
    lutItem( "gsus4/e:4"    ,    "-,-,0,0,1,0"      )
    lutItem( "gsus4/e:5"    ,    "-,-,0,5,5,3"      )
    lutItem( "gsus4/e:6"    ,    "-,5,5,5,-,0"      )
    lutItem( "gsus4/e:7"    ,    "-,10,12,12,13,0"  )
    lutItem( "gsus4/f"      ,    "3,3,0,0,1,1"      )
    lutItem( "gsus:1"       ,    "-,3,0,0,3,3"      )
    lutItem( "gsus:2"       ,    "-,3,5,5,3,3"      )
    lutItem( "gsus:3"       ,    "-,5,5,5,3,3"      )
lutEnd(gchords)
                                        
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
static int globalkey      = DEFAULT_VAL;
static int globaltranspose= DEFAULT_VAL;
static int globalstress   = DEFAULT_VAL;
static int globalsoft     = DEFAULT_VAL;

static tbl_t macros  = NULL;
static chs_t tmptext = NULL;
static chs_t rpl     = NULL;
static vec_t args    = NULL;
static vec_t tracks  = NULL;

#define MAX_TUNING 16

#define DO_CLEANUP 0

void usage()
{
  fprintf(stderr,"Usage: mpad filename\n" );
  exit(1);
}

void merr(char *msg, char *context)
{
  if (context && *context)
    fprintf(stderr,"<<...%.*s...>>\n",40,context);
  fprintf(stderr,"ERR: %s\n",msg);
  exit(1);
}

int keybyname(char *name, int len, int majmin)
{
  char buf[32];
  buf[0] = majmin;
  if (len>30) len=30;
  strncpy(buf+1,name,len);
  buf[len+1] = '\0';
  return lutGetSN(keys,buf,0);
}

int ctrlbyname(char *name, int len)
{
  char buf[32];
  if (len>30) len=30;
  strncpy(buf,name,len);
  buf[len] = '\0';
  return lutGetSN(instr,buf,0);
}

int instrbyname(char *name, int len)
{
  char buf[32];
  if (len>30) len=30;
  strncpy(buf,name,len);
  buf[len] = '\0';
  return lutGetSN(instr,buf,0);
}

char *gchordbyname(char *note, int acclen, char *type, int typelen)
{
  char buf[32];
  char *s = buf;
  *s++ = *note;
  if (acclen >0) {
    switch (note[1]) {
      case '#' : case '+':
        buf[0]++; if (buf[0] > 'g') buf[0] = 'a';
      case 'b' : case '-': *s++='b'; break;
    }
  }
  if (typelen>20) typelen = 20;
  if (typelen == 0 || *type == ':') {
    strcpy(s,"maj");
    s+=3;
  }
  if (typelen > 0) 
    strncpy(s,type,typelen);

  s[typelen] = '\0';
  
  s = lutGetSS(gchords,buf,NULL);
  //fprintf(stderr,"## %s -> [%s]\n",buf,s);
  return s;  
}

char *chordbyname(char *type, int typelen)
{
  char buf[32];
  char *s = buf;
  
  if (typelen>20) typelen = 20;
  if (typelen == 0 || *type == ':') {
    strcpy(s,"maj");
    s+=3;
  }
  if (typelen > 0) 
    strncpy(s,type,typelen);

  s[typelen] = '\0';
  
  s = lutGetSS(chords,buf,NULL);
  //fprintf(stderr,"## %s -> [%s]\n",buf,s);
  return s;  
}
      
char *notename(int note)
{
  return "c c#d d#e f f#g g#a a#b "+(note % 12) * 2;
}

char noteacc(int note)
{
  return " # #  # # # "[note % 12];
}

char notebase(int note)
{
  return "ccddeffggaab"[note % 12];
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
  int num;

  //fprintf(stderr,"xxx %c %c %d = ",note,acc,octave);
  if (octave > 10) octave = 10;
  num = "\011\013\000\002\004\005\007"[note-'a'] + 12 * octave;
  
  if (acc == '#' || acc == '+') num++;
  else if (acc == 'b' || acc == '-') num--;
  if (num > 127) num -= 12;
  else if (num < 0) num += 12;
  //fprintf(stderr,"%d\n",num);  
  return num;
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
   
   l = pmxLen(capt,1)-2;
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
  blankit(str+pmxStart(ret,0),  pmxLen(ret,0));
  return 0;
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
  int n;
  
  if (pmxLen(capt,1) == 0) return "";
  
  name = str+pmxStart(capt,1);
  c = name[pmxLen(capt,1)]; 
  name[pmxLen(capt,1)] = '\0';
  
  while (*name) { 
    *name = tolower((int)*name);
    name++;    
  }    
  name = str + pmxStart(capt,1);
  
  bd = tblGetSS(macros,name,NULL);
   
  if (!bd) {
    fprintf(stderr,"Unknown macro: '%s'\n",name);
    return "";
  }
  
  if (bd[0] == '@') { /* random macro */
    n = rand() % bd[1];
    //fprintf(stderr,"--- %d %d\n",n,bd[1]);
    bd = bd+2;
   
    while (n-->0)  
      bd += *bd;
  }
  bd++;
  
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
  //fprintf(stderr,"*** %s\n",rpl);
  return rpl;
}

chs_t getrndmacro(char *mtext)
{
  chs_t body = NULL;
  int n = 0;
  int l = 0;
  char *s=NULL;  
  
  //fprintf(stderr,"xx '%s'\n",mtext);
  
  chsCpy(body,"@@");
  
  #define T_MREPLACE     x81
  #define T_MSTRING      x82
  
  pmxScannerBegin(mtext)
                       
    pmxTokSet("&s",pmxTokIGNORE) 
    pmxTokSet("&q",T_MSTRING)
    pmxTokSet("<+S>",T_MREPLACE) 
                        
  pmxScannerSwitch
 
    pmxTokCase(T_MSTRING):
      l = pmxTokLen(0)-2;
      s = pmxTokStart(0)+1;
      goto replace_it;
      
    pmxTokCase(T_MREPLACE):
      l = pmxTokLen(0);
      s = pmxTokStart(0);
     
    replace_it:  
      chsAddChr(body,l+2);
      if (l>0) chsAddStrL(body,s,l);
      chsAddChr(body,'\377');
      n++;
      continue;
      
    pmxTokCase(pmxTokIGNORE):
      continue;

    default: merr("Internal error", pmxTokStart(0));
      break; 
     
  pmxScannerEnd;

  body[1] = n;
  
  for (s=body+2; *s; s++) 
    if (*s == '\377') *s = '\0';
    
  //fprintf(stderr,"++ %s\n",body);
  return body;
}

static int getmacro(char *str, pmx_t ret)
{
  chs_t body = NULL;
  int l = pmxLen(ret,0);
  char *s = str+pmxStart(ret,0);
  char *n = str+pmxStart(ret,2);
      
  str[pmxEnd(ret,2) ]  = '\0';
  str[pmxEnd(ret,3)-1] = '\0';  
  
  if (pmxLen(ret,1) > 0) {
    body = getrndmacro(str + pmxStart(ret,3)+1);
  }
  else {
    chsCpy(body,"$");
    chsAddStrL(body, str+pmxStart(ret,3)+1, pmxLen(ret,3));
  }

  tblSetSH(macros, n, body);
  blankit(s,l);
  
  return 0;
}

static chs_t expand(chs_t text)
{

  srand(time(0));
  
  /* get and expand macros */
  pmxScanStr(text, "&Km(<?$rnd>)$(<+a>)&K(&b())&K(&N)", getmacro);
  chsSubFun(text, 0,"&*$(<*a>)(&B())",submacro);

  /* Multiply */  
  chsSubFun(text,0,"&*(&b())&K*&K(<+d>)&K",mulpar);
  chsSubFun(text,0,"&*(<+! \t*>)&K*&K(<+d>)&K",mulstr);
  
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
  chs_t header = NULL;
  
  #define T_TEMPO       x81
  #define T_RESOLUTION  x82
  #define T_PPQN        x83
  #define T_GDUTY       x84
  #define T_GVELOCITY   x85
  #define T_GLOOSE      x86
  #define T_GVELVAR     x87
  #define T_GGUITON     x88 
  #define T_GKEY        x89 
  #define T_METER       x8A 
  #define T_SMPTE       x8B 
  #define T_GTRANSPOSE  x8D 
  #define T_GSTRESS     x8E
  #define T_GSOFT       x8F   
  
  pmxScannerBegin(text)
                       
    pmxTokSet("tempo&K(<+d>)",T_TEMPO)
    pmxTokSet("smpteoff<?$set>&K(&d)<?=,>(&d)<?=,>(&d)<?=,>(&d)<?=,>(&d)",T_SMPTE)
    pmxTokSet("resolution&K(<+d>)",T_RESOLUTION)
    pmxTokSet("ppqn&K(<+d>)",T_PPQN)
    pmxTokSet("duty&K(<+d>)",T_GDUTY)
    pmxTokSet("velocity&K(<+d>)",T_GVELOCITY)
    pmxTokSet("g<?$lobal>loose&K(<+d>)<?=,>(<*=0-9g>)",T_GLOOSE)
    pmxTokSet("g<?$lobal>velar&K(<+d>)<?=,>(<*=0-9g>)",T_GVELVAR)
    pmxTokSet("g<?$lobal>guit<?$ar>on",T_GGUITON) 
    pmxTokSet("g<?$lobal>meter&K(<+d>)/(<+d>)<?=,>(<*d>)<?=,>(<*d>)",T_METER)
    pmxTokSet("g<?$lobal>key&K(<?=+&-><=0-7>)()&K<?=,>&K(<?$minor$major$min$maj>)",T_GKEY)                   
    pmxTokSet("g<?$lobal>key&K()(<=a-g><?=#b>)&K<?=,>&K(<?$minor$major$min$maj>)",T_GKEY)                   
    pmxTokSet("g<?$lobal>t<?$ranspose>&K(&d)",T_GTRANSPOSE)
    pmxTokSet("g<?$lobal>stress&K(<+d>)",T_GSTRESS)
    pmxTokSet("g<?$lobal>soft&K(<+d>)",T_GSOFT)
    pmxTokSet("&s",pmxTokIGNORE) 
    pmxTokSet("<.>",pmxTokIGNORE) 
                        
  pmxScannerSwitch
 
    pmxTokCase(T_GKEY):
      if (pmxTokLen(1) > 0) { 
        val = atoi(pmxTokStart(1));
        if (pmxTokLen(3) > 0 && pmxTokStart(3)[2] == 'n') {
          val += (val < 0) ? - 100 : 100;
        } 
      }
      else {
        val = 'j';
        if (pmxTokLen(3)>0) val = pmxTokStart(3)[2];
        val = keybyname(pmxTokStart(2), pmxTokLen(2), val);
      }
      globalkey = val;
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GSTRESS):
      if (tempo != DEFAULT_VAL) 
        merr("Stress already specified", pmxTokStart(0));
      globalstress = atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GSOFT):
      if (tempo != DEFAULT_VAL)
        merr("Soft already specified", pmxTokStart(0));
      globalsoft = atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_TEMPO):
      if (tempo != DEFAULT_VAL)
        merr("Tempo already specified", pmxTokStart(0));
      tempo = atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_RESOLUTION):  
      if (ppqn != DEFAULT_VAL) 
        merr("Resolution already specified", pmxTokStart(0));
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
      if (ppqn != DEFAULT_VAL) 
        merr("ppqn already specified", pmxTokStart(0));
      ppqn =  atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GDUTY):        
      if (duty != DEFAULT_VAL) 
        merr("duty already specified", pmxTokStart(0));
      duty =  atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GVELOCITY):    
      if (velocity != DEFAULT_VAL) 
        merr("velocity already specified", pmxTokStart(0));
      velocity =  atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GLOOSE):   
      if (globalloose_w != DEFAULT_VAL) 
        merr("globalloose already specified", pmxTokStart(0));
      globalloose_w = atoi(pmxTokStart(1));
      if (pmxTokLen(2) > 0 && *pmxTokStart(2) != 'g')
        globalloose_q = atoi(pmxTokStart(2));
      else 
        globalloose_q = -1;
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GVELVAR):   
      if (globalvelvar_w != DEFAULT_VAL)
        merr("globalvelvar already specified", pmxTokStart(0));
      globalvelvar_w = atoi(pmxTokStart(1));
      if (pmxTokLen(2) > 0 && *pmxTokStart(2) != 'g')
        globalvelvar_q = atoi(pmxTokStart(2));
      else 
        globalvelvar_q = -1;
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GGUITON):
      if (globalguiton != DEFAULT_VAL) 
        merr("globalguitaron already specified", pmxTokStart(0));
      globalguiton = 1;
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_GTRANSPOSE):
      if (globaltranspose != DEFAULT_VAL) 
        merr("Global transpose already specified", pmxTokStart(0));
      globaltranspose = atoi(pmxTokStart(1));
      blankit(pmxTokStart(0),pmxTokLen(0));
      continue;

    pmxTokCase(T_METER):
      if (globalmeter_n != DEFAULT_VAL) 
        merr("Meter already specified", pmxTokStart(0));
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

    default: merr("Internal error", pmxTokStart(0));
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
  if (globaltranspose== DEFAULT_VAL )  globaltranspose= 0;
  if (globalkey      == DEFAULT_VAL )  globalkey      = 0;
  if (globalstress   == DEFAULT_VAL )  globalstress   = 120;
  if (globalsoft     == DEFAULT_VAL )  globalsoft     = 85;

  chsCpy(header,"00000000 header\n");
  chsAddFmt(header,"00000000 ppqn %d\n",ppqn);
  chsAddFmt(header,"00000000 duty %d\n",duty);
  chsAddFmt(header,"00000000 velocity %d\n", velocity);
  chsAddFmt(header,"00000000 loose %d,%d\n",globalloose_w ,globalloose_q);
  chsAddFmt(header,"00000000 velvar %d,%d\n",globalvelvar_w,globalvelvar_q);
  chsAddFmt(header,"00000000 guiton %d\n",globalguiton);
  chsAddFmt(header,"00000000 transpose %d\n",globaltranspose);
  chsAddFmt(header,"00000000 stress %d\n",globalstress);
  chsAddFmt(header,"00000000 soft %d\n",globalsoft);
  chsAddFmt(header,"00000000 key %d\n",globalkey);
  chsAddFmt(header,"00000000 tempo %d\n", tempo);
  chsAddStr(header,"00000000 end\n");
  
  vecSetH(tracks, 0, header);
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
  static int cur_track = 0;
  int len;
  chs_t trk;
  
  len = pmxLen(capt,2);
  
  if (len >0) {
    if (pmxLen(capt,1)>0) 
      cur_track = 1+atoi(str + pmxStart(capt,1));
    else cur_track++;
     
    trk = vecGetZS(tracks, cur_track, NULL); 
    chsAddChr(trk,' ');
    chsAddStrL(trk, str+pmxStart(capt,2), len);
    vecSetZH(tracks, cur_track, trk); 
    //fprintf(stderr, "**%s\n",trk);  
  }
    
  return 0;
}

chs_t parsetrack(chs_t trk)
{
  chs_t new_trk = NULL;
  
  int cur_duty      = duty;
  int cur_velocity  = velocity;
  int cur_loose_w   = globalloose_w;
  int cur_loose_q   = globalloose_q;
  int cur_velvar_w  = globalvelvar_w;
  int cur_velvar_q  = globalvelvar_q;
  int cur_guiton    = globalguiton;
  int cur_transpose = globaltranspose;
  int cur_stress    = globalstress;
  int cur_soft      = globalsoft;
  int cur_key       = globalkey;

  int   cur_tomson        = 0;
  int   cur_note          = 60;
  short cur_notelen       = 4;
  char  cur_instr         = 0;
  char  cur_ratio_n       = 1;
  char  cur_ratio_d       = 1;
  int   cur_pitch         = 0;
  int   cur_meter_n       = 4;
  int   cur_meter_d       = 4;
 
  unsigned long cur_tick  = 0;
    
  unsigned char cur_channel = 0;
  int   last_len = 0;
  
  char tuning[MAX_TUNING] = {52,57,62,67,71,76,0};
  
  int   d;
  int   n;
  int   o;
  int   k;
  char *t;
  char *s;
     
  chsCpy(new_trk,"00000000 track\n");  
  if (cur_guiton) {
    cur_instr = 24;
    chsAddFmt(new_trk,"00000000 instr %d\n",cur_instr);
  }
  
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
  #define T_UPOCTAVE    x9C
  #define T_DOWNOCTAVE  x9D 
  #define T_NUMBER      x9E 
  #define T_TRANSPOSE   x9F 
  #define T_TOMSMODE    xA0 
  #define T_GUITMODE    xA1 
  #define T_RATIO       xA2 
  #define T_VELOCITY    xA3 
  #define T_DUTY        xA4 
  #define T_LOOSE       xA5
  #define T_VELVAR      xA6
  #define T_PITCH       xA7
  #define T_CTRL        xA8
  #define T_KEY         xA9 
  #define T_TUNING      xAA
  #define T_GCHORD      xAB
  #define T_CHORD1      xAC
  #define T_CHORD2      xAD
  #define T_CHORD3      xAE

  pmxScannerBegin(trk)
    
    pmxTokSet("stress&K(<+d>)",T_STRESS)
    pmxTokSet("soft&K(<+d>)",T_SOFT)
    pmxTokSet("key&K(<?=+&-><=0-7>)()&K<?=,>&K(<?$minor$major$min$maj>)",T_KEY)                   
    pmxTokSet("key&K()(<=a-g><?=#b>)&K<?=,>&K(<?$minor$major$min$maj>)",T_KEY)                   
    pmxTokSet("pitch&K(<?=+&->)(<+d>)",T_PITCH)
    pmxTokSet("guit<?$ar>o(<$n$ff>)",T_GUITMODE)
    pmxTokSet("loose&K(&d),(<+=g0-9>)",T_LOOSE)
    pmxTokSet("velvar&K(&d),(<+=g0-9>)",T_VELVAR)
    pmxTokSet("r&K(<+d>)<?=/>(<*d>)",T_RATIO)
    pmxTokSet("v&K(<+d>)",T_VELOCITY)
    pmxTokSet("u&K(<+d>)",T_DUTY)
    pmxTokSet("tomso(<$n$ff>)",T_TOMSMODE)
    pmxTokSet("ch&K(<+d>)",T_CHANNEL)
    pmxTokSet("ctrl&K(<+d>)(),(<+d>)",T_CTRL)
    pmxTokSet("ctrl&K()(<+q>),(<+d>)",T_CTRL)
    pmxTokSet("i&K(<+d>)()",T_INSTR)
    pmxTokSet("i&K()(<+q>)",T_INSTR)
    pmxTokSet("t<?$ranspose>&K(&d)",T_TRANSPOSE)
    pmxTokSet("tuning&K[(<+!]>)]",T_TUNING)
    
    pmxTokSet("<?=',>[g:&K(<+=0-9, &->)]()()()(<?=/><*d>)&K(<*==>)",T_GCHORD)
    pmxTokSet("<?=',>[g:&K()(<=a-g>)(<?=#b+->)&K(<*! ]>)&K](<?=/><*d>)&K(<*==>)",T_GCHORD)

    pmxTokSet("<?=',>[&K(<=0-9a-gn&-><?=#b+&-><*d>&K,<+=0-9a-gn#+&-,>)()()()](<?=/><*d>)&K(<*==>)",T_CHORD1)
    pmxTokSet("<?=',>[&K()()()(<$au$di><*! ]>)&K](<?=/><*d>)&K(<*==>)",T_CHORD2)
    pmxTokSet("<?=',>[&K(<?=a-g>)(<?=#b+&->)()&K(<*! ]>)&K](<?=/><*d>)&K(<*==>)",T_CHORD3)

    pmxTokSet("/",T_UPOCTAVE)    
    pmxTokSet("\\",T_DOWNOCTAVE)    
    pmxTokSet("(<+d>)&K(<*==>)",T_NUMBER)    
    pmxTokSet("(<?=,'>)n(<?=t>)(<?=+&->)(<+d>)<?=/>(<*=0-9>)&K(<*==>)",T_NUMNOTE)
    pmxTokSet("(<?=,'>)(<=a-g><?=#b+&->)(<*=0-9>)(<?=/><*=0-9>)&K(<*==>)",T_NOTE)
    pmxTokSet("(<?=,'>)(x)()(<?=/><*=0-9>)&K(<*==>)",T_NOTE)
    pmxTokSet("(o)(<?=a-g><?=#b+&->)(<*=0-9>)(<?=/><*=0-9>)",T_NOTE)
    pmxTokSet("p(<?=/><*=0-9>)&K(<*==&->)",T_PAUSE)
    pmxTokSet("-()(<*==&->)",T_PAUSE)
    pmxTokSet("<=()>",pmxTokIGNORE) 
    pmxTokSet("&s",pmxTokIGNORE) 
    pmxTokSet("<.>",pmxTokERROR) 
                        
  pmxScannerSwitch

    pmxTokCase(T_STRESS):
      cur_stress = atoi(pmxTokStart(1)) & 0x7F;
      continue;
    
    pmxTokCase(T_SOFT):
      cur_soft = atoi(pmxTokStart(1)) & 0x7F;
      continue;
    
    pmxTokCase(T_GCHORD):
      k = 0;
      if (pmxTokLen(5) > 0) {
        if (*pmxTokStart(5) != '/') merr("Syntax Error",pmxTokStart(5)-1);
        cur_notelen = atoi(pmxTokStart(5)+1);
      }
      d = 1+pmxTokLen(6);
      
      if (pmxTokLen(1) == 0) 
        s = gchordbyname(pmxTokStart(2),pmxTokLen(3),pmxTokStart(4),pmxTokLen(4));
      else
        s = pmxTokStart(1);
      
      if (s == NULL) merr("Unknown chord", pmxTokStart(0));
      
      switch(*pmxTokStart(0)) {
        case '\'' : chsAddFmt(new_trk,"%08lx stress %d\n",cur_tick,cur_stress);
                    break;
        case ','  : chsAddFmt(new_trk,"%08lx soft %d\n",cur_tick,cur_soft);
                    break;
      }      
      
      chsAddFmt(new_trk,"%08lx gchord start\n",cur_tick);
      
      pmxScannerBegin(s)
        #define T_GCHNUM   x81
        #define T_GCHMINUS x82
        #define T_GCHEND   x83

        pmxTokSet("&d",T_GCHNUM)
        pmxTokSet("-", T_GCHMINUS)
        pmxTokSet(",", pmxTokIGNORE)
        pmxTokSet("]",T_GCHEND)
        pmxTokSet("&s",pmxTokIGNORE) 
        pmxTokSet("<.>",pmxTokERROR)
         
      pmxScannerSwitch
      
        pmxTokCase(T_GCHNUM) :
          if (tuning[k] > 0) {
            n = tuning[k++] + atoi(pmxTokStart(0));
            n = notenorm(n+cur_transpose);
            t = notename(n);
            o = noteoctave(n);
            chsAddFmt(new_trk,"%08lx ",cur_tick);
            chsAddFmt(new_trk,"note %c%c %d %d/%d", t[0], t[1], o, d, cur_notelen);
            if (cur_ratio_n != cur_ratio_d) {
              chsAddFmt(new_trk," %d/%d", cur_ratio_n , cur_ratio_d);
            }
            chsAddChr(new_trk,'\n');
          }          
          continue;
          
        pmxTokCase(T_GCHMINUS) :
          if (tuning[k] > 0) k++;
          continue;
          
        pmxTokCase(pmxTokIGNORE):  continue;
        pmxTokCase(pmxTokEOF):     break;
        pmxTokCase(pmxTokERROR):   merr("Syntax error",pmxTokStart(0));
                                   break;
        
      pmxScannerEnd;
        
      n = (ppqn * d * 4)/cur_notelen;
      if (cur_ratio_n != cur_ratio_d) 
        n = (n * cur_ratio_n) / cur_ratio_d;
        
      cur_tick += n; 
      chsAddFmt(new_trk,"%08lx gchord end\n",cur_tick);
      
      continue;

    pmxTokCase(T_CHORD1):
/*  "[&K(<=0-9a-gn&-><?=#b+&-><*d>&K,<+=0-9a-gn#+&-,>)()()()](<?=/><*d>)&K(<*==>)" */
      s = pmxTokStart(1);
      goto chord;

    pmxTokCase(T_CHORD3):
/*  "[&K(<?=a-g>)(<?=#b+&->)(<*d>)&K(<*! ]>)&K](<?=/><*d>)&K(<*==>)" */
      if ((pmxTokLen(3) + pmxTokLen(2) + pmxTokLen(1)) > 0) {
        if (pmxTokLen(3) > 0) o = atoi(pmxTokStart(3));
        else o = noteoctave(cur_note);
        if (pmxTokLen(2) > 0) k = *pmxTokStart(2);
        else k = noteacc(cur_note);
        if (pmxTokLen(1) > 0) n = *pmxTokStart(1);
        else n = notebase(cur_note);
        cur_note = notenum(n,k,o);
      }

    pmxTokCase(T_CHORD2):
/*  "[&K()()()(<$au$di><*! ]>)&K](<?=/><*d>)&K(<*==>)" */
      s = chordbyname(pmxTokStart(4),pmxTokLen(4));

    chord:
      if (s == NULL) merr("Unknown chord", pmxTokStart(0));
      
      k = 0;
      if (pmxTokLen(5) > 0) {
        if (*pmxTokStart(5) != '/') merr("Syntax Error",pmxTokStart(5)-1);
        cur_notelen = atoi(pmxTokStart(5)+1);
      }
      d = 1+pmxTokLen(6);
      
      switch(*pmxTokStart(0)) {
        case '\'' : chsAddFmt(new_trk,"%08lx stress %d\n",cur_tick,cur_stress);
                    break;
        case ','  : chsAddFmt(new_trk,"%08lx soft %d\n",cur_tick,cur_soft);
                    break;
      }
            
      chsAddFmt(new_trk,"%08lx chord start\n",cur_tick);
      
      pmxScannerBegin(s)
        #define T_CHNUM      x81
        #define T_CHNOTENUM  x82
        #define T_CHNOTE     x83
        #define T_CHEND      x84

        pmxTokSet("&d",T_CHNUM)
        pmxTokSet("n(<+d>)", T_CHNOTENUM)
        pmxTokSet("(<=a-g>)(<?=#b+&->)(<*d>)", T_CHNOTE)
        pmxTokSet("]",T_CHEND)
        pmxTokSet(",", pmxTokIGNORE)
        pmxTokSet("&s",pmxTokIGNORE) 
        pmxTokSet("<.>",pmxTokERROR)
         
      pmxScannerSwitch
      
        pmxTokCase(T_CHNUM) :
          n = atoi(pmxTokStart(0));
          n = notenorm(cur_note+n+cur_transpose);
          t = notename(n);
          o = noteoctave(n);
          chsAddFmt(new_trk,"%08lx ",cur_tick);
          chsAddFmt(new_trk,"note %c%c %d %d/%d", t[0], t[1], o, d, cur_notelen);
          if (cur_ratio_n != cur_ratio_d) {
            chsAddFmt(new_trk," %d/%d", cur_ratio_n , cur_ratio_d);
          }
          chsAddChr(new_trk,'\n');
          continue;
          
        pmxTokCase(T_CHNOTENUM) :
          cur_note = atoi(pmxTokStart(1));
          n = notenorm(cur_note+cur_transpose);
          t = notename(n);
          o = noteoctave(n);
          chsAddFmt(new_trk,"%08lx ",cur_tick);
          chsAddFmt(new_trk,"note %c%c %d %d/%d", t[0], t[1], o, d, cur_notelen);
          if (cur_ratio_n != cur_ratio_d) {
            chsAddFmt(new_trk," %d/%d", cur_ratio_n , cur_ratio_d);
          }
          chsAddChr(new_trk,'\n');
          continue;
          
        pmxTokCase(T_CHNOTE) :
          if (pmxTokLen(3) > 0) o = atoi(pmxTokStart(3));
          else o = noteoctave(cur_note);
          if (pmxTokLen(2) > 0) k = *pmxTokStart(2);
          else k = " # #  # # # "[cur_note % 12];
          cur_note = notenum(*pmxTokStart(1),k,o);
          n = notenorm(cur_note+cur_transpose);
          t = notename(n);
          chsAddFmt(new_trk,"%08lx ",cur_tick);
          chsAddFmt(new_trk,"note %c%c %d %d/%d", t[0], t[1], o, d, cur_notelen);
          if (cur_ratio_n != cur_ratio_d) {
            chsAddFmt(new_trk," %d/%d", cur_ratio_n , cur_ratio_d);
          }
          chsAddChr(new_trk,'\n');
          continue;
          
        pmxTokCase(pmxTokIGNORE):  continue;
        pmxTokCase(T_CHEND):       break;
        pmxTokCase(pmxTokERROR):   merr("Syntax error",pmxTokStart(0));
                                   break;
        
      pmxScannerEnd;
        
      n = (ppqn * d * 4)/cur_notelen;
      if (cur_ratio_n != cur_ratio_d) 
        n = (n * cur_ratio_n) / cur_ratio_d;
        
      cur_tick += n; 
      chsAddFmt(new_trk,"%08lx chord end\n",cur_tick);
      
      continue;

    pmxTokCase(T_TUNING):
        s = pmxTokStart(1);
        n = 0;
        
        #define T_TUNNOTE     x81
        #define T_TUNEND      x83
        #define T_TUNNOTENUM  x84
         
        pmxScannerBegin(s)
        
          pmxTokSet("(<=a-g>)(<?=#b+&->)(<+d>)",T_TUNNOTE)
          pmxTokSet("n(<+d>)",T_TUNNOTENUM)
          pmxTokSet(",", pmxTokIGNORE)
          pmxTokSet("]",T_TUNEND)
          pmxTokSet("&s",pmxTokIGNORE) 
          pmxTokSet("<.>",pmxTokERROR) 
      
        pmxScannerSwitch
      
          pmxTokCase(T_TUNNOTE) :
            if (n >= MAX_TUNING) merr("Syntax error",t);
            tuning[n++] = notenum(*pmxTokStart(1),
                                  pmxTokLen(2) > 0 ? *pmxTokStart(2) : ' ',
                                  atoi(pmxTokStart(3)));
            continue;
      
          pmxTokCase(T_TUNNOTENUM) :
            if (n >= MAX_TUNING) merr("Syntax error",t);
            tuning[n++] = atoi(pmxTokStart(1)) & 0x7F;
            continue;
      
          pmxTokCase(pmxTokIGNORE):  continue;
          pmxTokCase(T_TUNEND):      break;
          pmxTokCase(pmxTokERROR):   merr("Syntax error",pmxTokStart(0));
                                     break;
          
        pmxScannerEnd;
        
        tuning[n] = 0;
  
      continue;

    pmxTokCase(T_KEY):
      if (pmxTokLen(1)>0) { 
        d = atoi(pmxTokStart(1));
        if (pmxTokLen(3) > 0 && pmxTokStart(3)[2] == 'n') {
          d += (d < 0) ? - 100 : 100;
        } 
      }
      else {
        n = (pmxTokLen(3) > 0) ? pmxTokStart(3)[2] : 'j';
        d = keybyname(pmxTokStart(2), pmxTokLen(2), n);
      }
      chsAddFmt(new_trk,"%08lx ",cur_tick);
      chsAddFmt(new_trk,"key %d\n",d);
      continue;

    pmxTokCase(T_LOOSE):
      cur_loose_w = atoi(pmxTokStart(1));
      cur_loose_q = (*pmxTokStart(2) == 'g') ? -1 : atoi(pmxTokStart(2));
      chsAddFmt(new_trk,"%08lx ",cur_tick);
      chsAddFmt(new_trk,"loose %d,%d\n",cur_loose_w,cur_loose_q);        
      continue;
      
    pmxTokCase(T_VELVAR):
      cur_velvar_w = atoi(pmxTokStart(1));
      cur_velvar_q = (*pmxTokStart(2) == 'g') ? -1 : atoi(pmxTokStart(2));
      chsAddFmt(new_trk,"%08lx ",cur_tick);
      chsAddFmt(new_trk,"velvar %d,%d\n",cur_velvar_w,cur_velvar_q);        
      continue;
      
    pmxTokCase(T_PITCH):
      n = atoi(pmxTokStart(2));
      if (pmxTokLen(1)>0) {
        if (*pmxTokStart(1) == '-') n = -n;
        n += cur_pitch;
      }
      cur_pitch = n;
      chsAddFmt(new_trk,"%08lx ",cur_tick);
      chsAddFmt(new_trk,"pitch %d\n",cur_pitch);
      continue;
    
    pmxTokCase(T_RATIO):
      cur_ratio_n = atoi(pmxTokStart(1));
      cur_ratio_d = (pmxTokLen(2) == 0) ? 1 : atoi(pmxTokStart(2));
      if (cur_ratio_n < 1) cur_ratio_n = 1;
      if (cur_ratio_d < 1) cur_ratio_d = 1;
      if (cur_ratio_n == cur_ratio_d) { cur_ratio_n =1 ; cur_ratio_d = 1;}
      continue;

    pmxTokCase(T_VELOCITY):
      cur_velocity = atoi(pmxTokStart(1));
      chsAddFmt(new_trk,"%08lx ",cur_tick);
      chsAddFmt(new_trk,"vel %d\n",cur_velocity);
      continue;

    pmxTokCase(T_DUTY):
      cur_duty = atoi(pmxTokStart(1));
      chsAddFmt(new_trk,"%08lx ",cur_tick);
      chsAddFmt(new_trk,"duty %d\n",cur_duty);
      continue;

    pmxTokCase(T_TRANSPOSE):
      cur_transpose = atoi(pmxTokStart(1));
      continue;

    pmxTokCase(T_UPOCTAVE):
      cur_note  = notenorm(cur_note + 12);
      continue;

    pmxTokCase(T_DOWNOCTAVE):    
      cur_note  = notenorm(cur_note - 12);
      continue;
      
    pmxTokCase(T_TOMSMODE):
      cur_tomson = (*pmxTokStart(1) == 'n') ;
      if (cur_tomson) {
        cur_transpose = 0;
        cur_guiton = 0;
        if (cur_channel != 9) {
           chsAddFmt(new_trk,"%08lx ",cur_tick);
           chsAddStr(new_trk,"ch 9\n");
           cur_channel = 9;
        }
      }
      else if (cur_channel == 9) {
        chsAddFmt(new_trk,"%08lx ",cur_tick);
        chsAddStr(new_trk,"ch 0\n");
        cur_channel = 0;
      }
      continue;
      
    pmxTokCase(T_GUITMODE):
      cur_guiton = (*pmxTokStart(1) == 'n') ;
      if (cur_guiton) {
        if (cur_channel == 9) {
          chsAddFmt(new_trk,"%08lx ",cur_tick);
          chsAddStr(new_trk,"ch 0\n");
          cur_channel = 0;
        }
      }
      if (24 != cur_instr) {
        cur_instr = 24;
        chsAddFmt(new_trk,"%08lx ",cur_tick);
        chsAddFmt(new_trk,"instr %d\n",cur_instr);
      }

      continue;
      
    pmxTokCase(T_NUMBER):
      d = atoi(pmxTokStart(1));
      n = 0;
      if (cur_guiton) {
        n = d;
      } 
      else if (cur_tomson) {
        if (d<1) d=1; else if (d>6) d = 6;
        cur_note = "\001\062\060\057\055\053\051"[d];
      }
      else {
        cur_notelen = d;
      }
      n = notenorm(cur_note + cur_transpose + n);
      t = notename(n);
      o = noteoctave(n);
      d = (1+pmxTokLen(2));
      chsAddFmt(new_trk,"%08lx ",cur_tick);
      chsAddFmt(new_trk,"note %c%c %d %d/%d", t[0], t[1], o, d, cur_notelen);
      n = (ppqn * d * 4)/cur_notelen;
      if (cur_ratio_n != cur_ratio_d) {
        chsAddFmt(new_trk," %d/%d", cur_ratio_n , cur_ratio_d);
        n = (n * cur_ratio_n) / cur_ratio_d;
      }
      chsAddChr(new_trk,'\n');
      cur_tick += n; 
      continue;    

    pmxTokCase(T_NUMNOTE):
    
      if (pmxTokLen(1) > 0) {
        switch(*pmxTokStart(1)) {
          case '\'' : chsAddFmt(new_trk,"%08lx stress %d\n",cur_tick,cur_stress);
                      break;
          case ','  : chsAddFmt(new_trk,"%08lx soft %d\n",cur_tick,cur_soft);
                      break;
        }
      }
    
      n=atoi(pmxTokStart(4)); 
      if (pmxTokLen(3) > 0) {
        if (*pmxTokStart(3) == '-') n = -n;
        n += cur_note;
      }
      n = notenorm(n);
      t = notename(n+cur_transpose);
      
      chsAddFmt(new_trk,"%08lx ",cur_tick);
      chsAddFmt(new_trk,"note %c%c %d ", t[0], t[1], noteoctave(n+cur_transpose));
      
      d = cur_notelen;
      if (pmxTokLen(5) > 0) d = atoi(pmxTokStart(5));
      if (pmxTokLen(2) == 0) {cur_note = n;  cur_notelen = d;}
             
      chsAddFmt(new_trk,"%d/%d",(1+pmxTokLen(6)), d);

      n = (ppqn * d * 4)/cur_notelen;
      if (cur_ratio_n != cur_ratio_d) {
        chsAddFmt(new_trk," %d/%d", cur_ratio_n , cur_ratio_d);
        n = (n * cur_ratio_n) / cur_ratio_d;
      }
      chsAddChr(new_trk,'\n');
      cur_tick += n; 
      continue;
 
    pmxTokCase(T_NOTE):
      n = cur_note % 12;
      o = noteoctave(cur_note);
      if (pmxTokLen(3) > 0)  {
        o = atoi(pmxTokStart(3));
        if (o > 10) o = 10; else if (o < 0) o = 0;
        cur_note = notenorm((cur_note % 12) + o * 12);  
      }
      
      if (pmxTokLen(4) > 0)  {
        t = pmxTokStart(4);
        if (*t != '/') merr("Syntax error", t);
        cur_notelen = atoi(t+1);
      }
      
      if (pmxTokLen(2) > 0 && pmxTokStart(2)[0] != 'x')  {
        if ((pmxTokLen(2) > 1)) d = pmxTokStart(2)[1] ;
        else d = ' ';
        n = pmxTokStart(2)[0] - 'a';
        n = "\011\013\000\002\004\005\007"[n];
        if (d == '#' || d == '+') n++;
        else if (d == 'b' || d == '-') n--;
      }
      
      cur_note = notenorm(n + 12 * o);
               
      if (pmxTokLen(1) > 0) {
        switch(*pmxTokStart(1)) {
          case 'o'  : continue;
          case '\'' : chsAddFmt(new_trk,"%08lx stress %d\n",cur_tick,cur_stress);
                      break;
          case ','  : chsAddFmt(new_trk,"%08lx soft %d\n",cur_tick,cur_soft);
                      break;
        }
      }
      
      d = (1+pmxTokLen(5));
      n = notenorm(cur_note + cur_transpose);
      t = notename(n);
      o = noteoctave(n);
      
      chsAddFmt(new_trk,"%08lx ",cur_tick);
      chsAddFmt(new_trk,"note %c%c %d %d/%d", t[0], t[1], o, d, cur_notelen);
      n = (ppqn * d * 4)/cur_notelen;
      if (cur_ratio_n != cur_ratio_d) {
        chsAddFmt(new_trk," %d/%d", cur_ratio_n , cur_ratio_d);
        n = (n * cur_ratio_n) / cur_ratio_d;
      }
      chsAddChr(new_trk,'\n');
      cur_tick += n; 
      continue;

    pmxTokCase(T_PAUSE):
      if (pmxTokLen(1) > 0)  {
        if (*pmxTokStart(1) != '/') merr("Syntax Error", pmxTokStart(1));
        cur_notelen = atoi(pmxTokStart(1)+1);
      }
        
      d = (1+pmxTokLen(2));
      chsAddFmt(new_trk,"%08lx ",cur_tick);
      chsAddFmt(new_trk,"pause %d/%d", d, cur_notelen);
      n = (ppqn * d * 4)/cur_notelen;
      if (cur_ratio_n != cur_ratio_d) {
        chsAddFmt(new_trk," %d/%d", cur_ratio_n , cur_ratio_d);
        n = (n * cur_ratio_n) / cur_ratio_d;
      }
      chsAddChr(new_trk,'\n');
      cur_tick += n; 
      continue;

    pmxTokCase(T_CHANNEL):
      d = atoi(pmxTokStart(1)) -1;
      if (0 <= d && d <= 15 ) {
        cur_channel = d;
        chsAddFmt(new_trk,"%08lx ",cur_tick);
        chsAddFmt(new_trk,"ch %d\n",cur_channel);
      }
      continue;
      
    pmxTokCase(T_INSTR):
      if (pmxTokLen(2) > 0) {
        d = instrbyname(pmxTokStart(2), pmxTokLen(2));
        if (d & 0x80) {
          if (cur_channel != 9) {
            chsAddFmt(new_trk,"%08lx ",cur_tick);
            chsAddStr(new_trk,"ch 9\n");
            cur_channel = 9;
          }          
          cur_note = d &= 0x7F;
          continue;
        }
      }
      else {
        d = atoi(pmxTokStart(1))-1;
      }
      if (d < 0 || d > 127 ) d = 0;
      if (d != cur_instr) {
        cur_instr = d;
        chsAddFmt(new_trk,"%08lx ",cur_tick);
        chsAddFmt(new_trk,"instr %d\n",cur_instr);
      }
      continue;
      
    pmxTokCase(pmxTokIGNORE):
      continue;
      
    pmxTokCase(pmxTokERROR):
      merr("Syntax error", pmxTokStart(0));
      break;

    default: merr("Internal error", pmxTokStart(0));
      break; 
     
  pmxScannerEnd;
  
  chsAddFmt(new_trk,"%08lx ",cur_tick);
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

  for (k=1; k< vecCount(tracks); k++) {
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

  if (argc < 2) f = stdin;
  else { 
    fname=argv[1];
    f = fopen(fname,"r");
  }
  
  if (!f) merr("Unable to open file",NULL);
  
  tracks = mp_tracks(f);
   
  if (f != stdin) fclose(f);

  if (f == stdin) {
    fprintf(stdout,"Content-Type: text/plain\n\n");
  }
  
  for (k=0; k< vecCount(tracks); k++) {
    trk = vecGetS(tracks, k, NULL);
    if (trk != NULL) 
       fprintf(stdout,"%s\n",trk);
  }  
  
  tracks = mp_tracks_free(tracks);
  
  exit(0);
}
