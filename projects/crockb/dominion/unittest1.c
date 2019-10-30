#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

// 1.	Omitted a necessary step(s) to “discardCard” when the estate card was found.  
// This will cause the player’s hand to incorrectly retain an estate during gameplay.


// 2.	Decremented the supplyCount of estates after executing the gainCard() function 
// (duplicative reduction of supplyCount).  May cause the game to end too soon by over 
// removing estate cards when referenced in the Baron cards.

void printGameStateVariables(struct gameState *state)
{

	int i;

    // print out the results of the game state
	printf("numPlayers: %d\n", state->numPlayers);
	printf("supplyCount (baron): %d\n", state->supplyCount[baron]);
	printf("supplyCount (gardens): %d\n", state->supplyCount[gardens]);
	printf("supplyCount (ambassador): %d\n", state->supplyCount[ambassador]);
	printf("supplyCount (village): %d\n", state->supplyCount[village]);
	printf("supplyCount (minion): %d\n", state->supplyCount[minion]);
	printf("supplyCount (mine): %d\n", state->supplyCount[mine]);
	printf("supplyCount (sea_hag): %d\n", state->supplyCount[sea_hag]);
	printf("supplyCount (tribute): %d\n", state->supplyCount[tribute]);
	printf("supplyCount (smithy): %d\n", state->supplyCount[smithy]);
	printf("whosTurn (1): %d\n", state->whosTurn);
	printf("phase: %d\n", state->phase);
	printf("numActions: %d\n", state->numActions);
	printf("numBuys: %d\n", state->numBuys);

	printf("Player 1's hand:\n");
	for (i = 0; i < state->handCount[0]; i++)
		printf("  Card #%d: %d\n", i+1, state->hand[0][i]);

	printf("Player 2's hand:\n");
	for (i = 0; i < state->handCount[1]; i++)
		printf("  Card #%d: %d\n", i+1, state->hand[1][i]);

	printf("Player 1's deck:\n");
	for (i = 0; i < state->deckCount[0]; i++)
		printf("  Card #%d: %d\n", i+1, state->deck[0][i]);

	printf("Player 2's deck:\n");
	for (i = 0; i < state->deckCount[1]; i++)
		printf("  Card #%d: %d\n", i+1, state->deck[1][i]);

	printf("Player 1's disards:\n");
	for (i = 0; i < state->deckCount[0]; i++)
		printf("  Card #%d: %d\n", i+1, state->discard[0][i]);

	printf("Player 2's deck:\n");
	for (i = 0; i < state->deckCount[1]; i++)
		printf("  Card #%d: %d\n", i+1, state->discard[1][i]);

}


int testPlayBaron()
{

	// initialize variables
	// needs - baron, minion, ambassador, tribute, mine.  replaced adventurer, embargo
	int randomSeed = 1;
	struct gameState state;
	int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy
            };

    initializeGame(2, k, randomSeed, &state);

    printGameStateVariables(&state);


	// assert the results


	return 0;
}


// call unittest1
int main()
{
    testPlayBaron();
    return 0;
}
