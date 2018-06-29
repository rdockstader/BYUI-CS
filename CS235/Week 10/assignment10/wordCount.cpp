/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include <map>
#include <string>
#include <iostream>
#include <fstream>
//#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
using namespace std;
void readFile(map <string, int> & counts, const string & fileName);
std::string promptName();
bool equalsIgnoreCase(std::string, std::string);

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
	//init the map
	map<string, int> wordCounts;
	// read the file
	readFile(wordCounts, promptName());
	// cycle words
	std::cout << "What word whose frequency is to be found. Type ! when done" << std::endl;
	std::string input;
	do 
	{
		std::cout << "> ";
		std::cin >> input;
		std::cout << "\t" << input << " : " << ((wordCounts.find(input) != wordCounts.end())? wordCounts[input] : 0) << std::endl;
	} while (input != "!");

}

void readFile(map <string, int> & counts, const string & fileName)
{
	std::ifstream inputFile(fileName);
	std::string inputWord;
	// Read from file
	while (inputFile >> inputWord)
	{
		//if key exists
		if (counts.find(inputWord) != counts.end())
		{
			// inputWord found, ++ the value
			counts[inputWord] = counts[inputWord]++;
		}
		else
		{
			// input word not found, add it and set the value to 1
			counts[inputWord] = 1;
		}
	}
}

std::string promptName()
{
	std::string filePath;
	// prompt for file path
	std::cout << "What is the filename to be counted? ";
	std::cin >> filePath;

	return filePath;
	
}


bool equalsIgnoreCase(std::string, std::string)
{

}