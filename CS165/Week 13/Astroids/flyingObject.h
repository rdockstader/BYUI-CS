/***********************************************************************
* Header File:
*    Flying Object : The representation of a basic flying object
* Author:
*    Ryan Dockstader
* Summary:
*    Generic representation of an object flying through the air.
************************************************************************/

#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

/*********************************************
* FLYING OBJECT
* Basic representation of an object flying 
* through space
*********************************************/
class FlyingObject
{
public:
	// Constructors
	FlyingObject() : point(Point()), velocity(Velocity()), alive(true) {}

	// Getters
	Point getPoint() const { return this->point; }
	Velocity getVelocity() const { return this->velocity; }
	bool isAlive() { return this->alive; }

	// Setters
	void setPoint(Point point) { this->point = point; }
	void setVelocity(Velocity velocity) { this->velocity = velocity; }

	// Other public functions
	void kill() { alive = false; };
	void virtual advance();
	void virtual draw() { drawDot(this->getPoint()); };

protected:
	Point point;
	Velocity velocity;
	bool alive;

};


#endif /* flyingObject_h */
