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

#include <string.h>
#include <stdarg.h>
#include <stddef.h>

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
** .[Debugging]    To print debug tracing during development.
**  [Logging]      To print logging traces during program execution.
**                 It offers multilevel logging similar to '|log4j| 
**  [Unit Testing] A simple framework to create unit tests. Tests output
**                 is compliant with the TAP '(Test Anything Protocol) standard.
**  [Error handling] Simple handling for serious errors.
** ..   
**   It is part of the '|libutl| toolset but it can also be used on its own 
** by simply including it, with no need to link to other code. See next section
** for the details.
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

/* .% Messages Output
** ==================
**
** Debug messages and unit tests output normally go on '{stderr}.
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
**
**   Support for error handling is very minimal. Current version only allows
** you to exit on error. Future versions will allow you to  set a longjump.
**
**   The first parameter of the '{=err()} function is the error code (an
** integer) that will be used with '|exit()|. The rest of parameters are 
** the same that you would have used for a '|printf()|. 
**   To properly release resources you should register a cleanup function
** with |atexit()|
**
**   See previous section for a discussion of where the error message will 
** be printed.
*/

#define utlError(errnum,...)  do { \
                                if (stdout) fflush(stdout);\
                                if (utlStderr) {\
                                  fprintf(utlStderr,"ERR%d - ",errnum);\
                                  fprintf(utlStderr,__VA_ARGS__);\
                                }\
                                exit(errnum);\
                              } while (0)

/* '{=utlErrInternal} is provided to avoid repeating the string over
** and over again in the code.
*/

extern char *utlErrInternal; 

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
                       TSTWRITE("#\n# * %d. %s (%s:%d)\n",TSTSEC, s,__FILE__, __LINE__)),!utlZero)

/* to disable an intere test section, just prepend ''|_|' or ''|X|'*/
 
#define _TSTSECTION(s) if (utlZero)  
#define XTSTSECTION(s) if (utlZero)  

/* In each section, tests can be logically grouped so that different aspects
** of related functions can be tested.
*/

#define TSTGROUP(s) if ( TSTNUM=0, \
                     TSTWRITE("#\n# *   %d.%d %s\n", TSTSEC, ++TSTGRP, s),\
                     TSTGRP+1)
                     
/* to disable an intere test group , just prepend ''|_|' */
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

#define TST(s,x)    (TST_DO(s,(TSTSKP != NULL? 1 : (x))),\
                     (TSTSKP != NULL? TSTWRITE(" # SKIP %s",TSTSKP):0),\
                     TSTWRITE("\n"),TSTRES)

#define TST_DO(s,x) (TSTRES = (x), TSTGTT++, TSTTOT++, TSTNUM++,\
                     TSTWRITE("%s %4d - %s (:%d)",\
                              (TSTRES? (TSTGPAS++,TSTPASS++,TSTOK) : TSTKO),\
                              TSTGTT, s, __LINE__))

#define TSTTD(s,x,r) (TST_DO(s,x), TSTWRITE(" # TODO %s\n",r), TSTRES)

#define TSTFAILED  (!TSTRES)

/* You can skip a set of tests if a condition is not met.
** Nested skips are not supported!
*/
#define TSTSKIP(x,r) (TSTSKP = ((x)? r : NULL))

#define TSTENDSKIP  (TSTSKP = NULL)

#define TSTNOTE(...) (TSTWRITE("      "), TSTWRITE(__VA_ARGS__), TSTWRITE("\n"))

#define TSTONFAIL(...) (TSTRES? 0 : (TSTNOTE(__VA_ARGS__)))

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

#endif

/* .% Debugging
** ============
** 
**   Sometimes it's useful to insert tracing '|printf()| to understand what's
** going on in a program. Those '|printf()| statements are normally guarded
** with an |#ifdef DEBUG| so that they disappear in the final version of the
** software.  The downsides of this approach is that they visually clutter the
** source and selectively disable the messages is not easy.
**
**   The macro here helps inserting debug messages that can be turned on/off
** and that will be completely disappear from the program if the source is
** compiled without the '|DEBUG| symbol defined.
*/

/* Let's give precedence to '{NDEBUG} over '{DEBUG} */

#ifdef NDEBUG
#ifdef DEBUG
#undef DEBUG
#endif
#endif

