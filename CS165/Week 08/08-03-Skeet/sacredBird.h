#ifndef SACRED_BIRD_H
#define SACRED_BIRD_H

#include "bird.h"

class SacredBird : public Bird
{
public:
	int hit();
	void draw() { drawSacredBird(getPoint(), 30); }
};
#endif // !SACRED_BIRD_H

