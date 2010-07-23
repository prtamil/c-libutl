# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#

TOP=../
UNC=$(TOP)examples/uncomment

include $(TOP)config.mk

LIBSRC = utl.c pmx.c chs.c tbl.c 
LIBHDR = utl.h pmx.h chs.h tbl.h
LIBOBJ = chs$(_OBJ) pmx$(_OBJ) \
         tbl$(_OBJ) utl$(_OBJ)

libutl$(_LIB) : $(LIBOBJ) 
	$(AR) $@ $(LIBOBJ)
	$(CP) $@ $(DIST)
	$(CP) $(LIBOBJ) $(DIST)

chs$(_OBJ) : libutl.h
pmx$(_OBJ) : libutl.h
tbl$(_OBJ) : libutl.h
utl$(_OBJ) : libutl.h

libutl.h : $(LIBHDR)
	echo "#ifndef LIBUTL_H"   > $@
	echo "#define LIBUTL_H"  >> $@
	echo "#line 1 \"utl.h\"" >> $@
	$(CAT) utl.h             >> $@
	echo "#line 1 \"pmx.h\"" >> $@
	$(CAT) pmx.h             >> $@
	echo "#line 1 \"chs.h\"" >> $@
	$(CAT) chs.h             >> $@
	echo "#line 1 \"tbl.h\"" >> $@
	$(CAT) tbl.h             >> $@
	echo "#endif "           >> $@
	$(CP) $@ $(DIST)

clean:
	$(RM) libutl.h
	$(RM) libutl$(_LIB)
	$(RM) $(LIBOBJ)
	$(RM) $(DIST)/*
	$(RM) gmon.out
	$(RM) *.gc??

gdb_t2: t2$(_EXE) XXX
	-$(GDB) t2

t2$(_EXE): tbl2.c tbl2.h
	gcc -g -o t2 tbl2.c

XXX:

include $(TOP)targets.mk
