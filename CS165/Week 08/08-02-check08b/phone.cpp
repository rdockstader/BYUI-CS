/*********************
 * phone.cpp
 *********************/
#include "phone.h"

// TODO: Put your phone class methods here...
using namespace std;

void Phone::promptNumber()
 {
	cout << "Area Code: ";
	cin >> areaCode;
	cout << "Prefix: ";
	cin >> prefix;
	cout << "Suffix: ";
	cin >> suffix;
 }

void Phone::display()
{
	cout << "(" << this->areaCode << ")" << this->prefix << "-" << this->suffix << endl;
}
