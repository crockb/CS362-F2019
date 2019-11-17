/* randomtestcard2.c
	Author/Date:  Bryant Crock  11/16/19
	Description:  Test the outcomes of the refactored minion card playMinion();
	Business Requirements for Minion:
		 1. +1 Action
		 2. Choice 1:  +2 coins
		 3. Choice 2:  Discard hand, +4 cards, each other player discards their hand and draws 4
	Test Conditions Identified and Expected End States:
		CONDITION #1:  Choice 1 - Add 2 coins:   -1 hand[minion], +2 coins, 1 action
		CONDITION #2:  Choice 2 - Discard Hand (at least 1 other player has > 4 hand cards)

   	Known Bugs Inserted in Assignment 2:
		1. Removed the +1 Action of the card at the beginning.
        2. In the draw4 cards set of statements i has been replaced with j'
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

// global variables to check when conditions 1 & 2 conditions are met
int condition1 = 0, condition2 = 0;

// helper function signatures
int testPlayMinion();
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


// call randomtestcard2
int main()
{
    srand(time(NULL));
    testPlayMinion();
    return 0;
}


// function to execute the set of conditions for unittest#1
int testPlayMinion()
{

   	//int choice1, choice2, bonus = 0;
    int iterations = 0;

    struct gameState state, preState;
    int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy
            };

    printf("\n\n----- RANDOM TEST #2 - playMinion() - STARTED -----\n\n");

    //while (condition1 == 0 || condition2 == 0) {
    while (iterations < 1) {
    	// randomize the game state
    	randomizeGameState(&state, k);
    	printAllGameStateVariables(&state);


    	/*
        // provide player1 with a minion card
        state.hand[state.whoseTurn][0] = minion;
        state.supplyCount[minion]--;

        // update the states
        updateCoins(0, &state, bonus);
        memcpy(&preState, &state, sizeof(struct gameState));

        // int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
        choice1 = rand() % 2;
        choice2 = rand() % 2;

        playCard(0, choice1, choice2, 0, &state);
		printTestResults(&state, &preState, choice1, choice2);
		*/
    	iterations++;
	
	}

    printf("\n----- RANDOM TEST #2 - playMinion() - COMPLETED - (%d iterations) -----\n", iterations);
	
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
            state->discard[player][i] = state->deck[player][state->deckCount[player]-1];
            state->discardCount[player]++;
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

    int i, result1, result2, pHandTooMany;

    // CONDITION #1:  Choice 1 - Add 2 coins
    if (choice1 == 1 && condition1 == 0) {

    	printf("\nCONDITION #1 met:  Choice 1 - Add 2 coins\n");
        
        // update condition met criteria
        condition1 = 1;

    	// precondition #1 - player has one less minion in hand
    	result1 = assert(countCardType(minion, preState, 0)-1, countCardType(minion, state, 0));
    	if (result1 == 0)
      		printf("precondition #1 fail: # minions in hand: %d, expected: %d\n", countCardType(minion, state, 0), countCardType(minion, preState, 0)-1);
    	else
      		printf("precondition #1 pass: # minions in hand: %d, expected: %d\n", countCardType(minion, state, 0), countCardType(minion, preState, 0)-1);

    	// precondition #2 - player has +2 coins
    	result1 = assert(preState->coins+2, state->coins);
    	if (result1 == 0)
      		printf("precondition #2 fail: # of coins: %d, expected: %d\n", state->coins, preState->coins+2);
    	else
       		printf("precondition #2 pass: # of coins: %d, expected: %d\n", state->coins, preState->coins+2);   
    
    	// precondition #3 - player has 1 action
    	result1 = assert(1, state->numActions);
    	if (result1 == 0)
      		printf("precondition #3 fail: # of actions: %d, expected: 1\n", state->numActions);
    	else
       		printf("precondition #3 pass: # of actions: %d, expected: 1\n", state->numActions);

    }

    // CONDITION #2:  Choice 2 - Discard Hand (at least 1 other player has > 4 hand cards)
    result2 = 0;
    for (i = 0; i < state->numPlayers; i++) {
    	if (state->whoseTurn != i) {
    		// found a player with > 4 hand cards
    		if (state->handCount[i] > 4) {
    			result2 = 1;
    		}
    		else {
    			// do nothing
    		}
    	}
    }

 	if (choice1 == 0 && choice2 == 1 && result2 == 1 && condition2 == 0) {

    	printf("\nCONDITION #2 met:  Choice 2 - Discard Hand (at least 1 other player has > 4 hand cards)\n");
        
        // update condition met criteria
        condition2 = 1;

    	// precondition #1 - player has one less minion in hand
    	result1 = assert(countCardType(minion, preState, 0)-1, countCardType(minion, state, 0));
    	if (result1 == 0)
      		printf("precondition #1 fail: # minions in hand: %d, expected: %d\n", countCardType(minion, state, 0), countCardType(minion, preState, 0)-1);
    	else
      		printf("precondition #1 pass: # minions in hand: %d, expected: %d\n", countCardType(minion, state, 0), countCardType(minion, preState, 0)-1);

		// precondition #2 - all players should have <= 4 cards
    	result2 = 1;
    	for (i = 0; i < state->numPlayers; i++) {
    		// found a player with > 4 hand cards
    		if (state->handCount[i] > 4) {
    			result2 = 0;
    			pHandTooMany = i;
    		}
    		else {
    			// do nothing
    		}
    	}

    	result1 = assert(1, result2);
    	if (result1 == 0) {
      		printf("precondition #2 fail: all players have <= 4 hand cards: p%d has %d hand cards.\n", pHandTooMany+1, state->handCount[pHandTooMany]);
      		printf("whoseTurn = %d\n", state->whoseTurn);
      		printAllGameStateVariables(state);
    	}
    	else
      		printf("precondition #2 pass: all players have <= 4 hand cards\n");


    	// precondition #3 - player has 1 action
    	result1 = assert(1, state->numActions);
    	if (result1 == 0)
      		printf("precondition #3 fail: # of actions: %d, expected: 1\n", state->numActions);
    	else
       		printf("precondition #3 pass: # of actions: %d, expected: 1\n", state->numActions);
 	}

}

/* assignment #2 - a function to play the minion card */
/*
int playMinion(int choice1, int choice2, struct gameState *state, int handPos)
{

    int i;
    int j;
    int currentPlayer = whoseTurn(state);

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    if (choice1)
    {
        state->coins = state->coins + 2;
    }
    else if (choice2)       //discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
    {
        //discard hand
        while(numHandCards(state) > 0)
        {
            discardCard(0, currentPlayer, state, 0);
        }

        //draw 4
        for (i = 0; i < 4; i++)
        {
            drawCard(currentPlayer, state);
        }

        //other players discard hand and redraw if hand size > 4
        for (i = 0; i < state->numPlayers; i++)
        {
            if (i != currentPlayer)
            {
                if ( state->handCount[i] > 4 )
                {
                    //discard hand
                    while( state->handCount[i] > 0 )
                    {
                        discardCard(0, i, state, 0);
                    }

                    //draw 4
                    for (j = 0; j < 4; j++)
                    {
                        drawCard(j, state);
                    }
                }
            }
        }

    }
    return 0;
}
*/




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


void printAllGameStateVariables(struct gameState *state) {

  int i, j;

/*
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
*/
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