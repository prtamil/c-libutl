# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This sofwtare is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#
 
TOP = ../../

include $(TOP)config.mk

pmx2c$(_EXE) : $(CHKLIB) pmx2b$(_EXE) pmx2c.pmx
	./pmx2b pmx2c.pmx pmx2c.c
	$(CC) $(CFLAGS) -c -o pmx2c$(_OBJ) pmx2c.c
	$(LN)$@ pmx2c$(_OBJ) -lutl
	$(CP) $@ $(DIST)

pmx2b$(_EXE) : pmx2a$(_EXE) pmx2c.pmx
	./pmx2a pmx2c.pmx pmx2c.c
	$(CC) $(CFLAGS) -c -o pmx2c$(_OBJ) pmx2c.c
	$(LN)$@ pmx2c$(_OBJ) -lutl

pmx2a$(_EXE) : pmx2c_boot.c pmx2c.pmx
	$(CC) $(CFLAGS) -c -o pmx2c$(_OBJ) pmx2c_boot.c
	$(LN)$@ pmx2c$(_OBJ) -lutl

clean:
	$(RM) pmx2a$(_EXE)
	$(RM) pmx2b$(_EXE)
	$(RM) pmx2c$(_EXE)
	$(RM) $(DIST)/pmx2c$(_EXE)
	$(RM) pmx2c$(_OBJ)
	$(RM) pmx2c.c
	$(RM) gmon.out

include $(TOP)targets.mk
