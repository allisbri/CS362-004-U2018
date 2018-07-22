/* -----------------------------------------------------------------------
 * Much of the code used in "demonstration of how to write unit tests for dominion-base" from OSU CS362
 * is used in this file as a template.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define MAX 10

int main() {
    int seed = 1000;
    int numPlayer = MAX_PLAYERS;
    int p, handCount;

	int expectedCount;
	int actualCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int testPassCount = 0;
	int testFailCount = 0;
	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("TESTING numHandCards():\n");
    for (p = 0; p < numPlayer; p++)
    {
			for (handCount = 1; handCount <= MAX; handCount++)
			{
				G.whoseTurn = p;
				G.handCount[p] = handCount;  
					
				printf("p: %d, handCount: %d\n", p, handCount); 
				numHandCards(&G);
				expectedCount = handCount;
				actualCount = numHandCards(&G);
				printf("expected count: %d, actual count: %d\n", expectedCount, actualCount); 
				if (expectedCount == actualCount){
					printf("Passed test\n");
					testPassCount++;
				}
				else{
					printf("Failed test\n");
					testFailCount++;
				}
			}
	}
	int totalTests = testPassCount + testFailCount;
	printf("Passed %d out of %d tests\n", testPassCount, totalTests);

	return 0;
}
	

