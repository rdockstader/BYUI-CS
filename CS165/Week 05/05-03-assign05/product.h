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
	//getters
	float getSalesTax();
	float getShippingCost();
	float getTotalPrice();
	string getName() const { return this->name; }
	string getDescription() const { return this->description; }
	float getBasePrice() const { return this->basePrice; }
	float getWeight() const { return this->weight; }

	//Setters
	void prompt();
	void setName(string name) { this->name = name; }
	void setDescription(string desc) { this->description = desc; }
	void setBasePrice(float price) { this->basePrice = price; }
	void setWeight(float weight) { this->weight = weight; }

	//Constructors
	Product() { setName("none"); setDescription(""); setWeight(0.0f); setBasePrice(0.0f); }
	Product(string name, string desc, float price, float weight) { setName(name); setDescription(desc); setWeight(weight); setBasePrice(price); }

	//displayers
	void displayAdvertising();
	void displayInventory();
	void displayReceipt();
private:
	string name;
	float basePrice;
	float weight;
	string description;
	//private functions
	void formatReceiptLine(string name, float amount);
	float promptPrice();
};

#endif
