/***********************************************************************
* Source File:
*    Bullet : The representation of a bullet fired from an object
* Author:
*    Ryan Dockstader
* Summary:
*    Extention of FlyingObject. Holds attributes related to a projectile
************************************************************************/

#include "bullet.h"


#include <cmath>
#include <iostream>

const float  B_PI = 3.14159265358979323846;

using namespace std;

/******************************************
* BULLET : Fire Method w/ Point and Angle
* Fires the projetile based on a point
* in space, and a given angle
*****************************************/
void Bullet::fire(Point point, Angle angle)
{
	this->setPoint(point);

	Velocity v;
	v.setDx(BULLET_SPEED * angle.getXDir());
	v.setDy(BULLET_SPEED * angle.getYDir());
	setVelocity(v);
}

/******************************************
* BULLET : Fire Method w/ Point, Angle and 
* Velocity
* Fires the projetile based on a point
* in space, and a given angle with 
* velocity
*****************************************/
void Bullet::fire(Point point, Angle angle, Velocity velocity)
{
	this->setPoint(point);

	Velocity v;
	// Get Velocity from angle
	v.setDx(BULLET_SPEED * angle.getXDir());
	v.setDy(BULLET_SPEED * angle.getYDir());
	// Add velocity from passed velocity
	v.setDx(velocity.getDx());
	v.setDy(velocity.getDy());
	setVelocity(v);
}

/******************************************
* BULLET : Advance
* Advanced the projectile each frame
*****************************************/
void Bullet::advance()
{
	framesRemaining--;
	if (framesRemaining == 0)
	{
		this->kill();
	}

	FlyingObject::advance();
}

/******************************************
* BULLET : Get Frames Remaining
* Returns the amount of frames until death
*****************************************/
int Bullet::getFramesRemaining()
{
	return framesRemaining;
}

