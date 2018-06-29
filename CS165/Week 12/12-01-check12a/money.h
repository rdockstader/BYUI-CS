/******************
 * File: money.h
 ******************/
#ifndef MONEY_H
#define MONEY_H


#include <iostream>
#include <iomanip>

/******************************************************
 * Class: Money
 * Description: Holds a value of dollars and cents.
 ******************************************************/
class Money
{
private:
   int dollars;
   int cents;

public:
   /************************
    * Constructors
    ************************/
   Money()
   {
      setDollars(0);
      setCents(0);
   }

   Money(int dollars, int cents)
   {
      setDollars(dollars);
      setCents(cents);
   }

   /************************
    * Getters and Setters
    ************************/
   int getDollars() const { return dollars; }
   int getCents() const { return cents; }
   
   // These could be done in a smarter way to add cents to dollars if more than 100 etc.
   // but we're trying to keep it simple for this assignment...
   void setDollars(int dollars) { this->dollars = dollars; }
   void setCents(int cents) { this->cents = cents; }

   /************************
    * Other public methods
    ************************/
   void prompt();
   void display() const;
};

// Non-member operator prototypes go here
bool operator ==(const Money &m1, const Money &m2);
bool operator !=(const Money &m1, const Money &m2);

std::ostream & operator<<(std::ostream & out, const Money  & m);
#endif
