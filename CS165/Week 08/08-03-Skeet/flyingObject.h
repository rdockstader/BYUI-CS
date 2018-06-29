#ifndef FLYING_OBJECT_H
#define FLYING_OBJECT_H

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

class FlyingObject
{
protected:
	Point point;
	Velocity velocity;
	bool alive = true;
public:
	Point getPoint() { return this->point; }
	Velocity getVelocity() { return this->velocity; }
	bool isAlive() { return this->alive; }
	void setPoint(Point point) { this->point = point; }
	void setVelocity(Velocity velocity) { this->velocity = velocity; }
	void kill() { alive = false; };
	void advance();
	void virtual draw() { drawDot(this->getPoint()); };

};

#endif // !FLYING_OBJECT_H

