/* unittest2.c
	Author/Date:  Bryant Crock  11/9/19
	Description:  Test the outcomes of the refactored minion card playMinion();
	Business Requirements for Minion:
		 1. +1 Action
		 2. Choice 1:  +2 coins
		 3. Choice 2:  Discard hand, +4 cards, each other player discards their hand and draws 4
	Test Conditions Identified and Expected End States:
		CONDITION #1:  Choice 1 - Add 2 coins:   -1 hand[minion], +2 coins, 1 action
		CONDITION #2:  Choice 2 - Discard Hand (players 2 & 3 have 5 cards):   -1 hand[minion], +4 discard[] each player, -4 deck[] each player, 4 cards in hand[] each player
		CONDITION #3:  Choice 2 - Discard Hand (player 3 does not have 5 cards):   	-1 hand[minion], +4 discard[] p1 &p2 and 0 discard p3, -4 deck[] pl & p2, no change to p3, p3 should have 3 cards
	
   	Known Bugs Inserted in Assignment 2:
		1. Removed the +1 Action of the card at the beginning.
        2. In the draw4 cards set of statements i has been replaced with j'
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


// helper function signatures
int testPlayMinion();
int assert(int expected, int actual);
int countCardTypeInHand(int card, struct gameState *state);

// helper print functions
void printTestCondition1Results(struct gameState *state, struct gameState *preState);
void printTestCondition2Results(struct gameState *state, struct gameState *preState);
void printTestCondition3Results(struct gameState *state, struct gameState *preState);
void printPlayersCards(int player, struct gameState *state);

// call unittest2
int main()
{
    testPlayMinion();
    return 0;
}

int testPlayMinion()
{

  // initialize variables
  int player1 = 0, player3 = 2, bonus = 0;
  int randomSeed = 5678;
  struct gameState state, preState;
  int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy
            };


    // -------  condition #1 - choice1 (player1 chooses to add 2 coins) ------
    printf("\n----- UNIT TEST #2 - playMinion - CONDITION #1: player1 chooses to add 2 coins\n");

    // initialize the game
    initializeGame(3, k, randomSeed, &state);

    // provide player1 with a minion card
    state.hand[player1][0] = minion;
    state.supplyCount[minion]--;

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // run the refactored function playMinion() function
    playCard(0, 1, 0, 0, &state);
    
    // check the results
    printTestCondition1Results(&state, &preState);

    // -------  condition #2 - choice 2 discard hand (players 2 & 3 have 5 cards) ------
    printf("\n----- UNIT TEST #2 - CONDITION #2: all players discard and draw 4\n");

    // initialize the game
    initializeGame(3, k, randomSeed, &state);

    // provide player1 with a minion card
    state.hand[player1][0] = minion;
    state.supplyCount[minion]--;

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // run the refactored function playMinion() function
    playCard(0, 0, 1, 0, &state);

    // check the results
    printTestCondition2Results(&state, &preState);

    // -------  condition #3 - choice 2 discard hand (p1 & p2 have 5 cards, p3 does not) ------
    printf("\n----- UNIT TEST #2 - CONDITION #3: p1 & p2 discard and draw 4, p3 too few cards\n");

    // initialize the game
    initializeGame(3, k, randomSeed, &state);

    // provide player1 with a minion card
    state.hand[player1][0] = minion;
    state.supplyCount[minion]--;

    // reduce the number of cards in p3's hand (note this method is only for testing purposes)
    state.handCount[player3] = 3;

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // run the refactored function playMinion() function
    playCard(0, 0, 1, 0, &state);

    // check the results
    printTestCondition3Results(&state, &preState);

    printf("\n----- UNIT TEST #2 - playMinion() - COMPLETED -----\n");

	return 0;
}


int assert(int expected, int actual)
{
  if (expected == actual)
    return 1;
  else
    return 0;
}


int countCardTypeInHand(int card, struct gameState *state)
{
  int i;
  int count = 0;
  int player = state->whoseTurn;
  for (i = 0; i < state->handCount[player]; i++) {
    if (state->hand[player][i] == card)
      count++;
  }
  return count;
}



void printTestCondition1Results(struct gameState *state, struct gameState *preState)
{

    // CONDITION #1:  Choice 1 - Add 2 coins:   -1 hand[minion], +2 coins, 1 action

    //int player1 = 0;
    int result = 0;

    // precondition #1 - player has one less minion in hand
    result = assert(countCardTypeInHand(minion, preState)-1, countCardTypeInHand(minion, state));
    if (result == 0)
      printf("precondition #1 fail: # minions in hand: %d, expected: %d\n", countCardTypeInHand(minion, state), countCardTypeInHand(minion, preState)-1);
    else
      printf("precondition #1 pass: # minions in hand: %d, expected: %d\n", countCardTypeInHand(minion, state), countCardTypeInHand(minion, preState)-1);

    // precondition #2 - player has +2 coins
    result = assert(preState->coins+2, state->coins);
    if (result == 0)
      printf("precondition #2 fail: # of coins: %d, expected: %d\n", state->coins, preState->coins+2);
    else
       printf("precondition #2 pass: # of coins: %d, expected: %d\n", state->coins, preState->coins+2);       


    // precondition #3 - player has 1 action
    result = assert(1, state->numActions);
    if (result == 0)
      printf("precondition #3 fail: # of actions: %d, expected: 1\n", state->numActions);
    else
       printf("precondition #3 pass: # of actions: %d, expected: 1\n", state->numActions);

}


void printTestCondition2Results(struct gameState *state, struct gameState *preState)
{

	//CONDITION #2:  Choice 2 - Discard Hand (players 2 & 3 have 5 cards):   
	// -1 hand[minion], +4 discard[] each player, -4 deck[] each player, 4 cards in hand[] each player
  	
  	int player1 = 0, player2 = 1, player3 = 2;
  	int result = 0;

    // precondition #1 - player has one less minion in hand
    result = assert(countCardTypeInHand(minion, preState)-1, countCardTypeInHand(minion, state));
    if (result == 0)
      printf("precondition #1 fail: # minions in hand: %d, expected: %d\n", countCardTypeInHand(minion, state), countCardTypeInHand(minion, preState)-1);
    else
      printf("precondition #1 pass: # minions in hand: %d, expected: %d\n", countCardTypeInHand(minion, state), countCardTypeInHand(minion, preState)-1);

    // precondition #2 - each player has 4 discards
    result = assert(1, (state->discardCount[player1] == 4 && state->discardCount[player2] == 4 && state->discardCount[player3] == 4));
    if (result == 0)
      printf("precondition #2 fail: all players should have 4 discards: p1: %d, p2: %d, p3: %d\n", state->discardCount[player1], state->discardCount[player2], state->discardCount[player3]);
    else
      printf("precondition #2 pass: all players should have 4 discards: p1: %d, p2: %d, p3: %d\n", state->discardCount[player1], state->discardCount[player2], state->discardCount[player3]);

  	// precondition #3 - each player has 4 less cards in their deck
    result = assert(1, (state->deckCount[player1] == preState->deckCount[player1]-4 && state->deckCount[player2] == preState->deckCount[player2]-4 && state->deckCount[player3] == preState->deckCount[player3]-4));    
    if (result == 0)
    	printf("precondition #3 fail: all players should have 4 less cards in their deck piles: p1: actual %d expected %d, p2: actual %d expected %d, p3: actual %d expected %d\n", state->deckCount[player1], preState->deckCount[player1]-4, state->deckCount[player2], preState->deckCount[player2]-4, state->deckCount[player3], preState->deckCount[player3]-4);
    else
		printf("precondition #3 pass: all players should have 4 less cards in their deck piles: p1: actual %d expected %d, p2: actual %d expected %d, p3: actual %d expected %d\n", state->deckCount[player1], preState->deckCount[player1]-4, state->deckCount[player2], preState->deckCount[player2]-4, state->deckCount[player3], preState->deckCount[player3]-4);

    // precondition #4 - each player has 4 hand cards
    result = assert(1, (state->handCount[player1] == 4 && state->handCount[player2] == 4 && state->handCount[player3] == 4));
    if (result == 0)
      printf("precondition #4 fail: all players should have 4 hand cards: p1: %d, p2: %d, p3: %d\n", state->handCount[player1], state->handCount[player2], state->handCount[player3]);
    else
      printf("precondition #4 pass: all players should have 4 hand cards: p1: %d, p2: %d, p3: %d\n", state->handCount[player1], state->handCount[player2], state->handCount[player3]);

}

void printTestCondition3Results(struct gameState *state, struct gameState *preState)
{

	//CONDITION #3:  Choice 2 - Discard Hand (player 3 does not have 5 cards):   
	// -1 hand[minion], +4 discard[] p1 &p2 and 0 discard p3, 
	// -4 deck[] pl & p2, no change to p3, p3 should have 3 cards
  	
  	int player1 = 0, player2 = 1, player3 = 2;
  	int result = 0;

    // precondition #1 - player has one less minion in hand
    result = assert(countCardTypeInHand(minion, preState)-1, countCardTypeInHand(minion, state));
    if (result == 0)
      printf("precondition #1 fail: # minions in hand: %d, expected: %d\n", countCardTypeInHand(minion, state), countCardTypeInHand(minion, preState)-1);
    else
      printf("precondition #1 pass: # minions in hand: %d, expected: %d\n", countCardTypeInHand(minion, state), countCardTypeInHand(minion, preState)-1);


    // precondition #2 - p1 & p2 should have 4 discards, p3 should have 0
    result = assert(1, (state->discardCount[player1] == 4 && state->discardCount[player2] == 4 && state->discardCount[player3] == 0));
    if (result == 0)
      printf("precondition #2 fail: p1 & p2 should have 4 discards, p3 should have 0: p1: %d, p2: %d, p3: %d\n", state->discardCount[player1], state->discardCount[player2], state->discardCount[player3]);
    else
      printf("precondition #2 pass: p1 & p2 should have 4 discards, p3 should have 0: p1: %d, p2: %d, p3: %d\n", state->discardCount[player1], state->discardCount[player2], state->discardCount[player3]);


  	// precondition #3 - p1 & p2 should have 4 less deck cards, p3 should have the same
    result = assert(1, (state->deckCount[player1] == preState->deckCount[player1]-4 && state->deckCount[player2] == preState->deckCount[player2]-4 && state->deckCount[player3] == preState->deckCount[player3]));    
    if (result == 0)
    	printf("precondition #3 fail: p1 & p2 should have 4 less deck cards, p3 should have the same: p1: actual %d expected %d, p2: actual %d expected %d, p3: actual %d expected %d\n", state->deckCount[player1], preState->deckCount[player1]-4, state->deckCount[player2], preState->deckCount[player2]-4, state->deckCount[player3], preState->deckCount[player3]);
    else
    	printf("precondition #3 pass: p1 & p2 should have 4 less deck cards, p3 should have the same: p1: actual %d expected %d, p2: actual %d expected %d, p3: actual %d expected %d\n", state->deckCount[player1], preState->deckCount[player1]-4, state->deckCount[player2], preState->deckCount[player2]-4, state->deckCount[player3], preState->deckCount[player3]);


    // precondition #4 - p3 should have 3 cards (unchanged)
    result = assert(preState->handCount[player3], state->handCount[player3]);
    if (result == 0)
      printf("precondition #4 fail: p3 should have 3 cards (unchanged): actual %d, expected %d\n", state->handCount[player3], preState->handCount[player3]);
    else
      printf("precondition #4 pass: p3 should have 3 cards (unchanged): actual %d, expected %d\n", state->handCount[player3], preState->handCount[player3]);

}


void printPlayersCards(int player, struct gameState *state)
{
    int i;

    // print the hand
  printf("Player's hand:\n");
  for (i = 0; i < state->handCount[player]; i++)
    printf("  Card #%d: %d\n", i+1, state->hand[player][i]);

  // print the discard
  printf("Player's discard pile:\n");
  for (i = 0; i < state->discardCount[player]; i++)
    printf("  Card #%d: %d\n", i+1, state->discard[player][i]);

  // print the deck
  printf("Player's deck:\n");
  for (i = 0; i < state->deckCount[player]; i++)
    printf("  Card #%d: %d\n", i+1, state->deck[player][i]);
}