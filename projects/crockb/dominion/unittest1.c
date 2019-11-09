/* unittest1.c
	Author/Date:  Bryant Crock  11/1/19
	Description:  Test the outcomes of the refactored baron card playBaron();
	Business Requirements for Baron:
		 1. +1 Buy
		 2. Choice 1:  Discard an Estate for +4 coins.  If no Estate, receive an Estate
		 3. Choice 2:  Receive an Estate

	Test Conditions Identified and Expected End States:
		CONDITION #1:  Remove Estate (Has Estate):   -1 hand[estate], -1 hand[baron], 3 handCount, +4 coins, +1 buy, 0 actions, +1 discard[baron], estate supply count unchanged
		CONDITION #2:  Remove Estate (No Estate):   +1 hand[estate], -1 hand[baron], 5 handCount, same coins, +1 buy, 0 actions, +1 discard[baron], -1 supply[estate]
		CONDITION #3:  Gain an Estate (Multiple Estates Available):  +1 hand[estate], -1 hand[baron], 5 handCount, same coins, +1 buy, 0 actions, +1 discard[baron], -1 supply[estate]
		CONDITION #4:  Gain an Estate (1 Estate Available):  +1 hand[estate], -1 hand[baron], 5 handCount, same coins, +1 buy, 0 actions, +1 discard[baron], -1 supply[estate]


   	Known Bugs Inserted in Assignment 2:
		1. Omitted a necessary step(s) to “discardCard” when the estate card was found.  
           This will cause the player’s hand to incorrectly retain an estate during gameplay.

        2. Decremented the supplyCount of estates after executing the gainCard() function 
           (duplicative reduction of supplyCount).  May cause the game to end too soon by over 
           removing estate cards when referenced in the Baron cards.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "unittest_helpers.h"




// call unittest1
int main()
{
    testPlayBaron();
    return 0;
}


// function to execute the set of conditions for unittest#1
int testPlayBaron()
{

	// initialize variables
	int player1 = 0, bonus = 0;
	int randomSeed = 1234;
	struct gameState state, preState;
	int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy
            };


    // -------  condition #1 - choice1 (player1 has an estate) ------
    printf("----- UNIT TEST #1 - CONDITION #1: player1 chooses to discard an estate - player1 has an estate.\n");

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a baron card
    state.hand[player1][0] = baron;
    state.supplyCount[baron]--;

    // confirm player has an estate card in hand
  	provideEstateCardFromDeck(player1, &state);

  	// copy the initial pre-conditions
  	updateCoins(player1, &state, bonus);
  	memcpy(&preState, &state, sizeof(struct gameState));

  	// run the refactored function playBaron() function
    playCard(0, 1, 0, 0, &state);
  	
  	// check the results
  	printUnitTest1Condition1Results(&state, &preState);

  	// -------  condition #2 - choice1 (player1 has an estate) ------
    printf("\n----- UNIT TEST #1 - CONDITION #2: player1 chooses to discard an estate - player1 does not have an estate.\n");

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a baron card
    state.hand[player1][0] = baron;
    state.supplyCount[baron]--;

  	// confirm the player does not have an estate card
    removeEstateCardFromHand(player1, &state);

  	// copy the initial pre-conditions
  	updateCoins(player1, &state, bonus);
  	memcpy(&preState, &state, sizeof(struct gameState));

  	// run the refactored function playBaron() function
  	playCard(0, 1, 0, 0, &state);

   	// check the results
  	printUnitTest1Condition2to4Results(&state, &preState);

  	// -------  condition #3 - choice2 (estates available in the game) ------
    printf("\n----- UNIT TEST #1 - CONDITION #3: player1 chooses not to discard an estate - estates available in the game\n");

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a baron card
    state.hand[player1][0] = baron;
    state.supplyCount[baron]--;

  	// copy the initial pre-conditions
  	updateCoins(player1, &state, bonus);
  	memcpy(&preState, &state, sizeof(struct gameState));

  	// run the refactored function playBaron() function
  	playCard(0, 0, 1, 0, &state);

   	// check the results
  	printUnitTest1Condition2to4Results(&state, &preState);

  	// -------  condition #4 - choice2 (1 estate left in the game) ------
    printf("\n----- UNIT TEST #1 - CONDITION #4: player1 chooses not to discard an estate - 1 estate available in the game\n");

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a baron card
    state.hand[player1][0] = baron;
    state.supplyCount[baron]--;

    // reduce the estate supplyCount to 1
    state.supplyCount[estate] = 1;

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
  	memcpy(&preState, &state, sizeof(struct gameState));

  	// run the refactored function playBaron() function
  	playCard(0, 0, 1, 0, &state);

  	// check the results
  	printUnitTest1Condition2to4Results(&state, &preState);

    printf("\n----- UNIT TEST #1 - COMPLETED -----\n");

	return 0;
}
