# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#

all:
	cd pmx2c; make CCOPTS="$(CCOPTS)" LNOPTS="$(LNOPTS)"
	cd pmxshell; make CCOPTS="$(CCOPTS)" LNOPTS="$(LNOPTS)"
	cd uncomment; make CCOPTS="$(CCOPTS)" LNOPTS="$(LNOPTS)"
	cd cxrf; make CCOPTS="$(CCOPTS)" LNOPTS="$(LNOPTS)"

clean:
	cd pmx2c; make clean
	cd pmxshell; make clean
	cd uncomment; make clean
	cd cxrf; make clean
