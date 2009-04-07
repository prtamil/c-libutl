/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#ifndef PMX_H
#define PMX_H


/*
.v
                __ __  __ __ __ ___  ___ 
               |  '_ \|  '  '  |\  \/  / 
               |  |_) |  |  |  | /    /  
               |  ___/|__/__/__|/__/\__\ 
               |  |
               |__)
..

            ===============================
.T            Pattern Matching eXpressions 
            ===============================
            
.A         Remo Dentato (rdentato@gmail.com)


.% Overview
""""""""""""
  PMX is a library for strings pattern matching. It uses a set of patterns
that is different from the more commonly used regular expressions.

  One difference with RE is that PMX expressions are never ambigous. This
allows a faster matching algorithm at the expense of some expressive power: 
there are regular expressions that can't be matched in pmx but, at the same
time, there are pmx expressions that can't be matched with regular expressions.

  A key difference with Regular Expressions, is that PMX patterns are 
always /greedy/ and match as much of the string as they can. It is important
to remind this when you get unexpected results in your match.

  Since RE are very well known, we'll refer sometimes to them to explain
how pmx pattern match.  

  The syntax of pmx has been intentionally chosen to be different from RE
to avoid any confusion. 

  The tool <'|pmxshell|> (in the examples folder) allows you to test pmx 
patterns and get a better understanding of their behaviour. 


.% Patterns
""""""""""""
  Every character is a pattern that matches itself with the following
exceptions:

   .['|<|] Introduces a pmx complex pattern.
    
    ['|>|] Ends a complex pattern except when placed at the beginning or at
           the end of the pattern.
    
           At the beginning of a pattern indicates that it  can be matched
           anywhere in the string.  Without it, a PMX pattern will only be
           matched at the beginning of the string.  This is the opposite of 
           what Regular Expressions do: without the '^' character a RE will
           be matched anywhere. 
           
           At the end of the pattern indicates that the pattern has to be
           matched exatly at the end of the string. It is similar to what '$' 
           does at the end of a Regular Expressions.
           
    ['|&|] Introduces a "matching option". It is used to:
    
           .- Escape a special character (e.g. ''|&&|' or ''|&>|')
            - Denote a predefined recognizer (e.g. ''|&f|' it's a pattern
              that matches a decimal number like '|3.2|).
            - Set options while matching (e.g. ''|&i|' for case insensitive
              match or ''|&e|' to define the escape character). 
           ..
           
           Note that '|&| is only to be used with the characters specified
           below. Other tools built on top of PMX could assign a special
           mening to a given character.
    ..  

.%% Predefined character classes
''''''''''''''''''''''''''''''''
  These patterns match characters that are within commonly used sets.

 .['|<a>|]  (isalpha)	matches an alphabetic character
  ['|<c>|]  (iscntrl)	matches a control character
  ['|<d>|]  (isdigit)	matches a digit. Not locale-specific.
  ['|<g>|]  (isgraph)	matches a graphic character, excluding the space character.
  ['|<i>|]  (isascii) matches a character whose code is between 0 and 127
  ['|<k>|]  (isblank)	matches a blank character 
  ['|<l>|]  (islower)	matches a lowercase character
  ['|<p>|]  (ispunct)	matches a punctuation character
  ['|<q>|]  (isalnum)	matches an alphanumeric character
  ['|<r>|]  (isprint)	matches a printable character, including the space character.
  ['|<s>|]  (isspace)	matches a space character
  ['|<u>|]  (isupper)	matches an uppercase character
  ['|<w>|]  (isword)) matches an alphanumeric character or and underscore ''|_'
  ['|<x>|]  (isxdigit) matches an hexadecimal digit. Not locale-specific.
  ['|<.>|]  matches any character (except '|'\0'|).
 .. 

  To match characters that do *not* belong to a given set, use the uppercase
letter.  For example ''|<D>|' matches a character that is not a digit.


.%% User defined character classes
''''''''''''''''''''''''''''''''''
  It is possible to match a character that is in in a given set of characters 
as follows:

 .['|<=|...'|>|]  matches a character that belongs to the specified set
  ['|<!|...'|>|]  matches a character that doesn't belong to the specified set
  ['|<#|...'|>|]  matches a character that doesn't belong to the specified set
                  but skip over escaped characters (see the '|&e| matching
                  option below).
 ..
  
 For example:
 
 .['|<=xA-Ga-g>|] matches one of the following characters: '|ABCDEFGabcdefgx|
  ['|<!xyz>|]     matches anything except the characters '|x|, '|y| and '|z|
 ..

  If any of the characters '&', '>' or '-' are part of the set to be specified,
they must be preceeded by '&'.  For example:

 .['|<=A&-B>|] matches '|A|', '|B|' or '|-|'
  ['|<=<&>|]   matches '|<|' or '|>|'
 ..

  The pattern "'|<j...>|" (and its negation "'|<J...>|") is meant to be
used by tools that generate pmx expressions and not for expressions created
"by hand". It assumes that the patterns are sorted so that tests is faster.  

  For example, "'|<jA-Z_a-z>|" will work properly and will be slightly faster
than "'|<=A-Z_a-z>|"  while "'|<jA-Za-z_>|"  will not work! 

  My advice is to not use it, unless you know exactly what you're doing.

  
.%% Alternative strings
'''''''''''''''''''''''
  To match one of multiple strings use the pattern '|<$...$...$...>|'. For
example:
  
 .['|<$abc$def>|] matches "'|abc|" or "'|def|"
 ..
   
  If the characters '&', '>' or '$' are part of the strings specified,
they must be preceeded by '&'.  For example:

 .['|<$a&$b$c&>d>'] matches ''|a$b|' or  ''|c>d|'.
 ..
   
.%% Repetitions
'''''''''''''''
  A pattern may be repeated using ''|?|', ''|*|' and  ''|+|':
  
  .['|?|] Repeat 0 or 1 times, i.e make the pattern optional.
   ['|*|] Repeat 0 or n times
   ['|+|] Repeat 1 or n times
  ..

  Examples:
  
  .['|<+d>|]  matches a sequense of digits
   ['|x<?d>|] matches '|x| optionally followed by a digit.
   ['|<=A-Za-z_><*=A-Za-z0-9_>'] a C identifier
   ['|<+$ab$cd>']  matches "'|ab|" or "'|cd|" or "'|abcd|" 
                   or "'|cdcdabcdab|" etc.
  ..
  
.%% Recognizers
'''''''''''''''
  Recognizers are patterns that match a specific object (for example
"'|&q|" for a quoted string).
  
  .['|&b|'/xy/] Braced string. Matches a string enclosed by the characters
               /x/ and /y/.
               
               If /x/ and /y/ are different there must be a balanced number
               of delimiters to complete the match.  For example the 
               pattern "'|%b()|" matches the entire string
               "'|(defun f (x) (+ x 1))|".
               
               If /x/ and /y/ are equal, the match stops at the first occurence
               of the delimiter character.
               
               The recognires '|&b| honours the escape character set with '|&e|
               (see below)
                
   ['|&d|]     A possibly signed integer (e.g. : "'|32|", "'|-15|", "'|+7|")
   ['|&f|]     A possibly signed decimal number. It will also match integers
               (e.g. : '|3.2|, '|-.5|, '|+7|).
               
   ['|&k|]     A sequence of blanks (space or tab)
   ['|&l|]     The rest of the line up to the newline character(s) (see below)
   ['|&n|]     The end of the line. Matches any of "'|\r\n|", "'|\r|" or "'|\n|"
   ['|&q|]     A single or double quoted string (including the quotes). To
               match just one type of quoted string use the "'|&b|" recognizer
               (e.g. "'|&b'`'|" for single quoted strings).
 
               The recognizer '|&q| honours the escape character set with '|&e|
               (see below).
               
   ['|&s|]     A sequence of spaces (space, tab, newlines, vertical tabs, etc)
   ['|&x|]     An hexadecimal number (e.g. "'|C1A0|")
  ..

  Use the uppercase corresponding letter to make it optional. For example:
  
  .['|a&K+&Kb|] matches '|a+b|, '|a + b|, '|a+   b|, etc.
   ['|x&D|] matches '|x|, '|x42|, '|x+1|, etc.
   ['|&f<?=eE>&F|] matches '|-3.2|, '|+3.1E-52|', etc
  .. 


.%% Matching options
''''''''''''''''''''

  .['|&e|'/x/] Set the character '/x/ as the escape character. For example,
              given the string '|"abc!"def"|': 
              
                  .['|&q|]     matches '|"abc!"| 
                  .['|&e!&q|]  matches '|"abc!"def"|
                  ..
               
   ['|&E|]    Clear the escape character.
   ['|&G|]    Set the /goal/ of the match. This cand be used as a form
              of lookahead. For example "'|xy&G<D>|" will match the string
              "'|xy|" only if the next character is not a digit.
   ['|&i|]    Start case insensitive match.
   ['|&I|]    Stop case insensitive match.
  ..

.%% Submatching captures
''''''''''''''''''''''''
  Submatches can be denoted using parenthesis. There can be up to 9 
submatches. Submatches can be nested. Examples:

  .['|(&f)(<?$in$cm>)|]    matches "'|2.0cm|", "'|-3in|", "'|4.1|" etc.;
                           saves the number as capture 1 and the unit of
                           measure as capture 2.
                        
   ['|=((<?=+&->)<+d>))|]  matches "'|=-5|", "'|=42|", "'|=+1|" etc.;
                           saves the signed number as capture 1 and the
                           sign as capture 2;
  .. 


.%% Alternative expressions
'''''''''''''''''''''''''''
  Two pmx expressions can be joined with "'|&`||" to indicate that if the 
first expression fails, the second must be tried.

  In other words, if '|A| and '|B| are two generic pmx expressions, the 
expression '|A&`|B| matches if '|A| matches or if '|A| fails and '|B| matches. 


.%% Expression length
'''''''''''''''''''''
  The operator "'|&:|'/x/" is meant to be used, in conjunction with '|&`||,
by tools that generate pmx expressions and not for expressions created
"by hand".

  The value /x/ is the length of the expression, this makes faster skipping
over an alternative expressions that failed.


.% Tools
""""""""
  The '|examples| directory contains two useful tools for pmx.
  
  .[pmxshell]   an interactive shell that allows to define a set of 
                pmx patterns and test strings against them.  It is 
                intended to be used to ensure that a set of patterns
                behaves as it is supposed to.
               
   [pmx2c]      a preproprocessor that modifies the way the switch
                statment works allowing cases that are pmx patterns
                rather than constants. 
  ..
  
  You should read about them to better understand how to use pmx.
  
*/

