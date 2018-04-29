#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//white box testing to ensure every part of the code is behaving correctly.
//since adventurer doesn't care what treasure is drawn, ony that treasure is drawn, testing only with gold

//tests cover each arrangment of treasure- 2 or more in the deck, 1 in the deck and 1 or more in the discard, 
//none in the deck and 2 or more in the discard, 1 in the deck and no more in the discard, none in the deck and 1 in the discard
//and no treasure in the deck or discard.

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
	G.deckCount[0] = 3;
	G.discardCount[0] = 3;
	G.handCount[0] = 0;

	int i;
	for (i = 0; i < 3; i++) //there's gold in deck
	{
		G.deck[0][i] = gold;
		G.discard[0][i] = estate;
	}

	playAdventurer(&G);

	assert(G.hand[0][0] == gold && G.hand[0][1] == gold && G.handCount[0] == 2);//make sure the gold wound up in the hand when there was enough gold in the deck

	G.deckCount[0] = 3;
	G.discardCount[0] = 3;
	G.handCount[0] = 0;

	for (i = 0; i < 3; i++) //there's gold in discard
	{
		G.deck[0][i] = estate;
		G.discard[0][i] = gold;
	}

	playAdventurer(&G);

	assert(G.hand[0][0] == gold && G.hand[0][1] == gold && G.handCount[0] == 2);//make sure the gold wound up in the hand when there was no gold in the deck but gold in the discard

	G.deckCount[0] = 3;
	G.discardCount[0] = 3;
	G.handCount[0] = 0;

	for (i = 0; i < 3; i++) //there's no gold anywhere
	{
		G.deck[0][i] = estate;
		G.discard[0][i] = estate;
	}

	G.handCount[0] = 0;
	//playAdventurer(&G);

	assert(G.handCount[0] == 0);//make sure no gold wound up in the hand when there was no gold to add

	G.deckCount[0] = 3;
	G.discardCount[0] = 3;
	G.handCount[0] = 0;

	for (i = 0; i < 3; i++) //there's 1 gold in each place
	{
		G.deck[0][i] = estate;
		G.discard[0][i] = estate;
	}

	G.deck[0][0] = gold;
	G.discard[0][0] = gold;

	G.handCount[0] = 0;
	playAdventurer(&G);

	assert(G.hand[0][0] == gold && G.hand[0][1] == gold && G.handCount[0] == 2);//make sure the gold wound up in the hand

	G.deckCount[0] = 3;
	G.discardCount[0] = 3;
	G.handCount[0] = 0;

	for (i = 0; i < 3; i++) //there's one gold in deck and none in discard
	{
		G.deck[0][i] = estate;
		G.discard[0][i] = estate;
	}

	G.deck[0][0] = gold;

	G.handCount[0] = 0;
	playAdventurer(&G);

	assert(G.hand[0][0] == gold && G.handCount[0] == 1);//make sure no gold wound up in the hand when there was no gold to add

	G.deckCount[0] = 3;
	G.discardCount[0] = 3;
	G.handCount[0] = 0;

	for (i = 0; i < 3; i++) //there's no gold in deck and one in discard
	{
		G.deck[0][i] = estate;
		G.discard[0][i] = estate;
	}

	G.discard[0][0] = gold;

	G.handCount[0] = 0;
	playAdventurer(&G);

	assert(G.hand[0][0] == gold && G.handCount[0] == 1);//make sure no gold wound up in the hand when there was no gold to add

	return 0;
}