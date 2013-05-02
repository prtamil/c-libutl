# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#

_EXE=.exe
_OBJ=o
CC=gcc

TESTS = general logging

.SUFFIXES: .c .h $(_OBJ)

CFLAGS=-O3

.c.o:
	$(CC) $(CFLAGS) -c -o $*.$(_OBJ) $*.c

all: logging$(_EXE)   nologging$(_EXE)  general$(_EXE) \
     exception$(_EXE) exception2$(_EXE) memory$(_EXE) \
     fsm$(_EXE)

logging$(_EXE): utl.h  utl_logging_ut.c
	$(CC) $(CFLAGS) -c -o utl_logging_ut.$(_OBJ) utl_logging_ut.c
	gcc -o $@ utl_logging_ut.$(_OBJ)

nologging$(_EXE): utl.h utl_logging_ut.c
	$(CC) -DUTL_NOLOGGING $(CFLAGS) -c -o utl_logging_ut.$(_OBJ) utl_logging_ut.c
	gcc -DUTL_NOLOGGING -o $@ utl_logging_ut.$(_OBJ)

utl_general_ut.o: utl.h utl_general_ut.c

general$(_EXE): utl_general_ut.o
	gcc -o $@ $<

utl_exception_ut.o: utl.h utl_exception_ut.c

exception$(_EXE): utl_exception_ut.o
	gcc -o $@ $<
  
utl_exception2_ut.o: utl.h utl_exception2_ut.c

exception2$(_EXE): utl_exception2_ut.o
	gcc -o $@ $<

utl_memory_ut.o: utl.h utl_memory_ut.c

memory$(_EXE): utl_memory_ut.o
	gcc -o $@ $<

utl_fsm_ut.o: utl.h utl_fsm_ut.c

fsm$(_EXE): utl_fsm_ut.o
	gcc -o $@ $<
  
clean:
	rm -f *.exe *.$(_OBJ) *.tmp

