/* randomtestcard2.c
	Author/Date:  Bryant Crock  11/16/19
	Description:  Test the outcomes of the refactored minion card playMinion();
	Business Requirements for Minion:
		 1. +1 Action
		 2. Choice 1:  +2 coins
		 3. Choice 2:  Discard hand, +4 cards, each other player discards their hand and draws 4
	Test Conditions Identified and Expected End States:
		CONDITION #1:  Choice 1 - Add 2 coins:   -1 hand[minion], +2 coins, 1 action
		CONDITION #2:  Choice 2 - Discard Hand (players 2 & 3 have 5 cards):   -1 hand[minion], +4 discard[] each player, -4 deck[] each player, 4 cards in hand[] each player
		CONDITION #3:  Choice 2 - Discard Hand (player 3 does not have 5 cards):   	-1 hand[minion], +4 discard[] p1 &p2 and 0 discard p3, -4 deck[] pl & p2, no change to p3, p3 should have 3 cards
	
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




// call randomtestcard2
int main()
{
    srand(time(NULL));
    testPlayBaron();
    return 0;
}


// function to execute the set of conditions for unittest#1
int testPlayBaron()
{
	printf("Hello world\n");
	return 0;
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