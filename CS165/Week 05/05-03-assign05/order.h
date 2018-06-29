/***************************************************************
* File: product.h
* Author: Ryan Dockstader
* Purpose: Contains the definition of the Order class
***************************************************************/

#ifndef ORDER_H
#define ORDER_H

#include "product.h"
#include "customer.h"


class Order 
{
public:
	//Getters
	Product getProduct() const { return this->product; }
	int getQuantity() const { return this->quantity; }
	Customer getCustomer() const { return this->customer; }
	string getShippingZip() const { return this->getCustomer().getAddress().getZip(); }
	float getTotalPrice() const { return (this->getProduct().getTotalPrice() * this->quantity); }
	//Setters
	void setProduct(Product product) { this->product = product; }
	void setQuantity(int quantity) { this->quantity = quantity; }
	void setCustomer(Customer customer) { this->customer = customer; }
	//constructors
	Order() { setQuantity(0); setProduct(Product()); setCustomer(Customer()); }
	Order(Product product, int quantity, Customer customer) { setQuantity(quantity); setProduct(product); setCustomer(customer); }
	//Displayers
	void displayShippingLabel();
	void displayInformation();
private:
	Product product;
	int quantity;
	Customer customer;
};


#endif
