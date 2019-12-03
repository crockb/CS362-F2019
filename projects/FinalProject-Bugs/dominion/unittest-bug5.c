#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"



 int newAssert(int condition, int lineNumber){
    if(condition == 0){
        printf("Fail at line %d\n\n", lineNumber);
    }
    return 0;
 }



int main(){
    // set your card array
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
    int p = 0;
    int seed = 1000;
    // declare the game state
    struct gameState G;

    printf("\n----- UNIT TEST - Bug#5- scoreFor() incorrectly calculates score ------\n");
    //
    // Discard and deck count are not the same
    // This should not effect the score
    //

    memset(&G, 23, sizeof(struct gameState));

    // initialize a new game
    int r = initializeGame(2, k, seed, &G); 


    // set any other variables
    G.handCount[p] = 5;
    G.discardCount[p] = 5;
    G.deckCount[p] = 6;

    G.hand[ p ][ 0 ] = estate;
    G.hand[ p ][ 1 ] = estate;
    G.hand[ p ][ 2 ] = estate;
    G.hand[ p ][ 3 ] = estate;
    G.hand[ p ][ 4 ] = estate;

    G.discard[ p ][ 0 ] = duchy;
    G.discard[ p ][ 1 ] = duchy;
    G.discard[ p ][ 2 ] = duchy;
    G.discard[ p ][ 3 ] = duchy;
    G.discard[ p ][ 4 ] = duchy;

    G.deck[ p ][ 0 ] = curse;
    G.deck[ p ][ 1 ] = curse;
    G.deck[ p ][ 2 ] = curse;
    G.deck[ p ][ 3 ] = curse;
    G.deck[ p ][ 4 ] = curse;
    G.deck[ p ][ 5 ] = curse;



    // call the function
   r = scoreFor(0, &G);

    // verify that your assertspass, for the bugs your asserts may fail
    newAssert(r == 14,__LINE__); 
    printf("\n----- UNIT TEST - Bug#5 - complete ------\n");

    return 0;
}