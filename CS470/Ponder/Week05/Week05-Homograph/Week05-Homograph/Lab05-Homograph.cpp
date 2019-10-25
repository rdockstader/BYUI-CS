/***********************************************************************
 * Program:
 *    Lab 05, Path homographs
 *    Brother Wilson, CS470
 * Author:
 *    Ryan Dockstader
 * Summary:
 *    1. This program is designed to compare two file paths, and determine if they are homographs
 *    2. It will prompt the user for two paths, strip any extra information out of the paths, and then compare them
 *    3. The program assumes you are passing two paths
 ************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
#include <list>

std::string canonicalizeFileName(std::string fileName);
bool pathsAreHomographs(std::string path1, std::string path2);
std::string removeDotSlash(std::string str);
std::string removeCanceledDotDotSlash(std::string str);
int findBeginingOfpathPart(std::string pathPart);
bool itemIsInList(std::list<size_t> list, size_t item);
int findCharBeforeIndex(std::string str, char c, int index);
std::string removeEverythingBeforeHome(std::string str);

int main()
{
	std::string filePath1, filePath2;
	std::cout << "Specify the first filename:  ";
	std::cin >> filePath1;
	std::cout << "Specify the second filename: ";
	std::cin >> filePath2;
	if (pathsAreHomographs(filePath1, filePath2))
		std::cout << "The paths are homographs" << std::endl;
	else
		std::cout << "The paths are NOT homographs" << std::endl;


}

// check if two paths are homographs
bool pathsAreHomographs(std::string path1, std::string path2)
{
	return canonicalizeFileName(path1) == canonicalizeFileName(path2);
}

// canonicalize a given file name
std::string canonicalizeFileName(std::string fileName)
{
	return removeDotSlash(removeCanceledDotDotSlash(removeEverythingBeforeHome(fileName)));
}

// remove any ./ from the the given string
std::string removeDotSlash(std::string str)
{
	const std::string dotSlash = "./";
	size_t foundDotSlash = str.find(dotSlash);
	while (foundDotSlash != std::string::npos)
	{
		str = str.erase(foundDotSlash, 2);
		foundDotSlash = str.find(dotSlash);
	}	
	return str;
}

// removes any ../ that is canceled by navigating into a folder directly before it in the path
std::string removeCanceledDotDotSlash(std::string str)
{
	const std::string dotDotSlash = "../";
	std::list<size_t> validDotDotSlashes = {};
	size_t foundDotDotSlash = str.find(dotDotSlash);
	while (foundDotDotSlash != std::string::npos && !itemIsInList(validDotDotSlashes, foundDotDotSlash))
	{
		int foundSlash = findCharBeforeIndex(str, '/', foundDotDotSlash);
		if (foundSlash >= 0)
		{
			int beginningOfPathPart = findBeginingOfpathPart(str.substr(0, foundSlash));
			if(beginningOfPathPart >= 0)
				str = str.erase(beginningOfPathPart, foundDotDotSlash-beginningOfPathPart+2);
		}
		else
		{
			validDotDotSlashes.push_back(foundDotDotSlash);
		}
		
		foundDotDotSlash = str.find(dotDotSlash);
	}
	if (str[0] == '/')
		str = str.substr(1, str.length());
	return str;
}

// finds a character before a given index
int findCharBeforeIndex(std::string str, char c, int index)
{
	if (index > str.length())
		return -1;

	for(int i = index; i >= 0; i--)
	{
		if (str[i] == c)
			return i;
	}

	return -1;
}

// finds the beginning of a path part, based on /'s
int findBeginingOfpathPart(std::string pathPart)
{
	for (int i = pathPart.length(); i >= 0; i--)
	{
		if (pathPart[i] == '/')
			return i;
	}

	return 0;
}

// checks if the item is in the list
bool itemIsInList(std::list<size_t> list, size_t item)
{
	return std::find(list.begin(), list.end(), item) != list.end();
}

// if the string '/home' exists in the string, everything before it will be removed
std::string removeEverythingBeforeHome(std::string str)
{
	const std::string home = "home";
	size_t foundHome = str.find(home);
	if(foundHome != std::string::npos)
		str = str.erase(0, foundHome - 1);

	return str;
}