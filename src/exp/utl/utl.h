/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**
*/

#ifndef UTL_H
#define UTL_H

/* .% Overview
** ===========
** .v
**                           ___   __
**                       ___/  (_ /  )
**                ___  _(__   ___)  /
**               /  / /  )/  /  /  /
**              /  /_/  //  (__/  /
**             (____,__/(_____(__/
** ..
**
**   This file ('|utl.h|) provide the following basic elements:
**
**  .[Logging]        To print logging traces during program execution.
**                    It offers multilevel logging similar to '|log4j|
**                    but limited to files.
**
**   [Unit Testing]   A simple framework to create unit tests. Tests output
**                    is compliant with the TAP '(Test Anything Protocol)
**                    standard.
**
**   [Error handling] Simple handling for serious errors.
**
**   [Finite State Machine]
**                    Macros to use FSM as if they were a native C control
**                    structure (similar to switch).
**
**   [Exceptions]     A simple implementation of try/catch. Similar to C++.
**
**   [Guarded memory allocation]
**                    Replacement for malloc(), calloc(), realloc() and free()
**                    that account and report about misuse of memory.
**  ..
**
** .% How to add utl.h to your project
** ===================================
**
**
**  
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <string.h>
#include <stdarg.h>
#include <stddef.h>

#include <setjmp.h>


#ifdef UTL_NOMEMCHECK
#ifdef UTL_MEMCHECK
#undef UTL_MEMCHECK
#endif
#endif

#ifdef UTL_MEMCHECK
#ifdef UTL_NOLOGGING
#undef UTL_NOLOGGING
#endif
#endif

#ifdef NDEBUG
#ifdef DEBUG
#undef DEBUG
#endif
#endif

#ifdef UTL_UNITTEST
#ifndef DEBUG
#define DEBUG
#endif
#endif


/* .% Variables
** ============
**
**  A set of variable for generic use provided by for convenience.
**
**  .[utlEmptyFun]  A pointer to a do-nothing function that can be used
**                  as a generic placeholder (or NULL indicator) for
**                  function pointers. This can be useful as the C standard
**                  doesn't guarantee that one could mix pointers to objects
**                  with pointers to function (even if in reality this is
**                  practically always the case).  
**  ..
*/

int utlEmptyFun(void); 

/*  .[utlEmptyString]  A pointer to the empty string "" that provides unique
**                     representation for the empty string.  
**  ..
*/

extern char *utlEmptyString;

/*   .[utlZero]  Is a constant whose value is 0 and that is to be used in
**               idioms like '|do { ... } while (utlZero)|.
**               This is useful to avoid compilers warning about testing
**               constant values.
**   ..
*/
  
#ifdef __GNUC__
#define utlZero 0
#else
extern const int utlZero;
#endif

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

/* .% Messages Output
** ==================
**
** Log messages and unit tests output normally go on '{stderr}.
** This could be not suitable for applications that are not attached to 
** a console (e.g. background servers, GUI applications).
** 
** Functions and variables in this section allows you to define where to
** redirect those messages.
**
**   '{=utl_output} is a global variable holding the current file to be
** used when printing a debug or test message.   It's not intended be used
** directly, use the macro '{=utlOut} instead if you need to refer to 
** the file.
**
**   Actually I see no reason why you should need it, nut just in case ... 
*/

extern FILE *utl_output;
#define utlOut (utl_output? utl_output: stderr)

/*   The '/public/ function to set the output file, is '{=utlSetOutput()}
** that takes the filename as input, open the file and and sets '{utl_output}
** to it.  If a previous file had been opened, it will be closed. 
**
**   Passing '|NULL| as argument closes the current output file (if there
** was one opened) and sets '{utl_output} to '|NULL|, which implies that the
** default '|stderr| will be used from that moment on.
** 
*/
#define utlSetOutput(fname) ((utl_output ? fclose(utl_output) : 0),\
                             (utl_output = (fname? fopen(fname,"w"): NULL)))


/* .% Errors Handling
** ==================
**  Functions to handle serious errors.  
**  The error number is used to differentiate between errors:
**
**   Error codes are decimal numbers between 0 and 9999. The most significant
**  dgit determines which handler is invoked. 
*/

