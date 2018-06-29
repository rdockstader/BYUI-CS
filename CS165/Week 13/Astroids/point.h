/***********************************************************************
 * Header File:
 *    Point : The representation of a position on the screen
 *    Angle : The representation of a angle an object is facing
 * Author:
 *    Br. Helfrich / Ryan Dockstader
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/



#ifndef POINT_H
#define POINT_H

#include <iostream>

/*********************************************
 * POINT
 * A single position.  
 *********************************************/
class Point
{
public:
   // constructors
   Point()            : x(0.0), y(0.0)  {}
   Point(bool check)  : x(0.0), y(0.0)  {}
   Point(float x, float y);

   // getters
   float getX()       const { return x;              }
   float getY()       const { return y;              }

   // setters
   void setX(float x);
   void setY(float y);
   void addX(float dx)      { setX(getX() + dx);     }
   void addY(float dy)      { setY(getY() + dy);     }

   bool isClose(Point p2, float range);

private:
   float x;           // horizontal position
   float y;           // vertical position
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Point & pt);
std::istream & operator >> (std::istream & in,        Point & pt);

/*********************************************
* ANGLE
* An angle in degrees, with returns for x
* and y component, and in radians
*********************************************/
class Angle
{
public:
	//constructors
	Angle() : angle(0), xDir(0.0), yDir(0.0) {}
	Angle(float angle) { setAngle(angle); }

	//static variables
	const static float pi;

	//getters
	float getAngle() { return angle; }
	float getXDir() { return xDir; }
	float getYDir() { return yDir; }
	float getRadians();

	//setters
	void setAngle(float angle);

private:
	float angle;
	float xDir;
	float yDir;
};

#endif // POINT_H
