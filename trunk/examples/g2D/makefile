# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This sofwtare is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#
 
TOP=../../

include $(TOP)config.mk

gr2D$(_EXE): $(CHKLIB) gr2D$(_OBJ)
	$(LN)$@ gr2D$(_OBJ) -lutl

clean:
	$(RM) gr2D$(_EXE)
	$(RM) gr2D$(_OBJ)
	$(RM) gmon.out

include $(TOP)targets.mk