/*
.% pmx API
""""""""""

*/

#define pmxCaptMax 10

typedef size_t pmxMatches[pmxCaptMax+1][2];

typedef pmxMatches *pmxMatches_t;

/*
.%% Matching on a string
''''''''''''''''''''''''
.{{
*/
pmxMatches_t pmxMatchStr(char *text, char *p);

/*
.}}

.%% Get matched text
''''''''''''''''''''
.{{ */

int           pmxMatched (pmxMatches_t mtc);
unsigned char pmxToken(pmxMatches_t mtc);
pmxMatches_t  pmxMatchStr(char *text, char *p);
size_t        pmxLen     (pmxMatches_t mtc, unsigned char n);
size_t        pmxStart   (pmxMatches_t mtc, unsigned char n);
size_t        pmxEnd     (pmxMatches_t mtc, unsigned char n);

/* .}} 

.%% Function Scanner
~~~~~~~~~~~~~~~~~~~~

  The function '{pmxScanStr()} can be used to repeatedly match a pattern
against a text.
  
  The pattern is usually made by a list of expression joined with the '|&`||' 
operator.
  
  On a successful match, the callback function is called passing the matching
results as parameters.  

  If the callback function returns zero, the pattern is matched again
starting from the first character after the end of the previous match, 
otherwise '{pmxScanStr()} returns that value. 

  Look at the '|pmxshell.pmx| example for more details on how to use this function 

.{{ */

