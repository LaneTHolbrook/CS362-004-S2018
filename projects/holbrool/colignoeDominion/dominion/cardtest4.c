#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

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

int main()
{

	struct gameState G;

	G.numPlayers = 2;
	G.whoseTurn = 0;
	G.discardCount[0] = 0;
	G.handCount[0] = 1;
	G.playedCardCount = 0;
	G.hand[0][0] = village;
	G.numActions = 0;

	G.deckCount[0] = 10;

	int i;
	for (i = 0; i < 10; i++) //there're plenty of cards
	{
		G.deck[0][i] = estate;
	}

	cardEffect(village, 0, 0, 0, &G, 0, 0);

	assert(G.handCount[0] == 1 && G.numActions == 2);//make sure the correct number of cards are in hand after village resolves, and correct number of actions

	G.handCount[0] = 1;
	G.hand[0][0] = village;
	G.deckCount[0] = 0;
	G.numActions = 0;

	cardEffect(village, 0, 0, 0, &G, 0, 0);

	assert(G.handCount[0] == 0 && G.numActions == 2);//make sure the correct number of cards are in hand after village resolves (with no cards to draw), and correct number of actions

	return 0;
}