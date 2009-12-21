# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#


SYS=LINUX

ifneq "$(COMSPEC)" ""
 SYS=MINGW
endif

### Uncomment next line if you want to force Mingw as system (in case the 
### test above doesn't work)
#SYS=MINGW

### Uncomment next line if you don't want any ASM code to be used in the
### library
#NO_ASM=-DUTL_NOASM

################

_LIB=.a
_OBJ=.o
_EXE=

ifeq ($(SYS),MINGW)
_EXE=.exe
endif

CC=gcc
AR=ar -ru
CAT=cat
RM=rm -f
CP=cp -f
LN=gcc $(LNFLAGS) -o

##################

DIST=$(TOP)dist
CHKLIB=chklib

WFLAGS = -pedantic -std=c99 -Wall -Wextra -Wformat=2 \
         -Winit-self -Wswitch-default \
         -Wswitch-enum -Wunused-parameter -Wfloat-equal -Wundef \
         -Wshadow -Wbad-function-cast \
         -Wcast-qual -Wcast-align -Wconversion -Waggregate-return \
         -Wstrict-prototypes \ 
         -Wold-style-definition -Wmissing-prototypes \
         -Wmissing-declarations -Wpacked -Wpadded -Wredundant-decls \
         -Wnested-externs -Wunreachable-code -Winline -Winvalid-pch \
         -Wvolatile-register-var -Wstrict-aliasing=2 -Wstrict-overflow=2 \
         -Wtraditional-conversion -Wwrite-strings

WFLAGS = -Wall -Wextra -std=c99

CFLAGS=-I. -I$(DIST) $(WFLAGS) $(CCOPTS) $(NO_ASM)
LNFLAGS=-L. -L$(DIST) $(LNOPTS)

.SUFFIXES: .c .h .o .pmx

.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $*.c
	
.pmx.o:
	$(DIST)/pmx2c $*.pmx $*.c
	-$(CC) $(CFLAGS) -c -o $*.o $*.c
	$(RM) $*.c
	
###########
