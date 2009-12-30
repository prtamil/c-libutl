::  (C) by Remo Dentato (rdentato@gmail.com)
:: 
:: This software is distributed under the terms of the BSD license:
::   http://creativecommons.org/licenses/BSD/
::   http://opensource.org/licenses/bsd-license.php 
::

::@echo off

:: Uncomment next line to fall back to plain C only implementation

@call win_cctest.bat "Pelles" pocc -v
@if errorlevel 1 @goto nopelles

:: ------------ Pelles C
@echo Pelles C compiler
@set CC=pocc
@set AR=polib
@set AR_OUT=/OUT:
@set LN=polink
@set CFLAGS=/c /O2 /W0
:: @set NO_ASM=/DUTL_NOASM
@goto gotcc
:nopelles

@call win_cctest.bat "Watcom" cl -v
@if errorlevel 1 @goto nowatcom

:: ------------ Open Watcom
@echo Open Watcom compiler
@set CC=cl -nologo
@set AR=lib -nologo
@set AR_OUT=/OUT:
@set LN=link -nologo
@set CFLAGS=-c -O2
:: @set NO_ASM=-DUTL_NOASM
@goto gotcc
:nowatcom

@call win_cctest.bat "Microsoft" cl -v
@if errorlevel 1 @goto nomsvc

:: ------------ Visual C++
@echo Microsoft Visual C++
@set CC=cl -nologo
@set AR=lib
@set AR_OUT=/OUT:
@set LN=link -nologo
@set CFLAGS=/c /O2 /W0
:: @set NO_ASM=/DUTL_NOASM
@goto gotcc
:nomsvc

@echo ERROR: Unable to find a supported compiler
@goto theend

:gotcc
del cc.x cc.y

:: --------- LIBRARY  ------------
cd ..\src
@echo Building static library

copy utl.h+pmx.h+chs.h+rec.h+tbl.h libutl.h
echo /**/ >>libutl.h
%CC% %CFLAGS% %NO_ASM% utl.c
%CC% %CFLAGS% %NO_ASM% chs.c
%CC% %CFLAGS% %NO_ASM% tbl.c
%CC% %CFLAGS% %NO_ASM% rec.c
%CC% %CFLAGS% %NO_ASM% pmx.c

%AR% *.obj %AR_OUT%libutl.lib

copy *.obj ..\dist
copy libutl.lib ..\dist
copy libutl.h ..\dist

cd ..\examples\uncomment

%CC% %CFLAGS% -I ..\..\dist unc.c
%LN%  unc.obj ..\..\dist\libutl.lib /OUT:unc.exe
unc < ..\..\src\libutl.h > ..\..\dist\libutl.h    

:: --------- pmx2c ------------
@echo Building pmx2c tool

cd ..\pmx2c
%CC% %CFLAGS% -I ..\..\dist pmx2c_boot.c
%LN%  pmx2c_boot.obj ..\..\dist\libutl.lib /OUT:pmx2a.exe
pmx2a pmx2c.pmx pmx2c.c
 
%CC% %CFLAGS% -I ..\..\dist pmx2c.c
%LN%  pmx2c.obj ..\..\dist\libutl.lib /OUT:pmx2b.exe
pmx2b pmx2c.pmx pmx2c.c
  
%CC% %CFLAGS% -I ..\..\dist pmx2c.c
%LN%  pmx2c.obj ..\..\dist\libutl.lib /OUT:pmx2c.exe
copy pmx2c.exe ..\..\dist

del pmx2c.c
        
:: --------- pmxshell ------------
@echo Building pmxshell tool

cd ..\pmxshell

..\..\dist\pmx2c pmxshell.pmx pmxshell.c
%CC% %CFLAGS% -I ..\..\dist pmxshell.c
del pmxshell.c
%LN%  pmxshell.obj ..\..\dist\libutl.lib /OUT:pmxshell.exe
copy pmxshell.exe ..\..\dist

:: --------- DONE ------------
cd ..\..\build
 
:theend
