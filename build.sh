# file variables
source="Deque.h"
unitFile="TestDeque.c++"
outFile="TestDeque.out"

clear
echo COMPILING $source and $unitFile...
g++ -ansi -pedantic -ldl -Wall $unitFile -lcppunit -o $unitFile.app
	if ([ $? == 0 ]); then
echo RUNNING UNIT TESTS...
valgrind ./$unitFile.app >& $outFile
	fi


echo GENERATING COMMIT LOG...
git log > Deque.log

echo RUNNING DOXYGEN...
#doxygen -g
# EXTRACT_ALL            = YES
# EXTRACT_PRIVATE        = YES
# EXTRACT_STATIC         = YES
# GENERATE_LATEX         = NO
doxygen Doxyfile

zip Deque README.txt html/* Deque.h Deque.log TestDeque.c++ TestDeque.out

turnin --submit inbleric cs378pj4 Deque.zip
turnin --list   inbleric cs378pj4
turnin --verify inbleric cs378pj4

MULTICOMMENT
