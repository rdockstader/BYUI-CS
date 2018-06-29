/*********************
 * File: check12b.cpp
 *********************/

#include <iostream>
using namespace std;

#include "money.h"

/****************************************************************
 * Function: main
 * Purpose: Test the money class and practice operators
 ****************************************************************/
int main()
{
   Money account1;
   Money account2;

   // Get the input from the user
   account1.prompt();
   account2.prompt();
   cout << endl;

   cout << "The original values are: ";
   account1.display();
   cout << " and ";
   account2.display();
   cout << endl;



   // TODO: Add code here to add account2 onto account1 using the += operator
   account1 += account2;


   cout << "After doing account1 += account2, the value of account1 is: ";
   account1.display();
   cout << endl;

   Money account3;



   // TODO: Add code here to add account1 and account2 together
   // and put the result in account3
   account3 = account1 + account2;


   cout << "From account1 + account2, the value of account3 is: ";
   account3.display();
   cout << endl;


   // TODO: Add code here to apply the ++ pre-increment operator to account1;
   account1++;


   cout << "After ++account1, the value of account1 is: ";
   account1.display();
   cout << endl;


   return 0;
}

