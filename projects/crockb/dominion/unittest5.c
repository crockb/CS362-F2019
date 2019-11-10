/* unittest5.c
	Author/Date:  Bryant Crock  11/9/19
	Description:  Test the outcomes of the refactored mine card playMine();
	Business Requirements for Mine:
		 1. Trash a Treasure Card from Hand
		 2. Gain a Treasure Card Costing Up to +3 More

	CONDITIONS
 		 1: Invalid Trash Card (choice 1)
 		 	values:  choice1[1] = estate ($2), choice2 = silver ($3)
 		 	expected outcome(s):  return -1

 		 2: Invalid Purchase Card (choice 2) is out of bounds
 		 	values: choice[1] = copper ($0), choice2 = 100
 		 	expected outcome(s):  return -1

 		 3: Valid Trash Card, Purchase Card (Should Be Too) Expensive
 		 	values: choice[1] = copper ($0), choice2 = gold ($6)
 		    expected outcome(s):  return -1

 		 4: Valid Trash Card, Purchase Card Is In Range
 		    values: choice[1] = copper ($0), choice2 = silver ($3)
 		    expected outcome(s):  +1 silver in hand, -1 copper from hand
					   
   	Known Bugs Inserted in Assignment 2:
		1.	In the discardCard statement at the bottom of the function replaced i with j.  
			Instead of referencing the correct index position it will irrelevantly reference 
			a card index within the game, causing the wrong card to be removed or step outside 
			the boundaries of the player’s hand.

        2.  In the gainCard statement replaced choice2 with choice 1.  Instead of receiving 
        	the card they chose to add they will receive a copy of the card they chose to trash. 

     Card Options
     		choice 1 - index of card to be trashed
        	choice 2 - card to be purchased
*/


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


// helper function signatures
int testPlayMine();
int assert(int expected, int actual);
int countCardTypeInHand(int card, struct gameState *state);
void printPlayersCards(int player, struct gameState *state);


// helper function to set conditions before playing card
void setCondition1(struct gameState *state);     			// #1 - Left player has 1 or less cards in discard/deck - deckCount = 1, discard = 0
void setCondition2(struct gameState *state);     			// #2 - Left player has 1 or less cards in discard/deck - discardCount = 1
void setCondition3(struct gameState *state);               			// #3 - Left player has 1 or less cards in discard/deck - no cards
void setCondition4(struct gameState *state);  // #4 - Left player has 2 or more cards in discard/deck - no deck cards



int main()
{
	testPlayMine();
	return 0;
}


int testPlayMine()
{
  	// initialize variables
  	int player1 = 0, result = -1, bonus = 0, returnValue = -10;
  	int randomSeed = 7890;
  	struct gameState state, preState;
  	int k[10] = {baron, gardens, ambassador, village, minion, mine, cutpurse,
               great_hall, tribute, smithy
            };


    // -------  beginning of unit test conditions ------
    printf("----- UNIT TEST #5 ----- 4 conditions tested ------ \n");

    // ----- CONDITION 1 - Invalid Trash Card (choice 1) ---------

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // condition 1 -  Invalid Trash Card (choice 1) -    
    setCondition1(&state);

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // values:  choice1[1] = estate ($2), choice2 = silver ($3) 
    returnValue = playCard(0, state.hand[player1][1], silver, 0, &state); 

    // expected outcome(s):  return -1
    result = assert(-1, returnValue);
    if (result == 0)
    	printf("condition 1 - FAIL: Invalid Trash Card (-1 Error): actual %d, expected: %d\n", returnValue, -1);
    else
    	printf("condition 1 - PASS: Invalid Trash Card (-1 Error): actual %d, expected: %d\n", returnValue, -1);


    // ----- CONDITION 2 - Invalid Purchase Card (choice 2) is out of bounds ----

    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // condition 2 -  Invalid Purchase Card (choice 2) is out of bounds ----    
    setCondition2(&state);

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // values: choice[1] = copper ($0), choice2 = 100
    returnValue = playCard(0, state.hand[player1][1], 100, 0, &state); 

    // expected outcome(s):  return -1
    result = assert(-1, returnValue);
    if (result == 0)
    	printf("condition 2 - FAIL: Invalid Purchase Card (-1 Error): actual %d, expected: %d\n", returnValue, -1);
    else
    	printf("condition 2 - PASS: Invalid Purchase Card (-1 Error): actual %d, expected: %d\n", returnValue, -1);



    // ----- CONDITION 3 - Valid Trash Card, Purchase Card (Should Be Too) Expensive ----
    
    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // condition 3 -  Valid Trash Card, Purchase Card (Should Be Too) Expensive ----    
    setCondition3(&state);

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)

    // values: choice[1] = copper ($0), choice2 = gold ($6)
    returnValue = playCard(0, state.hand[player1][1], gold, 0, &state); 

    // expected outcome(s):  return -1 (too expensive)
    result = assert(-1, returnValue);
    if (result == 0)
    	printf("condition 3 - FAIL: Purchase Card Too Expensive (-1 Error): actual %d, expected: %d\n", returnValue, -1);
    else
    	printf("condition 3 - PASS: Purchase Card Too Expensive (-1 Error): actual %d, expected: %d\n", returnValue, -1);


    // ----- CONDITION 4 - Valid Trash Card, Purchase Card Is In Range ----
    
    // initialize the game
    initializeGame(2, k, randomSeed, &state);

    // condition 4 -  Valid Trash Card, Purchase Card Is In Range ----    
    setCondition4(&state);

    // copy the initial pre-conditions
    updateCoins(player1, &state, bonus);
    memcpy(&preState, &state, sizeof(struct gameState));

    // playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)

    // values: choice[1] = copper ($0), choice2 = silver ($3)
    playCard(0, state.hand[player1][1], silver, 0, &state); 

    // int countCardTypeInHand(int card, struct gameState *state);

    // expected outcome(s):  +1 silver in hand
    result = assert(countCardTypeInHand(silver, &preState)+1, countCardTypeInHand(silver, &state));
    if (result == 0)
    	printf("condition 4 (part 1) - FAIL: +1 silver in hand: actual %d, expected: %d\n", countCardTypeInHand(silver, &state), countCardTypeInHand(silver, &preState)+1);
    else
    	printf("condition 4 (part 1) - PASS: +1 silver in hand: actual %d, expected: %d\n", countCardTypeInHand(silver, &state), countCardTypeInHand(silver, &preState)+1);

    // expected outcome(s): -1 copper from hand
    result = assert(countCardTypeInHand(copper, &preState)-1, countCardTypeInHand(copper, &state));
    if (result == 0)
    	printf("condition 4 (part 2) - FAIL: -1 copper in hand: actual %d, expected: %d\n", countCardTypeInHand(copper, &state), countCardTypeInHand(copper, &preState)-1);
    else
    	printf("condition 4 (part 2) - PASS: -1 copper in hand: actual %d, expected: %d\n", countCardTypeInHand(copper, &state), countCardTypeInHand(copper, &preState)-1);

	return 0;
}



