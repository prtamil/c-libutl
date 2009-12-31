::  (C) by Remo Dentato (rdentato@gmail.com)
:: 
:: This software is distributed under the terms of the BSD license:
::   http://creativecommons.org/licenses/BSD/
::   http://opensource.org/licenses/bsd-license.php 
::

::@echo off


:: === SET UP COMPILATION
@set K_=@rem
@set J=K_
:: --- Some defaults for compiler
@set SYS=X 
@set CC=cl -nologo
@set CCFLAGS=/c /O2
@set AR=lib -nologo
@set AR_OUT=/OUT:
@set LN=link -nologo
@set LN_OUT=/OUT:
@set O=obj
@set A=lib

@if "%1"=="clean" goto clean
@if "%1"=="help" goto usage
@if "%1"=="/h" goto usage
@if "%1"=="/?" goto usage
@if "%1"=="-h" goto usage
@if NOT "%1"==""  goto %1
:: --- Guess compiler

:: This code will be copied in the test_cc.bat file
%K_% @echo. >cc.x
%K_% @echo. >cc.y
%K_% @%2 %3 %4 %5 >cc.x 2>cc.y
%K_% @type cc.y >> cc.x
%K_% @find %1 cc.x >nul
:: --------------------

:guess
:: create the test batch script

@set F=%0
@if NOT EXIST %F% set F=%0.bat
@if NOT EXIST %F% set F=%0.cmd
@if NOT EXIST %F% goto usage
@find "%J%" <%F% >test_cc.bat
@if NOT EXIST test_cc.bat goto usage


:: ------------ lcc
:: LCC does not support variadic macros :( 
@call test_cc.bat "lcc-Win32" lcc -v
@if errorlevel 1 @goto nolcc
:lcc
@goto nolcc
@set SYS=lcc
@set CC=lcc 
@set CCFLAGS=-ansic -c -O
@set AR=lcclib
@set LN=lcclnk -s -subsystem console   
@set LN_OUT=-o 
:: @set NO_ASM=/DUTL_NOASM
@goto gotcc
:nolcc


:: ------------ gcc
@call test_cc.bat "GCC" gcc --version
@if errorlevel 1 @goto nogcc
:gcc
@set SYS=GCC
@set CC=gcc
@set CCFLAGS=-c -O2
@set AR=ar
@set AR_OUT=-ru  
@set LN=gcc
@set LN_OUT=-o 
@set O=o
@set A=a
:: @set NO_ASM=/DUTL_NOASM
@goto gotcc
:nogcc

:: ------------ Digital Mars
@call test_cc.bat ".." dmc --
@if errorlevel 1 @goto nodmc
:dmc
@set SYS=Digital_Mars
@set CC=dmc
@set CCFLAGS=-w2 -o -c
@set AR=lib
@set AR_OUT=-c   
@set LN=dmc
@set LN_OUT=-o 
:: @set NO_ASM=/DUTL_NOASM
@goto gotcc
:nodmc

:: ------------ Pelles C
@call test_cc.bat "Pelles" pocc -v
@if errorlevel 1 @goto nopelles
:pelles
@set SYS=PELLES_C 
@set CC=pocc
@set AR=polib
@set LN=polink
:: @set NO_ASM=/DUTL_NOASM
@goto gotcc
:nopelles

:: ------------ Visual C++
@call test_cc.bat "Microsoft" cl -v
@if errorlevel 1 @goto nomsvc
:msvc
@set SYS=MSVC 
:: @set NO_ASM=/DUTL_NOASM
@goto gotcc
:nomsvc

:: ------------ Open Watcom
@call test_cc.bat "Watcom" cl -v
@if errorlevel 1 @goto nowatcom
:watcom
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

%AR% %AR_OUT%libutl.%A% utl.%O% chs.%O% tbl.%O% rec.%O% pmx.%O%

copy *.%O% ..\dist
copy libutl.%A% ..\dist
copy libutl.h ..\dist
goto done
cd ..\examples\uncomment

%CC% %CCFLAGS% -I..\..\dist unc.c
%LN% %LN_OUT%unc.exe unc.%O% ..\..\dist\libutl.%A%
unc < ..\..\src\libutl.h > ..\..\dist\libutl.h    

:: --------- pmx2c ------------
@echo Building pmx2c tool

cd ..\pmx2c
%CC% %CCFLAGS% -I..\..\dist pmx2c_boot.c
%LN% %LN_OUT%pmx2a.exe pmx2c_boot.%O% ..\..\dist\libutl.%A%
pmx2a pmx2c.pmx pmx2c.c
 
%CC% %CCFLAGS% -I..\..\dist pmx2c.c
%LN% %LN_OUT%pmx2b.exe pmx2c.%O% ..\..\dist\libutl.%A%
pmx2b pmx2c.pmx pmx2c.c
  
%CC% %CCFLAGS% -I..\..\dist pmx2c.c
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

:nocc
@echo ERROR: Unable to find a supported compiler
@goto done
 
:usage
@echo USAGE: %0 [opt]
@echo   opt:  help     this help 
@echo         clean    cleanup files 
@echo         guess    Find available compiler
@echo         dmc      Digital Mars C 
@echo         gcc      GNU C 
@echo         msvc     Microsft Visual C++
@echo         pelles   Pelles-C
@echo         watcom   Open Watcom 
@goto done

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
