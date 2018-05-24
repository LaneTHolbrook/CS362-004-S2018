#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define MIN_CARD 0 //all values being sorted by compare are between 0 (the curse card) and 26 (the treasure map), thus these constitute the boundaries.
#define MAX_CARD 26

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
	int* a;
	int* b;

	//test cases for a > b, a < b, and a = b

	int c = MIN_CARD;
	int d = MAX_CARD;

	a = &c;
	b = &d;

	int res;
	
	assert(compare(a, b) == -1); //boundary test where a < b, should return 1

	*a = MAX_CARD;
	*b = MIN_CARD;

	assert(compare(a, b) == 1); //boundary test where a > b, should return -1

	*a = MAX_CARD;
	*b = MAX_CARD;

	assert(compare(a, b) == 0); //boundary test where a = b, should return 0

	return 0;
}