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
** In general macros can have a type (e.g. |mrnd$x($a $b)| expands as |$a| or
** as |$b| at random). Macros in this form ar recognized but not handled in
** this example.
*/

#include <stdio.h>
#include <ctype.h>

#include "libutl.h"

void usage()
{
  fprintf(stderr,"Usage: macr filename\n" );
  exit(1);
}

void merr(char *msg)
{
  fprintf(stderr,"ERR: %s\n",msg);
  exit(1);
}

chs_t text = NULL;
tbl_t macros = NULL;
chs_t body = NULL;
chs_t rpl  = NULL;
vec_t args = NULL;


char *getmacro(char *str, pmxMatches_t capt)
{
  char *name;
  char c;
  
  name = str + pmxStart(capt,2);
  c=name[pmxLen(capt,2)];
  name[pmxLen(capt,2)] = '\0';
    
  while (*name) { 
    *name = tolower(*name);
    name++;    
  }    
  name = str + pmxStart(capt,2);
  
  body = chsCpyL(body,str+pmxStart(capt,1),pmxLen(capt,1));
  body = chsAddChr(body,'$');
  if (pmxLen(capt,3) > 0)
    body = chsAddStrL(body,str+pmxStart(capt,3)+1,pmxLen(capt,3)-2);   

  macros = tblSetSS(macros,name,body);
  
  name[pmxLen(capt,2)] = c;
  
/*  return (pmxLen(capt,4)  ? utlEmptyString : " "); */
  return utlEmptyString;
}


char *subargs(char *str, pmxMatches_t capt)
{ 
  int k;
  char *r;

  k = str[pmxStart(capt,0)+1]-'1';
  r = vecGetS(args, k, NULL);
  
  return (r? r : utlEmptyString);
}

char *submacro(char *str, pmxMatches_t capt)
{
  char *name;
  char *bd;
  char c;
  
  name = str+pmxStart(capt,1);
  c = name[pmxLen(capt,1)]; 
  name[pmxLen(capt,1)] = '\0';
  
  while (*name) { 
    *name = tolower(*name);
    name++;    
  }    
  name = str+pmxStart(capt,1);
  
  bd = tblGetSS(macros,name,NULL);
   
  if (!bd) {
    fprintf(stderr,"Unknown macro: '%s'\n",name);
    return "";
  }
  
  while (*bd && *bd++ != '$');
  rpl = chsCpy(rpl,bd);
  
  name[pmxLen(capt,1)] = c;

  args = vecFree(args);
  if (pmxLen(capt,2)>2) {  
    name = str+pmxStart(capt,2);
    c = name[pmxLen(capt,2)]; 
    name[pmxLen(capt,2)] = '\0';
    
    args = vecSplit(name,","," \t()");
    name[pmxLen(capt,2)] = c;
  }
  
  /* replace args */
  rpl = chsSubFun(rpl,0,">$<=1-9>",subargs);
  
  return rpl;
}

int main(int argc, char *argv[])
{
  FILE *f;
  int k;
  
  if (argc < 2) usage(); 
    
  macros = tblNew();
  if (!macros) merr("Unable to create table for macro");
  
  body = chsNew();
  if (!body) merr("Unable to create temporary buffer");
  
  f = fopen(argv[1],"r");
  if (!f) merr("Unable to open file");
  
  /* Load text into the buffer */
  text = chsRead(text, f, 'w');
  
  fputs(text,stdout);
  fputs("-----------------\n",stdout);

  /* the |&B| recognizer will get a balanced parenthesis*/
  text = chsSubFun(text, 0,">&Km(<*a>)$(<+a>)(&B())&K(&N)",getmacro);

  tblForeach(macros,k) {
    printf("[%s] = \"%s\"\n",tblKeyS(macros,k),tblValS(macros,k)); 
  }

  /* Note the use of '&*' at the beginning that will make the
  ** search and replace recursive: the replaced text will be
  ** searched again looking for other occurence of the search
  ** pattern.    
  **/
  text = chsSubFun(text, 0,"&*>$(<+a>)(&B())",submacro);
  
  fputs(text,stdout);
  fputs("-----------------\n",stdout);
  
  text = chsFree(text);
  macros = tblFree(macros);
  body = chsFree(body);
  
  exit(0);
}
