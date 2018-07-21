/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = maxPlayers;
    int maxBonus = 10;
	int handPos = 0;
    int p, r, handCount;
    int trashFlag = 0; //trash flag not set
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int testPassCount = 0;
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
	hand[9] = baron
    printf ("TESTING discardCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 0; handCount <= maxHandCount; handCount++)
        {
            for (trashFlag = 0; trashFlag <= 1; trashFlag++)
            {
				for (handPos = 0; handPos <= maxHandCount; handPos++){

					printf("player: %d, handCount: %d, trashFlag: %d, handPos: %d\n", p, handCount, trashFlag, handPos);

					memset(&G, 23, sizeof(struct gameState));   // clear the game state
					r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
					G.handCount[p] = handCount;                 // set the number of cards on hand
					memcpy(G.hand[p], hand, sizeof(int) * handCount); // set all the cards to copper
					//int chosenCard = hand[handPos];
					discardCard(handPos, p, &G, trashFlag);
					printf("Hand count test:\n");
					printf("Expected: handCount: %d\n", handCount);
					printf("Actual: handCount: %d\n", G.handCount[p]);

					if ((handCount) - 1) == G.handCount[p]){
						printf("passed handcount test\n", p, handCount, trashFlag, handPos);
						testPassCount++;
					}
					else{
						printf("failed handcount test\n");
					}
					
					if ((handCount - 1) == handPos){
						printf("Last card discard test:\n");
						printf("Expected: handCount: %d\n", handCount);
						printf("Actual: handCount: %d\n", G.handCount[p]);
						
						if (G.hand[p][handPos] == -1){
							printf("passed last card discarded test\n");
							testPassCount++;
						}
						else{
							printf("failed last card discarded test\n");
						}
					}
					else{
						printf("Last card discard test:\n");
						printf("Expected: card: %d\n", hand[handCount - 1]);
						printf("Actual: card: %d\n", G.hand[p]]handPos]);
						if (hand[handCount - 1] == G.hand[p][handPos]){
							printf("passed discard replacement test\n");
							testPassCount++;
							
						}
						else{
							printf("failed discard replacement test\n");
						}
					}
					
					if (trashFlag == 0){
						
						printf("No trash flag, add to played card count and add to played pile, test:\n");
						printf("Expected: played card count: 1, card: \n", hand[handPos]);
						printf("Actual: played card count: %d, card: %d\n", G.playedCardCount, G.playedCards[G.playedCardCount - 1]);
						if (G.playedCardCount == 1){
							printf("Played count increased by 1\n");
							if (G.playedCards[G.playedCardCount - 1] == hand[handPos])
								printf("and card is the same as chosen card...passed\n");
								testPassCount++;
							}
							else{
								printf("but card is not same as chosen card...failed\n");
							}
						}
						else{
							printf("failed, discard not added to played pile\n");
						}
						
					}
					
					if (trashFlag == 1){
						printf("Trash flag set test:\n");
						printf("Expected: played card count: 0\n");
						printf("Actual: played card count: %d\n", G.playedCardCount);
						if (G.playedCardCount == 0){
							printf("passed, played card count was not increased\n");
						}
						else {
							printf("failed, played card count was increased\n");
						}
							
						
					}
				}
            }
        }
    }

    printf("Passed %d out of 5 tests\n", testPassCount);

    return 0;
}
