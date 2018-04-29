#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//white box testing to ensure every part of the code is behaving correctly.
//since smithy doesn't care what card is drawn, ony that cards are drawn, testing only with total number of cards and not different specific cards

//tests cover each relevant state the card could be played in- there are more than enough cards to draw in the deck+discard
//there are just enough cards to draw, and there aren fewer total cards than the card tries to draw

int assert(int a)
{
	if (a == 0)
	{
		printf("assertion failed\n");
	}
}

int main()
{
	struct gameState G;

	G.whoseTurn = 0;
	G.deckCount[0] = 10;
	G.discardCount[0] = 10;
	G.handCount[0] = 1;
	G.playedCardCount = 0;
	G.hand[0][0] = smithy;

	int i;
	for (i = 0; i < 10; i++) //there're plenty of cards
	{
		G.deck[0][i] = estate;
		G.discard[0][i] = estate;
	}

	playSmithy(&G, 0);

	assert(G.handCount[0] == 3);//make sure the correct number of cards are in hand after smithy resolves.

	G.deckCount[0] = 3;
	G.discardCount[0] = 0;
	G.handCount[0] = 1;
	G.playedCardCount = 0;

	for (i = 0; i < 3; i++) //there're just enough cards
	{
		G.deck[0][i] = estate;
	}

	playSmithy(&G, 0);

	assert(G.handCount[0] == 3);//make sure the correct number of cards are in hand after smithy resolves.

	int j;
	for (j = 2; j >= 0; j--)
	{
		G.deckCount[0] = j;
		G.discardCount[0] = 0;
		G.handCount[0] = 1;
		G.playedCardCount = 0;

		for (i = 0; i < j; i++) //there aren't enough cards
		{
			G.deck[0][i] = estate;
		}

		playSmithy(&G, 0);

		assert(G.handCount[0] == j);//make sure the correct number of cards are in hand after smithy resolves.
	}

	return 0;
}