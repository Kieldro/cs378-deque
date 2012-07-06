# file variables
source="Deque.h"
unitFile="TestDeque.c++"
outFile="TestDeque.out"

clear
echo COMPILING $source and $unitFile...
g++ -ansi -pedantic -ldl -Wall $unitFile -lcppunit -o $unitFile.app
	if ([ $? == 0 ]); then
echo RUNNING UNIT TESTS...
./$unitFile.app #>& $outFile
	fi

<<MULTICOMMENT
echo CHECKING OUTPUT...; diff -lc RunInteger.out RunInteger.in

echo GENERATING COMMIT LOG...
git log > Deque.log

#echo RUNNING DOXYGEN...; doxygen Doxyfile

zip Deque README.txt html/* Deque.h Deque.log TestDeque.c++ TestDeque.out

turnin --submit inbleric cs378pj4 Deque.zip
MULTICOMMENT
