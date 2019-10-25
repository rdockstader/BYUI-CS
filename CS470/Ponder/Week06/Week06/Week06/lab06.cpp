/***********************************************************************
 * Program:
 *    Lab 06, Sanitization
 *    Brother Wilson, CS470
 * Author:
 *    Ryan Dockstader
 * Summary:
 *    Please include a detailed description of:
 *    1. Santizes a given HTML string, using a whitelist of acceptable tags
 ************************************************************************/

#include <iostream>
#include <string>
#include <deque>

bool charIsspace(char c);
bool isEndingTag(std::string str, int index);
std::string sanatizeChar(char c);
std::deque<std::string> populateWhiteList();
bool objIsInVector(std::string obj, std::deque<std::string> arr);
bool charIsForwardSlash(char c);
bool charIsRightAngleBracket(char c);
bool charIsLeftAngleBracket(char c);
std::string getTagName(std::string str, int index);
std::string sanatizeString(std::string unsanatizedString, std::deque<std::string> whiteList);

int main()
{
	std::string p1;
	std::deque<std::string> whiteList = populateWhiteList();
	do
	{
		std::cout << "> ";
		std::getline(std::cin, p1);
		std::cout << "\t" << sanatizeString(p1, whiteList) << std::endl;
	} while (p1 != "quit");
}

std::string sanatizeString(std::string str, std::deque<std::string> whiteList)
{
	std::deque<std::string> currentScope = {};
	for (int i = 0; i < str.length(); i++)
	{
		if (!charIsLeftAngleBracket(str[i]))
			continue;

		std::string tag = getTagName(str, i + 1);
		bool isClosingTag = isEndingTag(str, i + 1);
		if (!isClosingTag)
			currentScope.push_back(tag);
		// std::cout << tag << std::endl;
		if (objIsInVector(tag, whiteList) && (!isClosingTag || ((!currentScope.empty() && tag == currentScope.back()))))
		{
			if (isClosingTag && !currentScope.empty() && tag == currentScope.back())
				currentScope.pop_back();
			continue;
		}
			

		std::string santizedStart = sanatizeChar(str[i]);
		int endBracket;
		if (isClosingTag)
		{
			endBracket = i + tag.length() + 2;
			if (!currentScope.empty() && objIsInVector(tag, whiteList))
			{
				str += "</" + tag + ">";
			}
				
		}	
		else
			endBracket = i + tag.length() + 1;
		std::string santizedEnd = sanatizeChar(str[endBracket]);

		str.replace(endBracket, 1, santizedEnd);
		str.replace(i, 1, santizedStart);
		
	}

	return str;
}

std::string getTagName(std::string str, int index)
{
	char curChar = str[index];
	std::string tagName = "";
	while (!charIsRightAngleBracket(curChar) && !charIsspace(curChar))
	{
		if(!charIsForwardSlash(curChar) && !charIsRightAngleBracket(curChar))
			tagName += curChar;
		if (index >= str.length())
			break;
		curChar = str[++index];
	}

	return tagName;
}

bool isEndingTag(std::string str, int index)
{
	char curChar = str[index];
	std::string tagName = "";
	while (!charIsRightAngleBracket(curChar))
	{
		if (charIsForwardSlash(curChar))
			return true;
		if (index >= str.length())
			break;
		curChar = str[++index];
	}

	return false;
}

bool charIsLeftAngleBracket(char c)
{
	return c == '<';
}

bool charIsRightAngleBracket(char c)
{
	return c == '>';
}

bool charIsForwardSlash(char c)
{
	return c == '/';
}

bool charIsspace(char c)
{
	return c == ' ';
}

bool objIsInVector(std::string obj, std::deque<std::string> arr)
{
	for (std::string str : arr)
	{
		if (str == obj)
			return true;
	}

	return false;
}

std::deque<std::string> populateWhiteList()
{
	return std::deque<std::string>
	{
		"a",
		"abbr",
		"acronym",
		"b",
		"blockquote",
		"cite",
		"code",
		"del",
		"em",
		"i",
		"q",
		"strike",
		"strong"
	};
}

std::string sanatizeChar(char c)
{
	switch (c)
	{
	case '<':
		return "&lt;";
	case '>':
		return "&gt;";
	}
	
	return "";
}