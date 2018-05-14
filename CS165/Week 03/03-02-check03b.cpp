/***********************************************************************
* Program:
*    Checkpoint 03b Exceptions
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
	bool passed = false;

	while (!passed) {
		
		cout << "Enter a number: ";
		cin >> num;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Invalid input." << endl;;
			passed = false;
		}
		else
			passed = true;
	}

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
