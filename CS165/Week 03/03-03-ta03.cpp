/**********************************************************************
 * File: ta03.cpp
 * Author: Br. Burton
 *
 * Description: Use this file as a starting point for Team Activity 03.
 *    You do not need to "submit" your code, but rather, answer the
 *    questions in the I-Learn assessment.
 **********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

/***********************************************************************
 * Struct: Scripture
 * Description: Holds the reference to a scripture (book, chapter, verse
 ***********************************************************************/
struct Scripture
{
   string book;
   int chapter;
   int beginVerse;
   int endVerse;
};

/***********************************************************************
 * Function: display
 * Description: Displays the passed scripture.
 ***********************************************************************/
void display(const Scripture &scripture)
{
   cout << scripture.book << " ";
   cout << scripture.chapter << ":";
   cout << scripture.beginVerse;
   cout << "-";
   cout << scripture.endVerse;
}

/***********************************************************************
* Function: read file
* Description: reads in a file one line at a time
***********************************************************************/
vector<Scripture> readFile(string fileName) throw (string)
{
	ifstream fin(fileName);
	vector<Scripture> scriptures;
	string line;

	if (fin.fail())
	{
		throw string("File failed to open.");
	}

	while (getline(fin, line))
	{
		stringstream ss(line);
		Scripture scrip;
		ss >> scrip.book;
		ss >> scrip.chapter;
		ss >> scrip.beginVerse;
		ss >> scrip.endVerse;

		scriptures.push_back(scrip);
	}
	return scriptures;
}

/***********************************************************************
* Function: Prompt fileName
* Description: reads in a file one line at a time
***********************************************************************/
string promptFileName() throw (string) {
	string fileName;
	cout << "Enter filename: ";
	getline(cin, fileName);
	if (cin.fail())
	{
		throw string("Filename invalid");
		cin.clear();
		cin.ignore(256, '\n');
	}
	

	return fileName;
}

/***********************************************************************
 * Function: main
 * Description: The driver for the program.
 ***********************************************************************/
int main()
{
	//vector<Scripture> scriptures = readFile(promptFileName());

	string stringInt = "ABCDEFG";

	int i = -1;
	try
	{
		i = stoi(stringInt);
	}
	catch(invalid_argument& e)
	{
		i = -1;
	}

	cout << i << endl;

	char dummy;
	cin >> dummy;

	return 0;
}