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

#SYS=MINGW

################

_LIB=.a
_OBJ=.o
_EXE=

ifeq ($(SYS),MINGW)
_EXE=.exe
endif

AR=ar -ru
CAT=cat
RM=rm -f
CP=cp -f
LN=gcc $(LNFLAGS) -o

##################

DIST=$(TOP)dist
CHKLIB=$(DIST)/libutl$(_LIB)

CFLAGS=-I. -I$(DIST) -Wall $(CCOPTS)
LNFLAGS=-L. -L$(DIST) $(LNOPTS)

.SUFFIXES: .c .h .o .pmx

.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $*.c
	
.pmx.o:
	$(DIST)/pmx2c $*.pmx $*.c
	-$(CC) $(CFLAGS) -c -o $*.o $*.c
	$(RM) $*.c
	
###########
