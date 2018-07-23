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

#define MAX 20

int main() {
    int seed = 1000;
    int numPlayer = MAX_PLAYERS;
    int p, handCount, deckCount, discardCount;
	p = 0;
	int dCount;
	int expectedCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int testPassCount = 0;
	int testFailCount = 0;
	
    int hand1[MAX] = {[0 ... (MAX - 1)] = adventurer};
	int deck1[MAX] = {[0 ... (MAX - 1)] = adventurer};
	int discard1[MAX] = {[0 ... (MAX - 1)] = adventurer};
	
	int hand2[MAX] = {[0 ... 19] = copper};
	int deck2[MAX] = {[0 ... (MAX - 1)] = copper};
	int discard2[MAX] = {[0 ... (MAX - 1)] = copper};
	
    printf("TESTING fullDeckCount():\n");
    for (handCount = 1; handCount <= MAX; handCount++)
    {
		for (deckCount = 0; deckCount <= MAX; deckCount++)
		{
			for (discardCount = 0; discardCount <= MAX; discardCount++)
			{
					printf("p: %d, handCount: %d, deckCount: %d, discardCount: %d\n", p, handCount, deckCount, discardCount); 
					memset(&G, 23, sizeof(struct gameState));   // clear the game state
					initializeGame(numPlayer, k, seed, &G); // initialize a new game
					G.handCount[p] = handCount;                 // set the number of cards on hand
					G.deckCount[p] = deckCount;
					G.discardCount[p] = discardCount;
					memcpy(G.hand[p], hand1, sizeof(int) * handCount); // set all the hand cards to adventurer
					memcpy(G.deck[p], deck1, sizeof(int) * deckCount); // set all the deck cards to adventurer
					memcpy(G.discard[p], discard1, sizeof(int) * discardCount); //set all the discard cards to adventurer
					
					expectedCount = handCount + deckCount + discardCount;
					dCount = fullDeckCount(p, adventurer, &G);

					printf("\nTest 1: all adventurer count\n");
					printf("Expected full deck count: %d, Actual full deck count: %d\n", expectedCount, dCount);

					if (expectedCount == dCount){
						printf("passed full deck adventurer count test and");
						testPassCount++;
					}
					else{
						printf("failed full deck adventurer count test\n");
						testFailCount++;
					}
					
					memset(&G, 23, sizeof(struct gameState));   // clear the game state
					initializeGame(numPlayer, k, seed, &G); // initialize a new game
					G.handCount[p] = handCount;                 // set the number of cards on hand
					G.deckCount[p] = deckCount;
					G.discardCount[p] = discardCount;                // set the number of cards on hand
					memcpy(G.hand[p], hand2, sizeof(int) * handCount); // set all the hand cards to adventurer
					memcpy(G.deck[p], deck2, sizeof(int) * deckCount); // set all the deck cards to adventurer
					memcpy(G.discard[p], discard2, sizeof(int) * discardCount); //set all the discard cards to adventurer
					
					printf("\nTest 2: no adventurer count\n");
					expectedCount = 0;
					dCount = fullDeckCount(p, adventurer, &G);
					printf("\nall cards copper -- adventurer count test:\n");

					printf("Expected full deck count: %d, Actual full deck count: %d\n", expectedCount, dCount);

					if (expectedCount == dCount){
						printf("passed full deck copper -- adventurer count test\n");
						testPassCount++;
					}
					else{
						printf("failed full deck copper -- adventurer count test\n");
						testFailCount++;
					}	
				
			}
		}
	}
	int totalTests = testPassCount + testFailCount;
	printf("Passed %d out of %d tests\n", testPassCount, totalTests);

	return 0;
}
	