/* '{=utlErrInternal} is provided to avoid repeating the string over
** and over again in the code.
*/

extern char *utlErrInternal; 

#define utl_MAXTRY 8
extern jmp_buf utl_jmp_lst[utl_MAXTRY];
extern int     utl_jmp_cnt;
extern int     utlErr;

/* .%% Try/Catch
** ~~~~~~~~~~~~~~~~~~~~~~~
**  Simple implementation of try/catch. Up to utl_MAXTRY (8) level of nested
** try/catch are allowed but if you use so many level you have have most
** probably big problems. Try to stay simple!
**
**   utlTry {
**      ... code ...
**      if (something_failed) utlThrow(execption_num)  // must be > 0 
**      some_other_func(); // you can trhow exceptions from other functions 
**      ... code ...
**   }  
**   utlCatch(3) {
**      ... code ...
**   }
**   utlCatch(4) {
**      ... code ...
**   }
**   utlCatchAny {  // None of the above! If not present the exception
**                  // will be thrown again at the upper level
**                  // if no handler is found the program exits
**      ... code ...
**   }
**   utlTryEnd ;
** 
*/ 

#define utl_jmp_next ((utl_jmp_cnt < utl_MAXTRY)? utl_jmp_cnt++ : utl_jmp_cnt)
#define utl_jmp_prev ((utl_jmp_cnt > 0)         ? utl_jmp_cnt-- : utl_jmp_cnt)

#define utlTry      do{ int caught = 0; \
                        switch (setjmp(utl_jmp_lst[utl_jmp_cnt])) {  \
                          case 0: if (utl_jmp_cnt<utl_MAXTRY)        \
                                    utl_jmp_cnt++;}                  \
                                  utlErr = 0; caught = 0;
                                  
                              
#define utlCatch(e)               break;                         \
                          case e: caught = 1;
                        
#define utlCatchAny                break;                        \
                          default: caught = 1;
                        
#define utlTryEnd     }                                          \
                      if (caught) utlErr = 0;                    \
                      else if (utlErr) utlThrow(utlErr);         \
                      else if (utl_jmp_cnt > 0) utl_jmp_cnt--;   \
                    } while (utlZero)
                      

/* 
**  The function '{utlError} jumps out of the current function
** and executes the error handler function. If no handler has 
** been defined, it exits
**
*/

#define utlThrow(e) (utlErr=e, (utl_jmp_cnt && utlErr? \
                                  longjmp(utl_jmp_lst[--utl_jmp_cnt], utlErr):\
                                  exit(utlErr)))

#define utlError(e,m)  (logError("ERR: %d %s",e,m), utlThrow(e))


/* .% UnitTest
** ===========
**
**   These macros will help you writing unit tests.  The log produced
** is '<TAP 1.3=http://testanything.org> compatible.
**
**   They are available only if the symbol '|UTL_UNITTEST| is defined before
** including the '|utl.h| header.
** 
**   '{UTL_UNITTEST} implies '{DEBUG}
*/

#ifdef UTL_UNITTEST

#define TSTWRITE(...) (fprintf(utlOut,__VA_ARGS__),fflush(utlOut))

#define TSTTITLE(s) TSTWRITE("TAP version 13\n#\n# ** %s - (%s)\n",s,__FILE__)

/* Tests are divided in sections introduced by '{=TSTSECTION(title)} macro.
** The macro reset the appropriate counters and prints the section header 
*/

#define TSTSECTION(s) if ((TSTSTAT(), TSTGRP = 0, TSTSEC++, TSTPASS=0, \
                       TSTWRITE("#\n# * %d. %s (%s:%d)\n", \
                                TSTSEC, s,__FILE__, __LINE__)),!utlZero)

/* to disable an entire test section, just prepend ''|_|' or ''|X|'*/
 
#define _TSTSECTION(s) if (utlZero)  
#define XTSTSECTION(s) if (utlZero)  

/* In each section, tests can be logically grouped so that different aspects
** of related functions can be tested.
*/

#define TSTGROUP(s) if ( TSTNUM=0, \
                     TSTWRITE("#\n# *   %d.%d %s\n", TSTSEC, ++TSTGRP, s),\
                     TSTGRP+1)
                     
