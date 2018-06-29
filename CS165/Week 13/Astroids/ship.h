/***********************************************************************
* Header File:
*    Ship : Defines a ship object that the user will control
* Author:
*    Ryan Dockstader
* Summary:
*    Defines a ship object that the user will control, from a flying
*	 object base class
************************************************************************/

#ifndef ship_h
#define ship_h

#include "flyingObject.h"

#define SHIP_SIZE 10
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5
#define SPAWN_ANGLE 90

/*********************************************
* SHIP
* Defines the user controlled ship class
*********************************************/
class Ship : public FlyingObject
{
public:
	// Constructors
	Ship() : FlyingObject(), angle(Angle(SPAWN_ANGLE)), radius(SHIP_SIZE) {}
	Ship(Point p) : FlyingObject(), angle(Angle(SPAWN_ANGLE)), radius(SHIP_SIZE) { this->setPoint(p); }

	// Getters
	int getRadius() { return radius; }
	Angle getAngle() { return angle; }
	int getRotation() { return angle.getAngle(); }

	// Other Public Methods
	void applyThrust(bool isForward);
	void applyRotation(bool isRight);
	void draw() { drawShip(this->getPoint(), angle.getAngle()-90); }
	void reset(Point p) { angle = Angle(SPAWN_ANGLE); alive = true; setPoint(p); setVelocity(Velocity()); }

private:
	void applyRotation(int rotation);
	Angle angle;
	int radius;
};

#endif /* ship_h */
