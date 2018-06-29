/***************************************************************
* File: customer.h
* Author: Ryan Dockstader
* Purpose: Contains the definition of the Customer class
***************************************************************/

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "address.h"

class Customer 
{
public:
	//getters
	Address getAddress() const { return this->address; };
	string getName() const { return this->name; }

	//Setters
	void setAddress(Address address) { this->address = address; }
	void setName(string name) { this->name = name; }

	//constructors
	Customer() { setName("unspecified"); setAddress(Address()); }
	Customer(string name, Address address) { setName(name); setAddress(address); }

	//Public Member Funciton
	void display();

private:
	string name;
	Address address;

};

// put your Customer class here

#endif
