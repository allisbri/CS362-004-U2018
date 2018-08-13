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
	int handPos = 1;
	int bonus = 0;
	int i;
	int j;
	int c;
	int closest;
	int closest2;
	int x;
	int expectedCard1;
	int expectedCard2;
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
	int hand1[5] = {adventurer, baron, village, smithy, remodel};
	int hand2[5] = {adventurer, council_room, feast, gardens, mine};
	int hand3[5] = {feast, council_room, remodel, mine, smithy};
	int hand4[5] = {village, council_room, feast, mine, remodel};
	int d1[5] = {village, village, village, village, village};
	int d2[5] = {adventurer, council_room, feast, gardens, mine};
	int d3[5] = {feast, council_room, remodel, mine, smithy};
	int d4[5] = {village, council_room, feast, mine, remodel};
	int deckA[4] = {copper, copper, copper, copper};
	int deckB[4] = {steward, adventurer, council_room, feast};
	int deckC[4] = {silver, silver, silver, silver};
	int deckD[4] = {remodel, adventurer, council_room, silver};
	int deckE[4] = {gold, gold, gold, gold};

    printf("TESTING adventurer:\n");
	
	for (j = 0; j < 5; j++){
		c = 0;
		handCount = 5;
		closest = -1;
		closest2 = -1;
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &G); // initialize a new game
		G.whoseTurn = 0;
		G.handCount[0] = 5;  
		G.handCount[1] = 5;
		G.handCount[2] = 5;
		G.handCount[3] = 5;
		G.deckCount[0] = 4;  
		G.deckCount[1] = 4;
		G.deckCount[2] = 4;
		G.deckCount[3] = 4;
		G.discardCount[0] = 5;
		G.discardCount[1] = 5;
		G.discardCount[2] = 5;
		G.discardCount[3] = 5;
		
		memcpy(G.discard[0], d1, sizeof(int) * handCount);
		memcpy(G.discard[1], d2, sizeof(int) * handCount);
		memcpy(G.discard[2], d3, sizeof(int) * handCount);
		memcpy(G.discard[3], d4, sizeof(int) * handCount);
		
		memcpy(G.hand[0], hand1, sizeof(int) * handCount);
		
		int sCount[25]; 
		if (j == 0){
			memcpy(G.deck[0], deckA, sizeof(int) * deckCount);
		}
		else if (j == 1){
			memcpy(G.deck[0], deckB, sizeof(int) * deckCount);
		}
		else if (j == 2){
			memcpy(G.deck[0], deckC, sizeof(int) * deckCount);
		}
		else if (j == 3){
			memcpy(G.deck[0], deckD, sizeof(int) * deckCount);
		}
		else if (j == 4){
			memcpy(G.deck[0], deckE, sizeof(int) * deckCount);
		}
		
		memcpy(G.deck[1], deckB, sizeof(int) * deckCount);
		memcpy(G.deck[2], deckC, sizeof(int) * deckCount);
		memcpy(G.deck[3], deckD, sizeof(int) * deckCount);
		memcpy(sCount, G.supplyCount, sizeof(int) * 25);
		for (x = 0; x < G.deckCount[0]; x++){
			if (G.deck[0][x] == silver || G.deck[0][x] == gold || G.deck[0][x] == copper){
				c++;
				closest2 = closest;
				closest = x;
			}
		}
		
		cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
		
		printf("\ntest 1: player 1 recieves correct number of cards, other players do not recieve any\n");
		if (j == 0){
			p1ExHandCount = handCount + 1; //accounting for discarded adventurer
		}
		else if (j == 1){
			p1ExHandCount = handCount - 1; //accounting for discarded adventurer
		}
		else if (j == 2){
			p1ExHandCount = handCount + 1; //accounting for discarded adventurer
		}
		else if (j == 3){
			p1ExHandCount = handCount; //accounting for discarded adventurer
		}
		else if (j == 4){
			p1ExHandCount = handCount + 1; //accounting for discarded adventurer
		}
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
		
		printf("\ntest 2: player 1's deck is down by correct number of cards, other players decks do not change\n");
		
		if (j == 0){
			p1ExDeckCount = closest2;  
		}
		else if (j == 1){
			p1ExDeckCount = 0;  
		}
		else if (j == 2){
			p1ExDeckCount = closest2;  
		}
		else if (j == 3){
			p1ExDeckCount = closest;  
		}
		else if (j == 4){
			p1ExDeckCount = closest2;  
		}
		
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
		
		printf("\ntest 4: correct cards from player1's deck added to hand");
		if (j == 0){
			expectedCard1 = copper;
			expectedCard2 = copper;
		}
		else if (j == 1){
			expectedCard1 = G.hand[0][handCount - 2];
			expectedCard2 = G.hand[0][handCount - 1];
		}
		else if (j == 2){
			expectedCard1 = silver;
			expectedCard2 = silver; 
		}
		else if (j == 3){
			expectedCard1 = silver;
			expectedCard2 = G.hand[0][handCount - 1]; 
		}
		else if (j == 3){
			expectedCard1 = gold;
			expectedCard2 = gold; 
		}
		
		printf("Expected card1: %d  card2: %d\n", expectedCard1, expectedCard2);
		printf("Actual card1: %d  card2: %d\n", G.hand[0][handCount - 2], G.hand[0][handCount - 1]);
		if(expectedCard1 == G.hand[0][handCount - 2] && expectedCard2 == G.hand[0][handCount - 1]){
			printf("passed test 4\n");
			testPassCount++;
		}
		else{
			printf("failed test 4\n");
			testFailCount++;
		}
	}
	totalTests = testFailCount + testPassCount;
	printf("Passed %d out of %d tests\n", testPassCount, totalTests);
	return 0;
}
	

