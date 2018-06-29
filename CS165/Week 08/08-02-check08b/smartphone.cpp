/*******************
 * smartphone.cpp
 *******************/

#include "smartphone.h"

using namespace std;

// TODO: Put your SmartPhone methods here

void SmartPhone::prompt()
 {
	Phone::promptNumber();
	cin.ignore(255, '\n');
	cout << "Email: ";
	getline(cin, email);
 }

void SmartPhone::display()
{
	Phone::display();
	cout << email << endl;
}
