# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This sofwtare is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#
 
TOP=../../

include $(TOP)config.mk

pmxshell$(_EXE): $(CHKLIB) pmxshell$(_OBJ)
	$(LN)$@ pmxshell$(_OBJ) -lutl
	$(CP) $@ $(DIST)

clean:
	$(RM) pmxshell$(_EXE)
	$(RM) pmxshell$(_OBJ)
	$(RM) $(DIST)/pmxshell$(_EXE)
	$(RM) gmon.out

include $(TOP)targets.mk
