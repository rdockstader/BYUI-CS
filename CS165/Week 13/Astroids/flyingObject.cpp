/***********************************************************************
* Source File:
*    Flying Object : The representation of a basic flying object
* Author:
*    Ryan Dockstader
* Summary:
*    Generic representation of an object flying through the air.
************************************************************************/

#include "flyingObject.h"
#include <iostream>

/******************************************
* BULLET : Advance
* Advances the flying object each frame
*****************************************/
void FlyingObject::advance()
{
	Point p = this->getPoint();

	p.addX(getVelocity().getDx());
	p.addY(getVelocity().getDy());

	if (p.getX() > 200)
		p.setX(-200);
	else if (p.getX() < -200)
		p.setX(200);

	if (p.getY() > 200)
		p.setY(-200);
	else if (p.getY() < -200)
		p.setY(200);

	this->setPoint(p);
	draw();
}
