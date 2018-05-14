/***********************************************************************
* Program:
*    Assignment 02, Digital Forensics        
*    Brother Alvey, CS165
* Author:
*    Ryan Dockstader
* Summary: 
*    A program to scan through the system logs for the ACME Widget
*    Corporation, to assist with a recent digital security
*    breach. It reads in a the logs, prompts for a start and
*    end date and then lists all files accessed and 
*    which user accessed them.
*
*    Estimated:  4.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
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
void displayAccessRecords(const AccessRecord (&ar)[500])
{
   const int LINE_LENGTH = 19;
   cout << "The following records match your criteria:" << endl;
   cout << endl;
   cout << "      Timestamp" << " " << "               File";
   cout << " " << "               User" << endl;
   cout << "--------------- ------------------- -------------------" << endl;
   for (int i = 0; i < 500; i++)
   {
      if (ar[i].timeStamp > 0 && ar[i].fileName.size() > 0 && ar[i].userName.size() > 0)
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
   cout << endl;
   //Read in access records from file;
   ifstream inputFileStream;
   inputFileStream.open(filePath.c_str());
   string word;
   int i = 0;
   while (inputFileStream >> word)
   {
      allAccessRecords[i].fileName = word;
      inputFileStream >> allAccessRecords[i].userName;
      inputFileStream >> allAccessRecords[i].timeStamp;
      i++;
   }
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

   //char dummy;
   //cin >> dummy;

   return 0;
}
