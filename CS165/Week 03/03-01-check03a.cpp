/***********************************************************************
* Program:
*    Checkpoint 03a Exceptions  
*    Brother Alvey, CS165
* Author:
*    Ryan Dockstader
* Summary: 
*    Summaries are not necessary for checkpoint assignments.
* ***********************************************************************/

#include <iostream>
#include <string>
using namespace std;

/**********************************************************************
* Function: Prompt
* Purpose: prompts the user for a number, and returns it.
***********************************************************************/
int prompt() throw (string){
	int num = -1;
	cout << "Enter a number: ";
	cin >> num;

	if (num < 0)
		throw string("The number cannot be negative.");

	if (num > 100)
		throw string("The number cannot be greater than 100.");

	if (num % 2 != 0)
		throw string("The number cannot be odd.");

	return num;

}

/**********************************************************************
 * Function: main
 * Purpose: This is the entry point and driver for the program.
 ***********************************************************************/
int main()
{
	int num = 0;
	try 
	{
		num = prompt();
		cout << "The number is " << num << "." << endl;
	}
	catch (string err)
	{
		cout << "Error: " << err << endl;
	}
	
	//char dummy;
	//cin >> dummy;

   return 0;
}
