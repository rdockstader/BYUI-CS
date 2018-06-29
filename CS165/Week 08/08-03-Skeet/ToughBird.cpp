#include "toughBird.h"

int ToughBird::hit()
{
	--healthRemaining;
	int score = 1;
	if (healthRemaining <= 0)
	{
		kill();
	}
	//std::cout << "Hit Score: " << score << std::endl;
	return score;
}
