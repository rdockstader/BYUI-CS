// File: address.cpp

#include "address.h"

#include <iostream>

using namespace std;

/**********************************************************************
* FUNCTION: Display
* PURPOSE: Displays the address in a mailing format
***********************************************************************/
void Address::display()
{
	cout << this->street << endl;
	cout << this->city << ", " << this->state;
	cout << " " << this->zip << endl;
}
