/* randomtestcard1.c
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


    Known Bugs Inserted in Assignment 2:
        1. Omitted a necessary step(s) to “discardCard” when the estate card was found.  
           This will cause the player’s hand to incorrectly retain an estate during gameplay.

        2. Decremented the supplyCount of estates after executing the gainCard() function 
           (duplicative reduction of supplyCount).  May cause the game to end too soon by over 
           removing estate cards when referenced in the Baron cards.

    
    struct gameState {
    int numPlayers; //number of players
    int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
    int embargoTokens[treasure_map+1];
    int outpostPlayed; // flag indicating if an outpost was played during the turn
    int outpostTurn; // 
    int whoseTurn; // set to the current player's turn
    int phase; // keeps track of the phase number within the game
    int numActions; // Starts at 1 each turn
    int coins; // Use as you see fit!
    int numBuys; // Starts at 1 each turn
    int hand[MAX_PLAYERS][MAX_HAND];  // holds the cards within each player's hand
    int handCount[MAX_PLAYERS]; // holds the number of cards within each player's hand
    int deck[MAX_PLAYERS][MAX_DECK]; // holds the cards within each player's deck
    int deckCount[MAX_PLAYERS]; // holds the number of cards in each player's deck
    int discard[MAX_PLAYERS][MAX_DECK]; // holds the cards within each player's discard pile
    int discardCount[MAX_PLAYERS]; // holds the number of cards in each player's discard pile
    int playedCards[MAX_DECK]; // 
    int playedCardCount;

    int playBaron(int choice1, struct gameState *state, int handPos)
    Requirements for Random Tester:
       --- randomizeGameStates ()
          --- handPosition of card (leave at 0?) - GOOD
          --- set of cards in the game (set a constant state?) - GOOD
          --- number of players in the game (2 to 4) - GOOD
          --- randomize type of cards in the hand - GOOD
          --- number of cards in hand (minion (4)) - GOOD
          --- number of cards in discard (tribute 1 or 0) = randomizeDiscard - GOOD
          --- number of cards in deck (tribute 1 or 0) = randomizeDeck - GOOD
          --- supply counts for estate (baron 0 or 2) --- can be a 50/50
          --- number of estates in hand (yes/no) --- can be a 50/50
          --- whos turn is it (number of players) --- can be taken care of early

*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

// global variables to check when 1-4 conditions already met
int condition1, condition2, condition3, condition4 = 0;

// helper function signatures
int testPlayBaron();
int assert(int expected, int actual);
int countCardType(int card, struct gameState *state, int pileToCheck);

// helper functions for randomizing the game state
int randomizePlayerCount();
void randomizeDeckCards(struct gameState *state, int kingdomCards[10]);
void randomizePiles(struct gameState *state);
void randomizeGameState(struct gameState *state, int kingdomCards[10]);

// helper print functions
void printTestResults(struct gameState *state, struct gameState *preState, int choice1, int choice2);
void printPlayersCards(int player, struct gameState *state);
void printAllSupplyCounts(struct gameState *state);
void printAllGameStateVariables(struct gameState *state);
int printCardName(int card);


// call randomtestcard1
int main()
{
    srand(time(NULL));
    testPlayBaron();
    return 0;
}

// function to execute the set of conditions for unittest#1
int testPlayBaron()
{
    int choice1, choice2, bonus = 0;
    int iterations = 0;
    struct gameState state, preState;
    int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy
            };

    printf("\n\n----- RANDOM TEST #1 - playBaron() - STARTED -----\n\n");

    while (condition1 == 0 || condition2 == 0 || condition3 == 0 || condition4 == 0) {

        // randomize the game state
        randomizeGameState(&state, k);

        // provide player1 with a baron card
        state.hand[state.whoseTurn][0] = baron;
        state.supplyCount[baron]--;

        // update the states
        updateCoins(0, &state, bonus);
        memcpy(&preState, &state, sizeof(struct gameState));

        // int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
        choice1 = rand() % 2;
        choice2 = rand() % 2;

        playCard(0, choice1, choice2, 0, &state);

        printTestResults(&state, &preState, choice1, choice2);
        iterations++;
      }


    printf("\n----- RANDOM TEST #1 - playBaron() - COMPLETED - (%d iterations) -----\n", iterations);

    return 0;


}

int assert(int expected, int actual)
{
  if (expected == actual)
    return 1;
  else
    return 0;
}



void randomizeGameState(struct gameState *state, int kingdomCards[10]) {

    int n;

    // initialize the game
    initializeGame(randomizePlayerCount(), kingdomCards, 1234, state);

    randomizeDeckCards(state, kingdomCards);
    randomizePiles(state);

    // randomize who's turn, # of estates
    n = rand() % state->numPlayers;
    state->whoseTurn = n;

    n = rand() % 4;
    state->supplyCount[estate] = n;

}


int randomizePlayerCount(){
    int n;
    n = rand() % 4 + 1;
    if (n == 1)
       n = 2;
    return n;
}

// int shuffle(int player, struct gameState *state)
void randomizeDeckCards(struct gameState *state, int kingdomCards[10]) {

  int player, i, j, n;

  // randomly swap out a deck card with another from the gameset
  for (player = 0; player < state->numPlayers; player++) {

      // move all hand cards to the deck
      for (i = 0; i < state->handCount[player]; i++) {
          state->deck[player][state->deckCount[player]] = state->hand[player][i];
          state->deckCount[player]++;
      }
      state->handCount[player] = 0;

      // move all hand cards to the deck
      for (i = 0; i < state->discardCount[player]; i++) {
          state->deck[player][state->deckCount[player]] = state->discard[player][i];
          state->deckCount[player]++;
      }   
      state->handCount[player] = 0;

      for (i = 0; i < 20; i++) {
          j = rand() % state->deckCount[player];
          n = rand() % 10;
          state->deck[player][j] = kingdomCards[n];
      }
  }
}

void randomizePiles(struct gameState *state){
    int player, i, numHand, numDiscard;

    for (player = 0; player < state->numPlayers; player++) {
        numHand = rand() % state->deckCount[player];
        if (numHand < 3)
            numHand = numHand + 3;

        // draw cards
        for (i = 0; i < numHand; i++){
          drawCard(player, state);
        }

        // randomly set discard pile from back of deck pile
        numDiscard = rand() % state->deckCount[player];

        for (i = 0; i < numDiscard; i++){
            state->discardCount[player]++;
            state->discard[player][i] = state->deck[player][state->deckCount[player]-1];
            state->deckCount[player]--;
        }

    }

}


int countCardType(int card, struct gameState *state, int pileToCheck)
{

  int i;
  int count = 0;
  int player = state->whoseTurn;
  int hand = 0;
  int discard = 1;
  int deck = 2;

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

  // error - no pile indicated
  return -1;

}


void printTestResults(struct gameState *state, struct gameState *preState, int choice1, int choice2) {

    int player = state->whoseTurn;
    int result;

    // CONDITION #1:  Remove Estate (Player Has An Estate)
    if (choice1 == 1 && countCardType(estate, state, 0) >=1 && condition1 == 0) {
        
        printf("\nCONDITION #1 met:  Remove Estate (Player Has An Estate)\n");
        
        // update condition met criteria
        condition1 = 1;

        // precondition #1 - player has one less estate in hand
        result = assert(countCardType(estate, preState, 0)-1, countCardType(estate, state, 0));
        if (result == 0)
            printf("precondition #1 fail: # estates in hand: %d, expected: %d\n", countCardType(estate, state, 0), countCardType(estate, preState, 0)-1);
        else
            printf("precondition #1 pass: # estates in hand: %d, expected: %d\n", countCardType(estate, state, 0), countCardType(estate, preState, 0)-1);

        // precondition #2 - player has one less baron in hand
        result = assert(countCardType(baron, preState, 0)-1, countCardType(baron, state, 0));
        if (result == 0)
            printf("precondition #2 fail: # barons in hand: %d, expected: %d\n", countCardType(baron, state, 0), countCardType(baron, preState, 0)-1);
        else
            printf("precondition #2 pass: # barons in hand: %d, expected: %d\n", countCardType(baron, state, 0), countCardType(baron, preState, 0)-1);

        // precondition #3 - player has 3 cards in hand (less 1 estate, less 1 baron)
        result = assert(preState->handCount[player]-2, state->handCount[player]);
        if (result == 0)
            printf("precondition #3 fail: # cards in hand: %d, expected: %d\n", state->handCount[player], preState->handCount[player]-2);
        else
            printf("precondition #3 pass: # cards in hand: %d, expected: %d\n", state->handCount[player], preState->handCount[player]-2);    

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

        // precondition #7 - player has +1 discarded baron
        result = assert(countCardType(baron, preState, 1)+1, countCardType(baron, state, 1));
        if (result == 0)
            printf("precondition #7 fail: # barons in discard: %d, expected: %d\n", countCardType(baron, state, 1), countCardType(baron, preState, 1)+1);
        else
            printf("precondition #7 pass: # barons in discard: %d, expected: %d\n", countCardType(baron, state, 1), countCardType(baron, preState, 1)+1);  

        // precondition #8 - supplyCount for estate unchanged
        result = assert(preState->supplyCount[estate], state->supplyCount[estate]);
        if (result == 0)
            printf("precondition #8 fail: estate supply count unchanged: %d, expected: %d\n", state->supplyCount[estate], preState->supplyCount[estate]);
        else
            printf("precondition #8 pass: estate supply count unchanged: %d, expected: %d\n", state->supplyCount[estate], preState->supplyCount[estate]);

    }



    // CONDITION #2:  Remove Estate (Player Does Not Have An Estate)
    if (choice1 == 1 && countCardType(estate, state, 0) == 0 && condition2 == 0) {
        
        printf("\nCONDITION #2 met:  Remove Estate (Player Does Not Have An Estate)\n");
        
        // update condition met criteria
        condition2 = 1;

        // precondition #1 - player gains 1 more estate
        result = assert(countCardType(estate, preState, 0)+1, countCardType(estate, state, 0));
        if (result == 0)
          printf("precondition #1 fail: gain an estate - # estates in hand: %d, expected: %d\n", countCardType(estate, state, 0), countCardType(estate, preState, 0)+1);
        else
          printf("precondition #1 pass: gain an estate - # estates in hand: %d, expected: %d\n", countCardType(estate, state, 0), countCardType(estate, preState, 0)+1);

        // precondition #2 - player has one less baron in hand
        result = assert(countCardType(baron, preState, 0)-1, countCardType(baron, state, 0));
        if (result == 0)
            printf("precondition #2 fail: # barons in hand: %d, expected: %d\n", countCardType(baron, state, 0), countCardType(baron, preState, 0)-1);
        else
            printf("precondition #2 pass: # barons in hand: %d, expected: %d\n", countCardType(baron, state, 0), countCardType(baron, preState, 0)-1);
        
        // precondition #3 - player has same # of cards in hand (lose baron, gain estate)
        result = assert(preState->handCount[player], state->handCount[player]);
        if (result == 0)
            printf("precondition #3 fail: same # of cards in hand: %d, expected: %d\n", state->handCount[player], preState->handCount[player]);
        else
            printf("precondition #3 pass: same # of cards in hand: %d, expected: %d\n", state->handCount[player], preState->handCount[player]);    
    
        // precondition #4 - player has the same number of coins
        result = assert(preState->coins, state->coins);
        if (result == 0)
            printf("precondition #4 fail: same # of coins: %d, expected: %d\n", state->coins, preState->coins);
        else
            printf("precondition #4 pass: same # of coins: %d, expected: %d\n", state->coins, preState->coins); 

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

        // precondition #7 - player has +1 discarded baron
        result = assert(countCardType(baron, preState, 1)+1, countCardType(baron, state, 1));
        if (result == 0)
            printf("precondition #7 fail: # barons in discard: %d, expected: %d\n", countCardType(baron, state, 1), countCardType(baron, preState, 1)+1);
        else
            printf("precondition #7 pass: # barons in discard: %d, expected: %d\n", countCardType(baron, state, 1), countCardType(baron, preState, 1)+1);  

        // precondition #8 - supplyCount for estate -1
        result = assert(preState->supplyCount[estate]-1, state->supplyCount[estate]);
        if (result == 0)
            printf("precondition #8 fail: estate supply count reduced by 1: %d, expected: %d\n", state->supplyCount[estate], preState->supplyCount[estate]-1);
        else
            printf("precondition #8 pass: estate supply count reduced by 1: %d, expected: %d\n", state->supplyCount[estate], preState->supplyCount[estate]-1);

    }

    // CONDITION #3:  Choose to Gain an Estate (Multiple Estates Available)
    if (choice1 == 0 && countCardType(estate, state, 0) >= 2 && condition3 == 0) {
        
        printf("\nCONDITION #3 met:  Choose to Gain an Estate (Multiple Estates Available)\n");
        
        // update condition met criteria
        condition3 = 1;

        // precondition #1 - player gains 1 more estate
        result = assert(countCardType(estate, preState, 0)+1, countCardType(estate, state, 0));
        if (result == 0)
          printf("precondition #1 fail: gain an estate - # estates in hand: %d, expected: %d\n", countCardType(estate, state, 0), countCardType(estate, preState, 0)+1);
        else
          printf("precondition #1 pass: gain an estate - # estates in hand: %d, expected: %d\n", countCardType(estate, state, 0), countCardType(estate, preState, 0)+1);

        // precondition #2 - player has one less baron in hand
        result = assert(countCardType(baron, preState, 0)-1, countCardType(baron, state, 0));
        if (result == 0)
            printf("precondition #2 fail: # barons in hand: %d, expected: %d\n", countCardType(baron, state, 0), countCardType(baron, preState, 0)-1);
        else
            printf("precondition #2 pass: # barons in hand: %d, expected: %d\n", countCardType(baron, state, 0), countCardType(baron, preState, 0)-1);
        
        // precondition #3 - player has same # of cards in hand (lose baron, gain estate)
        result = assert(preState->handCount[player], state->handCount[player]);
        if (result == 0)
            printf("precondition #3 fail: same # of cards in hand: %d, expected: %d\n", state->handCount[player], preState->handCount[player]);
        else
            printf("precondition #3 pass: same # of cards in hand: %d, expected: %d\n", state->handCount[player], preState->handCount[player]);    
    
        // precondition #4 - player has the same number of coins
        result = assert(preState->coins, state->coins);
        if (result == 0)
            printf("precondition #4 fail: same # of coins: %d, expected: %d\n", state->coins, preState->coins);
        else
            printf("precondition #4 pass: same # of coins: %d, expected: %d\n", state->coins, preState->coins); 

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

        // precondition #7 - player has +1 discarded baron
        result = assert(countCardType(baron, preState, 1)+1, countCardType(baron, state, 1));
        if (result == 0)
            printf("precondition #7 fail: # barons in discard: %d, expected: %d\n", countCardType(baron, state, 1), countCardType(baron, preState, 1)+1);
        else
            printf("precondition #7 pass: # barons in discard: %d, expected: %d\n", countCardType(baron, state, 1), countCardType(baron, preState, 1)+1);  

        // precondition #8 - supplyCount for estate -1
        result = assert(preState->supplyCount[estate]-1, state->supplyCount[estate]);
        if (result == 0)
            printf("precondition #8 fail: estate supply count reduced by 1: %d, expected: %d\n", state->supplyCount[estate], preState->supplyCount[estate]-1);
        else
            printf("precondition #8 pass: estate supply count reduced by 1: %d, expected: %d\n", state->supplyCount[estate], preState->supplyCount[estate]-1);

    }

    // CONDITION #4:  Choose to Gain an Estate (<= 1 Estate Available)
    if (choice1 == 0 && countCardType(estate, state, 0) <= 1 && condition4 == 0) {

        printf("\nCONDITION #4 met:  Choose to Gain an Estate (<= 1 Estate Available)\n");
        
        // update condition met criteria
        condition4 = 1;

        // precondition #1 - player gains 1 more estate
        result = assert(countCardType(estate, preState, 0)+1, countCardType(estate, state, 0));
        if (result == 0)
          printf("precondition #1 fail: gain an estate - # estates in hand: %d, expected: %d\n", countCardType(estate, state, 0), countCardType(estate, preState, 0)+1);
        else
          printf("precondition #1 pass: gain an estate - # estates in hand: %d, expected: %d\n", countCardType(estate, state, 0), countCardType(estate, preState, 0)+1);

        // precondition #2 - player has one less baron in hand
        result = assert(countCardType(baron, preState, 0)-1, countCardType(baron, state, 0));
        if (result == 0)
            printf("precondition #2 fail: # barons in hand: %d, expected: %d\n", countCardType(baron, state, 0), countCardType(baron, preState, 0)-1);
        else
            printf("precondition #2 pass: # barons in hand: %d, expected: %d\n", countCardType(baron, state, 0), countCardType(baron, preState, 0)-1);
        
        // precondition #3 - player has same # of cards in hand (lose baron, gain estate)
        result = assert(preState->handCount[player], state->handCount[player]);
        if (result == 0)
            printf("precondition #3 fail: same # of cards in hand: %d, expected: %d\n", state->handCount[player], preState->handCount[player]);
        else
            printf("precondition #3 pass: same # of cards in hand: %d, expected: %d\n", state->handCount[player], preState->handCount[player]);    
    
        // precondition #4 - player has the same number of coins
        result = assert(preState->coins, state->coins);
        if (result == 0)
            printf("precondition #4 fail: same # of coins: %d, expected: %d\n", state->coins, preState->coins);
        else
            printf("precondition #4 pass: same # of coins: %d, expected: %d\n", state->coins, preState->coins); 

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

        // precondition #7 - player has +1 discarded baron
        result = assert(countCardType(baron, preState, 1)+1, countCardType(baron, state, 1));
        if (result == 0)
            printf("precondition #7 fail: # barons in discard: %d, expected: %d\n", countCardType(baron, state, 1), countCardType(baron, preState, 1)+1);
        else
            printf("precondition #7 pass: # barons in discard: %d, expected: %d\n", countCardType(baron, state, 1), countCardType(baron, preState, 1)+1);  

        // precondition #8 - supplyCount for estate -1
        result = assert(preState->supplyCount[estate]-1, state->supplyCount[estate]);
        if (result == 0)
            printf("precondition #8 fail: estate supply count reduced by 1: %d, expected: %d\n", state->supplyCount[estate], preState->supplyCount[estate]-1);
        else
            printf("precondition #8 pass: estate supply count reduced by 1: %d, expected: %d\n", state->supplyCount[estate], preState->supplyCount[estate]-1);

      }

}



void printPlayersCards(int player, struct gameState *state)
{
    int i;

    // print the hand
  printf("Player's hand:\n");
  for (i = 0; i < state->handCount[player]; i++) {
    printf("  Card #%d: ", i+1);
    printCardName(state->hand[player][i]);
  }

  // print the discard
  printf("Player's discard pile:\n");
  for (i = 0; i < state->discardCount[player]; i++) {
    printf("  Card #%d: ", i+1);
    printCardName(state->discard[player][i]);
  }

  // print the deck
  printf("Player's deck:\n");
  for (i = 0; i < state->deckCount[player]; i++) {
    printf("  Card #%d: ", i+1);
    printCardName(state->deck[player][i]);
  }
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

  int i, j;

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

  // print all player's hands

  for(j = 0; j < state->numPlayers; j++) {
      // print the hand
      printf("Player %d's hand:\n", j+1);
      for (i = 0; i < state->handCount[j]; i++) {
        printf("  Card #%d: ", i+1);
        printCardName(state->hand[j][i]);
      }

      // print the discard
      printf("Player %d's discard pile:\n", j+1);
      for (i = 0; i < state->discardCount[j]; i++) {
        printf("  Card #%d: ", i+1);
        printCardName(state->discard[j][i]);
      }

      // print the deck
      printf("Player %d's deck:\n", j+1);
      for (i = 0; i < state->deckCount[j]; i++) {
        printf("  Card #%d: ", i+1);
        printCardName(state->deck[j][i]);
      }

  }

}


int printCardName(int card)
{

    switch(card)
    {
    case curse:
        printf("curse\n");
        return 1;
    case estate:
        printf("estate\n");
        return 1;
    case duchy:
        printf("duchy\n");
        return 1;
    case province:
        printf("province\n");
        return 1;
    case copper:
        printf("copper\n");
        return 1;
    case silver:
        printf("silver\n");
        return 1;
    case gold:
        printf("gold\n");
        return 1;
    case adventurer:
        printf("adventurer\n");
        return 1;
    case council_room:
        printf("council_room\n");
        return 1;
    case feast:
        printf("feast\n");
        return 1;
    case gardens:
        printf("gardens\n");
        return 1;
    case mine:
        printf("mine\n");
        return 1;
    case remodel:
        printf("remodel\n");
        return 1;
    case smithy:
        printf("smithy\n");
        return 1;
    case village:
        printf("village\n");
        return 1;
    case baron:
        printf("baron\n");
        return 1;
    case great_hall:
        printf("great_hall\n");
        return 1;
    case minion:
        printf("minion\n");
        return 1;
    case steward:
        printf("steward\n");
        return 1;
    case tribute:
        printf("tribute\n");
        return 1;
    case ambassador:
        printf("ambassador\n");
        return 1;
    case cutpurse:
        printf("cutpurse\n");
        return 1;
    case embargo:
        printf("embargo\n");
        return 1;
    case outpost:
        printf("outpost\n");
        return 1;
    case salvager:
        printf("salvager\n");
        return 1;
    case sea_hag:
        printf("sea_hag\n");
        return 1;
    case treasure_map:
        printf("treasure_map\n");
        return 1;

    }

    return -1;
}