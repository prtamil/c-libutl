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
tbl_t states = NULL;

recDef(state,
  chs_t name;
  chs_t pattern;
  vec_t rules;
);

recDefDel(state,a)   { vecFree(a->rules); }
recDefNew(state,a)   { a->name = NULL; a->rules = NULL; }
recDefUid(state,a)   { return a->name; }
recDefCmp(state,a,b) { return strcmp(a->name,b->name); }
recDefCpy(state,a,b) { }

int cur_ln = 1;

/*
.v
script = state*

state = "[" state_name "]" rule*

rule  = "\"" pattern "\"" replace? ";"

replace = "=" (value | func)+

value = "$" var_name | "$" DIGIT | STRING | NUMBER

func = add | sub | cat | set | div | mul | mod | len | nxt | if

add = "@add" "(" var_name "," value ")"
sub = "@sub" "(" var_name "," value ")"
set = "@set" "(" var_name "," value ")"
div = "@div" "(" var_name "," value ")"
mul = "@mul" "(" var_name "," value ")"
mod = "@mod" "(" var_name "," value ")"
cat = "@cat" "(" var_name "," value ")"
mid = "@mid" "(" var_name "," value "," value "," value ")"
len = "@len" "(" var_name "," value ")"
nxt = "@nxt" "(" state_name ")"

if = ("@if" | "@ifn") "(" value op value "," func ("," func)? ")"
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
            pmxTokCase(T_COMMENT):
                  cur_ln++;
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
            pmxTokCase(T_COMMENT):
                  cur_ln++;
                  GOTO(rule);

            pmxTokCase(T_PATTERN):
                  GOTO(rule);
          }
          fprintf(stderr,"ERROR 102\n"); break;
          
   }
   
   return 0;
}


int main(int argc, char *argv[])
{
  chs_t str = NULL;
 
  exit(0);
}
