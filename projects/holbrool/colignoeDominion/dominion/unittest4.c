#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//testing that the score calculates correctly for each point card in each zone

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

	G.handCount[1] = 1;
	G.discardCount[1] = 0;
	G.deckCount[1] = 0;

	G.hand[1][0] = curse;
	assert(scoreFor(1, &G) == -1); //test that a curse is counted the correct sum of points from hand

	G.hand[1][0] = estate;
	assert(scoreFor(1, &G) == 1); //test that an estate is counted the correct sum of points from hand

	G.hand[1][0] = duchy;
	assert(scoreFor(1, &G) == 3); //test that a duchy is counted the correct sum of points from hand

	G.hand[1][0] = province;
	assert(scoreFor(1, &G) == 6); //test that a province is counted the correct sum of points from hand

	G.hand[1][0] = great_hall;
	assert(scoreFor(1, &G) == 1); //test that a great hall is counted the correct sum of points from hand

	G.hand[1][0] = gardens;
	assert(scoreFor(1, &G) == 0); //test that gardens are counted the correct sum of points from hand with less than 10 cards

	G.discardCount[1] = 9;
	assert(scoreFor(1, &G) == 1); //test that gardens are counted the correct sum of points from hand with 10 total cards

	G.discardCount[1] = 19;
	assert(scoreFor(1, &G) == 2); //test that gardens are counted the correct sum of points from hand with 20 total cards


	G.handCount[1] = 0;
	G.discardCount[1] = 1;

	G.discard[1][0] = curse;
	assert(scoreFor(1, &G) == -1); //test that a curse is counted the correct sum of points from discard

	G.discard[1][0] = estate;
	assert(scoreFor(1, &G) == 1); //test that an estate is counted the correct sum of points from discard

	G.discard[1][0] = duchy;
	assert(scoreFor(1, &G) == 3); //test that a duchy is counted the correct sum of points from discard

	G.discard[1][0] = province;
	assert(scoreFor(1, &G) == 6); //test that a province is counted the correct sum of points from discard

	G.discard[1][0] = great_hall;
	assert(scoreFor(1, &G) == 1); //test that a great hall is counted the correct sum of points from discard

	G.discard[1][0] = gardens;
	assert(scoreFor(1, &G) == 0); //test that gardens are counted the correct sum of points from discard with less than 10 cards

	G.deckCount[1] = 9;
	assert(scoreFor(1, &G) == 1); //test that gardens are counted the correct sum of points from discard with 10 total cards

	G.deckCount[1] = 19;
	assert(scoreFor(1, &G) == 2); //test that gardens are counted the correct sum of points from discard with 20 total cards


	G.discardCount[1] = 0;
	G.deckCount[1] = 1;

	G.deck[1][0] = curse;
	assert(scoreFor(1, &G) == -1); //test that a curse is counted the correct sum of points from discard

	G.deck[1][0] = estate;
	assert(scoreFor(1, &G) == 1); //test that an estate is counted the correct sum of points from discard

	G.deck[1][0] = duchy;
	assert(scoreFor(1, &G) == 3); //test that a duchy is counted the correct sum of points from discard

	G.deck[1][0] = province;
	assert(scoreFor(1, &G) == 6); //test that a province is counted the correct sum of points from discard

	G.deck[1][0] = great_hall;
	assert(scoreFor(1, &G) == 1); //test that a great hall is counted the correct sum of points from discard

	G.deck[1][0] = gardens;
	assert(scoreFor(1, &G) == 0); //test that gardens are counted the correct sum of points from discard with less than 10 cards

	G.hand[1][0] = smithy;
	G.handCount[1] = 9;
	assert(scoreFor(1, &G) == 1); //test that gardens are counted the correct sum of points from discard with 10 total cards

	G.handCount[1] = 19;
	assert(scoreFor(1, &G) == 2); //test that gardens are counted the correct sum of points from discard with 20 total cards

	return 0;
}