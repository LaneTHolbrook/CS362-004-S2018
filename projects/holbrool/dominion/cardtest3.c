#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//white box testing to ensure every part of the code is behaving correctly.
//since council room doesn't care what card is drawn, ony that cards are drawn, testing only with total number of cards and not different specific cards

//tests cover each relevant state the card could be played in- there are enough cards to draw in the deck,
//and there aren fewer total cards than the card tries to draw. There is no need to test every combination of player having cards and not, since
//one player drawing does not effect other players drawing.
//as well as other players both having a hard to draw and not, at both the minimum and maximum number of other players
// and the card being played by both the first and last player

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

	G.numPlayers = 2;
	G.whoseTurn = 0;
	G.discardCount[0] = 0;
	G.discardCount[1] = 0;
	G.discardCount[2] = 0;
	G.discardCount[3] = 0;
	G.handCount[0] = 1;
	G.playedCardCount = 0;
	G.hand[0][0] = council_room;
	G.numBuys = 0;

	G.deckCount[0] = 10;
	G.deckCount[1] = 10;
	G.handCount[1] = 0;

	int i;
	for (i = 0; i < 10; i++) //there're plenty of cards
	{
		G.deck[0][i] = estate;
		G.deck[1][i] = estate;
	}

	playCouncil_room(&G, 0);

	assert(G.handCount[0] == 4 && G.handCount[1] == 1 && G.numBuys == 1);//make sure the correct number of cards are in hand after council room resolves, 2 players, player 1 playing the card, everyone has enough cards, and the extra buy


	G.handCount[0] = 1;
	G.deckCount[0] = 10;
	G.deckCount[1] = 10;
	G.deckCount[2] = 10;
	G.deckCount[3] = 10;
	G.handCount[1] = 0;
	G.handCount[2] = 0;
	G.handCount[3] = 0;
	G.numPlayers = 4;

	for (i = 0; i < 10; i++) //there're plenty of cards
	{
		G.deck[0][i] = estate;
		G.deck[1][i] = estate;
		G.deck[2][i] = estate;
		G.deck[3][i] = estate;
	}

	playCouncil_room(&G, 0);

	assert(G.handCount[0] == 4 && G.handCount[1] == 1 && G.handCount[2] == 1 && G.handCount[3] == 1);//make sure the correct number of cards are in hand after council room resolves, 4 players, player 1 playing the card, everyone has enough cards


	G.handCount[0] = 1; //no one has cards
	G.deckCount[0] = 0;
	G.deckCount[1] = 0;
	G.deckCount[2] = 0;
	G.deckCount[3] = 0;
	G.handCount[1] = 0;
	G.handCount[2] = 0;
	G.handCount[3] = 0;
	G.numPlayers = 4;


	playCouncil_room(&G, 0);

	assert(G.handCount[0] == 0 && G.handCount[1] == 0 && G.handCount[2] == 0 && G.handCount[3] == 0);//make sure the correct number of cards are in hand after council room resolves, 4 players, player 1 playing the card, no one has any enough cards


	G.deckCount[1] = 10;
	G.deckCount[2] = 10;
	G.deckCount[3] = 10;
	G.handCount[0] = 0;
	G.handCount[1] = 0;
	G.handCount[2] = 0;
	G.handCount[3] = 1;
	G.numPlayers = 4;
	G.whoseTurn = 3;

	for (i = 0; i < 10; i++) //there're plenty of cards
	{
		G.deck[0][i] = estate;
		G.deck[1][i] = estate;
		G.deck[2][i] = estate;
		G.deck[3][i] = estate;
	}

	playCouncil_room(&G, 0);

	assert(G.handCount[0] == 1 && G.handCount[1] == 1 && G.handCount[2] == 1 && G.handCount[3] == 4);//make sure the correct number of cards are in hand after council room resolves, 4 players, player 4 playing the card, everyone has enough cards

	return 0;
}