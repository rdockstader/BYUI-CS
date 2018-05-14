/***********************************************************************
* Program:
*    Checkpoint 01a, review          (e.g. Checkpoint 01a, review)
*    Brother Alvey, CS165
* Author:
*    your name
* Summary:
*    Summaries are not necessary for checkpoint assignments.
* ***********************************************************************/

#include <iostream>
#include <string>
using namespace std;

/**********************************************************************
* Function: main
* Purpose: This is the entry point and driver for the program.
***********************************************************************/
int main()
{
	std::string firstName = "";
	int age = 0;

	cout << "Hello CS 165 World!" << endl;
	cout << "Please enter your first name: ";
	cin >> firstName;
	cout << "Please enter your age: ";
	cin >> age;
	cout << std::endl;
	cout << "Hello " << firstName << ", you are " << age << " years old." << endl;

	//char dummy = 'a';
	//std::cout << "enter any character to exit" << std::endl;
	//std::cin >> dummy;

	return 0;
}