/* unittest2.c
	Author/Date:  Bryant Crock  11/9/19
	Description:  Test the outcomes of the refactored minion card playMinion();
	Business Requirements for Minion:
		 1. +1 Action
		 2. Choice 1:  +2 coins
		 3. Choice 2:  Discard hand, +4 cards, each other player discards their hand and draws 4
	Test Conditions Identified and Expected End States:
		CONDITION #1:  Choice 1 - Add 2 coins:   -1 hand[minion], 4 handCount, +2 coins, 1 action
		CONDITION #2:  Choice 2 - Discard Hand (players 2 & 3 have 5 cards):   -1 hand[minion], +4 discard[] each player, -4 deck[] each player
		CONDITION #2:  Choice 2 - Discard Hand (player 3 does not have 5 cards):   -1 hand[minion], +4 discard[] player 1&2, -4 deck[] player 1&2, no change to player3 deck
   	Known Bugs Inserted in Assignment 2:
		1. Removed the +1 Action of the card at the beginning.
        2. In the draw4 cards set of statements i has been replaced with j'
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


// call unittest2
int main()
{
    testPlayMinion();
    return 0;
}

int testPlayMinion()
{
	printf("Hello friend.\n");

/*
    // print player's cards
    // printPlayersCards(0, &state);
    // print number of each card type:
    printf("preState:\n");
    printf("Number of barons: %d\n", countCardTypeInHand(baron, &preState));
    printf("Number of estates: %d\n", countCardTypeInHand(estate, &preState));
    printf("Number of coppers: %d\n", countCardTypeInHand(copper, &preState));
    // print number of each card type:
    printf("state:\n");
    printf("Number of barons: %d\n", countCardTypeInHand(baron, &state));
    printf("Number of estates: %d\n", countCardTypeInHand(estate, &state));
    printf("Number of coppers: %d\n", countCardTypeInHand(copper, &state));
*/


	return 0;
}