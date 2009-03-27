# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This sofwtare is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#
 
TOP=../../

include $(TOP)config.mk

mpnotes$(_EXE): $(CHKLIB) mpnotes$(_OBJ)
	$(LN)$@ mpnotes$(_OBJ) -lutl

clean:
	$(RM) mpnotes$(_EXE)
	$(RM) mpnotes$(_OBJ)
	$(RM) gmon.out

include $(TOP)targets.mk
