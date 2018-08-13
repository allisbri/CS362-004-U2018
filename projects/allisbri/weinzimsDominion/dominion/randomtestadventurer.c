 /* Brian Allison
 *  CS362
 *  Description: This is a random tester for adventurer card
 * -----------------------------------------------------------------------
 * Some of the code here is similar to the code used in "betterTestDrawCard.c" from OSU CS362.
 * That file was used as a template for this test.
 * -----------------------------------------------------------------------
 *
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testPassCount = 0;
int testFailCount = 0;

void testAdventurer(int *totalTests, int *testPassCount, int *testFailCount, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus) {
  int r;
  r = cardEffect(adventurer, choice1, choice2, choice3, state, handPos, bonus);
  printf("returned from cardEffect\n");
  if (r == 0){
	  printf("passed adventurer call test\n");
	  testPassCount++;
  }
  else{
	  printf("failed adventurer call test\n");
	  testFailCount++;
  }
}

int main() {
    //int seed = 1000;
    //int numPlayer = MAX_PLAYERS;
	//int handCount = 5;
	int p;
	int c;
	int cd;

	int exHand[] = {-1, -1, -1, -1};
	int exDeck[] = {-1, -1, -1, -1};
	int sCount[25]; 
	int closest;
	int closest2;
	
    struct gameState G;
	int randHandSelect;
	int totalTests;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;

	int bonus = 0;
	int i;
	int j;
	int n;

	SelectStream(2);
	PutSeed(3);

    printf("TESTING adventurer:\n");
	
	for (n = 0; n < 2000; n++) {
		c = 0;
		cd = 0;

		closest = -1;
		closest2 = -1;
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
			if (G.deck[p][j] == silver || G.deck[p][j] == gold || G.deck[p][j] == copper){
				c++;
				closest2 = closest;
				closest = j;
			}
		}
		
		for (j = 0; j < G.discardCount[p]; j++){
			G.discard[p][j] = floor(Random() * 27);
			if (G.discard[p][j] == silver || G.discard[p][j] == gold || G.discard[p][j] == copper){
				cd++;
			}
		}
		
		randHandSelect = floor(Random() * G.handCount[p]);
		G.hand[p][randHandSelect] = adventurer;
		
		//set up expected counts for all players
		for (j = 0; j < G.numPlayers; j++){
			if (j == p){
				if (c == 0){
					exHand[p] = G.handCount[p] - 1; //accounting for discarded adventurer
					exDeck[p] = G.deckCount[p]; 
					printf("exDeck is %d and acDeck is %d for this\n", exDeck[p], G.deckCount[p]);
				}
				else if (c == 1){
					exHand[p] = G.handCount[p]; //accounting for discarded adventurer
					exDeck[p] = closest;
				}
				else if (c > 1){
					exHand[p] = G.handCount[p] + 1; //accounting for discarded adventurer
					exDeck[p] = closest2;
				}
			}
			else{
				exHand[j] = G.handCount[j];
				exDeck[j] = G.deckCount[j];
			}
		}
		
		for (j = 0; j < 25; j++){
			sCount[j] = G.supplyCount[j];
		}
		
		testAdventurer(&totalTests, &testPassCount, &testFailCount, choice1, choice2, choice3, &G, randHandSelect, &bonus);
		
		printf("\ntest 1: player %d recieves correct number of cards, other players do not recieve any\n", p);
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
		
		printf("\ntest 2: player %d draws correct number of cards, other players do not draw any\n", p);
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
		
		
	}

	totalTests = testFailCount + testPassCount;
	printf("Passed %d out of %d tests\n", testPassCount, totalTests);

	return 0;
}
	

