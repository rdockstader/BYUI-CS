#ifndef VELOCITY_H
#define VELOCITY_H


class Velocity {
public:
	//Constructors
	Velocity() { setDx(0); setDy(0); }
	Velocity(float x, float y) { setDx(x); setDy(y); }
	//Getters
	float getDx() const { return this->x; }
	float getDy() const { return this->y; }
	//Setters
	void setDx(float x) { this->x += x; }
	void setDy(float y) { this->y += y; }
	
private:
	float x;
	float y;
};

#endif // !VELOCITY_H

