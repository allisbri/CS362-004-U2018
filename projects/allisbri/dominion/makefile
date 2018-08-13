CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

betterTestDrawCard: betterTestDrawCard.c dominion.o rngs.o
	gcc -o betterTestDrawCard -g  betterTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestresults: dominion.o randomtestadventurer.c randomtestcard1.c rngs.o
	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	
	echo "randomtestcard1.c:" >> randomtestcard1.out
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	
	echo "randomtestcard2.c:" >> randomtestcard2.out
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	
unittestresults: dominion.o unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c  cardtest4.c rngs.o
	echo "Result for running unit tests:" > unittestingresults.out
	
	echo "cardtest1.c:" >> unittestingresults.out
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	cardtest1 >> unittestingresults.out
	gcov dominion.c >> unittestingresults.out
	cat dominion.c.gcov >> unittestingresults.out
	
	echo "cardtest2.c:" >> unittestingresults.out
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	cardtest2 >> unittestingresults.out
	gcov dominion.c >> unittestingresults.out
	cat dominion.c.gcov >> unittestingresults.out
	
	echo "cardtest3.c:" >> unittestingresults.out
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	cardtest3 >> unittestingresults.out
	gcov dominion.c >> unittestingresults.out
	cat dominion.c.gcov >> unittestingresults.out
	
	echo "cardtest4.c:" >> unittestingresults.out
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	cardtest4 >> unittestingresults.out
	gcov dominion.c >> unittestingresults.out
	cat dominion.c.gcov >> unittestingresults.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe