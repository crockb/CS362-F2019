/* randomtestcard1.c
  Author/Date:  Bryant Crock  11/1/19
  Description:  Test the outcomes of the refactored baron card playBaron();
  Business Requirements for Baron:
     1. +1 Buy
     2. Choice 1:  Discard an Estate for +4 coins.  If no Estate, receive an Estate
     3. Choice 2:  Receive an Estate

  Test Conditions Identified and Expected End States:
    CONDITION #1:  Remove Estate (Has Estate):  -1 hand[estate], -1 hand[baron], 3 handCount, +4 coins, +1 buy, 0 actions, +1 discard[baron], estate supply count unchanged
    CONDITION #2:  Remove Estate (No Estate):   +1 hand[estate], -1 hand[baron], 5 handCount, same coins, +1 buy, 0 actions, +1 discard[baron], -1 supply[estate]
    CONDITION #3:  Gain an Estate (Multiple Estates Available):  +1 hand[estate], -1 hand[baron], 5 handCount, same coins, +1 buy, 0 actions, +1 discard[baron], -1 supply[estate]
    CONDITION #4:  Gain an Estate (1 Estate Available):  +1 hand[estate], -1 hand[baron], 5 handCount, same coins, +1 buy, 0 actions, +1 discard[baron], -1 supply[estate]


    Known Bugs Inserted in Assignment 2:
        1. Omitted a necessary step(s) to “discardCard” when the estate card was found.  
           This will cause the player’s hand to incorrectly retain an estate during gameplay.

        2. Decremented the supplyCount of estates after executing the gainCard() function 
           (duplicative reduction of supplyCount).  May cause the game to end too soon by over 
           removing estate cards when referenced in the Baron cards.

    

    int playBaron(int choice1, struct gameState *state, int handPos)
    Requirements for Random Tester:
       --- randomizeGameState
          --- handPosition of Baron
          --- 
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
int testPlayBaron();

// call randomtestcard1
int main()
{
    srand(time(NULL));
    testPlayBaron();
    return 0;
}

// function to execute the set of conditions for unittest#1
int testPlayBaron()
{
  int n, i;

  for (i = 0; i < 10; i++)
  {
      n = rand() % 10;
      printf("Random number: %d\n", n);

  }


  return 0;
}

