/* unittest-bug9.c
	Author/Date:  Bryant Crock  11/29/19
	Description:  Tribute handles duplicate “revealed cards” improperly.  Test file is designed to
	 			  reveal the bug to the tester.
	
	Business Requirements for Tribute:
		 1. The player to the left reveals then discards top 2 cards
		 2. For each differently named card:
		 		- Action: +2 actions
		 		- Treasure Card: +2 coins
		 		- Victory Card: +2 cards

	CONDITION:
			Next player has 10 deck cards:
				Cards 7-10 = estate

 	Expected Unittest Outcomes:
        + 2 hand cards
        + 0 actions

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
int countCardType(int card, struct gameState *state, int pileToCheck);
void printPlayersCards(int player, struct gameState *state);

// helper function to set conditions before playing card
void setCondition(struct gameState *state);


int main()
{
	testPlayTribute();
	return 0;
}


int testPlayTribute()
{

  	// initialize variables
  	int player1 = 0, bonus = 0, result = -10;
  	int randomSeed = 1234;
  	struct gameState state, preState;
  	int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               great_hall, tribute, smithy
            };

    // -------  beginning of unit test conditions ------
    printf("\n----- UNIT TEST - Bug#9 - Tribute handles duplicate “revealed cards” improperly ------\n");

	// ----- CONDITION - Next player has 2 or more cards in discard/deck with cards in deck
	// -----             Next player has estates at backend of deck
    
    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // set the condition  
    setCondition(&state);

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // play the tribute card
    playCard(0, 0, 0, 0, &state);

    // Assertion #1:  Player1 has +2 hand cards
    result = assert(preState.handCount[player1]+2, state.handCount[player1]);
    if (result == 0)
    	printf("Player1 has +2 hand cards - FAIL: actual %d, expected: %d\n", state.handCount[player1], preState.handCount[player1]+2);
    else
    	printf("Player1 has +2 hand cards - PASS: actual %d, expected: %d\n", state.handCount[player1], preState.handCount[player1]+2);

	// Assertion #2:  Player1 has 0 actions
    result = assert(preState.numActions -1, state.numActions);
    if (result == 0)
    	printf("Player1 has 0 actions - FAIL: actual %d, expected: %d\n", state.numActions, preState.numActions -1);
    else
    	printf("Player1 has 0 actions - PASS: actual %d, expected: %d\n", state.numActions, preState.numActions -1);

    printf("\n----- UNIT TEST - Bug#9 - complete ------\n");


	return 0;
}


int assert(int expected, int actual)
{
  if (expected == actual)
    return 1;
  else
    return 0;
}

// set the condition for player1's hand
void setCondition(struct gameState *state)
{
	int player1 = 0;
	int player2 = 1;

    // provide player1 with a Tribute card
    state->hand[player1][0] = tribute;
    state->supplyCount[tribute]--;

    // set the last 4 cards to estate for player 2
	state->deck[player2][state->deckCount[player2]-4] = estate;
	state->deck[player2][state->deckCount[player2]-3] = estate;
	state->deck[player2][state->deckCount[player2]-2] = estate;
	state->deck[player2][state->deckCount[player2]-1] = estate;
}


int countCardType(int card, struct gameState *state, int pileToCheck)
{

  int i;
  int count = 0;
  int player = state->whoseTurn;
  int hand = 0;
  int discard = 1;
  int deck = 2;
  int played = 3;

  // check the hand
  if (pileToCheck == hand) {
    for (i = 0; i < state->handCount[player]; i++) {
      if (state->hand[player][i] == card)
        count++;
    }
    return count;
  }

  // check the discard
  if (pileToCheck == discard) {
    for (i = 0; i < state->discardCount[player]; i++) {
      if (state->discard[player][i] == card)
        count++;
    }
    return count;
  }

  // check the deck
  if (pileToCheck == deck) {
    for (i = 0; i < state->deckCount[player]; i++) {
      if (state->deck[player][i] == card)
        count++;
    }
    return count;
  }

  // check the deck
  if (pileToCheck == played) {
    for (i = 0; i < state->playedCardCount; i++) {
      if (state->playedCards[i] == card)
        count++;
    }
    return count;
  }


  // error - no pile indicated
  return -1;

}


void printPlayersCards(int player, struct gameState *state)
{
    int i;

    // print the hand
  	printf("Player%d's  hand:\n", player+1);
  	for (i = 0; i < state->handCount[player]; i++)
    	printf("  Card #%d: %d\n", i+1, state->hand[player][i]);

  	// print the discard
  	printf("Player%d's  discard pile:\n", player+1);
  	for (i = 0; i < state->discardCount[player]; i++)
    	printf("  Card #%d: %d\n", i+1, state->discard[player][i]);

  	// print the deck
  	printf("Player%d's deck:\n", player+1);
  	for (i = 0; i < state->deckCount[player]; i++)
    	printf("  Card #%d: %d\n", i+1, state->deck[player][i]);

    // print the playedCards
    printf("Played Cards: \n");
   	for (i = 0; i < state->playedCardCount; i++)
    	printf("  Card #%d: %d\n", i+1, state->playedCards[i]);   
}