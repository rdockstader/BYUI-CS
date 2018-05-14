/********************************************************************
* File: date.h
* Purpose: Holds the definition of the Date class.
********************************************************************/

#ifndef DATE_H
#define DATE_H


/**********************************************************************
* Enum: Month
* Purpose: Lists out month options
***********************************************************************/
enum eMonth {
	JANUARY,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER,
};


/**********************************************************************
* Class: Date
* Purpose: Stores information about a date
***********************************************************************/
class Date {
private:
	eMonth month;
	int day;
	int year;
public:

	void set(eMonth month, int day, int year);
	void displayAmerican();
	void displayEuropean();
	void displayISO();
};

#endif // !DATE_H