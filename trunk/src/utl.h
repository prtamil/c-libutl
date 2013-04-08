/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**
*/

#ifndef UTL_H
#define UTL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <string.h>
#include <stdarg.h>
#include <stddef.h>

#include <setjmp.h>

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
*/

/* .% Variables
** ============
**
**  A set of variable of generic use is provided by '|utl.h| for convenience.
**
**  .[utlEmptyFun]  A pointer to a do-nothing function that can be used
**                  as a generic placeholder (or NULL indicator) for
**                  function pointers. This can be useful as the C standard
**                  doesn't guarantee that one could mix pointers to objects
**                  with pointers to function (even if in reality this is
**                  often the case).  
**  ..
*/

void utlEmptyFun(void);

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
**   '{=utl_stderr} is a global variable holding the current file to be
** used when printing a debug or test message.   It's not intended be used
** directly, use the macro '{=utlStderr} instead if you need to refer to 
** the file.
**
**   Actually I see no reason why you should need it, nut just in case ... 
*/

extern FILE *utl_stderr;
#define utlStderr (utl_stderr? utl_stderr: stderr)

/*   The '/public/ function to set the output file, is '{=utlSetOutput()}
** that takes the filename as input, open the file and and sets '{utl_stderr}
** to it.  If a previous file had been opened, it will be closed. 
**
**   Passing '|NULL| as argument closes the current output file (if there
** was one opened) and sets '{utl_stderr} to '|NULL|, which implies that the
** default '|stderr| will be used from that moment on.
** 
*/
#define utlSetOutput(fname) ((utl_stderr ? fclose(utl_stderr) : 0),\
                             (utl_stderr = (fname? fopen(fname,"w"): NULL)))


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
**   They are available only if the symbol |UTL_UNITTEST| is defined before
** including the |utl.h| header.
** 
**   '{UTL_UNITTEST} implies '{DEBUG}
*/

#ifdef UTL_UNITTEST

#ifndef DEBUG
#define DEBUG
#endif

#define TSTWRITE(...) (fprintf(utlStderr,__VA_ARGS__),fflush(utlStderr))

#define TSTTITLE(s) TSTWRITE("# ** %s **\nTAP version 13\n\n",s)

/* Tests are divided in sections introduced by '{=TSTSECTION} macro.
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

#define TST(s,x)    (TST_DO(s,(TSTSKP != NULL? 1 : (x))),\
                     (TSTSKP != NULL? TSTWRITE(" # SKIP %s",TSTSKP):0),\
                     TSTWRITE("\n"),TSTRES)

#define TST_DO(s,x) (TSTRES = (x), TSTGTT++, TSTTOT++, TSTNUM++,\
                     TSTWRITE("%s %4d - %s (:%d)",\
                              (TSTRES? (TSTGPAS++,TSTPASS++,TSTOK) : TSTKO),\
                               TSTGTT, s, __LINE__))

#define TSTTODO(s,x,r) (TST_DO(s,x), TSTWRITE(" # TODO %s\n",r), TSTRES)

#define TSTTD TSTTODO

#define TSTFAILED  (!TSTRES)

/* You can skip a set of tests if a condition is not met.
** Nested skips are not supported!
*/
#define TSTSKIP(x,r) (TSTSKP = ((x)? r : NULL))

#define TSTENDSKIP  (TSTSKP = NULL)

#define TSTNOTE(...) (TSTWRITE("      "), TSTWRITE(__VA_ARGS__), TSTWRITE("\n"))

#define TSTONFAIL(...) (TSTRES? 0 : (TSTNOTE(__VA_ARGS__)))

#define TSTBAILOUT(x,r) (TSTRES? TSTRES = 1 : (TSTWRITE("Bail out! %s",r), exit(1)))

/* At the end of a section, the accumulated stats can be printed out */
#define TSTSTAT() \
          (TSTTOT == 0 ? 0 : (\
           TSTWRITE("#\n# SECTION %d PASSED: %d/%d\n",TSTSEC,TSTPASS,TSTTOT),\
           TSTTOT = 0))