/* to disable an intere test group , just prepend ''|_|' or '|X|' */
#define _TSTGROUP(s) if (utlZero)  
#define XTSTGROUP(s) if (utlZero)  

/* You may want to disable just a block of instructions */
#define TSTBLOCK if (!utlZero) 
#define _TSTBLOCK if (utlZero) 
#define XTSTBLOCK if (utlZero) 
                     
/* The single test is defined  with the '|TST(s,x)| macro.
**   .['|s|] is a short string that identifies the test
**    ['|x|] an assertion that has to be true for the test to succeed.
**   ..
*/
#define XTST(s,x)

#define TST(s,x) (TST_DO(s,(TSTSKP? 1 : (x))), TST_WRDIR, TSTWRITE("\n"), TSTRES)

#define TST_DO(s,x) (TSTRES = (x), TSTGTT++, TSTTOT++, TSTNUM++,\
                     TSTPASSED = (TSTPASSED && (TSTRES || TSTTD)),\
                     TSTWRITE("%s %4d - %s (:%d)",\
                              (TSTRES? (TSTGPAS++,TSTPASS++,TSTOK) : TSTKO),\
                               TSTGTT, s, __LINE__))

#define TST_WRDIR (TSTSKP ? (TSTNSK++, TSTWRITE(" # SKIP %s",TSTSKP)) \
                          : (TSTTD ? (TSTNTD++, (TSTWRITE(" # TODO %s%s",TSTTD,\
                                                (TSTRES?TSTWRN:utlEmptyString)))) \
                                   : 0) )


#define TSTFAILED  (!TSTRES)

/* You can skip a set of tests giving a reason.
** Nested skips are not supported!
*/
#define TSTSKIP(r) for (TSTSKP = (r) ; TSTSKP; TSTSKP = NULL)

#define TSTTODO(r) for (TSTTD = (r) ; TSTTD; TSTTD = NULL)

#define TSTNOTE(...) (TSTWRITE("#      "), TSTWRITE(__VA_ARGS__), TSTWRITE("\n"))

#define TSTONFAIL(...) (TSTRES? 0 : (TSTNOTE(__VA_ARGS__)))

#define TSTBAILOUT(x,r) ((x)? 0 : (TSTWRITE("Bail out! %s",r), exit(1)))

/* At the end of a section, the accumulated stats can be printed out */
#define TSTSTAT() \
          (TSTTOT == 0 ? 0 : (\
           TSTWRITE("#\n# SECTION %d OK: %d/%d\n",TSTSEC,TSTPASS,TSTTOT),\
           TSTTOT = 0))

/* At the end of all the tests, the accumulated stats can be printed out */
#define TSTDONE() if (TSTGTT > 0) { TSTSTAT(); \
                    TSTWRITE("#\n# TOTAL OK: %d/%d\n",TSTGPAS,TSTGTT);\
                    TSTWRITE("#\n# TEST SET: %s \n",TSTPASSED ? "PASSED" : "FAILED");\
                    TSTWRITE("#\n1..%d\n",TSTGTT),fflush(utlOut);\
                  }

/* Execute a statement if a test succeeded */
#define TSTIF_OK  if (TSTRES)

/* Execute a statement if a test failed */
#define TSTIF_NOTOK if (!TSTRES)

static int TSTRES   = 0;  /* Result of the last performed '|TST()| */
static int TSTNUM   = 0;  /* Last test number */
static int TSTGRP   = 0;  /* Current test group */
static int TSTSEC   = 0;  /* Current test SECTION*/
static int TSTTOT   = 0;  /* Number of tests executed */
static int TSTGTT   = 0;  /* Number of tests executed (Grand Total) */
static int TSTGPAS  = 0;  /* Number of tests passed (Grand Total) */
static int TSTPASS  = 0;  
static int TSTBAIL  = 0;  
static int TSTPASSED  = 1;  
static int TSTNSK   = 0;  
static int TSTNTD   = 0;  

static char       *TSTSKP = NULL;
static char       *TSTTD  = NULL;
static const char *TSTOK  = "ok    ";
static const char *TSTKO  = "not ok";
static const char *TSTWRN = " (passed unexpectedly!)";

#else /* UTL_UNITTEST */

#define TSTWRITE(...) 

#define TSTTITLE(s) 