typedef int (*pmxScanFun_t)(char *txt, pmxMatches_t mtc);
int pmxScanStr(char* text, char *ptrn, pmxScanFun_t f);

/* .}} */


/*
.%% Scanner
~~~~~~~~~~~

  pmx offers another format for scanners that directly refers to "tokens".
  
  

.v
   pmxScanner (string, token_patterns, token_handlers)
..

  Where '|token_patterns| i

*/

#define pmxTok_defcase(y) 0##y 
#define pmxTok_defstr(y)  #y 
#define pmxTokCase(y) case pmxTok_defcase(y)

extern char *pmx_tmpstr;
extern char *pmx_tmpptrn;
extern pmxMatches_t pmx_tmpmtc;

#define pmxScanner(s,p,c) do {\
    for (pmx_tmpstr = s, pmx_tmpptrn =  p, \
                       pmx_tmpmtc = pmxMatchStr(pmx_tmpstr, pmx_tmpptrn); \
         *pmx_tmpstr && pmx_tmpmtc; \
         pmx_tmpstr += pmxLen(pmx_tmpmtc,0), \
                       pmx_tmpmtc = pmxMatchStr(pmx_tmpstr, pmx_tmpptrn)) \
    { switch (pmxToken(pmx_tmpmtc)) { c } ; break; } \
    pmx_tmpstr = ""; \
  } while (pmx_tmpstr == NULL)

#define pmxTokStart(x) (pmx_tmpstr+pmxStart(pmx_tmpmtc,x))
#define pmxTokEnd(x)   (pmx_tmpstr+pmxEnd(pmx_tmpmtc,x))
#define pmxTokLen(x)   pmxLen(pmx_tmpmtc,x)
#define pmxTokSet(x,y) "&|" x pmxTok_defstr(&\y)

#define pmxScannerBegin(s) do {\
    for (pmx_tmpstr = s, pmx_tmpptrn =  
    
#define pmxTokSwitch  , \
                       pmx_tmpmtc = pmxMatchStr(pmx_tmpstr, pmx_tmpptrn); \
         *pmx_tmpstr && pmx_tmpmtc; \
         pmx_tmpstr += pmxLen(pmx_tmpmtc,0), \
                       pmx_tmpmtc = pmxMatchStr(pmx_tmpstr, pmx_tmpptrn)) \
    { switch (pmxToken(pmx_tmpmtc)) { 
    
#define pmxScannerEnd } ; break; } \
    pmx_tmpstr = ""; \
  } while (pmx_tmpstr == NULL)


#endif
