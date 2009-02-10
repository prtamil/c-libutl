# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This sofwtare is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#
 
TOP=../../

include $(TOP)config.mk

cxrf$(_EXE): $(CHKLIB) cxrf$(_OBJ)
	$(LN)$@ cxrf$(_OBJ) -lutl

clean:
	$(RM) cxrf$(_EXE)
	$(RM) cxrf$(_OBJ)
	$(RM) gmon.out

include $(TOP)targets.mk
