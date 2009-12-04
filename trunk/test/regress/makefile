# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#
 
TOP=../../

include $(TOP)config.mk

RGR_TESTS=rgr_vec$(_EXE) rgr_chs$(_EXE)

all: $(RGR_TESTS)

rgr_vec$(_EXE): $(CHKLIB) rgr_vec$(_OBJ)
	$(LN)$@ rgr_vec$(_OBJ) -lutl

rgr_chs$(_EXE): $(CHKLIB) rgr_chs$(_OBJ)
	$(LN)$@ rgr_chs$(_OBJ) -lutl

clean:
	$(RM) rgr_vec$(_EXE) rgr_vec$(_OBJ)
	$(RM) gmon.out

include $(TOP)targets.mk
