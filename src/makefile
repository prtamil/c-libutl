# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#

TOP=../

include $(TOP)config.mk

LIBSRC = chs.c pmx.c tbl.c utl.c
LIBHDR = utl.h pmx.h chs.h tbl.h
LIBOBJ = chs$(_OBJ) pmx$(_OBJ) tbl$(_OBJ) utl$(_OBJ)

libutl$(_LIB) : $(LIBOBJ) 
	$(AR) $@ $(LIBOBJ)
	$(CP) $@ $(DIST)
	$(CP) $(LIBOBJ) $(DIST)

$(LIBSRC) : libutl.h

libutl.h : $(LIBHDR)
	$(CAT) $(LIBHDR) > $@
	$(CP) $@ $(DIST)

clean:
	$(RM) libutl.h
	$(RM) $(DIST)/libutl.h
	$(RM) libutl$(_LIB)
	$(RM) $(DIST)/libutl$(_LIB)
	$(RM) $(LIBOBJ)
	$(RM) gmon.out

include $(TOP)targets.mk
