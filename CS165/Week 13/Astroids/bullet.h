/***********************************************************************
* Header File:
*    Bullet : The representation of a bullet fired from an object
* Author:
*    Ryan Dockstader
* Summary:
*    Extention of FlyingObject. Holds attributes related to a projectile
************************************************************************/

#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40


#include "flyingObject.h"
#include "point.h"
#include "uiDraw.h"
/*********************************************
* BULLET
* A single Projectile.
*********************************************/
class Bullet : public FlyingObject
{
public:
	//Constructors
	Bullet(Point point) { setVelocity(Velocity()); setPoint(point); framesRemaining = 40; }
	Bullet() { setVelocity(Velocity()); setPoint(Point()); framesRemaining = 40; }

	//Getters
	int getFramesRemaining();

	//Other Public Functions
	void fire(Point point, Angle angle);
	void fire(Point point, Angle angle, Velocity velocity);
	void advance();

private:
	int framesRemaining;
};

#endif /* bullet_h */
