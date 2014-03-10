:: mk.bat
:: by Remo Dentato - 2011
::
:: Script to compile using MSys from PSPad
::
:: Configure your project "make" commands with:
::            %p\mk.bat %d 
:: it will be equivalent to being in the file directory and
:: give the make command

@set MSYSBIN=C:\Mingw\msys\1.0\bin

@%MSYSBIN%\bash -login -c "cd '%1' ; cd `pwd`; make %2 %3 %4 %5 %6 %7 %8 %9"
