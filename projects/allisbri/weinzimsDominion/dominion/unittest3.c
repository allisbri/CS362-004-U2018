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
    int p, handCount, handPos;
	handCount = 10;
	int expectedCard;
	int actualCard;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int testPassCount = 0;
	int testFailCount = 0;
	
    int hand1[MAX] = {great_hall, baron, village, smithy, remodel, mine, gardens, feast, council_room, adventurer};
	int hand2[MAX] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int hand3[MAX] = {feast, council_room, remodel,smithy, mine, village, adventurer,  gardens, great_hall, baron};
	int hand4[MAX] = {village, council_room, feast, mine, remodel, smithy, adventurer,  great_hall, baron, gardens};
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G); // initialize a new game
	G.handCount[0] = handCount;  
	G.handCount[1] = handCount;
	G.handCount[2] = handCount;
	G.handCount[3] = handCount;
	
	memcpy(G.hand[0], hand1, sizeof(int) * handCount);
	memcpy(G.hand[1], hand2, sizeof(int) * handCount);
	memcpy(G.hand[2], hand3, sizeof(int) * handCount);
	memcpy(G.hand[3], hand4, sizeof(int) * handCount);
    printf("TESTING handCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
			for (handPos = 0; handPos < MAX; handPos++)
			{
					G.whoseTurn = p;
					printf("Test 1: correct card return for player %d, handPos: %d\n", p, handPos);
					if (p == 0){
						expectedCard = hand1[handPos];
						actualCard = handCard(handPos, &G);
						printf("expected card: %d, handPos: %d\n", expectedCard, actualCard); 
						if (expectedCard == actualCard){
							printf("Passed: correct card\n");
							testPassCount++;
						}
						else{
							printf("Fail: incorrect card\n");
							testFailCount++;
						}
					}
					if (p == 1){
						expectedCard = hand2[handPos];
						actualCard = handCard(handPos, &G);
						printf("expected card: %d, handPos: %d\n", expectedCard, actualCard); 	
						if (expectedCard == actualCard){
							printf("Passed: correct card\n");
							testPassCount++;
						}
						else{
							printf("Fail: incorrect card\n");
							testFailCount++;
						}
					}
					if (p == 2){
						expectedCard = hand3[handPos];
						actualCard = handCard(handPos, &G);
						printf("expected card: %d, handPos: %d\n", expectedCard, actualCard); 	
						if (expectedCard == actualCard){
							printf("Passed: correct card\n");
							testPassCount++;
						}
						else{
							printf("Fail: incorrect card\n");
							testFailCount++;
						}
					}
					if (p == 3){
						expectedCard = hand4[handPos];
						actualCard = handCard(handPos, &G);
						printf("expected card: %d, handPos: %d\n", expectedCard, actualCard); 
						if (expectedCard == actualCard){
							printf("Passed: correct card\n");
							testPassCount++;
						}
						else{
							printf("Fail: incorrect card\n");
							testFailCount++;
						}						
					}
				
			}
	}
	int totalTests = testPassCount + testFailCount;
	printf("Passed %d out of %d tests\n", testPassCount, totalTests);

	return 0;
}
	

