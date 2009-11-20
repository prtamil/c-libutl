# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#
 
TOP=../../

include $(TOP)config.mk

OBJ_S=tbl_1$(_OBJ)
PRG_S=tbl_1$(_EXE)

tbl_1$(_EXE): $(CHKLIB) tbl_1$(_OBJ)
	$(LN)$@ tbl_1$(_OBJ) -lutl

clean:
	$(RM) $(PRG_S)
	$(RM) $(OBJ_S)
	$(RM) gmon.out

include $(TOP)targets.mk
