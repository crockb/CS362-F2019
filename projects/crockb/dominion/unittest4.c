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
int testTribute();
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


int main()
{
	testPlayTribute();
	return 0;
}


int testPlayTribute()
{
	printf("Hello friend.\n");
	return 0;
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