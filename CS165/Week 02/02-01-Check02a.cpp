/***********************************************************************
* Program:
*    Checkpoint 02a, STRUCTS  
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
* Struct: Student
* Purpose: Holds data pertaining to student information.
***********************************************************************/
struct Student {
	string firstName;
	string lastName;
	int id;
};

/**********************************************************************
* Function: main
* Purpose: This is the entry point and driver for the program.
***********************************************************************/
void displayStudent(Student student) 
{
	cout << student.id
		<< " - "
		<< student.firstName
		<< " "
		<< student.lastName
		<< endl;
}

/**********************************************************************
 * Function: main
 * Purpose: This is the entry point and driver for the program.
 ***********************************************************************/
int main()
{
	// Get user information
	Student user;
	cout << "Please enter your first name: ";
	cin >> user.firstName;
	cout << "Please enter your last name: ";
	cin >> user.lastName;
	cout << "Please enter your id number: ";
	cin >> user.id;
	cout << endl;
	// Display User Information
	cout << "Your information:" << endl;
	displayStudent(user);	

   return 0;
}
