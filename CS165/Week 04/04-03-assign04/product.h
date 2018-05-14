/***************************************************************
 * File: product.h
 * Author: Ryan Dockstader
 * Purpose: Contains the definition of the Product class
 ***************************************************************/
#ifndef PRODUCT_H
#define PRODUCT_H

#include<string>

using namespace std;

// put your class definition here
class Product{
public:
	//Setters
	void prompt();
	//getters
	float getSalesTax();
	float getShippingCost();
	float getTotalPrice();
	//displayers
	void displayAdvertisingProfile();
	void displayInventoryLineItem();
	void displayReceipt();
private:
	string name;
	float basePrice;
	float weight;
	string description;
	//private functions
	void formatReceiptLine(string name, float amount);
	void promptPrice();
};

#endif
