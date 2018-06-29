#include "sacredBird.h"

int SacredBird::hit()
{
	--healthRemaining;
	int score = 0;
	if (healthRemaining <= 0)
	{
		kill();
		score = -10;
	}
	kill();

	return score;
}