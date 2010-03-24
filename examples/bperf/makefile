
_OBJ =.o
_EXE =.exe

CFLAGS = -O2 

.cc$(_OBJ):
	gcc $(CFLAGS) -c $<

O  = lookupa$(_OBJ) recycle$(_OBJ) perfhex$(_OBJ) perfect$(_OBJ)
OF = lookupa$(_OBJ) recycle$(_OBJ) phash$(_OBJ) testperf$(_OBJ)

perfect$(_EXE) : $(O)
	gcc -o perfect $(O) -lm

testperf$(_EXE) : $(OF)
	gcc -o testperf $(OF) -lm


clean: 
	rm -f $(O) $(OF)
	rm -f perfect$(_EXE) testperf$(_EXE) 

# DEPENDENCIES

lookupa$(_OBJ)  : lookupa.c standard.h lookupa.h
recycle$(_OBJ)  : recycle.c standard.h recycle.h
perfhex$(_OBJ)  : perfhex.c standard.h lookupa.h recycle.h perfect.h
perfect$(_OBJ)  : perfect.c standard.h lookupa.h recycle.h perfect.h
phash$(_OBJ)    : phash.c standard.h phash.h lookupa.h
testperf$(_OBJ) : testperf.c standard.h recycle.h phash.h
