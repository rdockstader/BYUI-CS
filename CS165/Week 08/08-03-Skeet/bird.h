#ifndef BIRD_H
#define BIRD_H

#include "flyingObject.h"

class Bird : public FlyingObject
{
protected:
	int healthRemaining = 1;
public:
	int virtual hit();
	Bird();
	void draw() { drawCircle(getPoint(), 15); }
};
#endif 

