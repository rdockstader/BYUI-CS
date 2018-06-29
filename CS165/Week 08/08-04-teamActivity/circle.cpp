#include "circle.h"

#include <iostream>
#include <string>

using namespace std;

void Circle::promptForCircle()
{
	int r;
	this->point.promptForPoint();
	cout << "Enter Radius: ";
	cin >> r;
	setRadius(r);
}

void Circle::display()
{
	this->point.display();
	cout << " - Radius: " << getRadius() << endl;
}
