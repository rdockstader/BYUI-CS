/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    Chris Carrick, Harlen Hobbs, Ryan Docstader
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include "wholeNumber.h" // for WholeNumber
using namespace custom;
using namespace std;

/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibCount(int num)
{
   WholeNumber n1 = 1;
   WholeNumber n2 = 1;
   
   if (num >= 1)
      cout << "\t" << n1 << endl;
   
   if (num >= 2)
      cout << "\t" << n2 << endl;
   
   
   WholeNumber t1 = 0;
   
   for (int i = 1; i < num - 1; i++)
   {
      t1 = n1;
      n1 += n2;
      n2 = t1;
   
      cout << "\t" << n1 << endl;
   }
}

/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibDisplay(int num)
{
   WholeNumber n1 = 1;
   if (num >= 2)
   {
      WholeNumber n2 = 1;
      WholeNumber t1 = 0;
   
      for (int i = 2; i <= num - 1; i++)
      {
         t1 = n1;
         n1 += n2;
         n2 = t1;
         //cout << i + 1 << endl;
      }
   }
   cout << '\t' << n1 << endl;
}

/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   // your code to display the first <number> Fibonacci numbers
   fibCount(number);
   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   // your code to display the <number>th Fibonacci number
   fibDisplay(number);
   /*
   // Test extraction operator
   cout << "Enter a whole number: ";
   WholeNumber wholeNum;
   cin >> wholeNum;
   cout << wholeNum << endl;
   
   
   WholeNumber s1(1);
   WholeNumber s2(1);
   
   // Test subtraction
   cout << s1 - s2 << endl;
   
   // Test multiplication
   cout << s1 * s2 << endl;
   */
}


