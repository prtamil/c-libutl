::  (C) by Remo Dentato (rdentato@gmail.com)
:: 
:: This software is distributed under the terms of the BSD license:
::   http://creativecommons.org/licenses/BSD/
::   http://opensource.org/licenses/bsd-license.php 
::

::@echo off

@if "%1"=="clean" goto clean

:: === SET UP COMPILATION

:: --- Guess compiler

:: create the test batch script
@set F=%0
@if NOT EXIST %F% set F=%0.bat
@if NOT EXIST %F% goto usage
@find "%K%" <%F% >test_cc.bat

:: --- Some defaults
@set SYS=X 
@set CC=cl -nologo
@set CCFLAGS=/c /O2
@set AR=lib -nologo
@set AR_OUT=/OUT:
@set LN=link -nologo
@set LN_OUT=/OUT:
@set O=obj
@set A=lib

@call test_cc.bat "Pelles" pocc -v
@if errorlevel 1 @goto nopelles

:: ------------ Pelles C
@set SYS=PELLES_C 
@set CC=pocc
@set AR=polib
@set LN=polink
:: @set NO_ASM=/DUTL_NOASM
@goto gotcc
:nopelles

@call test_cc.bat "Microsoft" cl -v
@if errorlevel 1 @goto nomsvc

:: ------------ Visual C++
@echo Microsoft Visual C++
@set SYS=MSVC 
:: @set NO_ASM=/DUTL_NOASM
@goto gotcc
:nomsvc

@call test_cc.bat "Watcom" cl -v
@if errorlevel 1 @goto nowatcom

:: ------------ Open Watcom
@echo Open Watcom compiler
@set SYS=WATCOM 
:: @set NO_ASM=-DUTL_NOASM
@goto gotcc
:nowatcom

:: === BUILDING
:gotcc
@del cc.x cc.y
@del test_cc.bat
@if "%SYS"=="X" goto nocc

@echo Building with: %SYS%

:: --------- LIBRARY  ------------
cd ..\src
@echo Building static library

copy utl.h+pmx.h+chs.h+rec.h+tbl.h libutl.h
@echo /**/ >>libutl.h

%CC% %CCFLAGS% %NO_ASM% utl.c
%CC% %CCFLAGS% %NO_ASM% chs.c
%CC% %CCFLAGS% %NO_ASM% tbl.c
%CC% %CCFLAGS% %NO_ASM% rec.c
%CC% %CCFLAGS% %NO_ASM% pmx.c

%AR% *.%O% %AR_OUT%libutl.%A%

copy *.%O% ..\dist
copy libutl.%A% ..\dist
copy libutl.h ..\dist

cd ..\examples\uncomment

%CC% %CCFLAGS% -I ..\..\dist unc.c
%LN% %LN_OUT%unc.exe unc.%O% ..\..\dist\libutl.%A%
unc < ..\..\src\libutl.h > ..\..\dist\libutl.h    

:: --------- pmx2c ------------
@echo Building pmx2c tool

cd ..\pmx2c
%CC% %CCFLAGS% -I ..\..\dist pmx2c_boot.c
%LN% %LN_OUT%pmx2a.exe pmx2c_boot.%O% ..\..\dist\libutl.%A%
pmx2a pmx2c.pmx pmx2c.c
 
%CC% %CCFLAGS% -I ..\..\dist pmx2c.c
%LN% %LN_OUT%pmx2b.exe pmx2c.%O% ..\..\dist\libutl.%A%
pmx2b pmx2c.pmx pmx2c.c
  
%CC% %CCFLAGS% -I ..\..\dist pmx2c.c
%LN% %LN_OUT%pmx2c.exe pmx2c.%O% ..\..\dist\libutl.%A%
copy pmx2c.exe ..\..\dist

del pmx2c.c
        
:: --------- pmxshell ------------
@echo Building pmxshell tool

cd ..\pmxshell

..\..\dist\pmx2c pmxshell.pmx pmxshell.c
%CC% %CCFLAGS% -I ..\..\dist pmxshell.c
del pmxshell.c
%LN% %LN_OUT%pmxshell.exe pmxshell.%O% ..\..\dist\libutl.%A%
copy pmxshell.exe ..\..\dist

:: --------- DONE ------------
cd ..\..\build
@goto done

:usage
@echo USAGE: %0
@goto done

:nocc
@echo ERROR: Unable to find a supported compiler
@goto done
 

:: ==== TEST BATCH 
::
%K% @echo. >cc.x
%K% @echo. >cc.y
%K% @%2 %3 %4 %5 >cc.x 2>cc.y
%K% @type cc.y >> cc.x
%K% @find %1 cc.x >nul
::

:clean
echo off
cd ..
del /Q dist\*.*
del /Q src\libutl.h

del /Q /S *.obj
del /Q /S *.o
del /Q /S *.lib
del /Q /S *.a
del /Q /S *.exe

cd build
   
:done
