/* unittest4.c
	Author/Date:  Bryant Crock  11/9/19
	Description:  Test the outcomes of the refactored tribute card playTribute();
	Business Requirements for Tribute:
		 1. The player to the left reveals then discards top 2 cards
		 2. For each differently named card:
		 		- Action: +2 actions
		 		- Treasure Card: +2 coins
		 		- Victory Card: +2 cards
	Branches:
					   LEFT PLAYER HAS
						 only have 1 or less cards in their discard/deck
							if (state->deckCount[nextPlayer] > 0)
							else if (state->discardCount[nextPlayer] > 0)
							else (no cards to reveal)
						 have more than 1 card in discard/deck
						 	if nothing in deck (move from discard, reshuffle deck)
							else pull from the deck
						 check for duplicates
						 has action
						 has treasure (may need to slip in a great_hall)
						 has victory

		CONDITIONS:  1: Left player has 1 or less cards in discard/deck - deckCount > 0 (action)
					 2: Left player has 1 or less cards in discard/deck - discardCount = 1 (treasure)
					 3: Left player has 1 or less cards in discard/deck - no cards (failure)
					 4: Left player has 2 or more cards in discard/deck - no deck cards (shuffle)
					 	4.1:   has duplicates at the backend
					   		4.1.1: 2 coppers
					   		4.1.2: 2 estates
					   		4.1.3: 2 mines
					   	4.2:   has a copper, has an estate
					   	4.3:   has a copper, has a great_hall 
					   
   	Known Bugs Inserted in Assignment 2:
		1. 	Within the duplicate tribute card check, removed the statement that set 
			the tributeRevealedCards[1] = -1.  This wll cause the player to receive
			double benefits even though they shouldn’t because the cards revealed were the same.

        2.  In the discardCard() statements for the nextPlayer removed the -1 for the deckCount 
        	index.  The value for the tribute cards will always be set outside the bounds of 
        	the nextPlayer’s hand
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
int hasGameCard(int card, struct gameState *state, int pileToCheck);
int countCardTypeInHand(int card, struct gameState *state);
int provideEstateCardFromDeck(int player, struct gameState *state);
int removeEstateCardFromHand(int player, struct gameState *state);

// helper function to set conditions before playing card
void setCondition1(struct gameState *state, int card);     			// #1 - Left player has 1 or less cards in discard/deck - deckCount = 1, discard = 0
void setCondition2(struct gameState *state, int card);     			// #2 - Left player has 1 or less cards in discard/deck - discardCount = 1
void setCondition3(struct gameState *state);               			// #3 - Left player has 1 or less cards in discard/deck - no cards
void setCondition4(struct gameState *state, int card1, int card2);  // #4 - Left player has 2 or more cards in discard/deck - no deck cards

// helper print functions
void printTestCondition1Results(struct gameState *state, struct gameState *preState);
void printTestCondition2to4Results(struct gameState *state, struct gameState *preState);
void printPlayersCards(int player, struct gameState *state);
void printAllSupplyCounts(struct gameState *state);
void printAllGameStateVariables(struct gameState *state);


int main()
{
	testPlayTribute();
	return 0;
}


int testPlayTribute()
{
  	// initialize variables
  	int player1 = 0, result = -1, bonus = 0; //copperPos = -1, returnValue; // player2 = 0, player3 = 0;
  	int randomSeed = 7890;
  	struct gameState state, preState;
  	int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               great_hall, tribute, smithy
            };

    //playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)

    // -------  condition #4 - 1 or less cards in discard/deck - deckCount > 0 ------
    printf("----- UNIT TEST #4 - CONDITION #1: 1 or less cards in discard/deck - deckCount > 0\n");

/*
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

    // play the ambassador card
    playCard(0, 0, 0, 0, &state);

    // expected results: +2 actions (-1 of current turn)
    result = assert(preState.numActions+1, state.numActions);
    if (result == 0)
    	printf("condition 1.0 - FAIL: +2 actions: actual %d, expected: %d\n", state.numActions, preState.numActions+1);
    else
    	printf("condition 1.0 - PASS: +2 actions: actual %d, expected: %d\n", state.numActions, preState.numActions+1);

*/

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

    // play the ambassador card
    playCard(0, 0, 0, 0, &state);

    // expected results: +2 coins (treasure card)
    updateCoins(player1, &preState, 2);
    updateCoins(player1, &state, state.coins);

    result = assert(preState.coins, state.coins);
    if (result == 0)
    	printf("condition 2.0 - FAIL: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);
    else
    	printf("condition 2.0 - PASS: +2 coins: actual %d, expected: %d\n", state.coins, preState.coins);

    printPlayersCards(0, &preState);
    printPlayersCards(0, &state);




/*

	// condition 3.0 - 1 or less cards in discard/deck - no cards (failure)
    setCondition3(&state);

	// condition 4.1.1 - 2 or more cards in discard/deck - no deck cards (shuffle) - duplicates - 2 coppers
	setCondition4(&state, copper, copper);      

	// condition 4.1.2 - 2 or more cards in discard/deck - no deck cards (shuffle) - duplicates - 2 estates
	setCondition4(&state, estate, estate);

	// condition 4.1.3 - 2 or more cards in discard/deck - no deck cards (shuffle) - duplicates - 2 mines
	setCondition4(&state, mine, mine);

	// condition 4.2.0 -  or more cards in discard/deck - no deck cards (shuffle) - 1 copper, 1 estate
	setCondition4(&state, copper, estate);      

	// condition 4.3.0 -  or more cards in discard/deck - no deck cards (shuffle) - 1 copper, 1 great_hall
    setCondition4(&state, copper, great_hall);      // condition 4.1.1  	     

*/
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


/*

int playTribute(struct gameState *state, int handPos)
{
    int i;
    int currentPlayer = whoseTurn(state);
    int nextPlayer = currentPlayer + 1;
    int tributeRevealedCards[2] = {-1, -1};

    // check to see if the next player is player 0
    if (nextPlayer > (state->numPlayers - 1)) {
        nextPlayer = 0;
    }

    // discard tribute card
    discardCard(handPos, currentPlayer, state, 0);

    printf("Did this fire #1?\n");

    // check the availability of nextplayer cards and set them to the tribute cards
        if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1) {
            if (state->deckCount[nextPlayer] > 0) {
                tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
                discardCard(state->deckCount[nextPlayer]-1, nextPlayer, state, 0);
                state->deckCount[nextPlayer]--;
                printf("Did this fire #2?\n");
            }
            else if (state->discardCount[nextPlayer] > 0) {
                printf("Did this fire #3?\n");
                tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer]-1];
            }
            else {
                //No Card to Reveal
                if (DEBUG) {
                    printf("No cards to reveal\n");
                }
            }
        }

        else {
            if (state->deckCount[nextPlayer] == 0) {
                printf("Did this fire #4?\n");
                for (i = 0; i < state->discardCount[nextPlayer]; i++) {
                    state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
                    state->deckCount[nextPlayer]++;
                    state->discard[nextPlayer][i] = -1;
                    state->discardCount[nextPlayer]--;
                }

                shuffle(nextPlayer,state);//Shuffle the deck
            }
            printf("Did this fire #5?\n");
            tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            discardCard(state->deckCount[nextPlayer], nextPlayer, state, 0);

            tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            discardCard(state->deckCount[nextPlayer], nextPlayer, state, 0);
        }

        if (tributeRevealedCards[0] == tributeRevealedCards[1]) { //If we have a duplicate card, just drop one
            state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
            state->playedCardCount++;
            printf("Did this fire #6?\n");
        }

        for (i = 0; i < 2; i ++) {
            if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) { //Treasure cards
                state->coins += 2;
                printf("Did this fire #7?\n");
            }

            else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) { //Victory Card Found
                drawCard(currentPlayer, state);
                drawCard(currentPlayer, state);
                printf("Did this fire #8?\n");
                // great hall receives bonus from Action as well
                if (tributeRevealedCards[i] == great_hall) {
                    state->numActions = state->numActions + 2;
                    printf("Did this fire #9?\n");
                }
            }

            else if (tributeRevealedCards[i] == -1)
            {
                // do nothing - invalid card
                printf("Did this fire #10?\n");
            }

            else { //Action Card
                printf("Did this fire #11?\n");
                state->numActions = state->numActions + 2;
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