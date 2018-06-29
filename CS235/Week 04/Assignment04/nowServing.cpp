/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
//#include <deque>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // Initialize variables
   std::string input;
   NowServing servingApp;
   std::cin.clear();
   std::cin.ignore(256, '\n');
   int iteration = 0;
   while(StringUtils::toLower(input) != "finished") {
	   if (servingApp.hasAppointment())
	   {
		   servingApp.display();
		   servingApp.cycleMinute();
	   }
	   cout << "<" << iteration << "> ";
	   
	   std::getline(std::cin, input);
	   std::vector<std::string> parsedApp = StringUtils::parseString(input, ' ');
	   if (parsedApp.size() == 4 && parsedApp[0] == "!!")
	   {
		   // I hate that g++ isn't on c++ 11....
		   istringstream converter(parsedApp[3]);
		   int minutes;
		   converter >> minutes;
		   servingApp.addImportantApp(NowServing::createAppointment(parsedApp[1], parsedApp[2], minutes, true));
	   }
	   else if (parsedApp.size() == 3)
	   {
		   // I hate that g++ isn't on c++ 11....
		   istringstream converter(parsedApp[2]);
		   int minutes;
		   converter >> minutes;
		   servingApp.addRegularApp(NowServing::createAppointment(parsedApp[0], parsedApp[1], minutes, false));
	   }

	   servingApp.cycleCurrentApp();
	   iteration++;
   };
   // end
   cout << "End of simulation\n";
}

/************************************************
* NOW SERVING :: Add Important App
* Adds a appointment to the front of the deque
***********************************************/
void NowServing::addImportantApp(Appointment app)
{
	if (curApp.minutes > 0)
		deque.push_front(app);
	else
		curApp = app;
}

/************************************************
* NOW SERVING :: Add Regular App
* Adds a appointment to the back of the deque
***********************************************/
void NowServing::addRegularApp(Appointment app)
{
	if (curApp.minutes > 0)
		deque.push_back(app);
	else
		curApp = app;
}

/************************************************
* NOW SERVING :: Cycle Minute
* cycles the minute of the current appointment
***********************************************/
void NowServing::cycleMinute()
{
	if(curApp.minutes > 0)
		curApp.minutes--;
}

/************************************************
* NOW SERVING :: Cycle Current app
* cycles the current appointment if needed
***********************************************/
void NowServing::cycleCurrentApp()
{
	if (curApp.minutes < 1 && deque.size() > 0)
	{
		curApp = deque.front();
		deque.pop_front();
	}
		
}

/************************************************
* NOW SERVING :: Add Important App
* Adds a appointment to the front of the deque
***********************************************/
bool NowServing::hasAppointment()
{
	return (curApp.minutes > 0)? true : false;
}

/************************************************
* NOW SERVING :: Display
* displays the current appointment
***********************************************/
void NowServing::display()
{
	if (curApp.isEmergency)
		std::cout << "\tEmergency for ";
	else
		std::cout << "\tCurrently serving ";
	
	cout << curApp.name << " for class " << curApp.cla << ". Time left: " << curApp.minutes << std::endl;
}

/************************************************
* NOW SERVING :: Create Appointment (STATIC)
* creates an appointment struct from variables
***********************************************/
Appointment NowServing::createAppointment(std::string cla, std::string name, int minutes, bool isEmergency)
{
	Appointment app;
	app.cla = cla;
	app.name = name;
	app.minutes = minutes;
	app.isEmergency = isEmergency;
	return app;
}
/************************************************
* STRING UTILS :: Static Variables
* Define
***********************************************/
std::map<char, char> StringUtils::alpha;
std::string StringUtils::alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";;

/************************************************
* STRING UTILS :: Parse String
* Parses a phrase into individual words
***********************************************/
std::vector<std::string> StringUtils::parseString(std::string str, char breakChar)
{
	std::vector<std::string> parsedString;
	std::stringstream ss;
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (str[i] == breakChar)
		{

			parsedString.push_back(ss.str());
			ss.str(std::string());
		}
		else
		{
			ss << str[i];
		}
	}
	if (ss.str().size() > 0)
		parsedString.push_back(ss.str());

	return parsedString;
}

