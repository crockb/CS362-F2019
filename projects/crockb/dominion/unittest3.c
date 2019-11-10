/* unittest3.c
	Author/Date:  Bryant Crock  11/9/19
	Description:  Test the outcomes of the refactored ambassador card playAmbassador();
	Business Requirements for Ambassador:
		 1. Reveal a card from your hand (choice1)
		 2. Return up to 2 copies of the card to the supply
		 2. Each player gains a copy of the chosen card from the supply (in their discard)
	Test Conditions Identified and Expected End States:
		CONDITION #1:  Reveal a copper, return 2 copies to supply, each player receives 1 (in discard from supply)
					   p1 2 less coppers, +2 coppers supply, +1 copper each player (in discard pile)  
		CONDITION #2:  Attempt to discard 3 copies (fail)
					   (fail flag, no gameState changes)
		CONDITION #3:  Attempt to discard the ambassador (fail):
					   (fail flag, no gameState changes)
   	Known Bugs Inserted in Assignment 2:
		1. Replaced i < stateHandCount with i <=, could cause an out of bounds
        2. Replaced choice1 with choice2 in the statement "each player receives a copy"

    Other Notes:
    	choice1 reflects the cardPos the user reveals
    	choice2 reflects the number of cards to discard
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


// helper function signatures
int testPlayAmbassador();
int assert(int expected, int actual);
int hasGameCard(int card, struct gameState *state, int pileToCheck);
int countCardTypeInHand(int card, struct gameState *state);
int confirmNumCoppersInHand(int player, struct gameState *state, int num);

int provideEstateCardFromDeck(int player, struct gameState *state);
int removeEstateCardFromHand(int player, struct gameState *state);

// helper print functions
void printTestCondition1Results(struct gameState *state, struct gameState *preState);
void printPlayersCards(int player, struct gameState *state);
void printAllSupplyCounts(struct gameState *state);
void printAllGameStateVariables(struct gameState *state);


int main()
{
	testPlayAmbassador();
	return 0;
}


int testPlayAmbassador()
{
  	// initialize variables
  	int player1 = 0, bonus = 0, copperPos = -1; // player2 = 0, player3 = 0;
  	int randomSeed = 7890;
  	struct gameState state, preState;
  	int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy
            };

    // -------  condition #1 - reveal a copper, return 2 copies to supply, each player receives 1 (in discard from supply) ------
    printf("----- UNIT TEST #3 - CONDITION #1: reveal a copper, return 2 copies to supply, each player receives 1 (in discard from supply)\n");

    // initialize the game
    initializeGame(3, k, randomSeed, &state);

    // provide player1 with a ambassador card
    state.hand[player1][0] = ambassador;
    state.supplyCount[ambassador]--;

    // confirm player has 2 coppers in hand
    confirmNumCoppersInHand(player1, &state, 2);
    copperPos = hasGameCard(copper, &state, 1);

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    //playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
    // run the refactored function playAmbassador() function
    playCard(0, copperPos, 2, 0, &state);
    
    // check the results
    printTestCondition1Results(&state, &preState);

    // print player's cards
    printf("player 1 (pre-state)\n");
    printPlayersCards(0, &preState);
    printf("player 1 (post-state)\n");
    printPlayersCards(0, &state);

    printf("player 2 (pre-state)\n");
    printPlayersCards(1, &preState);
    printf("player 2 (post-state)\n");
    printPlayersCards(1, &state);

    printf("player 3 (pre-state)\n");
    printPlayersCards(2, &preState);
    printf("player 3 (post-state)\n");
    printPlayersCards(2, &state);

	return 0;
}



int assert(int expected, int actual)
{
  if (expected == actual)
    return 1;
  else
    return 0;
}

int confirmNumCoppersInHand(int player, struct gameState *state, int num) {
 // int countCardTypeInHand(int card, struct gameState *state)
 // int hasGameCard(int card, struct gameState *state, int pileToCheck)

    int tempCard;
    int copperPos;
	int i = 1;

    if (countCardTypeInHand(copper, state) < 2) {

      	// check for error - no available coppers
    	if (hasGameCard(copper, state, 3) < 0) {
        	printf("error: no coppers in deck\n");
        	return -1;
      	}
    
    	while (countCardTypeInHand(copper, state) < 2)
      	{
        	copperPos = hasGameCard(copper, state, 3);
        	tempCard = state->hand[player][i];
        	state->hand[player][i] = state->deck[player][copperPos];
        	state->deck[player][copperPos] = tempCard;
      	}
      	   return 0;
    }

    // already has 2 coppers
    else {
    	return 0;
    }

}



// helper functions for unittest1
int hasGameCard(int card, struct gameState *state, int pileToCheck)
{
  int i;
  int player = state->whoseTurn;

  // hand pile
  if (pileToCheck == 1) {

    for (i = 0; i < state->handCount[player]; i++) {
      if (state->hand[player][i] == card) {
        // card found
        return i;
      }
    }

      // card not found
      return -1;
  }

  // discard pile
  else if (pileToCheck == 2) {
    for (i = 0; i < state->discardCount[player]; i++) {
    if (state->discard[player][i] == card) {
      // card found
      return i;
    }

    // card not found
      return -1;
    }
  }

  // deck pile
  else if (pileToCheck == 3) {

    for (i = 0; i < state->deckCount[player]; i++) {
    if (state->deck[player][i] == card) {
      // card found
      return i;
    }

    // card not found
      return -1;
    }
  }

  // no pile match - error
  else
  {
    printf("critical error: hasGameCard no match.\n");
    return -2;
  }

  return -2;
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



// provide an estate card (if the player doesn't already have one in their hand)
int provideEstateCardFromDeck(int player, struct gameState *state)
{
    if (hasGameCard(estate, state, 1) < 0) {
      int tempCard;
      int estatePos;
      // provide an estate card from the deck
      if (hasGameCard(estate, state, 3) < 0) {
        printf("error: no estate card in deck\n");
        return -1;
      }
      else
      {
        estatePos = hasGameCard(estate, state, 3);
        tempCard = state->hand[player][1];
        state->hand[player][1] = state->deck[player][estatePos];
        state->deck[player][estatePos] = tempCard;
      }
    }

    return 0;
}

// remove estate cards from the players hand (if they have any)
int removeEstateCardFromHand(int player, struct gameState *state)
{
    int estateHandPos, copperDeckPos;
    
    while (hasGameCard(estate, state, 1) >= 0) {
      // swap estate card with nearest copper in deck
      copperDeckPos = hasGameCard(copper, state, 3);
      estateHandPos = hasGameCard(estate, state, 1);
      state->hand[player][estateHandPos] = copper;
      state->deck[player][copperDeckPos] = estate;
    }

    return 0;
}


void printTestCondition1Results(struct gameState *state, struct gameState *preState)
{

	int player1 = 0;
	int result = 0;

	//CONDITION #1:  Reveal a copper, return 2 copies to supply, each player receives 1 (in discard from supply)
	//				 p1 2 less coppers, +2 coppers supply, +1 copper each player (in discard pile)


    // precondition #1 - p1 2 less coppers
    result = assert(countCardTypeInHand(copper, preState)-2, countCardTypeInHand(copper, state));
    if (result == 0)
      printf("precondition #1 fail: p1 2 less coppers: actual %d, expected: %d\n", countCardTypeInHand(copper, state), countCardTypeInHand(copper, preState)-2);
    else
       printf("precondition #1 pass: p1 2 less coppers: actual %d, expected: %d\n", countCardTypeInHand(copper, state), countCardTypeInHand(copper, preState)-2);
  
  /*

    // precondition #2 - player has one less baron in hand
    result = assert(countCardTypeInHand(baron, preState)-1, countCardTypeInHand(baron, state));
    if (result == 0)
      printf("precondition #2 fail: # barons in hand: %d, expected: %d\n", countCardTypeInHand(baron, state), countCardTypeInHand(baron, preState)-1);
    else
       printf("precondition #2 pass: # barons in hand: %d, expected: %d\n", countCardTypeInHand(baron, state), countCardTypeInHand(baron, preState)-1);

    // precondition #3 - player has 3 cards in hand (less 1 estate, less 1 baron)
    result = assert(preState->handCount[player1]-2, state->handCount[player1]);
    if (result == 0)
      printf("precondition #3 fail: # cards in hand: %d, expected: %d\n", state->handCount[player1], preState->handCount[player1]-2);
    else
       printf("precondition #3 pass: # cards in hand: %d, expected: %d\n", state->handCount[player1], preState->handCount[player1]-2);    

    // precondition #4 - player has +4 coins
    result = assert(preState->coins+4, state->coins);
    if (result == 0)
      printf("precondition #4 fail: # of coins: %d, expected: %d\n", state->coins, preState->coins+4);
    else
       printf("precondition #4 pass: # of coins: %d, expected: %d\n", state->coins, preState->coins+4);       

    // precondition #5 - player has +1 buys
    result = assert(preState->numBuys+1, state->numBuys);
    if (result == 0)
      printf("precondition #5 fail: # of buys: %d, expected: %d\n", state->numBuys, preState->numBuys+1);
    else
       printf("precondition #5 pass: # of buys: %d, expected: %d\n", state->numBuys, preState->numBuys+1); 

    // precondition #6 - player 0 actions
    result = assert(preState->numActions-1, state->numActions);
    if (result == 0)
      printf("precondition #6 fail: # of actions: %d, expected: %d\n", state->numActions, preState->numActions-1);
    else
       printf("precondition #6 pass: # of actions: %d, expected: %d\n", state->numActions, preState->numActions-1);     

    // precondition #7 - player has 1 discarded baron
     result = assert(hasGameCard(baron, state, 2) >=0, 0 >= 0);
    if (result == 0)
      printf("precondition #7 fail: baron in discard pile: FALSE, expected: TRUE\n");
    else
       printf("precondition #7 pass: baron in discard pile: TRUE, expected: TRUE\n");    


    // precondition #8 - supplyCount for estate unchanged
    result = assert(preState->supplyCount[estate], state->supplyCount[estate]);
    if (result == 0)
      printf("precondition #8 fail: estate supply count unchanged: %d, expected: %d\n", state->supplyCount[estate], preState->supplyCount[estate]);
    else
        printf("precondition #8 pass: estate supply count unchanged: %d, expected: %d\n", state->supplyCount[estate], preState->supplyCount[estate]);
*/
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


