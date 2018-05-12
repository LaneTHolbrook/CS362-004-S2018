#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

//test for card 'adventurer'

//white box testing to ensure every part of the code is behaving correctly.
//since adventurer doesn't care what treasure is drawn, ony that treasure is drawn, testing only with gold

//tests cover each arrangment of treasure- 2 or more in the deck, 1 in the deck and 1 or more in the discard, 
//none in the deck and 2 or more in the discard, 1 in the deck and no more in the discard, none in the deck and 1 in the discard
//and no treasure in the deck or discard.

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

	int randInt = (rand() % (max + 1 - min)) + min;
	return randInt;
}

int getCard()//randomly returns either a treasure (all treasure being equal for testing purposes, it returns gold) or a non-treasure (estate to be specific)
{
	int card = getRand(0, 1);

	if (card)
	{
		card = gold;
	}
	else
	{
		card = estate;
	}
	return card;
}

int main()
{
	srand(time(NULL));
	struct gameState G;
	G.numPlayers = MAX_PLAYERS;
	int turn, i, testNum = 0, totalTreasure, deckTreasure, discardTreasure;

	while (testNum < 500000)//keep trying random values
	{
		testNum++;
		deckTreasure = 0;
		discardTreasure = 0;
		totalTreasure = 0;
		turn = getRand(0, 3); //randomly select which player is using adventurer
		G.whoseTurn = turn;
		G.deckCount[turn] = getRand(0, MAX_DECK); //randomize size of player deck and discard
		G.discardCount[turn] = getRand(0, MAX_DECK-G.deckCount[turn]);//any capacity left over from the deck maximum randomly filled in the discard
		G.handCount[turn] = 0; //hand size is not a relevant variable, as nothing in the function checks for what is already in the hand.

		

		for (i = 0; i < G.deckCount[turn]; i++) //randomize contents of deck
		{
			G.deck[turn][i] = getCard();
			if (G.deck[turn][i] == gold)
			{
				deckTreasure++;
			}
		}

		for (i = 0; i < G.discardCount[turn]; i++)
		{
			G.discard[turn][i] = getCard();
			if (G.deck[turn][i] == gold)
			{
				discardTreasure++;
			}
		}

		totalTreasure = deckTreasure + discardTreasure;

		playAdventurer(&G);

		if (totalTreasure == 0)//expected results by variable of total treasures.
		{
			if (!assert(G.handCount[turn] == 0))
			{
				printf("%i: player %i, %i treasures in deck, %i treasures in discard\n", testNum, turn + 1, deckTreasure, discardTreasure);
			}
		}
		else if (totalTreasure == 1)
		{
			if(!assert(G.hand[turn][0] == gold && G.handCount[turn] == 1))
			{
				printf("%i: player %i, %i treasures in deck, %i treasures in discard\n", testNum, turn + 1, deckTreasure, discardTreasure);
			}
		}
		else
		{
			if(!assert(G.hand[turn][0] == gold && G.hand[turn][1] == gold && G.handCount[turn] == 2))
			{
				printf("%i: player %i, %i treasures in deck, %i treasures in discard\n", testNum, turn + 1, deckTreasure, discardTreasure);
			}
		}
	}
	return 0;
}