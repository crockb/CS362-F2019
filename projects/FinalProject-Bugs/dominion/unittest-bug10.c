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

    printf("\n----- UNIT TEST 1 - Bug#10- cardEffect() ambassador switch branch incorrectly calculates number of copies of card in hand ------\n");
    //Reveal a card in hand and return 2 copies to the supply (where card + 2 copies currently exists in hand)

    memset(&G, 23, sizeof(struct gameState));

    // initialize a new game
    int r = initializeGame(2, k, seed, &G); 


    // set any other variables
    G.handCount[p] = 5;
    G.discardCount[p] = 0;
    G.hand[ p ][ 0 ] = ambassador;
    G.hand[ p ][ 1 ] = copper;
    G.hand[ p ][ 2 ] = estate;
    G.hand[ p ][ 3 ] = copper;
    G.hand[ p ][ 4 ] = copper;

    G.handCount[ p + 1 ] = 5;
    G.discardCount[p + 1] = 0;
    G.hand[ p + 1 ][ 0 ] = silver;
    G.hand[ p + 1 ][ 1 ] = silver;
    G.hand[ p + 1 ][ 2 ] = silver;
    G.hand[ p + 1 ][ 3 ] = silver;
    G.hand[ p + 1 ][ 4 ] = silver;
    G.discard[p + 1][0] = -1;

    G.supplyCount[copper] = 0;
    G.playedCardCount = 0;
    G.numActions = 0;
    G.numBuys = 0;
    G.coins = 0;



    // call the function
    r = cardEffect(ambassador, 1, 2, 0, &G, 0, 0);

    // verify that your asserts pass, for the bugs your asserts may fail
    //cards discarded
    newAssert(G.handCount[p] == 2, __LINE__);    
    int copperCount = 0;
    for(int i = 0; i < G.handCount[p]; i++){
        if(G.hand[p][i] == copper){
            copperCount++;
        }
    }
    newAssert(copperCount == 1, __LINE__);
    //copies added to other player’s discard pile
    newAssert(G.discardCount[p + 1] == 1, __LINE__);
    newAssert(G.discard[p + 1][0] == copper, __LINE__);
    newAssert(G.supplyCount[copper] == 1, __LINE__);

    printf("\n----- UNIT TEST 1- Bug#10 - complete ------\n");

    printf("\n----- UNIT TEST 2 - Bug#10- cardEffect() ambassador switch branch incorrectly calculates number of copies of card in hand ------\n");
    //Reveal a card in hand and return 1 copy to the supply (where card + 1 copy currently exists in hand)


    // set the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize a new game
    r = initializeGame(2, k, seed, &G); 


    // set any other variables
    G.handCount[p] = 5;
    G.discardCount[p] = 0;
    G.hand[ p ][ 0 ] = ambassador;
    G.hand[ p ][ 1 ] = copper;
    G.hand[ p ][ 2 ] = estate;
    G.hand[ p ][ 3 ] = copper;
    G.hand[ p ][ 4 ] = copper;

    G.handCount[ p + 1 ] = 5;
    G.discardCount[p + 1] = 0;
    G.hand[ p + 1 ][ 0 ] = silver;
    G.hand[ p + 1 ][ 1 ] = silver;
    G.hand[ p + 1 ][ 2 ] = silver;
    G.hand[ p + 1 ][ 3 ] = silver;
    G.hand[ p + 1 ][ 4 ] = silver;
    G.discard[p + 1][0] = -1;

    G.supplyCount[copper] = 0;
    G.playedCardCount = 0;
    G.numActions = 0;
    G.numBuys = 0;
    G.coins = 0;



    // call the function
    r = cardEffect(ambassador, 1, 1, 0, &G, 0, 0);

    // verify that your asserts pass, for the bugs your asserts may fail
    //cards discarded
    newAssert(G.handCount[p] == 3, __LINE__);
    copperCount = 0;
    for(int i = 0; i < G.handCount[p]; i++){
        if(G.hand[p][i] == copper){
            copperCount++;
        }
    }
    newAssert(copperCount == 2, __LINE__);

    //copies added to other player’s discard pile
    newAssert(G.discardCount[p + 1] == 1, __LINE__);
    newAssert(G.discard[p + 1][0] == copper, __LINE__);

    printf("\n----- UNIT TEST 2 - Bug#10 - complete ------\n");
    printf("\n----- UNIT TEST 3 - Bug#10- cardEffect() ambassador switch branch incorrectly calculates number of copies of card in hand ------\n");
    //Reveal a card in hand (where handPos == supplyPos) and return 1 copy to the supply (where card + 1 copy currently exists in hand)


    // set the game state
    memset(&G, 23, sizeof(struct gameState));

    // initialize a new game
    r = initializeGame(2, k, seed, &G); 


    // set any other variables
    G.handCount[p] = 5;
    G.discardCount[p] = 0;
    G.hand[ p ][ 0 ] = ambassador;
    G.hand[ p ][ 1 ] = copper;
    G.hand[ p ][ 2 ] = estate;
    G.hand[ p ][ 3 ] = copper;
    G.hand[ p ][ 4 ] = copper;

    G.handCount[ p + 1 ] = 5;
    G.discardCount[p + 1] = 0;
    G.hand[ p + 1 ][ 0 ] = silver;
    G.hand[ p + 1 ][ 1 ] = silver;
    G.hand[ p + 1 ][ 2 ] = silver;
    G.hand[ p + 1 ][ 3 ] = silver;
    G.hand[ p + 1 ][ 4 ] = silver;
    G.discard[p + 1][0] = -1;

    G.supplyCount[copper] = 0;
    G.playedCardCount = 0;
    G.numActions = 0;
    G.numBuys = 0;
    G.coins = 0;

    r = cardEffect(ambassador, 4, 1, 0, &G, 0, 0);

    // verify that your asserts pass, for the bugs your asserts may fail
    //cards discarded
    newAssert(G.handCount[p] == 3, __LINE__);
    copperCount = 0;
    for(int i = 0; i < G.handCount[p]; i++){
        if(G.hand[p][i] == copper){
            copperCount++;
        }
    }
    newAssert(copperCount == 2, __LINE__);

    //copies added to other player’s discard pile
    newAssert(G.discardCount[p + 1] == 1, __LINE__);
    newAssert(G.discard[p + 1][0] == copper, __LINE__);

    printf("\n----- UNIT TEST 3 - Bug#10 - complete ------\n");

    return 0;
}