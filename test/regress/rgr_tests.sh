# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#

O=""

NAMES=`ls rgr_*.c | sed 's/\.c//'`

echo "RGR_TESTS=`ls rgr_*.c | sed 's/\.c/\$(_EXE)\\\\/'`"
echo

echo "all: \$(RGR_TESTS)"
echo

for NAME in $NAMES
do
  echo "$NAME\$(_EXE): \$(CHKLIB) $NAME\$(_OBJ)"
	echo "	\$(LN)\$@ $NAME\$(_OBJ) -lutl"
  echo
  O="$O $NAME\$(_OBJ)"
done 

echo "RGR_OBJS=$O"
echo
