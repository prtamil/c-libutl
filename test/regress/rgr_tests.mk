RGR_TESTS=rgr_chs$(_EXE)\
rgr_pmx$(_EXE)\
rgr_pmx_nested$(_EXE)\
rgr_rec$(_EXE)\
rgr_tbl$(_EXE)\
rgr_vec$(_EXE)\
#rgr_mem$(_EXE)\

allall: $(RGR_TESTS)

allcov:
	make LNLIBS="-lgcov" CCOPTS="-fprofile-arcs -ftest-coverage"

rgr_mem$(_EXE): $(CHKLIB) rgr_mem$(_OBJ)
	$(LN)$@ rgr_mem$(_OBJ) -lutl $(LNLIBS)

rgr_chs$(_EXE): $(CHKLIB) rgr_chs$(_OBJ)
	$(LN)$@ rgr_chs$(_OBJ) -lutl  $(LNLIBS)

rgr_pmx$(_EXE): $(CHKLIB) rgr_pmx$(_OBJ)
	$(LN)$@ rgr_pmx$(_OBJ) -lutl $(LNLIBS)

rgr_pmx_nested$(_EXE): $(CHKLIB) rgr_pmx_nested$(_OBJ)
	$(LN)$@ rgr_pmx_nested$(_OBJ) -lutl $(LNLIBS)

rgr_rec$(_EXE): $(CHKLIB) rgr_rec$(_OBJ)
	$(LN)$@ rgr_rec$(_OBJ) -lutl $(LNLIBS)

rgr_tbl$(_EXE): $(CHKLIB) rgr_tbl$(_OBJ)
	$(LN)$@ rgr_tbl$(_OBJ) -lutl $(LNLIBS)

rgr_vec$(_EXE): $(CHKLIB) rgr_vec$(_OBJ)
	$(LN)$@ rgr_vec$(_OBJ) -lutl $(LNLIBS)

RGR_OBJS= rgr_chs$(_OBJ) rgr_pmx$(_OBJ) rgr_pmx_nested$(_OBJ) rgr_rec$(_OBJ) rgr_tbl$(_OBJ) rgr_vec$(_OBJ)

