/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Ryan Dockstader
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

#include "deque.h"     // for DEQUE
//#include <deque>
#include <string>
#include <vector>
#include <map>

/************************************************
* Appointment
* Holds the necessary data for an appointment
***********************************************/
struct Appointment
{
	std::string name;
	std::string cla;
	int minutes;
	bool isEmergency;

};

/************************************************
* NOW SERVING
* The interactive function allowing the user to
* handle help requests in the Linux lab
***********************************************/
class NowServing
{
public:
	void addImportantApp(Appointment app);
	void addRegularApp(Appointment app);
	void cycleMinute();
	void cycleCurrentApp();
	bool hasAppointment();
	void display();
	static Appointment createAppointment(std::string name, std::string cla, int minutes, bool isEmergency);
private:
	custom::deque<Appointment> deque;
	Appointment curApp;
};

/************************************************
* String Utils
* Functions that don't belong in the class
* above but were still necessary
***********************************************/
class StringUtils
{
public:
	static std::vector<std::string> parseString(std::string, char breakChar);
	static std::string toLower(std::string);
	static bool isAlpha(char c);
private:
	static char toLower(char);
	static void generateToLowerMap();
	static std::map<char, char> alpha;
	static std::string alphabet;
};



// the interactive nowServing program
void nowServing();

#endif // NOW_SERVING_H

