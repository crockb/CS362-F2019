#ifndef _UNITTEST_HELPERS_H
#define _UNITTEST_HELPERS_H

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

// helper functions
int testPlayBaron();
int assert(int expected, int actual);
int hasGameCard(int card, struct gameState *state, int pileToCheck);
int countCardTypeInHand(int card, struct gameState *state);
int provideEstateCardFromDeck(int player, struct gameState *state);
int removeEstateCardFromHand(int player, struct gameState *state);


// helper print functions
void printUnitTest1Condition1Results(struct gameState *state, struct gameState *preState);
void printUnitTest1Condition2to4Results(struct gameState *state, struct gameState *preState);
void printPlayersCards(int player, struct gameState *state);
void printAllSupplyCounts(struct gameState *state);
void printAllGameStateVariables(struct gameState *state);

#endif