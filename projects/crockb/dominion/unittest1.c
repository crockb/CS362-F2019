#include<stdio.h>
#include<stdlib.h>
#include "dominion.h"

// 1.	Omitted a necessary step(s) to “discardCard” when the estate card was found.  
// This will cause the player’s hand to incorrectly retain an estate during gameplay.


// 2.	Decremented the supplyCount of estates after executing the gainCard() function 
// (duplicative reduction of supplyCount).  May cause the game to end too soon by over 
// removing estate cards when referenced in the Baron cards.


int testPlayBaron()
{

	// initialize variables
	// needs - baron, minion, ambassador, tribute, mine.  replaced adventurer, embargo
	int randomSeed = 1;
	struct gameState G;
	int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy
            };

    initializeGame(2, k, randomSeed, &G);

	// print out the results of the hand
	printf("numPlayers: %d\n", state->numPlayers);

/*
	int numPlayers; //number of players
    int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
    int embargoTokens[treasure_map+1];
    int outpostPlayed; // flag indicating if an outpost was played during the turn
    int outpostTurn; // 
    int whoseTurn; // set to the current player's turn
    int phase; // keeps track of the phase number within the game
    int numActions; /* Starts at 1 each turn 
    int coins; /* Use as you see fit! 
    int numBuys; /* Starts at 1 each turn 
    int hand[MAX_PLAYERS][MAX_HAND];  // holds the cards within each player's hand
    int handCount[MAX_PLAYERS]; // holds the number of cards within each player's hand
    int deck[MAX_PLAYERS][MAX_DECK]; // holds the cards within each player's deck
    int deckCount[MAX_PLAYERS]; // holds the number of cards in each player's deck
    int discard[MAX_PLAYERS][MAX_DECK]; // holds the cards within each player's discard pile
    int discardCount[MAX_PLAYERS]; // holds the number of cards in each player's discard pile
    int playedCards[MAX_DECK]; // 
    int playedCardCount;
*/



	// assert the results


	return 0;
}


// call unittest1
int main()
{
    testPlayBaron();
    return 0;
}