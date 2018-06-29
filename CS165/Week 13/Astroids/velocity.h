/***********************************************************************
* Header File:
*    Velocity : Class to hold attributes about velocity for a given 
*				object
* Author:
*    Ryan Dockstader
* Summary:
*    Defines the currentvelocity for a given object.
************************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity {
public:
	//Constructors
	Velocity() { setDx(0); setDy(0); }
	Velocity(float x, float y) { setDx(x); setDy(y); }

	//Getters
	float getDx() const { return x; }
	float getDy() const { return y; }

	//Setters
	void setDx(float x) { this->x += x; }
	void setDy(float y) { this->y += y; }

private:
	float x = 0;
	float y = 0;
};


#endif // !VELOCITY_H
