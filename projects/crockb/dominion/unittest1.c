/* unittest1.c
   Author/Date:  Bryant Crock  11/1/19
   Description:  Test the outcomes of the refactored baron card playBaron(choice1, state, handPos);
   Business Requirements for Baron:
		 1. +1 Buy
		 2. Choice 1:  Discard an Estate for +4 coins.  If no Estate, receive an Estate
		 3. Choice 2:  Receive an Estate

Test #1:  Remove Estate (Has Estate):   -1 hand[estate], -1 hand[baron], 3 handCount, +4 coins, +1 buy, 0 actions, +1 discard[baron], 9 total cards, 0 whosTurn, 0 phase
Test #2:  Remove Estate (No Estate):   +1 hand[estate], -1 hand[baron], 5 handCount, same coins, +1 buy, 0 actions, +1 discard[baron], 11 total cards, -1 supply[estate], 0 whoseTurn, 0 phase
Test #3:  Gain an Estate (Estates Available):  +1 hand[estate], -1 hand[baron], 5 handCount, same coins, +1 buy, 0 actions, +1 discard[baron], 11 total cards, -1 supply[estate], 0 whoseTurn, 0 phase
Test #4:  Gain an Estate (No Estates Available):  +1 hand[estate], -1 hand[baron], 5 handCount, same coins, +1 buy, 0 actions, +1 discard[baron], 11 total cards, -1 supply[estate], 0 whoseTurn, 0 phase


   Known Bugs Inserted in Assignment 2:
		 1. Omitted a necessary step(s) to “discardCard” when the estate card was found.  
            This will cause the player’s hand to incorrectly retain an estate during gameplay.

         2. Decremented the supplyCount of estates after executing the gainCard() function 
            (duplicative reduction of supplyCount).  May cause the game to end too soon by over 
            removing estate cards when referenced in the Baron cards.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


// helper function signatures
int hasGameCardInHand(int card, struct gameState *state);
int hasGameCardInDeck(int card, struct gameState *state);
int provideEstateCardFromDeck(int player, struct gameState *state);
void printPlayersCards(int player, struct gameState *state);
void printAllGameStateVariables(struct gameState *state);

int testPlayBaron()
{

	// initialize variables
	//int i, j;
	int player1 = 0;
	int randomSeed = 1234;
	struct gameState state;
	int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy
            };

    initializeGame(2, k, randomSeed, &state);

    //printAllGameStateVariables(&state);

    // -------  test #1 - choice1 (player1 has an estate) ------
    printf("TEST 1: choice1 to discard estate - player1 has an estate.\n");

    // expected results: -1 hand[estate], -1 hand[baron], 3 handCount, +4 coins, +1 buy, 0 actions, +1 discard[baron], 9 total cards, 0 whosTurn, 0 phase

    // provide player1 with a baron card
    state.hand[player1][0] = baron;
    state.supplyCount[baron]--;

    // print player's cards
    printPlayersCards(0, &state);

    // confirm player has an estate card in hand


    // print the gamestate
    //printAllGameStateVariables(&state);

/*
    if (hasGameCardInHand(baron, &state) >= 0) {
    	printf("Baron Card Found\n");
    }
    else {
    	printf("Baron Card Not Found\n");
    }

*/

    // set the preconditions
//-1 hand[estate], -1 hand[baron], 3 handCount, +4 coins, +1 buy, 0 actions, +1 discard[baron], 9 total cards, 0 whosTurn, 0 phase

	return 0;
}


// call unittest1
int main()
{
    testPlayBaron();
    return 0;
}



// helper functions for unittest1

int hasGameCardInHand(int card, struct gameState *state)
{
	int i;
	int player = state->whoseTurn;

	for (i = 0; i < state->handCount[player]; i++) {
		if (state->hand[player][i] == card) {
			// card found
			return i;
		}
	}

    // card not found
    return -1;
}

int hasGameCardInDeck(int card, struct gameState *state)
{
	int i;
	int player = state->whoseTurn;

	for (i = 0; i < state->deckCount[player]; i++) {
		if (state->deck[player][i] == card) {
			// card found
			return i;
		}
	}

    // card not found
    return -1;
}


// provide an estate card
int provideEstateCardFromDeck(int player, struct gameState *state)
{
    if (hasGameCardInHand(estate, state) < 0) {
    	int tempCard;
    	int estatePos;
    	// provide an estate card from the deck
    	if (hasGameCardInDeck(estate, state) < 0) {
    		printf("error: no estate card in deck\n");
    		return -1;
    	}
    	else
    	{
    		estatePos = hasGameCardInDeck(estate, &state);
    		tempCard = state->hand[player][1];
    		state->hand[player][1] = state->deck[player][estatePos];
    		state->deck[player][estatePos] = tempCard;
    	}
    }

    return 0;
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

//set number of Curse cards
    if (numPlayers == 2)
    {
        state->supplyCount[curse] = 10;
    }
    else if (numPlayers == 3)
    {
        state->supplyCount[curse] = 20;
    }
    else
    {
        state->supplyCount[curse] = 30;
    }

    //set number of Victory cards
    if (numPlayers == 2)
    {
        state->supplyCount[estate] = 8;
        state->supplyCount[duchy] = 8;
        state->supplyCount[province] = 8;
    }
    else
    {
        state->supplyCount[estate] = 12;
        state->supplyCount[duchy] = 12;
        state->supplyCount[province] = 12;
    }

    //set number of Treasure cards
    state->supplyCount[copper] = 60 - (7 * numPlayers);
    state->supplyCount[silver] = 40;
    state->supplyCount[gold] = 30;


*/





/* assignment #2 - a function to play the baron card in the game 
int playBaron(int choice1, int choice2, struct gameState *state, int handPos)
{

    int currentPlayer = whoseTurn(state);
    discardCard(handPos, currentPlayer, state, 0);

    state->numBuys++;//Increase buys by 1!

        if (choice1 > 0) { //Boolean true or going to discard an estate
            int p = 0;//Iterator for hand!
            int card_not_discarded = 1;//Flag for discard set!
            while(card_not_discarded) {
                if (state->hand[currentPlayer][p] == estate) { //Found an estate card!
                    state->coins += 4;//Add 4 coins to the amount of coins
                    card_not_discarded = 0;//Exit the loop
                }
                else if (p > state->handCount[currentPlayer]) {
                    if(DEBUG) {
                        printf("No estate cards in your hand, invalid choice\n");
                        printf("Must gain an estate if there are any\n");
                    }
                    if (supplyCount(estate, state) > 0) {
                        gainCard(estate, state, 0, currentPlayer);
                        state->supplyCount[estate]--;

                        if (supplyCount(estate, state) == 0) {
                            isGameOver(state);
                        }
                    }
                    card_not_discarded = 0;//Exit the loop
                }

                else {
                    p++;//Next card
                }
            } 
        } 

        // else - player did not elect to discard an estate
        else {
            if (supplyCount(estate, state) > 0) {
                gainCard(estate, state, 0, currentPlayer);//Gain an estate
                state->supplyCount[estate]--;

                if (supplyCount(estate, state) == 0) {
                    isGameOver(state);
                }
            }
        }

        return 0;
}
*/