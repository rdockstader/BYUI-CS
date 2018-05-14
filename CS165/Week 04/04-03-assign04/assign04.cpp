/***************************************************************
 * File: assign04.cpp
 * Author: Ryan Dockstader
 * Purpose: Contains the main function to test the Product class.
 ***************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "product.h"

void displayOptions();
int getDisplayChoice();

int main()
{
	//Limit decimals
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	//Create product, and prompt user for product info
	Product product;
	product.prompt();
	//Prompt user for product display output
	displayOptions();
	switch(getDisplayChoice())
	{
	case 1:
		product.displayAdvertisingProfile();
		break;
	case 2:
		product.displayInventoryLineItem();
		break;
	case 3:
		product.displayReceipt();
		break;
	}
   return 0;
}

/**********************************************************************
* FUNCTION: Display Options
* PURPOSE: displays the available options for the user to choose from
***********************************************************************/
void displayOptions() {
	cout << endl;
	cout << "Choose from the following options:\n";
	cout << "1 - Advertising profile\n";
	cout << "2 - Inventory line item\n";
	cout << "3 - Receipt\n";
	cout << endl;
}

/**********************************************************************
* FUNCTION: Get Display Choice;
* PURPOSE: Gets the choice from the user, and returns it.
***********************************************************************/
int getDisplayChoice() {
	int choice;
	cout << "Enter the option that you would like displayed: ";
	cin >> choice;
	cout << endl;
	return choice;
}