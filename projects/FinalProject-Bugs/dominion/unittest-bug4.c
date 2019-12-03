/* unittest-bug4.c
	Author/Date:  Robert Pino   12/1/19
	Description:  Test if isGameOver() loops through all 27 cards when it checks if there are 3 cards with a card count of 0.
	
	Business Requirements for isGameOver():
    1. Checks if there are 0 Province cards in the stack - this is a sign the game is over.
    2. Loops through every card and checks the supply on that card.
      A. For every card it finds, it increases a second counter that keeps track of the number of cards found.
    3. If this second counter is equal or greater than 3, the game is not over.
    
	Conditions for Mine
      1. Supply pile has 1 Province card in it.
        A. G.supplyCount[province] = 1;
      2. Supply pile has 4 cards in it, all of which are treasure_hall (card 27)
        A. G.supplyCount[treasure_map] = 4; 
 		    
 	Expected Unittest Outcomes:
      1. isGameOver() returns 1
        A. This signifies that the game is not over
        B. The game should not be over, because there is still a Province in the supply, as well as other cards with a total greater than or equal to 3. 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include<time.h>


// helper function signatures
int setState();
int runTest(struct gameState *state);

int main()
{

	  setState();
	  return 0;
}

int setState()
{
// set card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

//declare the game state
    struct gameState G;

// initialize a new game
    int gameSeed = 1234;
    initializeGame(2, k, gameSeed, &G); 

// set the supply pile
  G.supplyCount[province] = 1; //neccesary because province cards are required to continue the game
  G.supplyCount[treasure_map] = 4; //this is what we are testing

  printf("\n----- UNIT TEST - Bug#4 - isGameOver() does not check cards 26 and 27.");

  runTest(&G);

  return 0;
}

//begin the actual test
int runTest(struct gameState *state)
{
//The game should not be over yet.
//The supply piles have cards (number 27).
//The hands have cards.
//We will check if the game is over.
  int actual = isGameOver(state);
    if (actual == 0) //game is over, even when it shouldn't be
      {
        printf("Checking cards 26 and 27 - FAIL\n");
        return 1;
      };
    if (actual == 1) //game is not over
      {
        printf("Checking cards 26 and 27 in loop - SUCCESS\n");
        return 0;
      };
	return 0;
}