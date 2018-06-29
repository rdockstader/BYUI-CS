#include "bullet.h"

#include <cmath>
#include <iostream>

const static float BULLET_SPEED = 10;
const float  B_PI = 3.14159265358979323846;

using namespace std;

void Bullet::fire(Point point, float angle)
{
	this->setPoint(point);
	float rAngle = angle * (B_PI / 180);
	//cout << "X: " << -cos(rAngle) << " Y: " << sin(rAngle) << endl;

	Velocity v;
	v.setDx(BULLET_SPEED * (-cos(rAngle)));
	v.setDy(BULLET_SPEED * (sin(rAngle)));
	setVelocity(v);
}