#define  TSTSECTION(s) if (utlZero)  
#define _TSTSECTION(s) if (utlZero)  
#define XTSTSECTION(s) if (utlZero)  

#define  TSTGROUP(s) if (utlZero)  
#define _TSTGROUP(s) if (utlZero)  
#define XTSTGROUP(s) if (utlZero)  

#define  TSTBLOCK if (utlZero) 
#define _TSTBLOCK if (utlZero) 
#define XTSTBLOCK if (utlZero) 
                     
#define TST(s,x) 
#define TSTTODO(s,x,r)
#define TSTFAILED  (1)
#define TSTSKIP(x,r)
#define TSTENDSKIP

#define TSTNOTE(...)
#define TSTONFAIL(...)

#define TSTBAILOUT(x,r)

#define TSTDONE() 

#define TSTIF_OK  if (utlZero)
#define TSTIF_NOTOK if (utlZero)


#endif /* UTL_UNITTEST */

/* .% Logging
** ==========
**
** While the debugging functions are meant to be used during the
** development process, logging functions are intended to be used
** in production, after a stable  version of the application has
** been released.
** 
** These functions are modeled after the widely used log4j
** framework but only offers logging to local files.
*/

/* Logging functions are available unless the symbol '{=UTL_NOLOGGING}
** has been defined before including '|utl.h|.
*/

#define log_All    0
#define log_Debug  1
#define log_Info   2
#define log_Warn   3
#define log_Error  4
#define log_Fatal  5
#define log_Msg    6
#define log_Off    7

#ifndef UTL_NOLOGGING
#include <time.h>
#include <ctype.h>

extern int         log_level;
extern char        log_timestr[32];
extern time_t      log_time;
extern char const *log_abbrev[];

/* .%% Logging levels
** ~~~~~~~~~~~~~~~~~~
**
**   Logging levels are hierarchical and structured as in log4j. The variable 
** '{=log_level} contains the current logging level.  Logging is off by default.
**
**   Use '{=logLevel()}    to set the desired level of logging.
**   Use '{=logLevelEnv()} to set the desired level of logging based on an
**                         enviroment variable.
*/

#define logLevel(level)         (log_level = (log_##level))
#define logLevelEnv(var,level)  (log_level = log_levelenv(var,log_##level))

int log_levelenv(const char *var, int level);

/*
** The table below shows whether a message of a certain level will be
** printed (Y) or not (N) given the current level of logging.
** .v
**                       message level 
**                    DBG INF WRN ERR FTL
**               DBG   Y   Y   Y   Y   Y
**               INF   N   Y   Y   Y   Y
**      current  WRN   N   N   Y   Y   Y
**      logging  ERR   N   N   N   Y   Y
**       level   FTL   N   N   N   N   Y
**               ALL   Y   Y   Y   Y   Y
**               OFF   N   N   N   N   N
** ..
*/

/* .%% Logging format
** ~~~~~~~~~~~~~~~~~~
** 
** Log files have the following format:
** .v
**     <date> <time> <level> <message>
** ..
**
**  For example:
** .v
**     2009-01-29 13:46:02 ERR An error!
**     2009-01-29 13:46:02 FTL An unrecoverable error
** ..
**
*/

/* .%% Setting the log file
** ~~~~~~~~~~~~~~~~~~~~~~~~
**
**   By default, logging messages will be sent to stderr. The internal
** variable '{=log_file} holds the file descriptor of the file the log
** messages should be sent to. 
**   Don't use it in your program, if you need a pointer to the log file,
** you should use the '{=logFile} macro.
*/

extern FILE *log_file;
#define logFile         (log_file? log_file: stderr) 

/*    Log files can be opened in "write" or "append" mode as any normal file 
** using the '{=logOpen()} function.
** For example:
** .v  
**   logOpen("file1.log","w") // Delete old log file and create a new one
**   ...
**   logOpen(NULL,NULL); // Close log file, send next messages to stderr
**   ... 
**   logOpen("file1.log","a") // Append to previous log file
** .. 
*/

#define logOpen(fname,mode) ((log_file? fclose(log_file) : 0),\
                                (log_file = fname? fopen(fname,mode) : NULL))

#define logClose() logOpen(NULL,NULL)

