/***********************************************************************
* Program:
*    Checkpoint 02b, Complex Numbers
*    Brother Alvey, CS165
* Author:
*    Ryan Dockstader
* Summary: 
*    Summaries are not necessary for checkpoint assignments.
* ***********************************************************************/

#include <iostream>
using namespace std;

/**********************************************************************
* Struct: Complex
* Purpose: Holds a real and imaginary part of a number
***********************************************************************/
struct Complex 
{
	double real;
	double imaginary;
};

/**********************************************************************
* Function: Prompt
* Purpose: Prompts user for a complex number
***********************************************************************/
Complex prompt()
{
	Complex c;
	cout << "Real: ";
	cin >> c.real;
	cout << "Imaginary: ";
	cin >> c.imaginary;

	return c;
}

/**********************************************************************
* Function: display
* Purpose: displays complex numbers
***********************************************************************/
void display(Complex c)
{
	cout << c.real << " + " << c.imaginary << "i";
}


/**********************************************************************
 * Function: addComplex
 * Purpose: Adds two complex numbers together and returns the sum.
 ***********************************************************************/
Complex addComplex(const Complex & x, const Complex & y)
{
	Complex z;
	z.imaginary = x.imaginary + y.imaginary;
	z.real = x.real + y.real;

	return z;


}


/**********************************************************************
 * Function: main
 * Purpose: This is the entry point and driver for the program.
 ***********************************************************************/
int main()
{
   // Declare two Complex objects, c1 and c2
	Complex c1, c2;

   // Call your prompt function twice to fill in c1, and c2 
	c1 = prompt();
	c2 = prompt();
	
   // Declare another Complex for the sum
	Complex sum;

   // Call the addComplex function, putting the result in sum;
	sum = addComplex(c1, c2);
   
   cout << "\nThe sum is: ";
   display(sum);
   cout << endl;
 
   return 0;
}


