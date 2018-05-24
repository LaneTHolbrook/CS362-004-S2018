#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//white box testing to ensure every part of the code is behaving correctly. As no part of this function is variable based on which card
//it is dealing with, examining behavior for one card should suffice.

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

	G.numBuys = 0;
	G.whoseTurn = 1;
	G.discardCount[G.whoseTurn] = 0;

	assert(buyCard(adventurer, &G) == -1); //test if trying to buy a card when you have no buys returns an error

	G.numBuys = 3;
	G.supplyCount[adventurer] = 0;

	assert(buyCard(adventurer, &G) == -1); //test if trying to buy a card when there are no more copies of that card returns an error

	G.supplyCount[adventurer] = 10;
	G.coins = 5;

	assert(buyCard(adventurer, &G) == -1); //test if test if trying to buy a card that costs more than you have returns an error

	G.coins = 10;

	buyCard(adventurer, &G);

	assert(G.coins == 4); // make sure the coins are being properly subtracted from total
	assert(G.numBuys == 2); // make sure the a buy is properly consumed
	assert(G.discardCount[G.whoseTurn] == 1); // make sure a card was added to the discard properly
	assert(G.discard[G.whoseTurn][0] == adventurer); //make sure the correct card was added

	return 0;
}