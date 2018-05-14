/***********************************************************************
* Program:
*    Checkpoint 01b, review   
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
* Function: Get Size
* Purpose: Gets a size of list from user and returns it
***********************************************************************/
int getSize() {
	int size = 0;
	cout << "Enter the size of the list: ";
	cin >> size;

	return size;
}

/**********************************************************************
* Function: Get List
* Purpose: Gets the list of numbers from the user
* and returns it
***********************************************************************/
void getList(int count, int (&passedArray)[20]) {
	for (int i = 0; i < count; i++) {
		cout << "Enter number for index " << i << ": ";
		cin >> passedArray[i];
	}
	cout << endl;
}

/**********************************************************************
* Function: Display Multiples
* Purpose: Displays if the number is
* divisable by 3
***********************************************************************/
void displayMultiples(int arraySize, int arr[20]) {
	cout << "The following are divisible by 3:" << endl;
	for (int i = 0; i < arraySize; i++) {
		if (arr[i] % 3 == 0) {
			cout << arr[i] << endl;
		}
	}
}

/**********************************************************************
* Function: main
* Purpose: This is the entry point and driver for the program.
***********************************************************************/
int main() {
	const int size = getSize();
	int arr[20];
	getList(size, arr);
	displayMultiples(size, arr);

	//char dummy = 'x';
	//cout << "enter any character to exit." << endl;
	//cin >> dummy;
	return 0;
}