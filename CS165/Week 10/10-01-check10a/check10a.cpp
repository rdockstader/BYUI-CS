/***********************************************************************
* Program:
*    Checkpoint 10a, Vectors
*    Brother Alvey, CS165
* Author:
*    Ryan Dockstader
* Summary: 
*    Summaries are not necessary for checkpoint assignments.
************************************************************************/

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**********************************************************************
* Function: promptIntVector
* Purpose: Handles the input of an integer vector
***********************************************************************/
vector<int> promptIntVector()
{
	int input = -1;
	vector<int> returnVec;

	while (input != 0)
	{
		cout << "Enter int: ";
		cin >> input;
		if(input != 0)
			returnVec.push_back(input);
	} 

	return returnVec;
}

/**********************************************************************
* Function: displayIntVector
* Purpose: Handles the display of an integer vector
***********************************************************************/
void displayIntVector(vector<int> vec)
{
	cout << "Your list is:" << endl;
	//for (auto it : vec) <-- This should work, if the labs g++ was on latest...
	for (vector<int> :: iterator it = vec.begin(); it != vec.end(); it++ )
	{
		cout << *it << endl;
	}
}

/**********************************************************************
* Function: promptStringVector
* Purpose: Handles the input of an string vector
***********************************************************************/
vector<string> promptStringVector()
{
	cin.ignore(255, '\n');
	string input = "";
	vector<string> returnVec;

	while (input != "quit")
	{
		cout << "Enter string: ";
		getline(cin, input);
		if(input != "quit")
			returnVec.push_back(input);
	} 

	return returnVec;
}

/**********************************************************************
* Function: displayStringVector
* Purpose: Handles the display of an string vector
***********************************************************************/
void displayStringVector(vector<string> vec)
{
	cout << "Your list is:" << endl;
	//for (auto it : vec) <-- Here again, this is easier to understand code. 
	for (vector<string> ::iterator it = vec.begin(); it != vec.end(); it++)
	{
		cout << *it << endl;
	}
}


/**********************************************************************
 * Function: main
 * Purpose: This is the entry point and driver for the program.
 ***********************************************************************/
int main()
{
	displayIntVector(promptIntVector());
	cout << endl;
	displayStringVector(promptStringVector());
   return 0;
}


