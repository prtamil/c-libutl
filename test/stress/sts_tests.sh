# 
#  (C) by Remo Dentato (rdentato@gmail.com)
# 
# This software is distributed under the terms of the BSD license:
#   http://creativecommons.org/licenses/BSD/
#   http://opensource.org/licenses/bsd-license.php
#

O=""

NAMES=`ls sts_*.c | sed 's/\.c//'`

echo "STS_TESTS=`ls sts_*.c | sed 's/\.c/\$(_EXE)\\\\/'`"
echo

echo "all: \$(STS_TESTS)"
echo

for NAME in $NAMES
do
  echo "$NAME\$(_EXE): \$(CHKLIB) $NAME\$(_OBJ)"
	echo "	\$(LN)\$@ $NAME\$(_OBJ) -lutl"
  echo
  O="$O $NAME\$(_OBJ)"
done 

echo "STS_OBJS=$O"
echo
 