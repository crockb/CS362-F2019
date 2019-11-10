/* unittest4.c
	Author/Date:  Bryant Crock  11/9/19
	Description:  Test the outcomes of the refactored tribute card playTribute();
	Business Requirements for Tribute:
		 1. The player to the left reveals then discards top 2 cards
		 2. For each differently named card:
		 		- Action: +2 actions
		 		- Treasure Card: +2 coins
		 		- Victory Card: +2 cards
	Test Conditions Identified and Expected End States:
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

		CONDITION #1:  Left player has 1 or less cards in discard/deck - deckCount > 0
					   Left player has 1 or less cards in discard/deck - discardCount = 1
					   Left player has 1 or less cards in discard/deck - no cards
					   Left player has 2 or more cards in discard/deck - no deck cards
					   		- has duplicates at the backend
					   		- has a copper, has an estate
					   		- has a copper, has a great_hall
		CONDITION #2:  
					   
		CONDITION #3:  
					   
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
  	int player1 = 0; //, bonus = 0, copperPos = -1, returnValue; // player2 = 0, player3 = 0;
  	int randomSeed = 7890;
  	struct gameState state; //preState;
  	int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               great_hall, tribute, smithy
            };

    //playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // provide player1 with a ambassador card
    state.hand[player1][0] = ambassador;
    state.supplyCount[ambassador]--;

    // confirm setConditions
	setCondition4(&state, great_hall, mine);
	printf("Expect: deckCount = 0, discard = 2\n");
	printPlayersCards(1, &state);

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

/*		
		
		#4 - Left player has 2 or more cards in discard/deck - no deck cards
			- #5 - has duplicates at the backend
			- #6 - has a copper, has an estate
			- #7 - has a copper, has a great_hall
*/

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

    // check the availability of nextplayer cards and set them to the tribute cards

		// if they only have 1 or less cards in their discard/deck
        if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1) {
            if (state->deckCount[nextPlayer] > 0) {
            	// assign the last card in the deck
                tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];

                // put that card in the discard pile
                discardCard(state->deckCount[nextPlayer]-1, nextPlayer, state, 0);
                state->deckCount[nextPlayer]--;
            }

            else if (state->discardCount[nextPlayer] > 0) {
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
                for (i = 0; i < state->discardCount[nextPlayer]; i++) {
                    state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
                    state->deckCount[nextPlayer]++;
                    state->discard[nextPlayer][i] = -1;
                    state->discardCount[nextPlayer]--;
                }

                shuffle(nextPlayer,state);//Shuffle the deck
            }
            tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            discardCard(state->deckCount[nextPlayer], nextPlayer, state, 0);

            tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            discardCard(state->deckCount[nextPlayer], nextPlayer, state, 0);
        }

        if (tributeRevealedCards[0] == tributeRevealedCards[1]) { //If we have a duplicate card, just drop one
            state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
            state->playedCardCount++;
        }

        for (i = 0; i < 2; i ++) {
            if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold) { //Treasure cards
                state->coins += 2;
            }

            else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall) { //Victory Card Found
                drawCard(currentPlayer, state);
                drawCard(currentPlayer, state);

                // great hall receives bonus from Action as well
                if (tributeRevealedCards[i] == great_hall) {
                    state->numActions = state->numActions + 2;
                }
            }

            else if (tributeRevealedCards[i] == -1)
            {
                // do nothing - invalid card
            }

            else { //Action Card
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