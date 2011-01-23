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

chs_t vars[27];
tbl_t states = NULL;

recDef(state,
  char *name;
  chs_t patterns;
  vec_t rules;
);

recDefDel(state,a)   { vecFree(a->rules); chsFree(a->patterns); }
recDefNew(state,a)   { a->name = NULL; a->rules = NULL; a->patterns = NULL; }
recDefUid(state,a)   { return a->name; }
recDefCmp(state,a,b) { return strcmp(a->name,b->name); }
recDefCpy(state,a,b) { }

int cur_ln = 1;
char *err = NULL;

/*
.v
script = state*

state = "[" state_name "]" rule*

rule  = '"' pattern '"' replace? next_state? ";"

nextsate = "->" state_name

replace = "=" (value | func)+

term = "$" var_name | "$" DIGIT | string | NUMBER

value = term+

func = add | sub | cat | set | div | mul | mod |
       cat | mid | len | if

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

string = "'" echr* "'" | '"' echr* '"'

echr = !\\"' | '\\\'' | CHAR 

..
*/

#define T_NEWLINE       x81
#define T_SPACE         x82
#define T_COMMENT       x83
#define T_STATE_NAME    x84
#define T_PATTERN       x85

/* Recursive descent parser */

char *parse_replace(char *cur)
{
  if (cur == NULL) return cur;
  
  while (isspace(*cur)) {
    if (*cur == '\n') cur_ln++;
    cur++;
  }
  if (*cur == '=') {
    
  }
  return cur;
}

char *parse_rule(char *cur)
{
  char *pat = NULL;
  
  while (pat == NULL) {
          pmxSwitch (cur, 
            pmxTokSet("&K&n",T_NEWLINE)
            pmxTokSet("&K#&L&n",T_COMMENT)
            pmxTokSet("&s",T_SPACE)
            pmxTokSet("&K&e\\(&q)&K",T_PATTERN)
          ) {
            pmxTokCase(T_NEWLINE):
            pmxTokCase(T_COMMENT):
                  cur_ln++;
                  break;
                  
            pmxTokCase(T_SPACE):
                  break;

            pmxTokCase(T_PATTERN):
                  pat = pmxTokStart(1);
                  break;
                  
            pmxTokCase(pmxTokEOF) :
                  return NULL;
                                    
            default :
                  return cur;      
          }
  }
  
  printf("pattern: %.*s\n",pmxTokLen(1),pmxTokStart(1));                  
  
  cur = parse_replace(cur);
  
  return cur;
}

char *parse_state(char *cur)
{
  char *name = NULL;
  
  while (name == NULL) {
  
          pmxSwitch (cur,
            pmxTokSet("&K&n",T_NEWLINE)
            pmxTokSet("&K#&L&n",T_COMMENT)
            pmxTokSet("&K[&K(<=A-Z_a-z><*=0-9A-Z_a-z>)&K]&K",T_STATE_NAME)
            pmxTokSet("&s",T_SPACE)
          ) {
            pmxTokCase(T_NEWLINE):
            pmxTokCase(T_COMMENT):
                  cur_ln++;
                  break;
                  
            pmxTokCase(T_STATE_NAME):
                  name = pmxTokStart(1);
                  break;
                  
            pmxTokCase(T_SPACE):
                  break;

            pmxTokCase(pmxTokEOF) :
                  return NULL;
                  
            default :
                  fprintf(stderr,"Syntax error line %d\n",cur_ln);
                  return NULL;      
          }
  }
  
  printf("state: %.*s\n",pmxTokLen(1),pmxTokStart(1));
     
  do {
    cur = parse_rule(++cur);
  } while (cur && *cur == ';');
      
  return cur;
}

char *parse (char *cur)
{
   while (cur && *cur)
     cur = parse_state(cur) ;

   return NULL;
}

void usage()
{
   fprintf(stderr,"Usage: fsm mach.fsm [input [output]]\n");
}

int main(int argc, char *argv[])
{
  chs_t str = NULL;
  FILE *f;
 
  if (argc < 2) {
    usage();
    exit(1);
  }
  
  f = fopen(argv[1],"r");
  
  if (!f) utlError(133,"Unable to open fsm file");
  
  chsCpyFile(str,f);
  fclose(f);
  
  parse(str);
 
  exit(0);
}
