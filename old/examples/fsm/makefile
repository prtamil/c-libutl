# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This sofwtare is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#
 
TOP=../../

include $(TOP)config.mk

fsm$(_EXE): $(CHKLIB) fsm$(_OBJ)
	$(LN)$@ fsm$(_OBJ) -lutl

clean:
	$(RM) fsm$(_EXE)
	$(RM) fsm$(_OBJ)
	$(RM) gmon.out

include $(TOP)targets.mk
