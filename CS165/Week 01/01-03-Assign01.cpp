/***********************************************************************
* Program:
*    Assignment 01, Genetic Genealogy       
*    Brother Alvey, CS165
* Author:
*    Ryan Dockstader
* Summary:
*    Takes a person genetic sequence, the amount of 
*	 relatives that person wants to enter
*    their names and sequences, and compares the sequences to each other.
*
*    Estimated:  2.0 hrs
*    Actual:     2.5 hrs
*		The most difficult part for me was the design. I felt that 
*		it'd make more sense to have all the functions
*		in a class structure, with the variables but shied 
*		away from that in the end since I wasn't sure it was a large
*		enough object to justify a full class structure. 
*		I settled somewhat in the middle, but after programming the entire
*		thing i wish I would have chosen to go with a class object structure 100%, 
*		and then called each function on the class.
*		It would have made a lot more sense then passing 
*		the same bits of information over and over. Also, getting connected to the
*		linux server was a bit of a pain point. I didn't include that in my 
*		overall time though, since it wasn't actual programming time.
************************************************************************/

#include <iostream>
#include <string>
using namespace std;


/**********************************************************************
*  Relative class
*  A class to make it easier to store the name, 
*  sequence and percentage related for a given Relative.
***********************************************************************/
class Relative 
{
   public:
      string name;
      string sequence;
      float percentageRelated;
};

/**********************************************************************
*  Get Sequence Function
*  gets the primary sequence, or a sequence without passing name
***********************************************************************/
string getSequence() 
{
   string sequence = "";
   cout << "Enter your DNA sequence: ";
   cin >> sequence;
   //Check length of sequence
   while (sequence.size() != 10) 
   {
      cout << "The Sequence you entered was not ";
      cout << "10 characters long. Please try again: " << endl;
      cin >> sequence;
   }
   return sequence;
}

/**********************************************************************
* get sequence Function
* overload function, gets the sequence for a Relative from the user
* , when the Relative has a name
***********************************************************************/
string getSequence(string name) 
{
   string sequence = "";
   cout << "Please enter the DNA sequence for " << name << ": ";
   cin >> sequence;
   //Check length of sequence
   while (sequence.size() != 10) 
   {
      cout << "The Sequence you entered was not ";
      cout << "10 characters long. Please try again: " << endl;
      cin >> sequence;
   }
   return sequence;
}

/**********************************************************************
*  Get Amount Relatives Function
*  Gets the user to enter the amount of potential relatives
***********************************************************************/
int getAmountRelatives() 
{
   int amount = 0;
   cout << "Enter the number of potential relatives: ";
   cin >> amount;
   cout << endl;
   return amount;
}

/**********************************************************************
*  Get relatives name Function
*  Asks the user for a name of each Relative
***********************************************************************/
void getRelativesNames(int amountRelatives, Relative (&relatives)[50]) 
{
   for (int i = 0; i < amountRelatives; i++) 
   {
      cout << "Please enter the name of relative #" << i+1 << ": ";
      cin >> relatives[i].name;
   }
   cout << endl;
}

/**********************************************************************
* Get Relatives Sequences Function
* Parses through an array to get a sequence for each Relative in that array
***********************************************************************/
void getRelativesSequences(int amountRelatives, Relative (&relatives)[50]) 
{
   for (int i = 0; i < amountRelatives; i++) 
   {
      relatives[i].sequence = getSequence(relatives[i].name);
   }
   cout << endl;
}

/**********************************************************************
* Determine Percentage Function
* Does the calculation on two strings, to determine how much the match.
***********************************************************************/
float determinePercentage(string s1, string s2) 
{
   float percentage = 0.00;
   int minSize = 0;
   int maxSize = 0;
   int matches = 0;
   if (s1.size() > s2.size()) 
   {
      minSize = s2.size();
      maxSize = s1.size();
   }
   else 
   {
      minSize = s1.size();
      maxSize = s2.size();
   }
   for (int i = 0; i < minSize; i++) 
   {
      if (s1[i] == s2[i]) 
      {
         matches++;
      }
   }
   return matches / (float)maxSize;
}

/**********************************************************************
* Get Relatives Percentages Function
* Moves through an array to calculate the percentage related of a DNA sequence
***********************************************************************/
void getRelativesPercentages(int amountRelatives
   , string baseSequence, Relative(&relatives)[50]) 
{
   for (int i = 0; i < amountRelatives; i++) 
   {
      relatives[i].percentageRelated = 
         determinePercentage(baseSequence, relatives[i].sequence);
   }
}

/**********************************************************************
* Display Relative Percentages Function
* Displays the Relative percentage match from an array of relatives.
***********************************************************************/
void displayRelativesPercentages(int amountRelatives
   , Relative(&relatives)[50]) 
{
   for (int i = 0; i < amountRelatives; i++) 
   {
      cout << "Percent match for " << relatives[i].name << ": ";
      cout << (int)(relatives[i].percentageRelated * 100) << "%" << endl;
   }
}

/**********************************************************************
* Main Function
* Gets input from user for sequences, relatives name and 
* sequences, and tells them a percentage match
***********************************************************************/
int main() 
{
   // Get sequence string from user of 10 characters
   string primarySequence = getSequence();
   //Get amount of potential relatives
   int amountRelatives = getAmountRelatives();
   // Get names for each potential relatives, 
   // and store them in an array of strings
   Relative relatives[50];
   getRelativesNames(amountRelatives, relatives);
   // Get relatives Sequences
   getRelativesSequences(amountRelatives, relatives);
   // Get percentage for the 10 character DNA marker for each Relative
   getRelativesPercentages(amountRelatives, primarySequence, relatives);
   // Display each potential Relative along with the percentage
   // of their sequence that matched the target user.
   displayRelativesPercentages(amountRelatives, relatives);
   return 0;
}