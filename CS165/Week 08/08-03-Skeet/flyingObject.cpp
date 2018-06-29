#include "flyingObject.h"
#include <iostream>

void FlyingObject::advance()
{
	Point p = this->getPoint();

	p.addX(getVelocity().getDx());
	p.addY(getVelocity().getDy());
	//std::cout << " point x: " << p.getX() << " point y: " << p.getY() << std::endl;
	//std::cout << " veloc x: " << getVelocity().getDx() << " veloc y: " << getVelocity().getDy() << std::endl;
	this->setPoint(p);
	draw();

	//std::cout << "Flying Object Advanced Called." << std::endl;
}
