/***********************************************************************
* Program:
*    Assignment 03, Digital Forensics w/ Corrupt Files  
*    Brother Alvey, CS165
* Author:
*    Ryan Dockstader
* Summary: 
*    A program to read digital log files, scan through the program to
*    identify users who accessed files in a particular window of time.
*    The program will ignore any corrupt log lines, but still return 
*    valid entries
*
*    Estimated:  4.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

/**********************************************************************
* STRUCT: AccessRecord
* PURPOSE: Stores data for an access record
***********************************************************************/
struct AccessRecord
{
   string userName;
   string fileName;
   long timeStamp;
};

/**********************************************************************
* STRUCT: AccessRecord
* PURPOSE: Stores data for a date range
***********************************************************************/
struct DateRange
{
   long startDate;
   long endDate;
};

/**********************************************************************
* FUNCTION: promptFilePath
* PURPOSE: Prompts the user for the filepath.
***********************************************************************/
string promptFilePath()
{
   string path;
   cout << "Enter the access record file: ";
   cin >> path;
   return path;
}

/**********************************************************************
* FUNCTION: promptTimes
* PURPOSE: Prompts the user for the start and end time.
***********************************************************************/
DateRange promptTimes()
{
   DateRange dr;
   cout << "Enter the start time: ";
   cin >> dr.startDate;
   cout << "Enter the end time: ";
   cin >> dr.endDate;
   return dr;
}

/**********************************************************************
* FUNCTION: displayAccessRecords
* PURPOSE: displays all access records for a passed array
***********************************************************************/
void displayAccessRecords(const AccessRecord(&ar)[500])
{
   const int LINE_LENGTH = 19;
   cout << "The following records match your criteria:" << endl;
   cout << endl;
   cout << "      Timestamp" << " " << "               File";
   cout << " " << "               User" << endl;
   cout << "--------------- ------------------- -------------------" << endl;
   for (int i = 0; i < 500; i++)
   {
      if (ar[i].timeStamp > 0 && ar[i].fileName.size() > 0 
         && ar[i].userName.size() > 0)
      {
         cout << "     " << ar[i].timeStamp << " ";
         for (int j = 0; j < (LINE_LENGTH - ar[i].fileName.size()); j++)
         {
            cout << " ";
         }
         cout << ar[i].fileName << " ";
         for (int j = 0; j < (LINE_LENGTH - ar[i].userName.size()); j++)
         {
            cout << " ";
         }
         cout << ar[i].userName << endl;
      }
   }
   cout << "End of records" << endl;
}

/**********************************************************************
* FUNCTION: displayAccessRecords
* PURPOSE: displays all access records for a passed array
***********************************************************************/
AccessRecord parseLine (string line) throw (string)
{
   AccessRecord ar;
   //Convert the line to a string stream
   stringstream ss;
   ss.str(line);
   //Read in filename
   ss >> ar.fileName;
   if (ss.fail())
      throw string("no filename on line");
   //Read in username
   ss >> ar.userName;
   if (ss.fail())
      throw string("no username on line");
   //Read in Timestamp
   ss >> ar.timeStamp;
   if (ss.fail())
      throw string("Timestamp is invalid/not found");
   if (ar.timeStamp < 1000000000)
      throw string("Timestamp is not long enough");
   if (ar.timeStamp > 10000000000)
      throw string("Timestamp is too long");
   return ar;
}

/**********************************************************************
* FUNCTION: displayAccessRecords
* PURPOSE: displays all access records for a passed array
***********************************************************************/
void parseFile(string fileName, AccessRecord(&ar)[500])
{
   //Read in access records from file;
   ifstream inputFileStream;
   inputFileStream.open(fileName.c_str());
   string line;
   int i = 0;
   while (getline(inputFileStream, line))
   {
      try
      {
         ar[i] = parseLine(line);
         i++;
      }
      catch (string err)
      {
         cout << "Error parsing line: " << line << endl;
      }	
   }
}

/**********************************************************************
* FUNCTION: Main
* PURPOSE: Reads in a the logs, prompts for a start and
* end date and then lists all files accessed and
* which user accessed them.
***********************************************************************/
int main()
{
   //Create Access record array
   AccessRecord allAccessRecords[500];
   //Prompt user for Filename
   string filePath = promptFilePath();
   //Read in file
   parseFile(filePath, allAccessRecords);
   cout << endl;
   //Prompt for start and end time
   DateRange range = promptTimes();
   cout << endl;
   //Find and display all access records in time frame.
   AccessRecord matchedRecords[500];
   int count = 0;
   for (int i = 0; i < 500; i++)
   {
      if (allAccessRecords[i].timeStamp >= range.startDate
         && allAccessRecords[i].timeStamp <= range.endDate)
      {
         matchedRecords[count] = allAccessRecords[i];
         count++;
      }
   }
   displayAccessRecords(matchedRecords);
   return 0;
}
