#ifndef LANDER_H
#define LANDER_H

#include "point.h"
#include "velocity.h"

class Lander {
public:
	// Constructors
	Lander() : point(Point()), velocity(Velocity()), alive(true), landed(false), fuel(500) {}
	// Getters
	Point getPoint() const { return this->point; }
	Velocity getVelocity() const { return this->velocity; }
	bool isAlive() const { return alive; }
	bool isLanded() const { return landed; }
	int getFuel() const { return fuel; }
	bool canThrust();
	// Setters
	void setLanded(bool isLanded) { this->landed = isLanded; }
	void setAlive(bool isAlive) { this->alive = isAlive; }
	void setFuel(int fuel) { this->fuel = fuel; }

	void applyGravity(float gravity);
	void applyThrustLeft();
	void applyThrustRight();
	void applyThrustBottom();
	
	void advance();
	void draw();
private:
	Point point;
	Velocity velocity;
	bool alive;
	bool landed;
	int fuel;
	void applyHorizontalThrust(float);
	void applyVerticalThrust(float);

};

#endif // !LANDER_H

