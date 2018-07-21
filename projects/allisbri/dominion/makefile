CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: tests.out

tests.out: unittest1.c dominion.c
	echo "Result for running tests:" > tests.out
	
	echo "unittest1.c:" >> tests.out
	gcc -o unittest1 compare.c bst.c unittest1.c $(CFLAGS)
	unittest1 >> tests.out
	gcov bst.c >> tests.out

clean:
	rm tests.out

cleanall: 
	rm tests.out unittest1 *.gcda *.gcno *.gcov
