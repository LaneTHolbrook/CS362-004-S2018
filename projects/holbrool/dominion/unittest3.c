#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

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

	G.supplyCount[province] = 0;
	assert(isGameOver(&G) == 1); //check that game is read as over once there are no more provinces

	int i;
	for (i = curse; i <= treasure_map; i++)       	//loop all cards
	{
		G.supplyCount[i] = 1;
	}

	assert(isGameOver(&G) == 0);	//test that the game has not ended when there are no empty piles

	G.supplyCount[curse]--;

	assert(isGameOver(&G) == 0);	//test that the game has not ended when there is only one empty pile

	G.supplyCount[estate]--;

	assert(isGameOver(&G) == 0);	//test that the game has not ended when there are only two empty piles

	for (i = duchy; i <= treasure_map; i++)       	//loop all cards
	{
		if (i != province)
		{
			G.supplyCount[i]--;
			assert(isGameOver(&G) == 1);	//test that the game has ended when there are three or more empty piles
		}
	}

	return 0;
}