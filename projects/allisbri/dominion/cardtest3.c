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

int testPassCount = 0;
int testFailCount = 0;

void testAdventurer(int *totalTests, int *testPassCount, int *testFailCount, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus) {
  int r;
  r = cardEffect(great_hall, choice1, choice2, choice3, state, handPos, bonus);
  printf("returned from cardEffect\n");
  if (r == 0){
	  printf("passed great_hall call test\n");
	  testPassCount++;
  }
  else{
	  printf("failed great_hall call test\n");
	  testFailCount++;
  }
}

int main() {
    //int seed = 1000;
    //int numPlayer = MAX_PLAYERS;
	int handCount = 5;
	int p;
	int c;
	int cd;
	int fd;
	int f;
	int exHand[] = {-1, -1, -1, -1};
	int exDeck[] = {-1, -1, -1, -1};
	int exDiscard[] = {-1, -1, -1, -1};
 
    struct gameState G;
	int totalTests;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos;
	int bonus = 0;
	int i;

    printf("TESTING great_hall:\n");
	
	int p;
	int c;
	int exHand[] = {-1, -1, -1, -1};
	int exDeck[] = {-1, -1, -1, -1};
	int sCount[25]; 
	int closest;
	int closest2;
	int expectedNumActions;
	
    struct gameState G;
	int randHandSelect;
	int totalTests;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 1;
	int bonus = 0;
	int i;
	int j;
	int n;

	SelectStream(2);
	PutSeed(3);

    printf("TESTING great_hall:\n");
	
	for (n = 0; n < 2000; n++) {
		c = 0;

		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = floor(Random() * 4);
		G.numPlayers = floor(Random() * 4) + 1;
		if (p >= G.numPlayers){
			G.numPlayers = p + 1;
		}
		G.whoseTurn = p;
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		for (j = 0; j < G.handCount[p]; j++){
			G.hand[p][j] = floor(Random() * 27);
		}
		
		for (j = 0; j < G.discardCount[p]; j++){
			G.discard[p][j] = floor(Random() * 27);	
		}
		
		for (j = 0; j < G.deckCount[p]; j++){
			G.deck[p][j] = floor(Random() * 27);
		}
		
		for (j = 0; j < G.numPlayers; j++){
			if (j == p){
				exDeck[j] = G.deckCount[p];
				exDiscard[j] = G.discardCount[p] + 1;
				exHand[j] = G.handCount[p];
			}
			else{
				exDeck[j] = G.deckCount[j];
				exDiscard[j] = G.discardCount[j];
				exHand[j] = G.handCount[j];
			}
		}

	expectedNumActions = G.numActions + 1;
	cardEffect(great_hall, choice1, choice2, choice3, &G, handPos, &bonus);
	
	printf("\ntest 1: player 1 recieves 1 cards, other players do not recieve any\n");
	for (j = 0; j < G.numPlayers; j++){
			if (exHand[j] == G.handCount[j]){
				printf("passed test 1 for player %d with expected %d and actual %d\n", j, exHand[j], G.handCount[j]);
				testPassCount++;
			}
			else{
				printf("failed test 1 for player %d with expected %d and actual %d \n", j, exHand[j], G.handCount[j]);
				testFailCount++;
			}
	}
	
	printf("\ntest 2: player 1's deck is down 1 card, other players decks do not change\n");
	for (j = 0; j < G.numPlayers; j++){
			if (exDeck[j] == G.deckCount[j]){
				printf("passed test 2 for player %d with expected %d and actual %d\n", j, exDeck[j], G.deckCount[j]);
				testPassCount++;
			}
			else{
				printf("failed test 2 for player %d with exDeck %d and exNow %d\n", j, exDeck[j], G.deckCount[j]);
				testFailCount++;
			}
	}
	
	printf("\ntest 3: no changes to province or kindom card piles\n");
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
	
	printf("\ntest 4: actions increased by 1");
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
}
	