/*   To actually write a message on the log file, use the '{=logWrite()}
** function as if it was a '|printf()| with the exception that the first
** paratmeter is the level of the message.
** Example:
** .v
**    logWrite(log_Info,"Something weird at %d is happening", counter);
** ..
*/

#define logWrite(lvl,...) \
       (lvl >= log_level  \
          ? (time(&log_time),\
             strftime(log_timestr,32,"%Y-%m-%d %X",localtime(&log_time)),\
             fprintf(logFile,"\n%s %s ",log_timestr, log_abbrev[lvl]),\
             fprintf(logFile,__VA_ARGS__),\
             fflush(logFile)\
            )\
          : 0)

/* You can also use one of the following functions that won't require you 
** to pass the message level as parameter:
*/          
#define logDebug(...)    logWrite(log_Debug, __VA_ARGS__)
#define logInfo(...)     logWrite(log_Info,  __VA_ARGS__)
#define logWarn(...)     logWrite(log_Warn,  __VA_ARGS__)
#define logError(...)    logWrite(log_Error, __VA_ARGS__)
#define logFatal(...)    logWrite(log_Fatal, __VA_ARGS__)
#define logMessage(...)  logWrite(log_Msg,   __VA_ARGS__)

/* If you want to add something to the log file without creating a new entry
** in the log file, you can use the '{=logMessage()} function. 
*/
#define logNote(...)  (fprintf(logFile,__VA_ARGS__), fflush(logFile))

#define logIndent     "\n                        "    
#define logContinue(...)  (fputs(logIndent,logFile),logNote(__VA_ARGS__))                       

/*   To ease text alignment in the log, the string '{=logIndent} contains 
** the spaces needed to pass the date, time and type field.
** For example:
** .v
**   logError("Too many items at counter %d (%d)",numcounter,numitems);
**   logContinue("Occured %d times",times++);
** ..
** will produce:
** .v
**     2009-01-29 13:46:02 ERR Too many items at counter 9 (5)
**                             Occured 3 times
** ..
*/

#define logIf(lvl) if (log_level >= log_##lvl)

#else

#define logLevel(level)         (utl_output = utl_output)
#define logLevelEnv(v,l)        (utl_output = utl_output)
#define logFile stderr          (utl_output = utl_output)
#define logOpen(fname,mode)     (utl_output = utl_output)
#define logClose()              (utl_output = utl_output)
#define logWrite(lvl,...)       (utl_output = utl_output)
#define logDebug(...)           (utl_output = utl_output)
#define logInfo(...)            (utl_output = utl_output)
#define logWarn(...)            (utl_output = utl_output)
#define logError(...)           (utl_output = utl_output)
#define logFatal(...)           (utl_output = utl_output)
#define logMessage(...)         (utl_output = utl_output)

#define logIf(x) if (utlZero)

#endif /*- UTL_NOLOGGING */

#ifdef NDEBUG
#undef logDebug
#define logDebug(...)
#endif

#define _logDebug(...)

/* dbgmsg shouldn't be used */
#define  dbgmsg  logDebug
#define _dbgmsg _logDebug

/*  .% Finite state machine
**  =======================
**
**  Macros to embed Finite state machine into C programs.
**
** .v
**      fsmStart(FSM_NAME) {
**        fsmState(x) { ...
**                   if (c == 0) fsmGoto(z);
**                   fsmGoto(y);
**        }
**
**        fsmState(y) { ...
**                   fsmExit(FSM_NAME);  // exit from the FSM
**        }
*
**        fsmState(z) { ...
**                   fsmGosub(t);
**        }
**
**        fsmState(t) { ...
**                   fsmReturn;  // Go back to the caller state
**        }
**      }
**      fsmEnd(FSM_NAME);
** ..
**
**   It's a good practice to include a graphic of the FSM in the technical
** documentation (e.g including the GraphViz description in comments).
*/