int assert(int expected, int actual)
{
  if (expected == actual)
    return 1;
  else
    return 0;
}

/*
	CONDITION #1
 		 1: Invalid Trash Card (choice 1)
 		 	values:  choice1[1] = estate ($2), choice2 = silver ($3)
 		 	expected outcome(s):  return -1
*/

void setCondition1(struct gameState *state)
{
	int player1 = 0;

    // provide player1 with a mine card
    state->hand[player1][0] = mine;
    state->supplyCount[mine]--;
    state->hand[player1][1] = estate;   // invalid card to trash

}


/*
	CONDITION #2
 		 2: Invalid Purchase Card (choice 2) is out of bounds
 		 	values: choice[1] = copper ($0), choice2 = 100
 		 	expected outcome(s):  return -1
*/
void setCondition2(struct gameState *state)
{
	int player1 = 0;

    // provide player1 with a mine card
    state->hand[player1][0] = mine;
    state->supplyCount[mine]--;
    state->hand[player1][1] = copper;   // valid choice
}


/*
	CONDITION #3
 		 3: Valid Trash Card, Purchase Card (Should Be Too) Expensive
 		 	values: choice[1] = copper ($0), choice2 = gold ($6)
 		    expected outcome(s):  return -1
*/
void setCondition3(struct gameState *state)
{
	int player1 = 0;

    // provide player1 with a mine card
    state->hand[player1][0] = mine;
    state->supplyCount[mine]--;
    state->hand[player1][1] = copper;   // valid card to trash
}

/*
	CONDITION #4
 		 4: Valid Trash Card, Purchase Card Is In Range
 		    values: choice[1] = copper ($0), choice2 = silver ($3)
 		    expected outcome(s):  gain silver in hand, trash copper from hand
*/
void setCondition4(struct gameState *state)
{
	int player1 = 0;

    // provide player1 with a mine card
    state->hand[player1][0] = mine;
    state->supplyCount[mine]--;
    state->hand[player1][1] = copper;   // valid card to trash
}


int countCardTypeInHand(int card, struct gameState *state)
{
  int i;
  int count = 0;
  int player = state->whoseTurn;
  for (i = 0; i < state->handCount[player]; i++) {
    if (state->hand[player][i] == card)
      count++;
  }
  return count;
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


/*

CONDITIONS
 1 - Invalid Trash Card (choice 1) -- return -1
 2 - Invalid Purchase Card (choice 2) is out of bounds - return -1
 3 - Valid Trash Card, Purchase Card Too Expensive
 4 - Valid Trash Card, Purchase Card Right (But Triggers Error)
 5 - Valid Trash Card), Purchase Works





int playMine(int choice1, int choice2, struct gameState *state, int handPos)
{

        // choice 1 - card to be trashed
        // choice 2 - card to be purchased
        int i;
        int currentPlayer = whoseTurn(state);
        int j = state->hand[currentPlayer][choice1];  //store card we will trash

        // discard the played card
        discardCard(handPos, currentPlayer, state, 0);

        if (j < copper || j > gold)
        {
            return -1;
        }

        if (choice2 > treasure_map || choice2 < curse)
        {
            return -1;
        }

        if ( (getCost(j + 3)) < getCost(choice2) )
        {
            return -1;
        }

        // int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)

        gainCard(choice1, state, 2, currentPlayer);

        //discard trashed card
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == j)
            {
                discardCard(j, currentPlayer, state, 0);
                break;
            }
        }

        return 0;

}


int getCost(int cardNumber)
{
    switch( cardNumber )
    {
    case curse:
        return 0;
    case estate:
        return 2;
    case duchy:
        return 5;
    case province:
        return 8;
    case copper:
        return 0;
    case silver:
        return 3;
    case gold:
        return 6;
    case adventurer:
        return 6;
    case council_room:
        return 5;
    case feast:
        return 4;
    case gardens:
        return 4;
    case mine:
        return 5;
    case remodel:
        return 4;
    case smithy:
        return 4;
    case village:
        return 3;
    case baron:
        return 4;
    case great_hall:
        return 3;
    case minion:
        return 5;
    case steward:
        return 3;
    case tribute:
        return 5;
    case ambassador:
        return 3;
    case cutpurse:
        return 4;
    case embargo:
        return 2;
    case outpost:
        return 5;
    case salvager:
        return 4;
    case sea_hag:
        return 4;
    case treasure_map:
        return 4;
    }

    return -1;
}


*/