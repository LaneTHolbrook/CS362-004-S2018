#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

//test for card 'smithy'

//white box testing to ensure every part of the code is behaving correctly.
//since smithy doesn't care what card is drawn, ony that cards are drawn, testing only with total number of cards and not different specific cards

//tests cover each relevant state the card could be played in- there are more than enough cards to draw in the deck+discard
//there are just enough cards to draw, and there aren fewer total cards than the card tries to draw

int assert(int a)
{
	if (a == 0)
	{
		printf("test failed\n");
		return 0;
	}
	return 1;
}

int getRand(int min, int max) //returns a positive random number in range of min and max. If min > max, returns -1
{
	if (min > max)
	{
		return -1;
	}

	int randInt = (rand() % (max - min)) + min;
	return randInt;
}

int main()
{
	srand(time(NULL));
	struct gameState G;
	int turn, testNum = 0, cardTotal, deckTotal, discardTotal;
	G.numPlayers = MAX_PLAYERS;

	while (testNum < 500000)
	{
		testNum++;
		cardTotal = 0;
		deckTotal = 0;
		discardTotal = 0;
		turn = getRand(0, 3); //randomly select which player is using adventurer
		G.whoseTurn = turn;
		G.deckCount[turn] = getRand(0, MAX_DECK); //randomize total number of cards in deck and discard
		G.discardCount[turn] = getRand(0, MAX_DECK - G.deckCount[turn]);//any capacity left over from the deck maximum randomly filled in the discard
		G.handCount[turn] = 1;
		G.playedCardCount = 0;
		G.hand[turn][0] = smithy;

		int i;
		for (i = 0; i < G.deckCount[turn]; i++) //initalize cards in deck and discard
		{
			G.deck[turn][i] = estate;
		}

		for (i = 0; i < G.discardCount[turn]; i++)
		{
			G.discard[turn][i] = estate;
		}

		deckTotal = G.deckCount[turn];
		discardTotal = G.discardCount[turn];
		cardTotal = deckTotal + discardTotal;

		playSmithy(&G, 0);

		if (cardTotal < 3)//make sure the correct number of cards are in hand after smithy resolves.
		{
			if (!assert(G.handCount[turn] == cardTotal))
			{
				printf("%i: player %i, %i cards in deck, %i cards in discard\n", testNum, turn + 1, deckTotal, discardTotal);
			}
		}
		else
		{
			if (!assert(G.handCount[turn] == 3))
			{
				printf("%i: player %i, %i cards in deck, %i cards in discard\n", testNum, turn + 1, deckTotal, discardTotal);
			}
		}
	}
	return 0;
}