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
	int handPos = 0;
    int p, handCount;
    int trashFlag = 0; //trash flag not set
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int testPassCount = 0;
	int testFailCount = 0;
    int maxHandCount = 10;
	
    int hand[maxHandCount];
	hand[0] = copper;
	hand[1] = adventurer;
	hand[2] = council_room;
	hand[3] = feast;
	hand[4] = gardens;
	hand[5] = mine;
	hand[6] = remodel;
	hand[7] = smithy;
	hand[8] = village;
	hand[9] = baron;
    printf("TESTING discardCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (trashFlag = 0; trashFlag <= 1; trashFlag++)
            {
				for (handPos = 0; handPos < handCount; handPos++){

					printf("player: %d, handCount: %d, trashFlag: %d, handPos: %d\n", p, handCount, trashFlag, handPos);

					memset(&G, 23, sizeof(struct gameState));   // clear the game state
					initializeGame(numPlayer, k, seed, &G); // initialize a new game
					G.handCount[p] = handCount;                 // set the number of cards on hand
					memcpy(G.hand[p], hand, sizeof(int) * handCount); // set all the cards to copper
					//int chosenCard = hand[handPos];
					discardCard(handPos, p, &G, trashFlag);
					printf("\nHand count test:\n");
					int expectedHandCount = handCount - 1;
					printf("Expected: handCount: %d\n", expectedHandCount);
					printf("Actual: handCount: %d\n", G.handCount[p]);

					if ((handCount - 1) == G.handCount[p]){
						printf("passed handcount test\n");
						testPassCount++;
					}
					else{
						printf("failed handcount test\n");
						testFailCount++;
					}
					
					if ((handCount - 1) == handPos){
						printf("\nLast card discard test:\n");
						printf("Expected: handCount: %d last card: -1 \n",  handCount);
						printf("Actual: handCount: %d last card: %d \n", G.handCount[p], G.hand[p][handPos]);
						
						if (G.hand[p][handPos] == -1){
							printf("passed last card discarded test\n");
							testPassCount++;
						}
						else{
							printf("failed last card discarded test\n");
							testFailCount++;
						}
					}
					else{
						printf("\nDiscard replacement test:\n");
						printf("Expected: card: %d\n", hand[handCount - 1]);
						printf("Actual: card: %d\n", G.hand[p][handPos]);
						if (hand[handCount - 1] == G.hand[p][handPos]){
							printf("passed discard replacement test\n");
							testPassCount++;
						}
						else{
							printf("failed discard replacement test\n");
							testFailCount++;
						}
					}
					
					if (trashFlag == 0){
						printf("\nNo trash flag, add to played card count and add to played pile, test:\n");
						printf("Expected: played card count: 1, card: %d\n", hand[handPos]);
						printf("Actual: played card count: %d, card: %d\n", G.playedCardCount, G.playedCards[G.playedCardCount - 1]);
						if (G.playedCardCount == 1){
							printf("Played count increased by 1\n");
							if (G.playedCards[G.playedCardCount - 1] == hand[handPos]){
								printf("and card is the same as chosen card...passed\n");
								testPassCount++;
							}
							else{
								printf("but card is not same as chosen card...failed\n");
								testFailCount++;
							}
						}
						else{
							printf("failed, discard not added to played pile\n");
							testFailCount++;
						}
						
					}
					
					if (trashFlag == 1){
						printf("\nTrash flag set test:\n");
						printf("Expected: played card count: 0\n");
						printf("Actual: played card count: %d\n", G.playedCardCount);
						if (G.playedCardCount == 0){
							printf("passed, played card count was not increased\n");
							testPassCount++;
						}
						else {
							printf("failed, played card count was increased\n");
							testFailCount++;
						}
							
					}
				}
			}
		}
	}
	int totalTests = testPassCount + testFailCount;
	printf("Passed %d out of %d tests\n", testPassCount, totalTests);

	return 0;
}
	