#define fsmStart(x) for(;;){\
          int utl_fsmcur; \
          int utl_fsmcnt; \
          int utl_fsmret; \
          int utl_fsmrets[16]; \
          for(utl_fsmcnt=0;utl_fsmcnt<16;utl_fsmcnt++) \
            utl_fsmrets[utl_fsmcnt] = 0;\
          for(utl_fsmret=0,utl_fsmcnt=0;;) { \
            goto fsm_##x##_s;\
            fsm_##x##_s : utl_fsmcur = __LINE__ ;  \
                 if (!utl_fsmret || (utl_fsmret == utl_fsmcur && !(utl_fsmret=0)))
                               


#define fsmState(x) \
   fsm_##x##_s : utl_fsmcur = __LINE__ ;  \
                 if (!utl_fsmret || (utl_fsmret == utl_fsmcur && !(utl_fsmret=0)))
                               
#define fsmGoto(x)  goto fsm_##x##_s
#define fsmGosub(x) do { \
                      if (utl_fsmcnt < utl_fsmmax) \
                        utl_fsmrets[utl_fsmcnt++] = utl_fsmcur; \
                      goto fsm_##x##_s; \
                    } while (utlZero) 
                  
#define fsmReturn do { \
                    utl_fsmret = (utl_fsmcnt > 0? utl_fsmrets[--utl_fsmcnt] : 0);\
                    continue; \
                  } while (utlZero) 

#define fsmExit(x) goto fsm_##x##_e 

#define fsmEnd(x) fsm_##x##_e: utl_fsmcnt=0; utl_fsmrets[0]+=0; break;} break;} 




/*  .% Traced memory check
**  ======================
*/
#define utlMemInvalid    -2
#define utlMemOverflow   -1
#define utlMemValid       0
#define utlMemNull        1

#ifdef UTL_MEMCHECK
void *utl_malloc  (size_t size, char *file, int line );
void *utl_calloc  (size_t num, size_t size, char *file, int line);
void *utl_realloc (void *ptr, size_t size, char *file, int line);
void  utl_free    (void *ptr, char *file, int line );
void *utl_strdup  (void *ptr, char *file, int line);

int utl_check(void *ptr,char *file, int line);

#ifdef UTL_C
/*************************************/

static char *BEG_CHK = "\xBE\xEF\xF0\x0D";
static char *END_CHK = "\xDE\xAD\xC0\xDA";
static char *CLR_CHK = "\xDE\xFA\xCE\xD0";

static size_t utl_mem_allocated = 0;

typedef struct {
   size_t size;
   char   chk[4];
   char   data[4];
} utl_mem_t;

#define utl_mem(x) ((utl_mem_t *)((char *)(x) -  offsetof(utl_mem_t, data)))

int utl_check(void *ptr,char *file, int line)
{
  utl_mem_t *p;
  
  if (ptr == NULL) return utlMemNull;
  p = utl_mem(ptr);
  if (memcmp(p->chk,BEG_CHK,4)) { 
    logError("Invalid or double freed %p (%u %s %d)",p->data,utl_mem_allocated, file, line);     
    return utlMemInvalid; 
  }
  if (memcmp(p->data+p->size,END_CHK,4)) {
    logError("Boundary overflow detected %p [%d] (%u %s %d)",p->data, p->size, utl_mem_allocated, file, line); 
    return utlMemOverflow;
  }
  logInfo("Valid pointer %p (%u %s %d)",ptr, utl_mem_allocated, file, line); 
  return utlMemValid; 
}

void *utl_malloc(size_t size, char *file, int line )
{
  utl_mem_t *p;
  
  if (size == 0) logWarn("Shouldn't allocate 0 bytes (%u %s %d)",utl_mem_allocated, file, line);
  p = malloc(sizeof(utl_mem_t) +size);
  if (p == NULL) {
    logError("Out of Memory (%u %s %d)",utl_mem_allocated, file, line);
    return NULL;
  }
  p->size = size;
  memcpy(p->chk,BEG_CHK,4);
  memcpy(p->data+p->size,END_CHK,4);
  utl_mem_allocated += size;
  logInfo("alloc %p [%d] (%u %s %d)",p->data,size,utl_mem_allocated, file, line);
  return p->data;
};

void *utl_calloc(size_t num, size_t size, char *file, int line)
{
  void *ptr;
  
  size = num * size;
  ptr = utl_malloc(size,file,line);
  if (ptr)  memset(ptr,0x00,size);
  return ptr;
};

