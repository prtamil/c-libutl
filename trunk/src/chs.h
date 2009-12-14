/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This sofwtare is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#ifndef CHS_H
#define CHS_H

/*
.v
                     __        
                    |  |        
                 ___|_ |__  ____
                /  __/ __ \/ ___)
               (  (_|  || |\___ \
                \___/__||_|/____/
..

         ===============================
.T             Character strings 
         ===============================
            
.A       Remo Dentato (rdentato@gmail.com)


   .% Overview
   ===========

 C strings have two major drawbacks:
 
  .- They cannot easily resized 
   - They are zero-terminated (meaning that getting the
     lenght of a strings costs O(n))
  ..

 This functions help handling variable lenght string. 

 
   .% Naming Conventions
   =====================
   
  Not all the functions, macros and variables exposed in this include file
are for general use. To distinguish names in the public API from names of
objects reserved for internal use, the following convention is used:
.>
    Public names are written in CamelCase
..


   .% The "block"
   ==================
  
  The following diagram shows the structure of a '|chs| string.

.v 
    __ this is the start of memory block
   |   allocated for each chs string
   |
   |                __  internal cursor
   v               | 
  +------+------+--v---+----------------------------
  | size | len  | cur  |  <--- string ... ---> \0
  +--A---+--A---+------+----------------------------
     |      |           A
     |      |           |__ this is the "string" pointer that is
     |      |               returned and by the chs functions
     |      |
     |      |__ used space (length of the string)
     |
     |__ allocated space     
..

as implemented by the '{=chs_blk_t} structure below.

  The '/string/ part at the end is incremented in steps of '{=chs_blk_inc} bytes.
*/
 
 
#define chs_blk_inc 16

typedef struct {
  long size;
  long len;
  long cur;
  char chs[chs_blk_inc];
} chs_blk_t;

/*
  All the '|chs| functions return a pointer to the '{chs[]} array within the 
'{chs_blk_t} structure. This allows '|chs| strings to be passed to the standard
C string functions.  

  Given a '|chs| string, to get back the associated information the 
macro '{=chs_blk} is used. 

*/

#define chs_blk(s) ((chs_blk_t *)(((char*)(s)) - offsetof(chs_blk_t,chs)))

/* .% Types
   =========

.['|chs_t|]  This is the type of a '|chs| string. It is equivalent to a 
             '|char *| so that it can be passed to any function accepting
             standard C strings.
             Of course the opposite is not true, passing a '|char *| to
             a function expecting a '|chs_t| will most likely result in
             a memory corruption and program crash.  
..
*/

typedef char *chs_t ;

/* .% Auxiliary variables
   ======================
   
   The following defines and variables are used within the '|chs| macros
   and defined in the '<chs.c> file.  
*/

extern chs_blk_t *chs_blk_;
extern chs_t      chs_tmp_;

#define chs_buf_size 1024
extern char chs_buf[chs_buf_size];

/*
.% API
=========

  All public functions have a CamelCase name, the only exception is the
type '{=chs_t}.  Every other identifier that contains an underscore (''_|')
is to be considered as reserved for internal use.

  A key concept to bear in mind is that the address of a '|chs| string may
change when the string is modified.  This makes address of '|chs| strings 
unsuitable to being stored in two different variable at the same time.

  The creation/modification functions take the chs string as first parameter
and can modify its value
*/

/*  .%% Creating/disposing strings
    ''''''''''''''''''''''''''''''
  .['|chsNew(s)|]   Set s to a freshly created, empty '|chs| string and
                    returns it.
  
   ['|chsDup(s)|]   Returns a freshly created '|chs| string, filled with
                    the content of the string '|s|.
                    '|s| can be a '|chs| string or a regular C string.
   
   ['|chsFree(s)|]  Frees the memory allocated for the string '|s| and
                    returns NULL. '|s| is reset to NULL and avoid the
                    risk of accessing de-allocated memory.
  .. 
*/

chs_t chs_setsize(chs_t s, long ndx);
#define chsNew(s) (s = chs_setsize(NULL,0)) 

#define chsDup(s)     chs_Cpy(NULL,s)
#define chsDupL(s,l)  chs_CpyL(NULL,s,l)

