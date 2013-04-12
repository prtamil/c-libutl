
_EXE=.exe
_OBJ=o
CC=gcc

TESTS = general logging

.SUFFIXES: .c .h $(_OBJ)

.c.o:
	$(CC) $(CFLAGS) -c -o $*$(_OBJ) $*.c

all: logging$(_EXE) nologging$(_EXE)
  
logging$(_EXE): utl.h  utl_logging_ut.c
	$(CC) $(CFLAGS) -c -o utl_logging_ut.$(_OBJ) utl_logging_ut.c
	gcc -o $@ utl_logging_ut.$(_OBJ)
  
nologging$(_EXE): utl.h utl_logging_ut.c
	$(CC) -DUTL_NOLOGGING $(CFLAGS) -c -o utl_logging_ut.$(_OBJ) utl_logging_ut.c
	gcc -DUTL_NOLOGGING -o $@ utl_logging_ut.$(_OBJ)
  
clean:
	rm -f *.exe *.$(_OBJ)

