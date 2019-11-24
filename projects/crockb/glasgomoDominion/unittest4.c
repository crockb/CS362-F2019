/* unittest4.c
	Author/Date:  Bryant Crock  11/9/19
	Description:  Test the outcomes of the refactored tribute card playTribute();
	Business Requirements for Tribute:
		 1. The player to the left reveals then discards top 2 cards
		 2. For each differently named card:
		 		- Action: +2 actions
		 		- Treasure Card: +2 coins
		 		- Victory Card: +2 cards

	CONDITIONS:  1: Left player has 1 or less cards in discard/deck - deckCount > 0 (action)
				 2: Left player has 1 or less cards in discard/deck - discardCount = 1 (treasure)
				 3: Left player has 1 or less cards in discard/deck - no cards (failure)
				 4: Left player has 2 or more cards in discard/deck - no deck cards (shuffle)
				   4.1:   has duplicates at the backend
				     4.1.1: 2 coppers
				     4.1.2: 2 estates
				     4.1.3: 2 mines
				   4.2:   has a copper, has an estate
				   4.3:   has a mine, has a great_hall 
					   
// signature for tribute
int cardEffectTribute(struct gameState *state)


*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


// helper function signatures
int testPlayTribute();
int assert(int expected, int actual);
int pauseStatement();

// helper function to set conditions before playing card
void setCondition1(struct gameState *state, int card);     			// #1 - Left player has 1 or less cards in discard/deck - deckCount = 1, discard = 0
void setCondition2(struct gameState *state, int card);     			// #2 - Left player has 1 or less cards in discard/deck - discardCount = 1
void setCondition3(struct gameState *state);               			// #3 - Left player has 1 or less cards in discard/deck - no cards
void setCondition4(struct gameState *state, int card1, int card2);  // #4 - Left player has 2 or more cards in discard/deck - no deck cards



int main()
{
	testPlayTribute();
	return 0;
}


int testPlayTribute()
{
  	// initialize variables
  	int player1 = 0, result = -1, bonus = 0, returnValue; // player2 = 0, player3 = 0;
  	int randomSeed = 7890;
  	struct gameState state, preState;
  	int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               great_hall, tribute, smithy
            };

    //playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)

    // -------  condition #4 - 1 or less cards in discard/deck - deckCount > 0 ------
    printf("\n----- UNIT TEST #4 - playTribute() ------\n");


	// ----- CONDITION 1.0 ---------

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a tribute card
    state.hand[player1][0] = tribute;
    state.supplyCount[tribute]--;

    // condition 1.0 - 1 or less cards in discard/deck - deckCount > 0 (mine)
    setCondition1(&state, mine);

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // play the tribute card
    returnValue = playCard(0, 0, 0, 0, &state);

    // expected results: +2 actions (-1 of current turn)
    result = assert(preState.numActions+1, state.numActions);
    if (result == 0)
    	printf("condition 1.0 - FAIL: +2 actions: actual %d, expected: %d\n", state.numActions, preState.numActions+1);
    else
    	printf("condition 1.0 - PASS: +2 actions: actual %d, expected: %d\n", state.numActions, preState.numActions+1);


	// ----- CONDITION 2.0 ---------

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a tribute card
    state.hand[player1][0] = tribute;
    state.supplyCount[tribute]--;

	// condition 2.0 - 1 or less cards in discard/deck - discardCount = 1 (treasure)
    setCondition2(&state, copper);

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // play the tribute card
    returnValue = playCard(0, 0, 0, 0, &state);

    // expected results: +2 coins (treasure card)
    updateCoins(player1, &preState, 2);
    updateCoins(player1, &state, state.coins);

    result = assert(preState.coins, state.coins);
    if (result == 0)
    	printf("condition 2.0 - FAIL: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);
    else
    	printf("condition 2.0 - PASS: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);


	// ----- CONDITION 3.0 ---------

	// initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a tribute card
    state.hand[player1][0] = tribute;
    state.supplyCount[tribute]--;

	// condition 3.0 - 1 or less cards in discard/deck - no cards (failure)
    setCondition3(&state);

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // play the tribute card
    returnValue = playCard(0, 0, 0, 0, &state);

    // expected results: (failure)
    result = assert(-1, returnValue);
    if (result == 0)
    	printf("condition 3.0 - FAIL: (fail flag not returned): actual %d, expected: %d\n", returnValue, -1);
    else
    	printf("condition 3.0 - PASS: (fail flag returned): actual %d, expected: %d\n", returnValue, -1);


	// ----- CONDITION 4.1.1 ---------

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a tribute card
    state.hand[player1][0] = tribute;
    state.supplyCount[tribute]--;

	// condition 4.1.1 - 2 or more cards in discard/deck - no deck cards (shuffle) - duplicates - 2 coppers
	setCondition4(&state, copper, copper); 

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // play the tribute card
    playCard(0, 0, 0, 0, &state);

    // expected results: +2 coins (treasure card) - no double counting
    updateCoins(player1, &preState, 2);
    updateCoins(player1, &state, state.coins);

    result = assert(preState.coins, state.coins);
    if (result == 0)
    	printf("condition 4.1.1 - FAIL: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);
    else
    	printf("condition 4.1.1 - PASS: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);
    pauseStatement();

	// ----- CONDITION 4.1.2 ---------

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a tribute card
    state.hand[player1][0] = tribute;
    state.supplyCount[tribute]--;

	// condition 4.1.2 - 2 or more cards in discard/deck - no deck cards (shuffle) - duplicates - 2 estates
	setCondition4(&state, estate, estate);

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // play the tribute card
    playCard(0, 0, 0, 0, &state);

    // expected results: +2 cards (-1 for the tribute)  (no double counting)
    result = assert(preState.handCount[player1]+1, state.handCount[player1]);
    if (result == 0)
    	printf("condition 4.1.2 - FAIL: +2 cards: actual %d, expected: %d\n", state.handCount[player1], preState.handCount[player1]+1);
    else
    	printf("condition 4.1.2 - PASS: +2 cards: actual %d, expected: %d\n", state.handCount[player1], preState.handCount[player1]+1);



	// ----- CONDITION 4.1.3 ---------

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a tribute card
    state.hand[player1][0] = tribute;
    state.supplyCount[tribute]--;

	// condition 4.1.3 - 2 or more cards in discard/deck - no deck cards (shuffle) - duplicates - 2 mines
	setCondition4(&state, mine, mine);

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // play the tribute card
    playCard(0, 0, 0, 0, &state);

    // expected results: +2 actions (-1 of current turn) (no double counting)
    result = assert(preState.numActions+1, state.numActions);
    if (result == 0)
    	printf("condition 4.1.3 - FAIL: +2 actions (-1 of current turn) (no double counting): actual %d, expected: %d\n", state.numActions, preState.numActions+1);
    else
    	printf("condition 4.1.3 - PASS: +2 actions (-1 of current turn) (no double counting): actual %d, expected: %d\n", state.numActions, preState.numActions+1);



	// ----- CONDITION 4.2.0 ---------

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a tribute card
    state.hand[player1][0] = tribute;
    state.supplyCount[tribute]--;

   	// condition 4.2.0 -  2 or more cards in discard/deck - no deck cards (shuffle) - 1 copper, 1 estate
	setCondition4(&state, copper, estate);      

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // play the tribute card
    playCard(0, 0, 0, 0, &state);

    // expected results: +2 coins, +2 cards
    updateCoins(player1, &preState, 2);
    updateCoins(player1, &state, state.coins);


    // check +2 coins
    result = assert(preState.coins, state.coins);
    if (result == 0)
    	printf("condition 4.2.0 - FAIL: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);
    else
    	printf("condition 4.2.0 - PASS: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);

	// check +2 cards
    result = assert(preState.handCount[player1]+1, state.handCount[player1]);
    if (result == 0)
    	printf("condition 4.2.0 - FAIL: +2 cards: actual %d, expected: %d\n", state.handCount[player1], preState.handCount[player1]+1);
    else
    	printf("condition 4.2.0 - PASS: +2 cards: actual %d, expected: %d\n", state.handCount[player1], preState.handCount[player1]+1);


	// ----- CONDITION 4.3.0 ---------

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a tribute card
    state.hand[player1][0] = tribute;
    state.supplyCount[tribute]--;

	// condition 4.3.0 -  or more cards in discard/deck - no deck cards (shuffle) - 1 copper, 1 great_hall
    setCondition4(&state, mine, great_hall);

     // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // play the tribute card
    playCard(0, 0, 0, 0, &state);

    // expected results: +4 actions (-1 for card played, +4 cards (-1 for card played)

   	// check +4 cards (-1 for card played)
    result = assert(preState.handCount[player1]+3, state.handCount[player1]);
    if (result == 0)
    	printf("condition 4.3.0 - FAIL: +4 cards (-1 of current turn): actual %d, expected: %d\n", state.handCount[player1], preState.handCount[player1]+3);
    else
    	printf("condition 4.3.0 - PASS: +4 cards (-1 of current turn): actual %d, expected: %d\n", state.handCount[player1], preState.handCount[player1]+3);

    // check +4 actions (-1 of current turn)
    result = assert(preState.numActions+3, state.numActions);
    if (result == 0)
    	printf("condition 4.3.0 - FAIL: +4 actions (-1 of current turn): actual %d, expected: %d\n", state.numActions, preState.numActions+3);
    else
    	printf("condition 4.3.0 - PASS: +4 actions (-1 of current turn): actual %d, expected: %d\n", state.numActions, preState.numActions+3);

    printf("\n----- UNIT TEST #4 - playTribute() - COMPLETED -----\n");

	return 0;
}

int pauseStatement(){
    return 0;
}


int assert(int expected, int actual)
{
  if (expected == actual)
    return 1;
  else
    return 0;
}

// CONDITION:  #1 - Left player has 1 or less cards in discard/deck - deckCount = 1, discard = 0
void setCondition1(struct gameState *state, int card)
{
	int player2 = 1;
	state->deckCount[player2] = 1;
	state->discardCount[player2] = 0;
	state->deck[player2][0] = card;
}

// CONDITION: #2 - Left player has 1 or less cards in discard/deck - discardCount = 1
void setCondition2(struct gameState *state, int card)
{
	int player2 = 1;
	state->deckCount[player2] = 0;
	state->discardCount[player2] = 1;
	state->discard[player2][0] = card;
}

// CONDITION: #3 - Left player has 1 or less cards in discard/deck - no cards
void setCondition3(struct gameState *state)
{
	int player2 = 1;
	state->deckCount[player2] = 0;
	state->discardCount[player2] = 0;
}

// CONDITION: #4 - Left player has 2 or more cards in discard/deck - no deck cards
void setCondition4(struct gameState *state, int card1, int card2)
{
	int player2 = 1;
	state->deckCount[player2] = 0;
	state->discardCount[player2] = 2;
	state->discard[player2][0] = card1;
	state->discard[player2][1] = card2;
}
