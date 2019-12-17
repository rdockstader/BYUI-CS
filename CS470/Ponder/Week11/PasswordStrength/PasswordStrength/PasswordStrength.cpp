/***********************************************************************
* Program:
*    Lab 11, Password Strength
*    Brother Wilson, CS470
* Author:
*    Ryan Dockstader
* Summary:
*    Please include a detailed description of:
*    1. What this program is designed to do
*    2. How this program will go about solving the problem
*    3. What assumptions about input (file or user) is made
*    4. Citations if the algorithm was borrowed or inspired from any source
************************************************************************/

// removed underscore from variables for style checker
// in my opinion this reduces readability.
#define ALPHALENGTH 26
#define NUMLENGTH 10
#define SPECLENGTH 32


#include <iostream>
#include <string>



char toUpper (char c);
char toLower (char c);
bool isNumber (char c);
bool isAlpha (char c);
long logTwo (long n);
long exp (long base, long exponent);
long getCombos (long length, long alphaSize);
long getBits (long combinations);

/******************************************************
 * MAIN
 * Main function of the program
 *****************************************************/
int main ()
{
   bool hasUpper = false,
      hasLower = false,
      hasNumber = false,
      hasSpecChar = false;
   long length = 0;
   long alphaSize = 0;
   std::string password = "";

   std::cout << "Please enter the password: ";
   std::cin >> password;

   length = password.length();
   for (long i = 0; i < length; i++)
   {
      char curChar = password[i];
      if (isNumber(curChar))
         hasNumber = true;
      else if (!isAlpha(curChar))
         hasSpecChar = true;
      else if (curChar == toUpper(curChar))
         hasUpper = true;
      else if (curChar == toLower(curChar))
         hasLower = true;
   }

   if (hasUpper)
      alphaSize += ALPHALENGTH;
   if (hasLower)
      alphaSize += ALPHALENGTH;
   if (hasSpecChar)
      alphaSize += SPECLENGTH;
   if (hasNumber)
      alphaSize += NUMLENGTH;

   long combos = getCombos(length, alphaSize);
   long bits = getBits(combos);
   std::cout << "There are " << combos << " combinations" << std::endl;
   std::cout << "That is equivalent to a key of ";
   std::cout << bits << " bits" << std::endl;

}

/******************************************************
 * GETCOMBOS
 * Returns the amount of combinations
 * of a given length and alphabet size
 *****************************************************/
long getCombos (long length, long alphaSize)
{
   return exp (alphaSize, length);
}

/******************************************************
 * GETCOMBOS
 * Returns the equivalent amount of bits
 * of the given amount of combinations
 *****************************************************/
long getBits (long combinations)
{
   return logTwo (combinations);
}

/******************************************************
 * EXP
 * Does exponential multiplication
 *****************************************************/
long exp(long base, long exponent)
{
   if (exponent < 2)
      return base;

   return base * exp (base, --exponent);
}

/******************************************************
 * LOGTWO
 * Does logarithmic division
 *****************************************************/
long logTwo (long n)
{
   long cycles = 0;
   while (n >= 2)
   {
      cycles++;
      n = n / 2;
   }
   return cycles;
}

/******************************************************
 * ISNUMBER
 * Returns if a character is a number
 *****************************************************/
bool isNumber (char c)
{
   return isdigit (c);
}

/******************************************************
 * ISALPHA
 * Returns if a character is an alphabet character
 *****************************************************/
bool isAlpha (char c)
{
   return isalpha (c);
}

/******************************************************
 * TOUPPER
 * Returns the uppercase equivalent of the
 * given character
 *****************************************************/
char toUpper (char c)
{
   switch (c)
   {
      case 'a':
      case 'A':
         return 'A';
      case 'b':
      case 'B':
         return 'B';
      case 'c':
      case 'C':
         return 'C';
      case 'd':
      case 'D':
         return 'D';
      case 'e':
      case 'E':
         return 'E';
      case 'f':
      case 'F':
         return 'F';
      case 'g':
      case 'G':
         return 'G';
      case 'h':
      case 'H':
         return 'H';
      case 'i':
      case 'I':
         return 'I';
      case 'j':
      case 'J':
         return 'J';
      case 'k':
      case 'K':
         return 'K';
      case 'l':
      case 'L':
         return 'L';
      case 'm':
      case 'M':
         return 'M';
      case 'n':
      case 'N':
         return 'N';
      case 'o':
      case 'O':
         return 'O';
      case 'p':
      case 'P':
         return 'P';
      case 'q':
      case 'Q':
         return 'Q';
      case 'r':
      case 'R':
         return 'R';
      case 's':
      case 'S':
         return 'S';
      case 't':
      case 'T':
         return 'T';
      case 'u':
      case 'U':
         return 'U';
      case 'v':
      case 'V':
         return 'V';
      case 'w':
      case 'W':
         return 'W';
      case 'x':
      case 'X':
         return 'X';
      case 'y':
      case 'Y':
         return 'Y';
      case 'z':
      case 'Z':
         return 'Z';
      default:
         return ' ';
   }
}

/******************************************************
 * TOLOWER
 * Returns the lowercase equivalent of the
 * given character
 *****************************************************/
char toLower (char c)
{
   switch (c)
   {
      case 'a':
      case 'A':
         return 'a';
      case 'b':
      case 'B':
         return 'b';
      case 'c':
      case 'C':
         return 'c';
      case 'd':
      case 'D':
         return 'd';
      case 'e':
      case 'E':
         return 'e';
      case 'f':
      case 'F':
         return 'f';
      case 'g':
      case 'G':
         return 'g';
      case 'h':
      case 'H':
         return 'h';
      case 'i':
      case 'I':
         return 'i';
      case 'j':
      case 'J':
         return 'j';
      case 'k':
      case 'K':
         return 'k';
      case 'l':
      case 'L':
         return 'l';
      case 'm':
      case 'M':
         return 'm';
      case 'n':
      case 'N':
         return 'n';
      case 'o':
      case 'O':
         return 'o';
      case 'p':
      case 'P':
         return 'p';
      case 'q':
      case 'Q':
         return 'q';
      case 'r':
      case 'R':
         return 'r';
      case 's':
      case 'S':
         return 's';
      case 't':
      case 'T':
         return 't';
      case 'u':
      case 'U':
         return 'u';
      case 'v':
      case 'V':
         return 'v';
      case 'w':
      case 'W':
         return 'w';
      case 'x':
      case 'X':
         return 'x';
      case 'y':
      case 'Y':
         return 'y';
      case 'z':
      case 'Z':
         return 'z';
      default:
         return ' ';
   }
}