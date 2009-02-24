# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#
 
TOP=../../

include $(TOP)config.mk

uncomment$(_EXE): $(CHKLIB) uncomment$(_OBJ)
	$(LN)$@ uncomment$(_OBJ) -lutl

clean:
	$(RM) uncomment$(_EXE)
	$(RM) uncomment$(_OBJ)
	$(RM) gmon.out

include $(TOP)targets.mk
