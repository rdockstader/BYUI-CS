/***************************************************************
* File: address.h
* Author: Ryan Dockstader
* Purpose: Contains the definition of the Address class
***************************************************************/

#ifndef ADDRESS_H
#define ADDRESS_H

#include  <string>

using namespace std;

class Address
{
public:
	//Getters
	string getStreet() const { return this->street; }
	string getCity() const { return this->city; }
	string getState() const { return this->state; }
	string getZip() const { return this->zip; }

	//Setters
	void setStreet(string street) { this->street = street; }
	void setCity(string city) { this->city = city; }
	void setState(string state) { this->state = state; }
	void setZip(string zip) { this->zip = zip;}

	//Constructors
	Address() { setStreet("unknown"); setZip("00000"); setCity(""); setState(""); };
	Address(string street, string city, string state, string zip) { setStreet(street); setZip(zip); setCity(city); setState(state); };


	//public member functions
	void display();

private:
	string street;
	string city;
	string state;
	string zip;
};

#endif
