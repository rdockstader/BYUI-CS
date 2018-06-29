/***********************************************************************
* Source File:
*    Point : The representation of a position on the screen
*    Angle : The representation of a angle an object is facing
* Author:
*    Br. Helfrich / Ryan Dockstader
* Summary:
*    Everything we need to know about a location on the screen, including
*    the location and the bounds.
************************************************************************/

#include "point.h"
#include <cassert>
#include <cmath>

/******************************************
 * POINT : CONSTRUCTOR WITH X,Y
 * Initialize the point to the passed position
 *****************************************/
Point::Point(float x, float y) : x(0.0), y(0.0)
{
   setX(x);
   setY(y);
}

/*******************************************
 * POINT : SET X
 * Set the x position if the value is within range
 *******************************************/
void Point::setX(float x)
{
   this->x = x;
}

/*******************************************
 * POINT : SET Y
 * Set the y position if the value is within range
 *******************************************/
void Point::setY(float y)
{
   this->y = y;
} 

/*******************************************
* POINT : IS CLOSE
* returns true if points are within range
*******************************************/
bool Point::isClose(Point p, float range)
{
	bool isClose = false;
	if ((fabs(this->getX() - p.getX()) < range) &&
		(fabs(this->getY() - p.getY()) < range))
	{
		isClose = true;
	}
	return isClose;
}

/******************************************
 * POINT insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream & operator << (std::ostream & out, const Point & pt)
{
   out << "(" << pt.getX() << ", " << pt.getY() << ")";
   return out;
}

/*******************************************
 * POINT extraction
 *       Prompt for coordinates
 ******************************************/
std::istream & operator >> (std::istream & in, Point & pt)
{
   float x;
   float y;
   in >> x >> y;

   pt.setX(x);
   pt.setY(y);

   return in;
}

/*******************************************
* POINT set const variale
*       sets static const for pi
******************************************/
const float Angle::pi = 3.14159265358979323846;

/*******************************************
* ANGLE : GET RADIANS
*       returns the angle in radians
******************************************/
float Angle::getRadians()
{
	return angle * (this->pi / 180);;
}

/*******************************************
* ANGLE : SET ANGLE
*       sets angle, x and y component
******************************************/
void Angle::setAngle(float angle) 
{

	int newAngle = angle;

	if (newAngle >= 360)
		newAngle = newAngle - 360;
	else if (newAngle < 0)
		newAngle = 360 + newAngle;

	this->angle = newAngle;

	//std::cout << "Angle: " << this->angle << std::endl;

	float radians = getRadians();

	this->xDir = cos(radians);
	this->yDir = sin(radians);
}
