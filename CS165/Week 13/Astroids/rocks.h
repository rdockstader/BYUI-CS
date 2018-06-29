/***********************************************************************
* Header File:
*    Rock : defines the base rock object. 
*    Big Rock : defines the largest rock object.
*    Medium Rock : Defines the medium sized rock object.
*    Small Rock : Defines the smallest rock object
* Author:
*    Ryan Dockstader
* Summary:
*    Defines each of the 4 rock objects for the astroid game
************************************************************************/

#ifndef rocks_h
#define rocks_h

#include "flyingObject.h"

#include <vector>

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define BIG_ROCK_SCORE 15
#define MEDIUM_ROCK_SCORE 10
#define SMALL_ROCK_SCORE 5

/*********************************************
* ROCK
* Defines the base rock class
*********************************************/
class Rock : public FlyingObject
{
public:
	//constructors
	Rock() : FlyingObject(), rotationDegPerFrame(0), size(0), angle(Angle()) {}
	Rock(int dpf, int size) : rotationDegPerFrame(dpf), size(size) {}
	Rock(int dpf, int size, Angle a) : rotationDegPerFrame(dpf), size(size), angle(a) {}
	//getters
	int getRotationDegPerFrame() { return rotationDegPerFrame; }
	Angle getAngle() { return angle; }
	int getSize() { return size; }
	//setters
	void setRotationDegPerFrame(int dpf) { rotationDegPerFrame = dpf; }
	void setAngle(Angle a) { angle = a; }
	void setAngle(float deg) { angle.setAngle(deg); }
	void setAngle(int deg) { angle.setAngle((int)deg); }

	// Pure Virtual functions
	virtual std::vector<Rock*> destory() = 0;
	virtual int getScore() = 0;
protected:
	int rotationDegPerFrame;
	int size;
	Angle angle;
};

/*********************************************
* BIG ROCK
* Defines the big rock class
*********************************************/
class BigRock : public Rock
{
public:
	// Constructors
	BigRock() : Rock(BIG_ROCK_SPIN, BIG_ROCK_SIZE) {}
	BigRock(Point p);

	// Getters
	int getScore() { return BIG_ROCK_SCORE; }

	// Other Public Methods
	std::vector<Rock*> destory();
	void draw() { drawLargeAsteroid(point, getRotationDegPerFrame()); }

};

/*********************************************
* MEDIUM ROCK
* Defines the medium rock class
*********************************************/
class MediumRock : public Rock
{
public:
	// Constructors
	MediumRock(Velocity velocity) : Rock(MEDIUM_ROCK_SPIN, MEDIUM_ROCK_SIZE) { this->setVelocity(velocity); }
	MediumRock(Velocity velocity, Point point) : Rock(MEDIUM_ROCK_SPIN, MEDIUM_ROCK_SIZE) { this->setVelocity(velocity); this->setPoint(point); }

	// Getters
	int getScore() { return MEDIUM_ROCK_SCORE; }

	// Other Public Methods
	std::vector<Rock*> destory();
	void draw() { drawMediumAsteroid(this->getPoint(), this->getRotationDegPerFrame()); }
};

/*********************************************
* SMALL ROCK
* Defines the small rock class
*********************************************/
class SmallRock : public Rock
{
public:
	// Constructors
	SmallRock(Velocity velocity) : Rock(SMALL_ROCK_SIZE, SMALL_ROCK_SIZE) { this->setVelocity(velocity); }
	SmallRock(Velocity velocity, Point point) : Rock(SMALL_ROCK_SIZE, SMALL_ROCK_SIZE) { this->setVelocity(velocity); this->setPoint(point); }

	// Getters
	int getScore() { return SMALL_ROCK_SCORE; }

	// Other Public Methods
	std::vector<Rock*> destory();
	void draw() { drawSmallAsteroid(getPoint(), getRotationDegPerFrame()); }
};


#endif /* rocks_h */
