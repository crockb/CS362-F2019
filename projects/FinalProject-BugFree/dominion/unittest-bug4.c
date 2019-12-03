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
void printAllSupplyCounts(struct gameState *state);


int main()
{

	  setState();
	  return 0;
}

int setState()
{
// set card array
    int k[27] = { curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast,
    gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute,
    ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map };

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
  printAllSupplyCounts(&G);

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


void printAllSupplyCounts(struct gameState *state)
{
  printf("supplyCount (curse): %d\n", state->supplyCount[curse]);
  printf("supplyCount (estate): %d\n", state->supplyCount[estate]);
  printf("supplyCount (duchy): %d\n", state->supplyCount[duchy]);
  printf("supplyCount (province): %d\n", state->supplyCount[province]);
  printf("supplyCount (copper): %d\n", state->supplyCount[copper]);
  printf("supplyCount (silver): %d\n", state->supplyCount[silver]);
  printf("supplyCount (gold): %d\n", state->supplyCount[gold]);
  printf("supplyCount (adventurer): %d\n", state->supplyCount[adventurer]);
  printf("supplyCount (council_room): %d\n", state->supplyCount[council_room]);
  printf("supplyCount (feast): %d\n", state->supplyCount[feast]);
  printf("supplyCount (gardens): %d\n", state->supplyCount[gardens]);
  printf("supplyCount (mine): %d\n", state->supplyCount[mine]);
  printf("supplyCount (remodel): %d\n", state->supplyCount[remodel]);
  printf("supplyCount (smithy): %d\n", state->supplyCount[smithy]);
  printf("supplyCount (village): %d\n", state->supplyCount[village]);
  printf("supplyCount (baron): %d\n", state->supplyCount[baron]);
  printf("supplyCount (great_hall): %d\n", state->supplyCount[great_hall]);
  printf("supplyCount (minion): %d\n", state->supplyCount[minion]);
  printf("supplyCount (steward): %d\n", state->supplyCount[steward]);
  printf("supplyCount (tribute): %d\n", state->supplyCount[tribute]);
  printf("supplyCount (ambassador): %d\n", state->supplyCount[ambassador]);
  printf("supplyCount (cutpurse): %d\n", state->supplyCount[cutpurse]);
  printf("supplyCount (embargo): %d\n", state->supplyCount[embargo]);
  printf("supplyCount (outpost): %d\n", state->supplyCount[outpost]);
  printf("supplyCount (salvager): %d\n", state->supplyCount[salvager]);
  printf("supplyCount (sea_hag): %d\n", state->supplyCount[sea_hag]);
  printf("supplyCount (sea_hag): %d\n", state->supplyCount[treasure_map]);
}