#define chsFree(s) \
 ((s) = ((chs_tmp_=(s))? (free(chs_blk(chs_tmp_)), NULL) : NULL))

#define chsLen(s)  ((chs_tmp_=(s))? chs_blk(chs_tmp_)->len  : 0)
#define chsSize(s) ((chs_tmp_=(s))? chs_blk(chs_tmp_)->size : 0)
#define chsCur(s)  ((chs_tmp_=(s))? chs_blk(chs_tmp_)->cur  : 0)


/*  .%% Strings as streams
    ''''''''''''''''''''''
  These functions provide a stream-like access to a '|chs| string.

  .['|chsSeek(s,p,w)|]
        Moves the current cursor in the string at the specified
        offset. The argument '|w| is one of the costants '|SEEK_SET|,
        '|SEEK_END| and '|SEEK_CUR| defined by in '|<stdio.h>|.
  
   ['|chsTells(s)|]
        Returns the offset of the cursor from the beginning of the file. 
   
   ['|chsEof(s)|]  
        Returns true if the cursor is at the end of the string;
        
   ['|chsGetChr(s)|]  
        Returns the character at the current cursor position;

   ['|chsChrAt(s,n)|]  
        Returns the character at the position n. The cursor will be
        moved on the next character;

   ['|chsSetChr(s,n,c)|]  
        Writes the character '|c| at the position '|n|. The cursor will be
        moved on the next character;

  .. 
*/

int    chsSeek   (chs_t dst, long pos, int whence);
size_t chsTell   (chs_t dst);
int    chsEof    (chs_t s);
int    chsGetChr (chs_t s);

char   chsChrAt  (chs_t s, long ndx);

chs_t  chs_SetChr (chs_t s, long ndx, char c) ;
#define chsSetChr(s, n, c) (s = chs_Set(s,n,c))

/*  .%% Modifying strings
    '''''''''''''''''''''
  Functions that add/remove content from a string. Whenever used, indexes
can be negative meaning they start at the end of the string (i.e index '|-1|
is the last character of the string).  
    
  .['|chsCpy(d,s)|]
        Copies the content of the string s in the '|chs| string d.
        
   ['|chsCpyL(d,s,l)|]
        Copies the content of the string s in the '|chs| string d
        up to l characters. 
        
   ['|chsAddChr(d,c)|]
        Appends a character to the '|chs| string d. 
        
   ['|chsAddStr(d,s)|]
        Appends a string to the '|chs| string d. 
        
   ['|chsAddStrL(d,s,l)|]
        Appends a string to the '|chs| string d up to l characters. 
        
   ['|chsInsChr(d,n,c)|]
        Inserts a character in the '|chs| string d at the specified index n. 
        
   ['|chsInsStr(d,n,s)|]
        Inserts a string to the '|chs| string d at the specified index n. 
        
   ['|chsInsStrL(d,n,s,l)|]
        Inserts a string to the '|chs| string d at the specified index n
        up to l characters.
         
   ['|chsCpyFmt(d,f,...)|]
        Format a string according to '|f| (same sintax as the C '|printf()|)
        and copies it into d. 
        
   ['|chsAddFmt(d,f,...)|]
        Format a string according to '|f| (same sintax as the C '|printf()|)
        and appends it at the end of d. 
        
   ['|chsInsFmt(d,n,f,...)|]
        Format a string according to '|f| (same sintax as the C '|printf()|)
        and insert it into d at the speficied index n. 
        
   ['|chsDel(d,b,e)|]
        Deletes the content of the string from the index '|b| to the index '|e|. 
  ..    
*/

chs_t chs_CpyL (chs_t dst, char *src, long len) ;
#define chsCpyL(d, s, l) (d = chs_CpyL(d,s,l))

chs_t chs_Cpy(chs_t dst, char *src) ;
#define chsCpy(d, s) (d = chs_Cpy(d,s))

chs_t chs_AddChr(chs_t dst, char c) ;
#define chsAddChr(d, c) (d = chs_AddChr(d,c))

chs_t chs_AddStrL(chs_t dst, char *src, long len) ;
#define chsAddStrL(d, s, l) (d = chs_AddStrL(d,s,l))
#define chsCatL chsAddStrL

chs_t chs_AddStr(chs_t dst, char *src) ;
#define chsAddStr(d, s) (d = chs_AddStr(d,s))
#define chsCat chsAddStr

