# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#

TOP=./

include $(TOP)config.mk

all: FORCE
	cd src ; make CCOPTS="$(CCOPTS)" LNOPTS="$(LNOPTS)"
	cd examples/pmx2c ; make CCOPTS="$(CCOPTS)" LNOPTS="$(LNOPTS)"
	cd examples/pmxshell ; make CCOPTS="$(CCOPTS)" LNOPTS="$(LNOPTS)"
        
release: FORCE
	cd src ; make release
	cd examples/pmx2c ; make release
	cd examples/pmxshell ; make release
	
debug: FORCE
	cd src ; make debug
	cd examples/pmx2c ; make debug
	cd examples/pmxshell ; make debug
	
profile: FORCE
	cd src ; make profile
	cd examples/pmx2c ; make profile
	cd examples/pmxshell ; make profile

clean:
	cd src ; make clean
	cd examples ; make clean

dist: FORCE
	make clean
	cd src ; make release
	cd examples/pmx2c ; make release
	cd examples/pmxshell ; make release
	strip dist/pmx2c$(_EXE)
	strip dist/pmxshell$(_EXE)

FORCE: 
