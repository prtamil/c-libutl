
_EXE=.exe
_OBJ=o
CC=gcc

TESTS = general logging

.SUFFIXES: .c .h $(_OBJ)

CFLAGS=-O3
.c.o:
	$(CC) $(CFLAGS) -c -o $*.$(_OBJ) $*.c

all: logging$(_EXE) nologging$(_EXE) general$(_EXE) \
     exception$(_EXE) exception2$(_EXE)  
  
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
  
clean:
	rm -f *.exe *.$(_OBJ) *.tmp

