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

int main() {
    int seed = 1000;
    int numPlayer = MAX_PLAYERS;
	int handCount = 5;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int testPassCount = 0;
	int testFailCount = 0;
	int totalTests;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 3;
	int bonus = 0;
	int i;
	
	int p1ExHandCount;
	int p1AcHandCount;
	int p2AcHandCount;
	int p3AcHandCount;
	int p4AcHandCount;
	int p1ExDeckCount;
	int p1AcDeckCount;
	int p2AcDeckCount;
	int p3AcDeckCount;
	int p4AcDeckCount;
	int deckCount = 4; 

	int hand1[5] = {great_hall, baron, village, smithy, remodel};
	int hand2[5] = {adventurer, council_room, feast, gardens, mine};
	int hand3[5] = {feast, council_room, remodel, mine, smithy};
	int hand4[5] = {village, council_room, feast, mine, remodel};
	int deck[4] = {copper, copper, copper, copper};
	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("TESTING village:\n");
	
    G.whoseTurn = 0;
	G.handCount[0] = handCount;  
	G.handCount[1] = handCount;
	G.handCount[2] = handCount;
	G.handCount[3] = handCount;
	G.deckCount[0] = deckCount;  
	G.deckCount[1] = deckCount;
	G.deckCount[2] = deckCount;
	G.deckCount[3] = deckCount;
	
	memcpy(G.hand[0], hand1, sizeof(int) * handCount);
	memcpy(G.hand[1], hand2, sizeof(int) * handCount);
	memcpy(G.hand[2], hand3, sizeof(int) * handCount);
	memcpy(G.hand[3], hand4, sizeof(int) * handCount);
	
	int sCount[25]; 
	memcpy(G.deck[0], deck, sizeof(int) * deckCount);
	memcpy(G.deck[1], deck, sizeof(int) * deckCount);
	memcpy(G.deck[2], deck, sizeof(int) * deckCount);
	memcpy(G.deck[3], deck, sizeof(int) * deckCount);
	memcpy(sCount, G.supplyCount, sizeof(int) * 25);
	
	int numActionsBefore = G.numActions;
	cardEffect(village, choice1, choice2, choice3, &G, handPos, &bonus);
	
	printf("\ntest 1: player 1 recieves 1 cards, other players do not recieve any\n");
	p1ExHandCount = handCount; //accounting for discarded village
	p1AcHandCount = G.handCount[0];
	p2AcHandCount = G.handCount[1];
	p3AcHandCount = G.handCount[2];
	p4AcHandCount = G.handCount[3];
	printf("player 1: Expected handCount: %d  Actual handCount: %d\n", p1ExHandCount, p1AcHandCount); 
	printf("player 2: Expected handCount: %d  Actual handCount: %d\n", handCount, p2AcHandCount); 
	printf("player 3: Expected handCount: %d  Actual handCount: %d\n", handCount, p3AcHandCount); 
	printf("player 4: Expected handCount: %d  Actual handCount: %d\n", handCount, p4AcHandCount); 
	if (p1ExHandCount == p1AcHandCount && p2AcHandCount == handCount && p3AcHandCount == handCount && p4AcHandCount == handCount){
		printf("passed test 1\n");
		testPassCount++;
	}
	else{
		printf("failed test 1\n");
		testFailCount++;
	}
	
	printf("\ntest 2: player 1's deck is down 1 card, other players decks do not change\n");
	p1ExDeckCount = deckCount - 1;
	p1AcDeckCount = G.deckCount[0];
	p2AcDeckCount = G.deckCount[1];
	p3AcDeckCount = G.deckCount[2];
	p4AcDeckCount = G.deckCount[3];	
	printf("player 1: Expected deckCount: %d  Actual deckCount: %d\n", p1ExDeckCount, p1AcDeckCount); 
	printf("player 2: Expected deckCount: %d  Actual deckCount: %d\n", deckCount, p2AcDeckCount); 
	printf("player 3: Expected deckCount: %d  Actual deckCount: %d\n", deckCount, p3AcDeckCount); 
	printf("player 4: Expected deckCount: %d  Actual deckCount: %d\n", deckCount, p4AcDeckCount); 			
	if (p1ExDeckCount == p1AcDeckCount && p2AcDeckCount == deckCount && p3AcDeckCount == deckCount && p4AcDeckCount == deckCount){
		printf("passed test 2\n");
		testPassCount++;
	}
	else{
		printf("failed test 2\n");
		testFailCount++;
	}
	
	printf("\ntest 3: no changes to province or kindom card piles\n");
	int test3FailCount = 0;
	for (i = 0; i < 25; i++){
		printf("Expected supplyCount: %d  Actual supplyCount: %d\n", sCount[i], G.supplyCount[i]);
		if (sCount[i] != G.supplyCount[i]){
			test3FailCount++;
		}
	}
	if (test3FailCount > 0){
		printf("failed test 3\n");
		testFailCount++;
	}
	else{
		printf("passed test 3\n");
		testPassCount++;
	}
	
	printf("\ntest 4: card from player1's deck added to hand");
	printf("Expected card1: %d  \n", deck[0]);
	printf("Actual card1: %d \n", G.deck[0][4]);
	if(deck[0] == G.deck[0][4]){
		printf("passed test 4\n");
		testPassCount++;
	}
	else{
		printf("failed test 4\n");
		testFailCount++;
	}
	
	printf("\ntest 5: actions increased by 1");
	int expectedNumActions = numActionsBefore + 2;
	printf("Expected num actions: %d  \n", expectedNumActions);
	printf("Actual num actions: %d \n", G.numActions);
	if(expectedNumActions == G.numActions){
		printf("passed test 4\n");
		testPassCount++;
	}
	else{
		printf("failed test 4\n");
		testFailCount++;
	}
	
	totalTests = testFailCount + testPassCount;
	printf("Passed %d out of %d tests\n", testPassCount, totalTests);
	return 0;
}
	

