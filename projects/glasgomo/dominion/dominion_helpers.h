#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int drawCards(int player, struct gameState *state, int numOfCards);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
                int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
               struct gameState *state, int handPos, int *bonus);
int cardEffectAmbassador(int choice1, int choice2, struct gameState *state, int handPos);
int cardEffectBaron(int choice1, struct gameState *state);
int cardEffectMinion(int choice1, int choice2, struct gameState *state, int handPos);
int cardEffectTribute(struct gameState *state);
int cardEffectMine(int choice1, int choice2, struct gameState *state, int handPos);


#endif
