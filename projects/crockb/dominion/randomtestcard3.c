/* randomtestcard3.c
	Author/Date:  Bryant Crock  11/16/19
	Description:  Test the outcomes of the refactored tribute card playTribute();
	Business Requirements for Tribute:
		 1. The player to the left reveals then discards top 2 deck cards
		 2. For each differently named card:
		 		- Action: +2 actions
		 		- Treasure Card: +2 coins
		 		- Victory Card: +2 cards

	CONDITIONS:  1: Left player has 1 or less cards in discard/deck - deckCount > 0
				 2: Left player has 1 or less cards in discard/deck - discardCount = 1
				 3: Left player has 1 or less cards in discard/deck - no cards
				 4: Left player has 2 or more cards in discard/deck - 2 duplicate money cards
				 5: Left player has 2 or more cards in discard/deck - 2 duplicate victory cards
				 6: Left player has 2 or more cards in discard/deck - 2 duplicate action cards
				 7: Left player has 2 or more cards in discard/deck - money and victory card
				 8: Left player has 2 or more cards in discard/deck - action and great_hall
					   
   	Known Bugs Inserted in Assignment 2:
		1. 	Within the duplicate tribute card check, removed the statement that set 
			the tributeRevealedCards[1] = -1.  This wll cause the player to receive
			double benefits even though they shouldn’t because the cards revealed were the same.

        2.  In the discardCard() statements for the nextPlayer removed the -1 for the deckCount 
        	index.  The value for the tribute cards will always be set outside the bounds of 
        	the nextPlayer’s hand // NOTE:  had to remove for unit testing coverage
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


// global variables to check when conditions 1-8 are met
int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0;

// helper function signatures
int testPlayTribute();
int assert(int expected, int actual);
int countCardType(int card, struct gameState *state, int pileToCheck);

// helper functions for randomizing the game state
int randomizePlayerCount();
void randomizeDeckCards(struct gameState *state, int kingdomCards[10]);
void randomizePiles(struct gameState *state);
void randomizeGameState(struct gameState *state, int kingdomCards[10]);


// helper print functions
void printPlayersCards(int player, struct gameState *state);
void printAllSupplyCounts(struct gameState *state);
void printAllGameStateVariables(struct gameState *state);
int printCardName(int card);


// call randomtestcard3
int main()
{
    srand(time(NULL));
    testPlayTribute();
    return 0;
}


// function to execute the set of conditions for randomtest #3
int testPlayTribute()
{
    int iterations = 0, bonus = 0, returnValue = 0;
    int currentPlayer, nextPlayer, card1, result, t1, t2, card2;

    struct gameState state, preState;
    int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy
            };


    printf("\n\n----- RANDOM TEST #3 - playTribute() - STARTED -----\n\n");

    while(c1 == 0 || c2 == 0 || c3 == 0 || c4 == 0 || c5 == 0 || c6 == 0 || c7 == 0 || c8 == 0) {

    	// randomize the game state
  		randomizeGameState(&state, k);

  		currentPlayer = state.whoseTurn;
        nextPlayer = currentPlayer + 1;

        card1 = -1;

        // provide player1 with a minion card
        state.hand[currentPlayer][0] = tribute;
        state.supplyCount[tribute]--;

   		// CONDITION #1:  Left player has 1 or less cards in discard/deck - deckCount > 0 (action)
    	if (c1 == 0 && state.discardCount[nextPlayer] == 0 && state.deckCount[nextPlayer] == 1) {

    		printf("\nCONDITION #1 met:  Left player has 1 or less cards in discard/deck - deckCount > 0\n");
 
    		card1 = (rand() % 19) + 7;  // range of action cards
    		if (card1 == 10 || card1 == 16)  // avoid garden and great hall
    			card1++;
			
			state.deck[nextPlayer][state.deckCount[nextPlayer]-1] = card1;
    		//t1 = state.deck[nextPlayer][state.deckCount[nextPlayer]-1];

    		// save the game states
        	updateCoins(0, &state, bonus);
        	memcpy(&preState, &state, sizeof(struct gameState));

        	// play the card
        	returnValue = playCard(0, 0, 0, 0, &state);

    		// expected results: +2 actions (-1 of current turn)
    		result = assert(preState.numActions+1, state.numActions);
    		if (result == 0)
    			printf("condition #1 - FAIL: +2 actions: actual %d, expected: %d\n", state.numActions, preState.numActions+1);
    		else
    			printf("condition #1 - PASS: +2 actions: actual %d, expected: %d\n", state.numActions, preState.numActions+1);

        	// update condition met criteria
        	c1 = 1;
    	}

   		// CONDITION #2:  Left player has 1 or less cards in discard/deck - discardCount > 0 (treasure)
    	if (c2 == 0 && state.discardCount[nextPlayer] == 1 && state.deckCount[nextPlayer] == 0) {

    		printf("\nCONDITION #2 met:  Left player has 1 or less cards in discard/deck - discardCount > 0\n");
  
    		card1 = (rand() % 3) + 4;  // range of money cards
			state.deck[nextPlayer][state.deckCount[nextPlayer]-1] = card1;
    		//t1 = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];

    		// save the game states
        	updateCoins(0, &state, bonus);
        	memcpy(&preState, &state, sizeof(struct gameState));

        	// play the card
        	returnValue = playCard(0, 0, 0, 0, &state);

    		// expected results: +2 coins (treasure card)
    		updateCoins(currentPlayer, &preState, 2);
    		updateCoins(currentPlayer, &state, state.coins);

    		result = assert(preState.coins, state.coins);
    		if (result == 0)
    			printf("condition 2.0 - FAIL: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);
    		else
    			printf("condition 2.0 - PASS: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);

        	// update condition met criteria
        	c2 = 1;
    	}

   		// CONDITION #3:  Left player has 1 or less cards in discard/deck - no cards
    	if (c3 == 0 && state.discardCount[nextPlayer] == 0 && state.deckCount[nextPlayer] == 0) {

    		printf("\nCONDITION #3 met:  Left player has 1 or less cards in discard/deck - no cards\n");

    		// save the game states
        	updateCoins(0, &state, bonus);
        	memcpy(&preState, &state, sizeof(struct gameState));

        	// play the card
        	returnValue = playCard(0, 0, 0, 0, &state);

    		// expected results: (failure)
    		result = assert(-1, returnValue);
    		if (result == 0)
    			printf("condition 3.0 - FAIL: (fail flag not returned): actual %d, expected: %d\n", returnValue, -1);
    		else
    			printf("condition 3.0 - PASS: (fail flag returned): actual %d, expected: %d\n", returnValue, -1);
  
        	// update condition met criteria
        	c3 = 1;
    	}

   		// CONDITION #4:  Left player has 2 or more cards in discard/deck - tribute = duplicate money card
    	if (state.deckCount[nextPlayer] >= 2) {

    		card1 = (rand() % 3) + 4;
    		card2 = (rand() % 3) + 4;
		
			state.deck[nextPlayer][state.deckCount[nextPlayer]-1] = card1;
			state.deck[nextPlayer][state.deckCount[nextPlayer]-2] = card2;
    	
    		t1 = state.deck[nextPlayer][state.deckCount[nextPlayer]-1]; 
    		t2 = state.deck[nextPlayer][state.deckCount[nextPlayer]-2];

    		// save the game states
        	updateCoins(0, &state, bonus);
        	memcpy(&preState, &state, sizeof(struct gameState));

        	// play the card
        	returnValue = playCard(0, 0, 0, 0, &state);

    		// expected results: +2 coins (treasure card) - no double counting
    		updateCoins(currentPlayer, &preState, 2);
    		updateCoins(currentPlayer, &state, state.coins);

    		if (c4 == 0 && (t1 == t2)) {

    			printf("\nCONDITION #4 met:  Left player has 2 or more cards in discard/deck - tribute = duplicate money card\n");  
        		
        		result = assert(preState.coins, state.coins);
    			if (result == 0)
    				printf("condition 4 - FAIL: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);
    			else
    				printf("condition 4 - PASS: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);

        		// update condition met criteria
        		c4 = 1;
    		}
    	}

   		// CONDITION #5:  Left player has 2 or more cards in discard/deck - treasure = duplicate victory cards
    	if (state.deckCount[nextPlayer] >= 2) {

    		card1 = (rand() % 3) + 1;
    		card2 = (rand() % 3) + 1;
		
			state.deck[nextPlayer][state.deckCount[nextPlayer]-1] = card1;
			state.deck[nextPlayer][state.deckCount[nextPlayer]-2] = card2;
    	
    		t1 = state.deck[nextPlayer][state.deckCount[nextPlayer]-1]; 
    		t2 = state.deck[nextPlayer][state.deckCount[nextPlayer]-2];

    		// save the game states
        	updateCoins(0, &state, bonus);
        	memcpy(&preState, &state, sizeof(struct gameState));

        	// play the card
        	returnValue = playCard(0, 0, 0, 0, &state);

    		if (c5 == 0 && (t1 == t2)) {

    			printf("\nCONDITION #5 met: Left player has 2 or more cards in discard/deck - tribute = duplicate victory cards\n");  
        		
    			// expected results: +2 cards (-1 for the tribute)  (no double counting)
    			result = assert(preState.handCount[currentPlayer]+1, state.handCount[currentPlayer]);
    			if (result == 0)
    				printf("condition 5 - FAIL: +2 cards: actual %d, expected: %d\n", state.handCount[currentPlayer], preState.handCount[currentPlayer]+1);
    			else
    				printf("condition 5 - PASS: +2 cards: actual %d, expected: %d\n", state.handCount[currentPlayer], preState.handCount[currentPlayer]+1);

        		// update condition met criteria
        		c5 = 1;
    		}
    	}

   		// CONDITION #6:  Left player has 2 or more cards in discard/deck - treasure = duplicate action cards
    	if (state.deckCount[nextPlayer] >= 2) {

    		card1 = (rand() % 19) + 7;
    		card2 = (rand() % 19) + 7;
		
			state.deck[nextPlayer][state.deckCount[nextPlayer]-1] = card1;
			state.deck[nextPlayer][state.deckCount[nextPlayer]-2] = card2;
    	
    		t1 = state.deck[nextPlayer][state.deckCount[nextPlayer]-1]; 
    		t2 = state.deck[nextPlayer][state.deckCount[nextPlayer]-2];

    		// save the game states
        	updateCoins(0, &state, bonus);
        	memcpy(&preState, &state, sizeof(struct gameState));

        	// play the card
        	returnValue = playCard(0, 0, 0, 0, &state);

    		if (c6 == 0 && (t1 == t2) && (card1 != 10 || card1 != 16)) {

    			printf("\nCONDITION #6 met: Left player has 2 or more cards in discard/deck - tribute = duplicate action cards\n");  
        		
    			// expected results: +2 actions (-1 of current turn) (no double counting)
    			result = assert(preState.numActions+1, state.numActions);
    			if (result == 0)
    				printf("condition 6 - FAIL: +2 actions (-1 of current turn) (no double counting): actual %d, expected: %d\n", state.numActions, preState.numActions+1);
    			else
    				printf("condition 6 - PASS: +2 actions (-1 of current turn) (no double counting): actual %d, expected: %d\n", state.numActions, preState.numActions+1);

        		// update condition met criteria
        		c6 = 1;
    		}
    	}

   		// CONDITION #7:  Left player has 2 or more cards in discard/deck - treasure = money and victory
    	if (state.deckCount[nextPlayer] >= 2) {
    	
    		card1 = (rand() % 3) + 4;
    		card2 = (rand() % 3) + 1;
		
			state.deck[nextPlayer][state.deckCount[nextPlayer]-1] = card1;
			state.deck[nextPlayer][state.deckCount[nextPlayer]-2] = card2;
    	
    		t1 = state.deck[nextPlayer][state.deckCount[nextPlayer]-1]; 
    		t2 = state.deck[nextPlayer][state.deckCount[nextPlayer]-2];

    		// save the game states
        	updateCoins(0, &state, bonus);
        	memcpy(&preState, &state, sizeof(struct gameState));

        	// play the card
        	returnValue = playCard(0, 0, 0, 0, &state);

        	// expected results: +2 coins, +2 cards
    		updateCoins(currentPlayer, &preState, 2);
    		updateCoins(currentPlayer, &state, state.coins);

    		if (c7 == 0) {

    			printf("\nCONDITION #7 met: Left player has 2 or more cards in discard/deck - tribute = money and victory\n");  
        	    
        	    // check +2 coins
    			result = assert(preState.coins, state.coins);
    			if (result == 0)
    				printf("condition 7 (part 1) - FAIL: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);
    			else
    				printf("condition 7 (part 1) - PASS: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);

				// check +2 cards
    			result = assert(preState.handCount[currentPlayer]+1, state.handCount[currentPlayer]);
    			if (result == 0)
    				printf("condition 7 (part 2) - FAIL: +2 cards: actual %d, expected: %d\n", state.handCount[currentPlayer], preState.handCount[currentPlayer]+1);
    			else
    				printf("condition 7 (part 2) - PASS: +2 cards: actual %d, expected: %d\n", state.handCount[currentPlayer], preState.handCount[currentPlayer]+1);
	
        		// update condition met criteria
        		c7 = 1;
    		}
    	}

   		// CONDITION #8:  Left player has 2 or more cards in discard/deck - treasure = action and great_hall
    	if (state.deckCount[nextPlayer] >= 2) {
    	
    		card1 = (rand() % 19) + 7;
    		card2 = great_hall;
		
			state.deck[nextPlayer][state.deckCount[nextPlayer]-1] = card1;
			state.deck[nextPlayer][state.deckCount[nextPlayer]-2] = card2;
    	
    		t1 = state.deck[nextPlayer][state.deckCount[nextPlayer]-1]; 
    		t2 = state.deck[nextPlayer][state.deckCount[nextPlayer]-2];

    		// save the game states
        	updateCoins(0, &state, bonus);
        	memcpy(&preState, &state, sizeof(struct gameState));

        	// play the card
        	returnValue = playCard(0, 0, 0, 0, &state);

    		if (c8 == 0 && (card1 != 10 || card1 != 16) ) {

    			printf("\nCONDITION #8 met: Left player has 2 or more cards in discard/deck - tribute = action and great hall\n");  
        		
        		// check +4 cards (-1 for card played)
    			result = assert(preState.handCount[currentPlayer]+3, state.handCount[currentPlayer]);
    			if (result == 0)
    				printf("condition 8 (part 1) - FAIL: +4 cards (-1 of current turn): actual %d, expected: %d\n", state.handCount[currentPlayer], preState.handCount[currentPlayer]+3);
    			else
    				printf("condition 8 (part 1) - PASS: +4 cards (-1 of current turn): actual %d, expected: %d\n", state.handCount[currentPlayer], preState.handCount[currentPlayer]+3);

    			// check +4 actions (-1 of current turn)
    			result = assert(preState.numActions+3, state.numActions);
    			if (result == 0)
    				printf("condition 8 (part 2) - FAIL: +4 actions (-1 of current turn): actual %d, expected: %d\n", state.numActions, preState.numActions+3);
    			else
    				printf("condition 8 (part 2) - PASS: +4 actions (-1 of current turn): actual %d, expected: %d\n", state.numActions, preState.numActions+3);

        		// update condition met criteria
        		c8 = 1;
    		}
    	}

  		iterations++;
    }

    printf("\n----- RANDOM TEST #3 - playTribute() - COMPLETED - (%d iterations) -----\n", iterations);
	
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