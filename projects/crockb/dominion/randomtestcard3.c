/* randomtestcard3.c
	Author/Date:  Bryant Crock  11/16/19
	Description:  Test the outcomes of the refactored tribute card playTribute();
	Business Requirements for Tribute:
		 1. The player to the left reveals then discards top 2 deck cards
		 2. For each differently named card:
		 		- Action: +2 actions
		 		- Treasure Card: +2 coins
		 		- Victory Card: +2 cards

	CONDITIONS:  1: Left player has 1 or less cards in discard/deck - deckCount > 0 (action)
				 2: Left player has 1 or less cards in discard/deck - discardCount = 1 (treasure)
				 3: Left player has 1 or less cards in discard/deck - no cards (failure)
				 4: Left player has 2 or more cards in discard/deck - no deck cards (shuffle)
				   4.1:   has duplicates at the backend
				     4.1.1: 2 coppers
				     4.1.2: 2 estates
				     4.1.3: 2 mines
				   4.2:   has a copper, has an estate
				   4.3:   has a mine, has a great_hall 
					   
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


// helper function signatures
int testPlayTribute();


// call randomtestcard2
int main()
{
    srand(time(NULL));
    testPlayTribute();
    return 0;
}


// function to execute the set of conditions for unittest#1
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
        if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1) {
            if (state->deckCount[nextPlayer] > 0) {
                tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
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