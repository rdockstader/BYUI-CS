/***************************************************************
 * File: product.cpp
 * Author: Ryan Dockstader
 * Purpose: Contains the method implementations for the Product class.
 ***************************************************************/

#include "product.h"

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/**********************************************************************
* FUNCTION: prompt
* PURPOSE: Prompts the user a name, desription, weight, and price.
***********************************************************************/
void Product::prompt()
{
	cout << "Enter name: ";
	getline(cin, this->name);
	cout << "Enter description: ";
	getline(cin, this->description);
	cout << "Enter weight: ";
	cin >> this->weight;
	promptPrice();
}
/**********************************************************************
* FUNCTION: prompt Price
* PURPOSE: Prompts the user a price, with error handling.
***********************************************************************/
void Product::promptPrice()
{
	float price = -1.0f;
	bool passed = false;
	while (!passed)
	{
		cout << "Enter price: ";
		try
		{
			cin >> price;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(256, '\n');
				throw string("Price must be a number");
			}
				

			if (price < 0)
				throw string("Price must be positive");

			passed = true;
		}
		catch(string err)
		{
			//TODO: log error message...
		}
	}
	this->basePrice = price;;
}

/**********************************************************************
* FUNCTION: Get Sales Tax
* PURPOSE: returns .06 (tax rate) * the base price.
***********************************************************************/
float Product::getSalesTax()
{
	return 0.06f * this->basePrice;
}

/**********************************************************************
* FUNCTION: Get Shipping Cost
* PURPOSE: returns the shipping cost of the product
***********************************************************************/
float Product::getShippingCost()
{
	float shippingCost = 2.0;
	if (this->weight > 5)
		shippingCost += ((weight - 5) * 0.1f);
	
	return shippingCost;

}

/**********************************************************************
* FUNCTION: Get Total Price
* PURPOSE: returns the base price + sales tax + shipping
***********************************************************************/
float Product::getTotalPrice()
{
	return (this->basePrice + getSalesTax() + getShippingCost());
}

/**********************************************************************
* FUNCTION: Display Advertising Profile
* PURPOSE: Displays product information in an advertising profile
***********************************************************************/
void Product::displayAdvertisingProfile()
{
	cout << this->name << " - $" << this->basePrice << endl;
	cout << "(" << this->description << ")" << endl;
}

/**********************************************************************
* FUNCTION: Display Inventory Line Item
* PURPOSE: Displays product information in an Inventory line item
***********************************************************************/
void Product::displayInventoryLineItem()
{
	cout << "$" << this->basePrice << " - " << this->name << " - ";
	cout.precision(1);
	cout <<this->weight << " lbs" << endl;
	cout.precision(2);
}

/**********************************************************************
* FUNCTION: Display Receipt
* PURPOSE: Displays product price broken down by base, tax, shipping,
*		   and total price
***********************************************************************/
void Product::displayReceipt()
{
	cout << this->name << endl;
	formatReceiptLine("Price", this->basePrice);
	formatReceiptLine("Sales tax", getSalesTax());
	formatReceiptLine("Shipping cost", getShippingCost());
	formatReceiptLine("Total", getTotalPrice());
}

/**********************************************************************
* FUNCTION: Format Receipt Line
* PURPOSE: Formats a line for the receipt
***********************************************************************/
void Product::formatReceiptLine(string name, float amount)
{
	const int AMOUNT_SPACES = 13;
	cout << "  " << name << ": ";
	for (int i = 0; i < AMOUNT_SPACES - name.length(); i++)
		cout << " ";
	cout << "$   ";
	if (amount < 10)
		cout << " ";
	cout << amount << endl;
}
