/* unittest-bug2.c
	Author/Date:  Bryant Crock  11/29/19
	Description:  Mine statement improperly checking cost of trash card to purchase card.  Unittest
                to reveal the bug to the tester.
	
	Business Requirements for Mine:
		 1. Trash a Treasure Card from Hand
		 2. Gain a Treasure Card Costing Up to +3 More

     Mine Card Options
     		choice 1 - index of card to be trashed
        choice 2 - card to be purchased
	Conditions for Mine
 		    Valid Trash Card (Copper), Purchase Card Is In Range (Silver)
 		    values: choice[1] = copper ($0), choice2 = silver ($3)
 		    
 	Expected Unittest Outcomes:
        playCard() return status 0
        Player1 hand: +1 Silver
        Player1 hand: -1 Copper

*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


// helper function signatures
int testPlayMine();
int assert(int expected, int actual);
int countCardType(int card, struct gameState *state, int pileToCheck);
void printPlayersCards(int player, struct gameState *state);

// helper function to set conditions before playing card
void setCondition(struct gameState *state);  // #4 - Left player has 2 or more cards in discard/deck - no deck cards


int main()
{
	testPlayMine();
	return 0;
}


int testPlayMine()
{

  	// initialize variables
  	int player1 = 0, result = -1, bonus = 0, returnValue = -10;
  	int randomSeed = 1234;
  	struct gameState state, preState;
  	int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               great_hall, tribute, smithy
            };

    // -------  beginning of unit test conditions ------
    printf("\n----- UNIT TEST - Bug#2 - Mine improperly checks cost of trash to purchase card ------\n");

	// ----- CONDITION - Valid Trash Card, Purchase Card Is In Range ----
    
    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // condition - Valid Trash Card, Purchase Card Is In Range ----    
    setCondition(&state);

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // values: choice[1] = silver ($3), choice2 = silver ($3)
    returnValue = playCard(0, 1, silver, 1, &state); 

    // Assertion #1:  playCard() return status 0
    result = assert(0, returnValue);
    if (result == 0)
    	printf("playCard() return status 0 - FAIL: actual %d, expected: %d\n", returnValue, 0);
    else
    	printf("playCard() return status 0 - PASS: actual %d, expected: %d\n", returnValue, 0);

    printf("\n----- UNIT TEST - Bug#2 - complete ------\n");

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

    // provide player1 with a mine card
    state->hand[player1][0] = mine;
    state->supplyCount[mine]--;
    state->hand[player1][1] = silver;   // valid card to trash
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