#ifndef TOUGH_BIRD_H
#define TOUGH_BIRD_H

#include "bird.h"

class ToughBird : public Bird
{
public:
	ToughBird() { Bird(); healthRemaining = 3; }
	void draw() { drawToughBird(getPoint(), 30, 3); }
	int hit();
};

#endif // !TOUGH_BIRD_H

