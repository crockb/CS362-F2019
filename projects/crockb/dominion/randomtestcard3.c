/* randomtestcard3.c
	Author/Date:  Bryant Crock  11/16/19
	Description:  Test the outcomes of the refactored tribute card playTribute();
	Business Requirements for Tribute:
		 1. The player to the left reveals then discards top 2 cards
		 2. For each differently named card:
		 		- Action: +2 actions
		 		- Treasure Card: +2 coins
		 		- Victory Card: +2 cards

	CONDITIONS:  1: Left player has 1 or less cards in discard/deck - deckCount > 0 (action)
				 2: Left player has 1 or less cards in discard/deck - discardCount = 1 (treasure)
				 3: Left player has 1 or less cards in discard/deck - no cards (failure)
				 4: Left player has 2 or more cards in discard/deck - no deck cards (shuffle)
				   4.1:   has duplicates at the backend
				     4.1.1: 2 coppers
				     4.1.2: 2 estates
				     4.1.3: 2 mines
				   4.2:   has a copper, has an estate
				   4.3:   has a mine, has a great_hall 
					   
   	Known Bugs Inserted in Assignment 2:
		1. 	Within the duplicate tribute card check, removed the statement that set 
			the tributeRevealedCards[1] = -1.  This wll cause the player to receive
			double benefits even though they shouldn’t because the cards revealed were the same.

        2.  In the discardCard() statements for the nextPlayer removed the -1 for the deckCount 
        	index.  The value for the tribute cards will always be set outside the bounds of 
        	the nextPlayer’s hand // NOTE:  had to remove for unit testing coverage
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
