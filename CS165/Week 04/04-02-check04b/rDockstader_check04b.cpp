/*********************************************************************
* File: check04b.cpp
* Purpose: contains the main method to exercise the Date class.
*********************************************************************/

#include "date.h"

#include <iostream>
using namespace std;

int main()
{
	// prompt for month, day, year
	int monthInt = -1, day = -1, year = -1;
	cout << "Month: ";
	cin >> monthInt;
	eMonth month = eMonth(monthInt);

	cout << "Day: ";
	cin >> day;
	cout << "Year: ";
	cin >> year;
	// create a Date object
	Date date;
	// set its values
	date.set(month, day, year);
	// call each display function
	cout << endl;
	date.displayAmerican();
	date.displayEuropean();
	date.displayISO();

	//char dummy;
	//cin >> dummy;

   return 0;
}
