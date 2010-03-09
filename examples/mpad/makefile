# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#
 
TOP=../../
NAME=mpad

include $(TOP)config.mk

$(NAME)$(_EXE): $(CHKLIB) $(NAME)$(_OBJ)
	$(LN)$@ $(NAME)$(_OBJ) -lutl

clean:
	$(RM) $(NAME)$(_EXE)
	$(RM) $(NAME)$(_OBJ)
	$(RM) gmon.out

include $(TOP)targets.mk
