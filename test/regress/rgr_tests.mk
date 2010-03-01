RGR_TESTS=rgr_chs$(_EXE)\
rgr_pmx$(_EXE)\
rgr_pmx_nested$(_EXE)\
rgr_rec$(_EXE)\
rgr_tbl$(_EXE)\
rgr_vec$(_EXE)\

allall: $(RGR_TESTS)

rgr_chs$(_EXE): $(CHKLIB) rgr_chs$(_OBJ)
	$(LN)$@ rgr_chs$(_OBJ) -lutl

rgr_pmx$(_EXE): $(CHKLIB) rgr_pmx$(_OBJ)
	$(LN)$@ rgr_pmx$(_OBJ) -lutl

rgr_pmx_nested$(_EXE): $(CHKLIB) rgr_pmx_nested$(_OBJ)
	$(LN)$@ rgr_pmx_nested$(_OBJ) -lutl

rgr_rec$(_EXE): $(CHKLIB) rgr_rec$(_OBJ)
	$(LN)$@ rgr_rec$(_OBJ) -lutl

rgr_tbl$(_EXE): $(CHKLIB) rgr_tbl$(_OBJ)
	$(LN)$@ rgr_tbl$(_OBJ) -lutl

rgr_vec$(_EXE): $(CHKLIB) rgr_vec$(_OBJ)
	$(LN)$@ rgr_vec$(_OBJ) -lutl

RGR_OBJS= rgr_chs$(_OBJ) rgr_pmx$(_OBJ) rgr_pmx_nested$(_OBJ) rgr_rec$(_OBJ) rgr_tbl$(_OBJ) rgr_vec$(_OBJ)

