#include "lander.h"
#include "uiDraw.h"

bool Lander::canThrust()
{
	if (isAlive() && !isLanded() && getFuel() > 0)
		return true;


	return false;
}

void Lander::applyGravity(float gravity)
{
	applyVerticalThrust(-gravity);
}

void Lander::applyThrustLeft()
{
	if (canThrust())
	{
		applyHorizontalThrust(0.1f);
		this->setFuel(getFuel() - 1);
	}
		
}

void Lander::applyThrustRight()
{
	if (canThrust())
	{
		applyHorizontalThrust(-0.1f);
		this->setFuel(getFuel() - 1);
	}
		
}

void Lander::applyThrustBottom()
{
	if (canThrust()) {
		applyVerticalThrust(0.3f);
		this->setFuel(getFuel() - 3);
	}
	
}


void Lander::applyHorizontalThrust(float thrust)
{

	this->velocity.setDx(thrust);
	//
	this->point.addX(this->velocity.getDx());
}


void Lander::applyVerticalThrust(float thrust)
{
	this->velocity.setDy(thrust);
	this->point.addY(this->velocity.getDy());
}



void Lander::advance()
{
	applyVerticalThrust(0);
	applyHorizontalThrust(0);
	drawLander(this->point);
}

void Lander::draw()
{
	drawLander(this->point);
}
