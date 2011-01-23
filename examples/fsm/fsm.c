/*
**  (C) by Remo Dentato (rdentato@gmail.com)
**
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php
*/

#define DEBUG
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

chs_t cur_statename = NULL;
chs_t cur_pattern = NULL;
chs_t cur_replace = NULL;
chs_t cur_nextstate = NULL;

/*
.v
script = rule* state*

state = "[" state_name "]" rule*

rule  = '"' pattern '"' replace? next_state? ";"

nextsate = "->" state_name | "$" var_name

replace = "=" (value | func)+

term = "$" var_name | "$" DIGIT | STRING | NUMBER

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

..
*/

#define T_NEWLINE       x81
#define T_SPACE         x82
#define T_COMMENT       x83
#define T_STATE_NAME    x84
#define T_PATTERN       x85
#define T_ANY           x86
#define T_ENDPATTERN    x87
#define T_ENDREPLACE    x87
#define T_NEXTSTATE     x88
#define T_VARIABLE      x8A
#define T_FUNCTION      x8B
#define T_STRING        x8C
#define T_NUMBER        x8D

#define T_SYNTAX_ERROR  xEF

/* Recursive descent parser */

static char *err_syn(int ln,char *msg)
{ 
  fprintf(stderr,"Error line %d %s\n",ln, msg ? msg : "");
  return NULL;
} 

char *parse_nextstate(char *cur)
{
  Xdbgmsg("nextstate: [%.10s]\n",cur);
  chsCpy(cur_nextstate,"");
  while (cur && *cur) {
    pmxSwitch (cur, 
      pmxTokSet("&n",T_NEWLINE)
      pmxTokSet("#&L",T_COMMENT)
      pmxTokSet("&k",T_SPACE)
      pmxTokSet("-&>&K(<=A-Z_a-z><*=0-9A-Z_a-z>)&K",T_NEXTSTATE)
      pmxTokSet("-&>&K($<=0-9A-Z_a-z>)&K",T_NEXTSTATE)
      pmxTokSet(";",T_ENDPATTERN)
    ) {
      pmxTokCase(T_NEWLINE): cur_ln++;
      pmxTokCase(T_COMMENT):
      pmxTokCase(T_SPACE)  : break;

      pmxTokCase(T_NEXTSTATE) : chsCpyL(cur_nextstate, pmxTokStart(1), pmxTokLen(1));
      pmxTokCase(T_ENDPATTERN): return cur;
      
      pmxTokCase(pmxTokEOF) :  return NULL;
                              
      default :  return err_syn(cur_ln,"parse_nextstate"); 
    } pmxSwitchEnd ;
  }
  
  return cur;
} 

char *parse_replace(char *cur)
{
  Xdbgmsg("replace: %30s\n",cur);
  chsCpy(cur_replace,"");
  
  while (cur && *cur) {
    pmxSwitch (cur, 
      pmxTokSet("&n",T_NEWLINE)
      pmxTokSet("#&L",T_COMMENT)
      pmxTokSet("&k",T_SPACE)
      pmxTokSet("&=",T_SPACE)
      pmxTokSet("(&d)",T_NUMBER)
      pmxTokSet("($<=0-9A-Za-z>)",T_VARIABLE)
      pmxTokSet("&e\\(&q)&K",T_STRING)
      pmxTokSet("<?=@>(<+a>&K&B())",T_FUNCTION)
      pmxTokSet(";",T_ENDREPLACE)
      pmxTokSet("-&>",T_ENDREPLACE)
    ) {
      pmxTokCase(T_NEWLINE): cur_ln++;
      pmxTokCase(T_COMMENT):
      pmxTokCase(T_SPACE)  : break;

      pmxTokCase(T_STRING):
      pmxTokCase(T_FUNCTION):
      pmxTokCase(T_VARIABLE):
            chsAddStrL(cur_replace, pmxTokStart(1), pmxTokLen(1));
            chsAddChr(cur_replace,' ');
            break;
            
      pmxTokCase(T_ENDREPLACE): return pmxTokStart(0);
           
      pmxTokCase(pmxTokEOF) :  return NULL;
                              
      default : return err_syn(cur_ln,"parse_replace");      
    } pmxSwitchEnd ;
  }
  
  return cur;
}

char *parse_state(char *cur)
{
  while (cur && *cur) {
    pmxSwitch (cur,
      pmxTokSet("&n",T_NEWLINE)
      pmxTokSet("#&L",T_COMMENT)
      pmxTokSet("&k",T_SPACE)
      pmxTokSet("[",T_STATE_NAME)
      pmxTokSet("&e\\(&q)&K",T_PATTERN)
      pmxTokSet(";",T_SPACE)
    ) {
      pmxTokCase(T_NEWLINE): cur_ln++;
      pmxTokCase(T_COMMENT):
      pmxTokCase(T_SPACE)  : break;

      pmxTokCase(T_STATE_NAME): return pmxTokStart(0);
            
      pmxTokCase(T_PATTERN): chsCpyL(cur_pattern, pmxTokStart(1), pmxTokLen(1));
                             cur = parse_replace(cur);
                             cur = parse_nextstate(cur);
                             chsTrim(cur_replace,NULL," ");
                             printf("[%s] [%s] [%s] [%s]\n",cur_statename,cur_pattern, cur_replace,cur_nextstate);
                             break;
                             
      pmxTokCase(pmxTokEOF) : return NULL;

      default :  return err_syn(cur_ln,"parse_state");
      
    } pmxSwitchEnd;
  }
  
  return cur;
}

char *parse (char *cur)
{
 
  chsCpy(cur_statename,"start");
  while (cur && *cur) {
    pmxSwitch (cur,
      pmxTokSet("&n",T_NEWLINE)
      pmxTokSet("#&L",T_COMMENT)
      pmxTokSet("[&K(<=A-Z_a-z><*=0-9A-Z_a-z>)&K]&K",T_STATE_NAME)
      pmxTokSet("&k",T_SPACE)
      pmxTokSet(";",T_SPACE)
      pmxTokSet("\"",T_PATTERN)
    ) {
      pmxTokCase(T_NEWLINE): cur_ln++;
      pmxTokCase(T_COMMENT):
      pmxTokCase(T_SPACE)  : break;
                  
      pmxTokCase(T_PATTERN): cur = parse_state(pmxTokStart(0));
                             break;
      
      pmxTokCase(T_STATE_NAME):
            chsCpyL(cur_statename, pmxTokStart(1),pmxTokLen(1));
            cur = parse_state(cur);
            break;
            
      pmxTokCase(pmxTokEOF) : return NULL;
      
      default :  return err_syn(cur_ln,"parse");      
      
    } pmxSwitchEnd;
  }
    
  return cur;
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
