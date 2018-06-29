/***********************************************************************
* Source File:
*    Rock : defines the base rock object.
*    Big Rock : defines the largest rock object.
*    Medium Rock : Defines the medium sized rock object.
*    Small Rock : Defines the smallest rock object
* Author:
*    Ryan Dockstader
* Summary:
*    Defines each of the 4 rock objects for the astroid game
************************************************************************/

#include "rocks.h"

/******************************************
* BIG ROCK : Constructor
* takes a point and creates a big rock,
* with a velocity in a random direction
*****************************************/
BigRock::BigRock(Point p) : Rock(BIG_ROCK_SPIN, BIG_ROCK_SIZE)
{
	this->setPoint(p);
	this->setAngle(random(0, 360));
	Velocity v = Velocity();
	v.setDx(this->getAngle().getXDir() * 1);
	v.setDy(this->getAngle().getYDir() * 1);
	this->setVelocity(v);
}

/******************************************
* BIG ROCK : Destory
* takes a big rock, and destroys it
* returning a collection of smaller rocks
*****************************************/
std::vector<Rock*> BigRock::destory()
{
	std::vector<Rock*> rocks;
	//First medium
	Velocity v = this->getVelocity();
	v.setDy(1);
	rocks.push_back(new MediumRock(v, this->getPoint()));
	//Second Medium
	v = this->getVelocity();
	v.setDy(-1);
	rocks.push_back(new MediumRock(v, this->getPoint()));
	//Small Rock
	v = this->getVelocity();
	v.setDx(2);
	rocks.push_back(new SmallRock(v, this->getPoint()));
	return rocks;
}

/******************************************
* MEDIUM ROCK : Destory
* takes a medium rock, and destroys it
* returning a collection of small rocks
*****************************************/
std::vector<Rock*> MediumRock::destory()
{
	std::vector<Rock*> rocks;
	//First small
	Velocity v = this->getVelocity(); 
	v.setDx(3);
	rocks.push_back(new SmallRock(v, this->getPoint()));
	v = this->getVelocity();
	v.setDx(-3);
	rocks.push_back(new SmallRock(v, this->getPoint()));
	return rocks;
}
 
/******************************************
* SMALL ROCK : Destory
* takes a small rock and destroy it,
* returning nothing.
*****************************************/
std::vector<Rock*> SmallRock::destory()
{
	return std::vector<Rock*>();
}