chs_t chs_InsChr(chs_t dst, long ndx, char c) ;
#define chsInsChr(d, n, c) (d = chs_InsChr(d,n,c))

chs_t chs_InsStrL(chs_t dst, long ndx, char *src, long len) ;
#define chsInsStrL(d, n , s, l) (d = chs_InsStrL(d,n,s,l))

chs_t chs_InsStr(chs_t dst, long ndx, char *src) ;
#define chsInsStr(d, n, s) (d = chs_InsStr(d,n,s))


#define chsCpyFmt(d,f,...)   (snprintf(chs_buf,chs_buf_size,f,__VA_ARGS__),chsCpy(d,chs_buf)) 
#define chsAddFmt(d,f,...)   (snprintf(chs_buf,chs_buf_size,f,__VA_ARGS__),chsAddStr(d,chs_buf)) 
#define chsInsFmt(d,n,f,...) (snprintf(chs_buf,chs_buf_size,f,__VA_ARGS__),chsInsStr(d,n,chs_buf)) 

chs_t chs_Del (chs_t dst, long from, long to) ;
#define chsDel(d, f, t) (d = chs_Del(d,f,t))

/*  .%% Reading from files
    ''''''''''''''''''''''
  This functions read content of a '|FILE *| into a string.

   .['|chsCpyFile(s,f)|]  Copies the content of the file from the current
                          position to the end of file into the string s.
   
    ['|chsAddFile(s,f)|]  Append to the string s the content of the file
                          from the current position to the end of file.
                          
    ['|chsCpyLine(s,f)|]  Copies the content of the file from the current
                          position to the end of line (\n or \r\n or \n)
                          into the string s.
   
    ['|chsAddLine(s,f)|]  Append to the string s the content of the file
                          from the current position to the end of line (\n
                          or \r\n or \n).
                          
    ['|chsForLines(l,f)|] Reads the content of the file f one lines at the
                          time in the string l and executes the next
                          instruction until the end of file is reached.
                          For example to print lines in a file:
.v
           chs_t l;
           FILE *f;
             ...
           f = fopen("myfile.txt","r");  
           chsForLines(l,f) {
             printf("<%s>\n",l);
           }
           chsFree(l);
           if (f) fclose(f);
             ...
..  
   
   ..

*/

chs_t chs_read(chs_t dst, FILE *f, char how, char what);

#define chsRead(s,f,h)   (s = chs_read(s,f,h,'A'))
#define chsReadln(s,f,h) (s = chs_read(s,f,h,'L'))

#define chsCpyFile(s,f) (s = chs_read(s,f,'w','A'))
#define chsCpyLine(s,f) (s = chs_read(s,f,'w','L'))

#define chsAddFile(s,f) (s = chs_read(s,f,'a','A'))
#define chsAddLine(s,f) (s = chs_read(s,f,'a','L'))

#define chsForLines(l,f)  for (l=chsReadln(l,f, 'w'); chsLen(l) > 0;\
                                                        chsReadln(l,f,'w'))

/* .%% Matching strings
   ''''''''''''''''''''
*/

pmxMatches_t chsMatch(chs_t s, long from, char *pat) ;

typedef char *(*chsSubF_t)(char *mtc, pmxMatches_t cpt);

chs_t chs_SubStr(chs_t s, size_t pos, char *pat, char *rpl) ;
#define chsSubStr(s, n, p, r) (s = chs_SubStr(s,n,p,r))

chs_t chs_SubFun(chs_t s, size_t pos, char *pat, chsSubF_t f);
#define chsSubFun(s, n, p, f) (s = chs_SubFun(s,n,p,f))

/* .%% Other  */

#define chsUpper(s) \
 do { char *p=s; if (p) while (*p) {*p = toupper(*p); p++;}} while(utlZero)
 
#define chsLower(s) \
 do { char *p=s; if (p) while (*p) {*p = tolower(*p); p++;}} while(utlZero)

#define chsReverse(s) \
 do { char *p,*q,t; \
      if ((p=s)) \
        for (q = p+chsLen(p); q-p > 0; p++) { \
          t = *--q ; *q = *p; *p = t; \
        } \
    } while(utlZero)


#endif  /* CHS_H */
