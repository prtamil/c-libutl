/*
**  (C) by Remo Dentato (rdentato@gmail.com)
**
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php
*/


#include <stdio.h>
#include "libutl.h"

chs_t vars[27];

vec_t states = NULL;


/*
.v
script = state*

state = "[" state_name "]" rule*

rule  = "\"" pattern "\"" replace? next_state? ";"

nextsate = "->" state_name

replace = "=" (value | func)+

value = "$" var_name | "$" DIGIT | STRING | NUMBER

func = add | sub | cat | set | div | mul | mod | len

add = "@add" "(" var_name "," value ")"
sub = "@sub" "(" var_name "," value ")"
set = "@set" "(" var_name "," value ")"
div = "@div" "(" var_name "," value ")"
mul = "@mul" "(" var_name "," value ")"
mod = "@mod" "(" var_name "," value ")"
cat = "@cat" "(" var_name "," value ")"
mid = "@mid" "(" var_name "," value "," value "," value ")"
len = "@len" "(" var_name "," value ")"

if = "@if" "(" value op value "," func ("," func)? ")"
op = "=" | "<" | ">" | "<=" | ">=" | "!="

..
*/

#define T_NEWLINE       x81
#define T_SPACE         x82
#define T_COMMENT       x83
#define T_STATE_NAME    x84
#define T_PATTERN       x85

int parse (char *machine)
{
   char *curchar = machine;
   
   FSM {
     STATE(state) :
          pmxSwitch (curchar,
            pmxTokSet("&K&n",T_NEWLINE)
            pmxTokSet("&K#&L&n",T_COMMENT)
            pmxTokSet("&K[&K<+=A-Z_a-z>&K]&K",T_STATE_NAME)
          ) {
            pmxTokCase(T_NEWLINE):
                  GOTO(state);

            pmxTokCase(T_COMMENT):
                  GOTO(state);
                  
            pmxTokCase(T_STATE_NAME):
                  GOTO(rule);
          }
          fprintf(stderr,"ERROR 101\n"); break;
          
     STATE(rule) : 
          pmxSwitch (curchar,
            pmxTokSet("&K&n",T_NEWLINE)
            pmxTokSet("&K#&L&n",T_COMMENT)
            pmxTokSet("&K&e\\(&Q)&K(<?$-&>$=>)",T_PATTERN)
          ) {
            pmxTokCase(T_NEWLINE):
                  GOTO(rule);

            pmxTokCase(T_COMMENT):
                  GOTO(rule);

            pmxTokCase(T_PATTERN):
                  GOTO(rule);
          }
          fprintf(stderr,"ERROR 102\n"); break;
          
   
   }
}


int main(int argc, char *argv[])
{
  chs_t str = NULL;
 
  str = chsCpyFmt(str,"value: %f %s 0x%04X\n",1.4,"LLLo",124);
  str = chsAddFmt(str,"and so %-10d on\n",34);
  str = chsInsFmt(str,6,"<%c>",64);

  printf("%s",str);
  exit(0);
}