#ifdef DEBUG
/*  You can use '{=dbgmsg()} as if it was a '|printf()| with the only
** difference that the output will be directed to '{utlStderr}.
*/
#define dbgmsg(...) ((stdout?fflush(stdout):0),\
                     fprintf(utlStderr,"# "),\
                     fprintf(utlStderr,__VA_ARGS__), fflush(utlStderr))

/* Note that to ensure that dbg messages are correctly interleaved with other
** messages that might have been printed on the screen, '|stdout| is
** flushed before printing and '{utlStderr} is flushed right after.
*/

#else
#define dbgmsg(...)
#endif /* DEBUG */

/*   To disable just one call to '{dbgmsg()}, you can place an underscore
** before its name as '{=_dbgmsg()} is a macro that always expand to nothing.
** 
**   If you are worried about the fact that identifiers beginning with an
** underscore may be reserved (as per ISO Stanadard 7.1.3) you can replace
** it with '|Xdbgmsg()|.  So far I've not find any
** reason to do it and using an underscore seems more natural to me. 
*/
#define _dbgmsg(...)
#define Xdbgmsg(...)


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
#define UTL_LOGGING
#ifdef UTL_LOGGING
#include <time.h>
extern char log_timestr[32];
extern time_t log_time;
extern  char *log_abbrev[];

/* .%% Logging levels
** ~~~~~~~~~~~~~~~~~~
**
**   Logging levels are hierarchical and structured as in log4j. The variable 
** '{=logLevel} contains the current logging level.  Logging is off by default.
**
**   Use '{=logSetLevel()} to set the desired level of logging.
*/

#define logALL    0
#define logDEBUG  1
#define logINFO   2
#define logWARN   3
#define logERROR  4
#define logFATAL  5
#define logOFF    6

extern int logLevel;
#define logSetLevel(level)     (logLevel = (level))

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
** using the '{=logSetLogFile()} function.
** For example:
** .v  
**   logSetLogFile("file1.log","w") // Delete old log file and create a new one
**   ...
**   logSetLogFile(NULL,NULL); // Close log file, send next messages to stderr
**   ... 
**   logSetLogFile("file1.log","a") // Append to previous log file
** .. 
*/

#define logSetFile(fname,mode) ((log_file? fclose(log_file) : 0),\
                                (log_file = fname? fopen(fname,mode) : NULL))

/*   To actually write a message on the log file, use the '{=logWrite()}
** function as if it was a '|printf()| with the exception that the first
** paratmeter is the level of the message.
** Example:
** .v
**    logWrite(logINFO,"Something weird at %d is happening", counter);
** ..
*/

#define logWrite(lvl,...) \
       (lvl >= logLevel  \
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
#define logDebug(...)    logWrite(logDEBUG,__VA_ARGS__)
#define logInfo(...)     logWrite(logINFO,__VA_ARGS__)
#define logWarn(...)     logWrite(logWARN,__VA_ARGS__)
#define logError(...)    logWrite(logERROR,__VA_ARGS__)
#define logFatal(...)    logWrite(logFATAL,__VA_ARGS__)

/* If you want to add something to the log file without creating a new entry
** in the log file, you can use the '{=logMessage()} function. 
*/
#define logMessage(...)  (fprintf(logFile,__VA_ARGS__), fflush(logFile))

#define logIndent     "\n                        "    
#define logContinue(...)  (fputs(logIndent,logFile),logMessage(__VA_ARGS__))                       

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

#else

#define logSetLevel(level)
#define logFile                 stderr 
#define logSetFile(fname,mode)
#define logWrite(lvl,...)
#define logDebug(...)
#define logInfo(...)
#define logWarn(...)
#define logError(...)
#define logFatal(...)
#define logMessage(...)

#endif /*- UTL_LOGGING */


/*  .% Finite state machine
**  =======================
**
**  Macros to embed Finite state machine into C programs.
**
** .v
**      FSM {
**        STATE(x) { ...
**                   if (c == 0) GOTO(z);
**                   GOTO(y);
**        }
**
**        STATE(y) { ...
**                   BREAK;  // exit from the FSM
**        }
*
**        STATE(z) { ...
**                   GOSUB(t);
**        }
**
**        STATE(t) { ...
**                   GOBACK;  // Go back to the caller state
**        }
**      }
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

#define fsmEnd(x) fsm_##x##_e: utl_fsmcnt=0; break;} break;} 


/*  .% Traced memory check
**  ======================
*/
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
#else
#define utlMemCheck(p) 
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

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

#endif /*- UTL_H */

