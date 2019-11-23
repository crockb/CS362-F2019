/* unittest1.c
  Author/Date:  Bryant Crock  11/1/19
  Description:  Test the outcomes of the refactored baron card playBaron();
  Business Requirements for Baron:
     1. +1 Buy
     2. Choice 1:  Discard an Estate for +4 coins.  If no Estate, receive an Estate
     3. Choice 2:  Receive an Estate

  Test Conditions Identified and Expected End States:
    CONDITION #1:  Remove Estate (Has Estate):  -1 hand[estate], -1 hand[baron], 3 handCount, +4 coins, +1 buy, 0 actions, +1 discard[baron], estate supply count unchanged
    CONDITION #2:  Remove Estate (No Estate):   +1 hand[estate], -1 hand[baron], 5 handCount, same coins, +1 buy, 0 actions, +1 discard[baron], -1 supply[estate]
    CONDITION #3:  Gain an Estate (Multiple Estates Available):  +1 hand[estate], -1 hand[baron], 5 handCount, same coins, +1 buy, 0 actions, +1 discard[baron], -1 supply[estate]
    CONDITION #4:  Gain an Estate (1 Estate Available):  +1 hand[estate], -1 hand[baron], 5 handCount, same coins, +1 buy, 0 actions, +1 discard[baron], -1 supply[estate]


// signature for playBaron()
int cardEffectBaron(int choice1, struct gameState *state)


*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"




// helper function signatures
int testPlayBaron();
int assert(int expected, int actual);
int hasGameCard(int card, struct gameState *state, int pileToCheck);
int countCardTypeInHand(int card, struct gameState *state);
int provideEstateCardFromDeck(int player, struct gameState *state);
int removeEstateCardFromHand(int player, struct gameState *state);

// helper print functions
void printTestCondition1Results(struct gameState *state, struct gameState *preState);
void printTestCondition2to4Results(struct gameState *state, struct gameState *preState);
void printPlayersCards(int player, struct gameState *state);
void printAllSupplyCounts(struct gameState *state);
void printAllGameStateVariables(struct gameState *state);


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
    printf("----- UNIT TEST #1 - playBaron() - CONDITION #1: player1 chooses to discard an estate - player1 has an estate.\n");

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
    printTestCondition1Results(&state, &preState);

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
    printTestCondition2to4Results(&state, &preState);

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
    printTestCondition2to4Results(&state, &preState);

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
    printTestCondition2to4Results(&state, &preState);

    printf("\n----- UNIT TEST #1 - playBaron() - COMPLETED -----\n");

  return 0;
}



int assert(int expected, int actual)
{
  if (expected == actual)
    return 1;
  else
    return 0;
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

    // precondition #1 - player has one less estate in hand
    result = assert(countCardTypeInHand(estate, preState)-1, countCardTypeInHand(estate, state));
    if (result == 0)
      printf("precondition #1 fail: # estates in hand: %d, expected: %d\n", countCardTypeInHand(estate, state), countCardTypeInHand(estate, preState)-1);
    else
       printf("precondition #1 pass: # estates in hand: %d, expected: %d\n", countCardTypeInHand(estate, state), countCardTypeInHand(estate, preState)-1);

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

}

void printTestCondition2to4Results(struct gameState *state, struct gameState *preState)
{
  int player1 = 0;
  int result = 0;

    // precondition #1 - player has gains 1 more estate
    result = assert(countCardTypeInHand(estate, preState)+1, countCardTypeInHand(estate, state));
    if (result == 0)
      printf("precondition #1 fail: gain an estate - # estates in hand: %d, expected: %d\n", countCardTypeInHand(estate, state), countCardTypeInHand(estate, preState)+1);
    else
       printf("precondition #1 pass: gain an estate - # estates in hand: %d, expected: %d\n", countCardTypeInHand(estate, state), countCardTypeInHand(estate, preState)+1);

    // precondition #2 - player has one less baron in hand
    result = assert(countCardTypeInHand(baron, preState)-1, countCardTypeInHand(baron, state));
    if (result == 0)
      printf("precondition #2 fail: # barons in hand: %d, expected: %d\n", countCardTypeInHand(baron, state), countCardTypeInHand(baron, preState)-1);
    else
       printf("precondition #2 pass: # barons in hand: %d, expected: %d\n", countCardTypeInHand(baron, state), countCardTypeInHand(baron, preState)-1);

    // precondition #3 - player has 5 cards in hand (lose baron, gain estate)
    result = assert(preState->handCount[player1], state->handCount[player1]);
    if (result == 0)
      printf("precondition #3 fail: # cards in hand: %d, expected: %d\n", state->handCount[player1], preState->handCount[player1]);
    else
       printf("precondition #3 pass: # cards in hand: %d, expected: %d\n", state->handCount[player1], preState->handCount[player1]);    

    // precondition #4 - player has the same number of coins
    result = assert(preState->coins, state->coins);
    if (result == 0)
      printf("precondition #4 fail: # of coins: %d, expected: %d\n", state->coins, preState->coins);
    else
       printf("precondition #4 pass: # of coins: %d, expected: %d\n", state->coins, preState->coins); 

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

    // precondition #8 - supplyCount for estate -1
    result = assert(preState->supplyCount[estate]-1, state->supplyCount[estate]);
    if (result == 0)
      printf("precondition #8 fail: estate supply count reduced by 1: %d, expected: %d\n", state->supplyCount[estate], preState->supplyCount[estate]-1);
    else
        printf("precondition #8 pass: estate supply count reduced by 1: %d, expected: %d\n", state->supplyCount[estate], preState->supplyCount[estate]-1);
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