void printAllSupplyCounts(struct gameState *state)
{
  printf("supplyCount (curse): %d\n", state->supplyCount[curse]);
  printf("supplyCount (estate): %d\n", state->supplyCount[estate]);
  printf("supplyCount (duchy): %d\n", state->supplyCount[duchy]);
  printf("supplyCount (province): %d\n", state->supplyCount[province]);
  printf("supplyCount (copper): %d\n", state->supplyCount[copper]);
  printf("supplyCount (silver): %d\n", state->supplyCount[silver]);
  printf("supplyCount (gold): %d\n", state->supplyCount[gold]);
  printf("supplyCount (baron): %d\n", state->supplyCount[baron]);
  printf("supplyCount (gardens): %d\n", state->supplyCount[gardens]);
  printf("supplyCount (ambassador): %d\n", state->supplyCount[ambassador]);
  printf("supplyCount (village): %d\n", state->supplyCount[village]);
  printf("supplyCount (minion): %d\n", state->supplyCount[minion]);
  printf("supplyCount (mine): %d\n", state->supplyCount[mine]);
  printf("supplyCount (sea_hag): %d\n", state->supplyCount[sea_hag]);
  printf("supplyCount (tribute): %d\n", state->supplyCount[tribute]);
  printf("supplyCount (smithy): %d\n", state->supplyCount[smithy]);

}


