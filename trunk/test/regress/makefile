# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#
 
TOP=../../

include $(TOP)config.mk

RGR_TESTS = rgr_rec$(_EXE) rgr_vec$(_EXE) \
            rgr_chs$(_EXE) rgr_tbl$(_EXE) \
            rgr_pmx$(_EXE)

RGR_OBJS = rgr_rec$(_OBJ) rgr_vec$(_OBJ) \
           rgr_chs$(_OBJ) rgr_tbl$(_OBJ) \
           rgr_pmx$(_OBJ)

all: $(RGR_TESTS)

rgr_pmx$(_EXE): $(CHKLIB) rgr_pmx$(_OBJ)
	$(LN)$@ rgr_pmx$(_OBJ) -lutl

rgr_rec$(_EXE): $(CHKLIB) rgr_rec$(_OBJ)
	$(LN)$@ rgr_rec$(_OBJ) -lutl

rgr_vec$(_EXE): $(CHKLIB) rgr_vec$(_OBJ)
	$(LN)$@ rgr_vec$(_OBJ) -lutl

rgr_tbl$(_EXE): $(CHKLIB) rgr_tbl$(_OBJ)
	$(LN)$@ rgr_tbl$(_OBJ) -lutl

rgr_chs$(_EXE): $(CHKLIB) rgr_chs$(_OBJ)
	$(LN)$@ rgr_chs$(_OBJ) -lutl

clean:
	$(RM) $(RGR_TESTS) 
	$(RM) $(RGR_OBJS) 
	$(RM) gmon.out

include $(TOP)targets.mk
