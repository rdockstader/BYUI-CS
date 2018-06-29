/***********************************************************************
* Program:
*    Checkpoint 08a, Inheritance
*    Brother Alvey, CS165
* Author:
*    Ryan Dockstader
* Summary: 
*    Summaries are not necessary for checkpoint assignments.
* ***********************************************************************/

#include <iostream>
#include <string>
using namespace std;

// For this assignment, for simplicity, you may put all of your classes
// in this file.

// TODO: Define your Book class here
class Book {
private:
	string title;
	string author;
	int publicationYear;
public:
	void promptBookInfo() 
	{
		cout << "Title: ";
		getline(cin, title);
		cout << "Author: ";
		getline(cin, author);
		cout << "Publication Year: ";
		cin >> publicationYear;

	}
	void displayBookInfo() {
		cout << title << " (" << publicationYear << ") by " << author << endl;
	}
};

// TODO: Define your TextBook class here
class TextBook : public Book {
private:
	string subject;
public:
	void promptSubject() 
	{
		cout << "Subject: ";
		getline(cin, subject);
	}
	void displaySubject() {
		cout << "Subject: " << subject << endl;
	}
};

// TODO: Add your PictureBook class here
class PictureBook : public Book {
private:
	string illustrator;
public:
	void promptIllustrator() 
	{
		cout << "Illustrator: ";
		getline(cin, illustrator);
	}
	void displayIllustrator()
	{
		cout << "Illustrated by " << illustrator << endl;
	}
};


/**********************************************************************
 * Function: main
 * Purpose: This is the entry point and driver for the program.
 ***********************************************************************/
int main()
{
   // Declare a Book object here and call its methods
	Book book;
	book.promptBookInfo();
	cout << endl;
	book.displayBookInfo();
	cout << endl;
	cin.ignore(255, '\n');

   // Declare a TextBook object here and call its methods
	TextBook textBook;
	textBook.promptBookInfo();
	cin.ignore(255, '\n');
	textBook.promptSubject();
	cout << endl;
	textBook.displayBookInfo();
	textBook.displaySubject();
	cout << endl;

   // Declare a PictureBook object here and call its methods
	PictureBook pictureBook;
	pictureBook.promptBookInfo();
	cin.ignore(255, '\n');
	pictureBook.promptIllustrator();
	cout << endl;
	pictureBook.displayBookInfo();
	pictureBook.displayIllustrator();



   return 0;
}


