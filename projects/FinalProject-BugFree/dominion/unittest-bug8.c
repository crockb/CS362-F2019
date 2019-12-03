/* unittest-bug8.c
	Author/Date:  Robert Pino     12/1/19
	Description:  Test whether the Baron, Minion, and Tribute cards correctly update their bonus coins. 
	
	Business Requirements for the cards:
		 1. player1's coins are set to 0.
     2. Minion card is played.
        A. Minion card is the easiest to implement in the test.
        B. Also, the bug we are testing for is the exact same code in all three cards, so if the bug can be isolated in one card, we can be sure it is the same bug in the others. 
        C. Minion card SHOULD grant player1 2 bonus coins.
     2. We test whether player1's coins are equal to 2.
 		    
 	Expected Unittest Outcomes:
 			player1's coins: 2
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
int runTest(struct gameState *state, struct gameState *preState);
int newInitialize(int numPlayers, int kingdomCards[10], int randomSeed,struct gameState *state);

int main()
{

	  setState();
	  return 0;
}

int setState()
{
// set card array - all Minion cards so they are the only card played
  int k[10] = { minion, minion, minion, minion, minion, minion, minion, tribute, minion, minion };
  int bonus = 0;
//declare the game state
  struct gameState G, preState;

// initialize a new game
  int gameSeed = 1234;

  //(this is a new, shortened function that removes any code that might grant coins)
  initializeGame(2, k, gameSeed, &G);
  updateCoins(0,&G,bonus);
  memcpy(&preState, &G, sizeof(struct gameState));

  printf("\n----- UNIT TEST - Bug#8 - The number of bonus coins from actions does not appear to be recorded correctly in cardEffect. ");

//player1 plays a card (guaranteed to be a Minion) with choice 1 (+2 coin)
  //int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
  playCard(0, 1, 1, 1, &G);

//run the test
  runTest(&G, &preState);
  return 0;
}



//begin the actual test
int runTest(struct gameState *state, struct gameState *preState)
{
//compare resulting coin values to expected coin values
  int actual = state->coins;
  int expected = preState->coins + 2;
    if (actual != expected) //Minion card did not update coins
      {
        printf("\nCoins FAILED to update: actual = %d, expected = %d\n", actual, expected);
        return 1;
      };
    if (actual == expected) //Minion card updated coins
      {
        printf("\nCoins SUCCESSFULLY: actual = %d, expected = %d\n", actual, expected);
        return 0;
      };
	return 0;
}