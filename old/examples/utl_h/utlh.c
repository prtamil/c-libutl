/*- 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

/* .% Overview
** ~~~~~~~~~~~
**
**   This is an example of how to use '|utl.h| by itself (i.e without
** having to link to '|libutl.a|).
**
**   If all you need is unit testing, debug trace and error handling,
** the entire libutl may be overkill.
** 
**   The utl.h header is structured in such a way that it can be just
** included in your project with no need of linking to the library.
**
**   To use the unit testing macros, the symbol '|UTL_UNITTEST| must
** be defined before including '|utl.h|.
**
**   Note that this also implicitly defines the symbol '|DEBUG|. 
** Unit testing are not available by default to avoid compiler warnings
** that would occur in programs that do not use them. Try to define 
** '|UTL_UNITEST| on a regular program and you will see the compiler
** complaining for variables defined and not used (assuming you had
** enabled that warning). 
*/
#define UTL_UNITTEST

/* Let's access the logging functions as well */
#define UTL_LOGGING

/* Since '|utl.h| requires some global variables and functions,
** if libutl.a is not linked, one of your file must define the symbol
** '|UTL_MAIN| before including it. 
** Usually this is the file where your '|main()| function is. 
*/
#define UTL_MAIN
#include "utl.h"

int main(int argc, char *argv[])
{
  /* dbgmsg()
  ** You can use '|dbgmsg()| exactly as if it was '|printf()| the difference
  ** is that the output will go on the file defined with '|utlSetOuput()| 
  ** (or '|stderr| if no file has been specified)     
  */  
  
  dbgmsg("This message will go on stderr %d\n",1);
  utlSetOutput("utlh1.dbg");
  dbgmsg("This message is on utlh1.log");
  utlSetOutput("utlh2.dbg"); /* the previous file is closed and the new one is opened*/
  dbgmsg("This message is on utlh2.log");
  utlSetOutput(NULL); 
  dbgmsg("This message will go on stderr %d",2);

  
  /* Logging is different from debugging messages in that the logging will
  ** remain in your production code and you will be able to enable it to
  ** monitor the application behavior.  
  */
    
  logSetLevel(logALL);
  logDebug("This is a log debug message. (%d)",logLevel);
  logSetLevel(logINFO);
  logDebug("This will not appear");
  logMessage("\n%s...continuing",logIndent);
  logWarn("And now a warning (%d)",5);
  logSetFile("utlh1.log","w");
  logError("An error!");
  logFatal("An unrecoverable error");
   
  return (0);
}
