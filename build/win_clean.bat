::  (C) by Remo Dentato (rdentato@gmail.com)
:: 
:: This sofwtare is distributed under the terms of the BSD license:
::   http://creativecommons.org/licenses/BSD/
::   http://opensource.org/licenses/bsd-license.php 
::

@echo off
cd ..
del /Q dist\*.*
del /Q src\libutl.h

del /Q /S *.obj
del /Q /S *.lib
del /Q /S *.exe

cd build
