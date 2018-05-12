#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include <time.h>

//test for card 'village'

//white box testing to ensure every part of the code is behaving correctly.

//village is quite simple, to ensure that it works we simply need to be sure it properly increases the number of actions and
//draws a card, or not if the deck is empty.

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

	G.numPlayers = MAX_PLAYERS;
	int turn, testNum = 0, cardTotal, deckTotal, discardTotal;

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
		G.hand[turn][0] = village;
		G.numActions = 0;

		int i;
		for (i = 0; i < G.deckCount[turn]; i++) //initialize the cards in the deck
		{
			G.deck[0][i] = estate;
		}

		for (i = 0; i < G.discardCount[turn]; i++)
		{
			G.discard[turn][i] = estate;
		}

		deckTotal = G.deckCount[turn];
		discardTotal = G.discardCount[turn];
		cardTotal = deckTotal + discardTotal;

		cardEffect(village, 0, 0, 0, &G, 0, 0);

		if (cardTotal == 0)
		{
			if (!assert(G.handCount[0] == 0 && G.numActions == 2))//make sure the correct number of cards are in hand after village resolves, and correct number of actions
			{
				printf("%i: player %i, %i cards in deck, %i cards in discard\n", testNum, turn + 1, deckTotal, discardTotal);
			}
		}
		else
		{
			if (!assert(G.handCount[0] == 1 && G.numActions == 2))//make sure the correct number of cards are in hand after village resolves, and correct number of actions
			{
				printf("%i: player %i, %i cards in deck, %i cards in discard\n", testNum, turn + 1, deckTotal, discardTotal);
			}
		}
	}
	return 0;
}