void utl_free(void *ptr, char *file, int line)
{
  utl_mem_t *p=NULL;
  
  switch (utl_check(ptr,file,line)) {
    case utlMemNull  :    logInfo("free NULL (%u %s %d)", utl_mem_allocated, file, line);
                          break;
                          
    case utlMemValid :    p = utl_mem(ptr); 
                          memcpy(p->chk,CLR_CHK,4);
    case utlMemOverflow : utl_mem_allocated -= p->size;
                          free(p);
                          logInfo("free %p [%d] (%u %s %d)",ptr,p?p->size:0,utl_mem_allocated, file, line);
                          break;
  }
}

void *utl_realloc(void *ptr, size_t size, char *file, int line)
{
  utl_mem_t *p;
  
  if (size == 0) {
    logInfo("realloc %p -> [0] (%u %s %d)",ptr,utl_mem_allocated, file, line);
    utl_free(ptr,file,line); 
  } 
  else {
    switch (utl_check(ptr,file,line)) {
      case utlMemNull     : logInfo("realloc NULL (%u %s %d)",utl_mem_allocated, file, line);
                            return utl_malloc(size,file,line);
                          
      case utlMemValid    : p = utl_mem(ptr); 
                            p = realloc(p,sizeof(utl_mem_t) + size); 
                            if (p == NULL) {
                              logError("Out of Memory (%u %s %d)",utl_mem_allocated, file, line);
                              return NULL;
                            }
                            utl_mem_allocated -= p->size;
                            utl_mem_allocated += size; 
                            logInfo("realloc %p [%d] -> %p [%d] (%u %s %d)",ptr, p->size, p->data, size, utl_mem_allocated, file, line);
                            p->size = size;
                            memcpy(p->chk,BEG_CHK,4);
                            memcpy(p->data+p->size,END_CHK,4);
                            ptr = p->data;
                            break;
    }
  }
  return ptr;
}


void *utl_strdup(void *ptr, char *file, int line)
{
  char *dest;
  size_t size;
  
  if (ptr == NULL) {
    logWarn("strdup NULL (%u %s %d)", utl_mem_allocated, file, line);
    return NULL;
  }
  size = strlen(ptr)+1;

  dest = utl_malloc(size,file,line);
  if (dest) memcpy(dest,ptr,size);
  logInfo("strdup %p [%d] -> %p (%u %s %d)",ptr, size, dest, utl_mem_allocated, file, line);
  return dest;
}
#undef utl_mem

/*************************************/
#endif

#define malloc(n)     utl_malloc(n,__FILE__,__LINE__)
#define calloc(n,s)   utl_calloc(n,s,__FILE__,__LINE__)
#define realloc(p,n)  utl_realloc(p,n,__FILE__,__LINE__)
#define free(p)       utl_free(p,__FILE__,__LINE__)
#define strdup(p)     utl_strdup(p,__FILE__,__LINE__)

#define utlMemCheck(p) utl_check(p,__FILE__, __LINE__)

#else /* UTL_MEMCHECK */

#define utlMemCheck(p) utlMemValid

#endif /* UTL_MEMCHECK */


#endif /* UTL_H */

/**************************************************************************/

#ifdef UTL_C

#ifndef __GNUC__
const int utlZero = 0 ;
#endif

int utlEmptyFun(void) {return 0;}
char *utlEmptyString = "";

/* % Error handlers
** ================ 
*/

char *utlErrInternal = "Internal error" ;
FILE *utl_output = NULL;
jmp_buf utl_jmp_lst[utl_MAXTRY];
int     utl_jmp_cnt = 0;
int     utlErr = 0;

/*************************************/
#ifndef UTL_NOLOGGING
FILE *log_file = NULL;
int log_level = log_Off;
/*
** These variables are used internally to compose and print log messages:
**
**  .['{=log_abbrev}] The string abbreviations for the levels. 
**  ..
*/

                           /* 0     1     2     3     4     5     6     7 */
char const *log_abbrev[] = {"ALL","DBG","INF","WRN","ERR","FTL","MSG","OFF"};

/* 
**  .['{=log_timestr}]  A buffer to compose current time.
**   ['{=log_time}]     A '|time_t| structure to compose current time. 
**  .. 
*/

char log_timestr[32];
time_t log_time = 0 ;
#endif /* UTL_NOLOGGING */

#endif