void printAllGameStateVariables(struct gameState *state)
{

  int i;

    // print out the results of the game state
  printf("numPlayers: %d\n", state->numPlayers);
  printf("supplyCount (curse): %d\n", state->supplyCount[curse]);
  printf("supplyCount (estate): %d\n", state->supplyCount[estate]);
  printf("supplyCount (duchy): %d\n", state->supplyCount[duchy]);
  printf("supplyCount (province): %d\n", state->supplyCount[province]);
  printf("supplyCount (copper): %d\n", state->supplyCount[copper]);
  printf("supplyCount (silver): %d\n", state->supplyCount[silver]);
  printf("supplyCount (gold): %d\n", state->supplyCount[gold]);
  printf("supplyCount (baron): %d\n", state->supplyCount[baron]);
  printf("supplyCount (gardens): %d\n", state->supplyCount[gardens]);
  printf("supplyCount (ambassador): %d\n", state->supplyCount[ambassador]);
  printf("supplyCount (village): %d\n", state->supplyCount[village]);
  printf("supplyCount (minion): %d\n", state->supplyCount[minion]);
  printf("supplyCount (mine): %d\n", state->supplyCount[mine]);
  printf("supplyCount (sea_hag): %d\n", state->supplyCount[sea_hag]);
  printf("supplyCount (tribute): %d\n", state->supplyCount[tribute]);
  printf("supplyCount (smithy): %d\n", state->supplyCount[smithy]);
  printf("whoseTurn (1): %d\n", state->whoseTurn);
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

  printf("Player 1's discards:\n");
  for (i = 0; i < state->discardCount[0]; i++)
    printf("  Card #%d: %d\n", i+1, state->discard[0][i]);

  printf("Player 2's discards:\n");
  for (i = 0; i < state->discardCount[1]; i++)
    printf("  Card #%d: %d\n", i+1, state->discard[1][i]);

}





/*


int playAmbassador(int choice1, int choice2, struct gameState *state, int handPos)
{
    int i;
    int currentPlayer = whoseTurn(state);
    int j = 0;      //used to check if player has enough cards to discard

    // impossible choice
    if (choice2 > 2 || choice2 < 0)
    {
        return -1;
    }

    // player chose to reveal card they played (not possible)
    if (choice1 == handPos)
    {
        return -1;
    }

    // count the number of cards of a specific kind chosen by the user
        for (i = 0; i <= state->handCount[currentPlayer]; i++)
        {
            if (i != handPos && state->hand[currentPlayer][i]  == state->hand[currentPlayer][choice1] && i != choice1)
            {
                j++;
            }
        }
        if (j < choice2)
        {
            return -1;
        }

        if (DEBUG)
            printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);

        //increase supply count for choosen card by amount being discarded
        state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;

        //each other player gains a copy of revealed card
        for (i = 0; i < state->numPlayers; i++)
        {
            if (i != currentPlayer)
            {
                gainCard(state->hand[currentPlayer][choice2], state, 0, i);
            }
        }

        //discard played card from hand
        discardCard(handPos, currentPlayer, state, 0);

        //trash copies of cards returned to supply
        for (j = 0; j < choice2; j++)
        {
            for (i = 0; i < state->handCount[currentPlayer]; i++)
            {
                if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1])
                {
                    discardCard(i, currentPlayer, state, 1);
                    break;
                }
            }
        }

        return 0;
}



*/
