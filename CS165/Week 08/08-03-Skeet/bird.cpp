#include "bird.h"
#include "uiDraw.h"

#include <iostream>

int Bird::hit()
{
	--healthRemaining;
	int score = 0;
	if (healthRemaining <= 0)
	{
		kill();
		score = 1;
	}
	//std::cout << "Hit Score: " << score << std::endl;
	return score;
}

/*

To give the user a greater chance to hit the Tough Bird, it should move more slowly than the others. In particular, its horizontal velocity should be taken from the range: 2 to 4, 
and it's vertical velocity from the range -3 to +3.

A delay of up to 1 second should be introduced before the first bird is released or after each round before the next one is released.

*/

Bird::Bird()
{
	// Set random point
	// The initial position of the bird is anywhere along the left side the screen
	Point p = Point();
	p.setX((random(1, 3) == 1) ? 180 : -180);
	p.setY(random(-175, 175));
	setPoint(p);

	//set random velocity
	Velocity v = Velocity();
	//If the bird starts on the top half of the screen, it should have a generally downward velocity (down and to the right at amounts defined below).
	//The vertical component of the velocity should be between -4 and +4 pixels/frame (positive or negative depending on whether it starts on the top or bottom half of the screen).
	if (getPoint().getY() > 0)
		v.setDy(-random(1, 5));
	//If the bird starts on the bottom half of the screen, it should have a generally upward velocity (up and to the right at amounts defined below).
	else
		v.setDy(random(1, 5));
	//The horizontal component of the velocity should be between 3 and 6 pixels/frame.
	if (getPoint().getX() == 180)
		v.setDx(-random(3, 7));
	else
		v.setDx(random(3, 7));

	setVelocity(v);

	//std::cout << "v Y: " << v.getDy() << " V X: " << v.getDx() << std::endl;
}
