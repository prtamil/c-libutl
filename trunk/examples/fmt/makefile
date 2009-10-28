# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This sofwtare is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#
 
TOP=../../

include $(TOP)config.mk

fmt$(_EXE): $(CHKLIB) fmt$(_OBJ)
	$(LN)$@ fmt$(_OBJ) -lutl

clean:
	$(RM) fmt$(_EXE)
	$(RM) fmt$(_OBJ)
	$(RM) gmon.out

include $(TOP)targets.mk
