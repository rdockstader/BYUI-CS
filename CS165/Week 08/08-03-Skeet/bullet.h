#ifndef BULLET_H
#define BULLET_H

#include "flyingObject.h"
#include "point.h"
#include "uiDraw.h"




class Bullet : public FlyingObject
{
public:
	void fire(Point point, float angle);
	Bullet(Point point) { setVelocity(Velocity()); setPoint(point); };
	Bullet() { setVelocity(Velocity()); }
};

#endif // !BULLET_H

