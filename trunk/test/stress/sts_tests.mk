STS_TESTS=sts_tbl$(_EXE)\
sts_vec$(_EXE)\

all: $(STS_TESTS)

sts_tbl$(_EXE): $(CHKLIB) sts_tbl$(_OBJ)
	$(LN)$@ sts_tbl$(_OBJ) -lutl

sts_vec$(_EXE): $(CHKLIB) sts_vec$(_OBJ)
	$(LN)$@ sts_vec$(_OBJ) -lutl

STS_OBJS= sts_tbl$(_OBJ) sts_vec$(_OBJ)

