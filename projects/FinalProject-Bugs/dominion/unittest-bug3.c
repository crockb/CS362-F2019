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

    printf("\n----- UNIT TEST 1 - Bug#3- cardEffect() remodel switch branch incorrect cost comparison ------\n");
    //The player attempts to gain a card that is of a lesser value than 2 coins more than the trashed card.


    memset(&G, 23, sizeof(struct gameState));

    // initialize a new game
    int r = initializeGame(2, k, seed, &G); 


    // set any other variables
    G.handCount[p] = 2;                
    G.hand[p][0] = remodel; //ensure remodel card is in hand
    G.hand[p][1] = estate;      //estate card costs 2 coins
    G.supplyCount[copper] = 5;       //copper costs 0 coins
    G.supplyCount[province] = 5; //province costs 8 coins


    // call the function
    r = cardEffect(remodel, 1, copper, 0, &G, 0, 0);

    // verify that your assertspass, for the bugs your asserts may fail
    newAssert(r == 0,__LINE__); 
    printf("\n----- UNIT TEST 1 - Bug#3 - complete ------\n");

//----------------------------------------------------------------------------------------------------------------------------

    printf("\n----- UNIT TEST 2 - Bug#3- cardEffect() remodel switch branch incorrect cost comparison ------\n");
    //The player attempts to gain a card costing more than 2 coins more than the trashed card

    // set the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize a new game
    r = initializeGame(2, k, seed, &G); 


    // set any other variables
    G.handCount[p] = 2;                
    G.hand[p][0] = remodel; //ensure remodel card is in hand
    G.hand[p][1] = estate;      //estate card costs 2 coins
    G.supplyCount[copper] = 5;       //copper costs 0 coins
    G.supplyCount[province] = 5; //province costs 8 coins


    // call the function
    r = cardEffect(remodel, 1, province, 0, &G, 0, 0);

    // verify that your assertspass, for the bugs your asserts may fail
    newAssert(r == -1,__LINE__); 

    printf("\n----- UNIT TEST 2 - Bug#3 - complete ------\n");


    return 0;
}