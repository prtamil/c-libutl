::  (C) by Remo Dentato (rdentato@gmail.com)
:: 
:: This software is distributed under the terms of the BSD license:
::   http://creativecommons.org/licenses/BSD/
::   http://opensource.org/licenses/bsd-license.php 
::

::@echo off

:: Uncomment next line to fall back to plain C only implementation
:: set NO_ASM=/DUTL_NOASM

:: --------- NO CONFIG AFTER THIS LINE ------------
 
set CFLAGS=/c /O2 /W0

:: --------- LIBRARY  ------------
cd ..\src
echo Building static library

copy utl.h+pmx.h+chs.h+tbl.h libutl.h
cl -nologo %CFLAGS% %NO_ASM% utl.c
cl -nologo %CFLAGS% %NO_ASM% chs.c
cl -nologo %CFLAGS% %NO_ASM% tbl.c
cl -nologo %CFLAGS% %NO_ASM% pmx.c

lib *.obj /OUT:libutl.lib

copy *.obj ..\dist
copy libutl.lib ..\dist
copy libutl.h ..\dist

cd ..\examples\uncomment

cl -nologo %CFLAGS% /I..\..\dist unc.c
link unc.obj ..\..\dist\libutl.lib /OUT:unc.exe
unc < ..\..\src\libutl.h > ..\..\dist\libutl.h    

:: --------- pmx2c ------------
echo Building pmx2c tool

cd ..\pmx2c
cl -nologo %CFLAGS% /I..\..\dist pmx2c_boot.c
link pmx2c_boot.obj ..\..\dist\libutl.lib /OUT:pmx2a.exe
pmx2a pmx2c.pmx pmx2c.c
 
cl -nologo %CFLAGS% /I..\..\dist pmx2c.c
link pmx2c.obj ..\..\dist\libutl.lib /OUT:pmx2b.exe
pmx2b pmx2c.pmx pmx2c.c
  
cl -nologo %CFLAGS% /I..\..\dist pmx2c.c
link pmx2c.obj ..\..\dist\libutl.lib /OUT:pmx2c.exe
copy pmx2c.exe ..\..\dist

del pmx2c.c
        
:: --------- pmxshell ------------
echo Building pmxshell tool

cd ..\pmxshell

..\..\dist\pmx2c pmxshell.pmx pmxshell.c
cl -nologo %CFLAGS% /I..\..\dist pmxshell.c
del pmxshell.c
link pmxshell.obj ..\..\dist\libutl.lib /OUT:pmxshell.exe
copy pmxshell.exe ..\..\dist

:: --------- DONE ------------
cd ..\..\build 