/* At the end of all the tests, the accumulated stats can be printed out */
#define TSTDONE() if (TSTGTT > 0) { TSTSTAT(); \
                    TSTWRITE("#\n# TOTAL PASSED: %d/%d\n",TSTGPAS,TSTGTT);\
                    TSTWRITE("#\n# END OF TESTS\n1..%d\n",TSTGTT),fflush(utlStderr);\
                  }

/* Execute a statement if a test succeeded */
#define TSTIF_OK  if (TSTRES)

/* Execute a statement if a test failed */
#define TSTIF_NOTOK if (!TSTRES)

static int TSTRES  = 0;  /* Result of the last performed '|TST()| */
static int TSTNUM  = 0;  /* Last test number */
static int TSTGRP  = 0;  /* Current test group */
static int TSTSEC  = 0;  /* Current test SECTION*/
static int TSTTOT  = 0;  /* Number of tests executed */
static int TSTGTT  = 0;  /* Number of tests executed (Grand Total) */
static int TSTGPAS = 0;  /* Number of tests passed (Grand Total) */
static int TSTPASS = 0;  /* Number of passed tests */

static char       *TSTSKP = NULL;
static const char *TSTOK  = "ok    ";
static const char *TSTKO  = "not ok";

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

/* Logging functions are available only if the symbol '{=UTL_LOGGING}
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

extern int log_level;

#ifndef UTL_NOLOGGING
#include <time.h>
#include <ctype.h>
extern char log_timestr[32];
extern time_t log_time;
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

#define logLevel(level)         (log_level=log_Off)
#define logLevelEnv(v,l)        (log_level=log_Off)
#define logFile stderr          (log_level=log_Off)
#define logOpen(fname,mode)     (log_level=log_Off)
#define logClose()              (log_level=log_Off)
#define logWrite(lvl,...)       (log_level=log_Off)
#define logDebug(...)           (log_level=log_Off)
#define logInfo(...)            (log_level=log_Off)
#define logWarn(...)            (log_level=log_Off)
#define logError(...)           (log_level=log_Off)
#define logFatal(...)           (log_level=log_Off)
#define logMessage(...)         (log_level=log_Off)

#define logIf(x) if (utlZero)

#endif /*- UTL_LOGGING */

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

#ifdef UTL_NOMEMCHECK
#ifdef UTL_MEMCHECK
#undef UTL_MEMCHECK
#endif
#endif

void *utl_malloc  (size_t size, char *file, int line );
void *utl_calloc  (size_t num, size_t size, char *file, int line);
void *utl_realloc (void *ptr, size_t size, char *file, int line);
void  utl_free    (void *ptr, char *file, int line );
void *utl_strdup  (void *ptr, char *file, int line);

#define utlMemInvalid    -2
#define utlMemOverflow   -1
#define utlMemValid       0
#define utlMemNull        1

int utl_check(void *ptr,char *file, int line);

#ifdef UTL_MEMCHECK

#ifdef malloc
#undef malloc
#endif 
#define malloc(n) utl_malloc(n,__FILE__,__LINE__)

#ifdef calloc
#undef calloc
#endif 
#define calloc(n,s) utl_calloc(n,s,__FILE__,__LINE__)

#ifdef realloc
#undef realloc
#endif 
#define realloc(p,n) utl_realloc(p,n,__FILE__,__LINE__)

#ifdef free
#undef free
#endif 
#define free(p) utl_free(p,__FILE__,__LINE__)

#ifdef strdup
#undef strdup
#endif 
#define strdup(p) utl_strdup(p,__FILE__,__LINE__)

#define utlMemCheck(p) utl_check(p,__FILE__, __LINE__)

#else /* UTL_MEMCHECK */

#define utlMemCheck(p) utlMemValid

#endif /* UTL_MEMCHECK */


#endif /* UTL_H */