/************************************************
* STRING UTILS :: To Lower (string)
* Converts a string into all lower case
***********************************************/
std::string StringUtils::toLower(std::string data)
{
	for (unsigned int i = 0; i < data.size(); i++)
	{
		data[i] = toLower(data[i]);
	}

	return data;
}

/************************************************
* STRING UTILS :: Generate To Lower Map
* Generates the To Lower Map for converting
* capitols into lowercase.
***********************************************/
void StringUtils::generateToLowerMap()
{
	alpha.insert(std::make_pair('A', 'a'));
	alpha.insert(std::make_pair('B', 'b'));
	alpha.insert(std::make_pair('C', 'c'));
	alpha.insert(std::make_pair('D', 'd'));
	alpha.insert(std::make_pair('E', 'e'));
	alpha.insert(std::make_pair('F', 'f'));
	alpha.insert(std::make_pair('G', 'g'));
	alpha.insert(std::make_pair('H', 'h'));
	alpha.insert(std::make_pair('I', 'i'));
	alpha.insert(std::make_pair('J', 'j'));
	alpha.insert(std::make_pair('K', 'k'));
	alpha.insert(std::make_pair('L', 'l'));
	alpha.insert(std::make_pair('M', 'm'));
	alpha.insert(std::make_pair('N', 'n'));
	alpha.insert(std::make_pair('O', 'o'));
	alpha.insert(std::make_pair('P', 'p'));
	alpha.insert(std::make_pair('Q', 'q'));
	alpha.insert(std::make_pair('R', 'r'));
	alpha.insert(std::make_pair('S', 's'));
	alpha.insert(std::make_pair('T', 't'));
	alpha.insert(std::make_pair('U', 'u'));
	alpha.insert(std::make_pair('V', 'v'));
	alpha.insert(std::make_pair('W', 'w'));
	alpha.insert(std::make_pair('X', 'x'));
	alpha.insert(std::make_pair('Y', 'y'));
	alpha.insert(std::make_pair('Z', 'z'));
	alpha.insert(std::make_pair('a', 'a'));
	alpha.insert(std::make_pair('b', 'b'));
	alpha.insert(std::make_pair('c', 'c'));
	alpha.insert(std::make_pair('d', 'd'));
	alpha.insert(std::make_pair('e', 'e'));
	alpha.insert(std::make_pair('f', 'f'));
	alpha.insert(std::make_pair('g', 'g'));
	alpha.insert(std::make_pair('h', 'h'));
	alpha.insert(std::make_pair('i', 'i'));
	alpha.insert(std::make_pair('j', 'j'));
	alpha.insert(std::make_pair('k', 'k'));
	alpha.insert(std::make_pair('l', 'l'));
	alpha.insert(std::make_pair('m', 'm'));
	alpha.insert(std::make_pair('n', 'n'));
	alpha.insert(std::make_pair('o', 'o'));
	alpha.insert(std::make_pair('p', 'p'));
	alpha.insert(std::make_pair('q', 'q'));
	alpha.insert(std::make_pair('r', 'r'));
	alpha.insert(std::make_pair('s', 's'));
	alpha.insert(std::make_pair('t', 't'));
	alpha.insert(std::make_pair('u', 'u'));
	alpha.insert(std::make_pair('v', 'v'));
	alpha.insert(std::make_pair('w', 'w'));
	alpha.insert(std::make_pair('x', 'x'));
	alpha.insert(std::make_pair('y', 'y'));
	alpha.insert(std::make_pair('z', 'z'));
}

/************************************************
* STRING UTILS :: To Lower (char)
* Converts a char to it's lower case version
***********************************************/
char StringUtils::toLower(char c)
{
	if (isAlpha(c))
	{
		if (alpha.size() < 1)
		{
			generateToLowerMap();
		}
		
		return alpha.find(c)->second;
	}

	return char();
	
}

/************************************************
* STRING UTILS :: Is Alpha
* Checks if a character is an alpha char
***********************************************/
bool StringUtils::isAlpha(char c)
{
	for (unsigned int i = 0; i < alphabet.size(); i++)
	{
		if (c == alphabet[i])
			return true;
	}

	return false;
}

