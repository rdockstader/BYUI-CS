// File: customer.cpp

#include "customer.h"

#include <string>
#include <iostream>

/**********************************************************************
* FUNCTION: Display
* PURPOSE: Displays the name, and address in a mailing format
***********************************************************************/
void Customer::display()
{
	cout << this->name << endl;
	this->address.display();
}
