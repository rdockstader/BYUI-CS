/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <map>		   // for MAP
#include "stack.h"     // for STACK
using namespace std;

/*****************************************************
* IS DIGIT
* check if character is a digit
*****************************************************/
bool isDigit(char c)
{
	return ('0' <= c && c <= '9');
}
/*****************************************************
* IS ALPHA
* check if character is a character
*****************************************************/
bool isAlpha(char c)
{
	static string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < alpha.size(); i++)
	{
		if (c == alpha[i])
			return true;
	}

	return false;
}
/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   //variables
   string postfix = " ";
   int postfixPos = 0;
   custom::stack<char> stack;
   //create order of oprations map
   map<char, int> orderOfOps;
   orderOfOps['-'] = 1;
   orderOfOps['+'] = 1;
   orderOfOps['/'] = 2;
   orderOfOps['*'] = 2;
   orderOfOps['^'] = 3;
   orderOfOps['('] = 0;
   orderOfOps[')'] = 0;
   // for each infix character
   for(int i = 0; i < infix.size();)
   {
	   //check for space
	   if (infix[i] == ' ')
	   {
	      i++;
		  //check if previous character was apce
		  if (postfix[postfixPos] != ' ')
		  {
			  // if not, put a space.
			  postfix += ' ';
			  postfixPos++;
		  }	
	   }
	   // check if digit, alpha, or .
	   else if(isDigit(infix[i]) || isAlpha(infix[i]) || infix[i] == '.')
	   { 
		  //add to output
	      postfix += infix[i++];
		  postfixPos++;
	   }
	   // check for begin paren
	   else if (infix[i] == '(')
	   {
		  // if found push on stack
		  stack.push(infix[i++]);
	   }
	   // check for end paren
	   else if (infix[i] == ')')
	   {
	      while (stack.top() != '(')
		  {
			  // conditionally add a space
			  if (postfix[postfixPos] != ' ')
			  {
				  postfix += ' ';
				  postfixPos++;
			  }
			  // add operators until we hit begin paren
		     postfix += stack.top();
			 postfixPos++;
			 stack.pop();
		  }
		  // remove begin paren and iterate
		  stack.pop();
		  i++;
	   }
	   else
	   {
		  // if we have an operator, check if it's of a higher order
	      while (!stack.empty() && orderOfOps.find(infix[i])->second <= orderOfOps.find(stack.top())->second)
		  {
			  // conditionally add a space
			  if (postfix[postfixPos] != ' ')
			  {
				  postfix += ' ';
				  postfixPos++;
			  }
			 // add operator to postfix
		     postfix += stack.top();
			 postfixPos++;
			 stack.pop();
		  }
		  // add new operator to the stack.
		  stack.push(infix[i++]);
		  // conditionally add a space.
		  if (postfix[postfixPos] != ' ')
		  {
			  postfix += ' ';
			  postfixPos++;
		  }
	   }
   }
   // if we have any operators left, add them too.
   while (!stack.empty())
   {
	   postfix += ' ';
	   postfix += stack.top();
	   postfixPos++;
	   stack.pop();
   }
   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   // Setup initial variables
   string assembly;
   char   rhs = 0;
   char   lhs = 0;
   char   variable = 'A';
   custom::stack <char> sAssembly;

   // Loop through our postfix string passed to our function
   for (int i = 0; i < postfix.size(); i++)
   {
	   // Check if we encounter a number or a space
	   if (isdigit(postfix[i]) || isspace(postfix[i]))
	   {
		   // ignore the space
		   if (!isspace(postfix[i]))
			   sAssembly.push(postfix[i]);
	   }
	   else // we encounrtered punctuation
	   {
		   try
		   {
			   rhs = sAssembly.top();
		   }
		   catch (const char * error) { cout << error << endl; }

		   sAssembly.pop();  // Remove the top element of our stack

		   try
		   {
			   lhs = sAssembly.top();
		   }
		   catch (const char * error) { cout << error << endl; }

		   sAssembly.pop(); // Remove the second top element of our stack

							// Check if the "lhs" contains a variable or a number
		   if (!isalpha(lhs))
		   {
			   assembly += "LOD ";
			   assembly += lhs;
			   assembly += '\n';
		   }
		   else
		   {
			   assembly += "SET ";
			   assembly += lhs;
			   assembly += '\n';

		   }

		   // convert punction to assembly commands
		   switch (postfix[i])
		   {
		   case '+':
			   assembly += "ADD ";
			   break;
		   case '-':
			   assembly += "SUB ";
			   break;
		   case '*':
			   assembly += "MUL ";
			   break;
		   case '/':
			   assembly += "DIV ";
			   break;
		   case '%':
			   assembly += "MOD ";
			   break;
		   case '^':
			   assembly += "EXP ";
			   break;
		   default:
			   break;
		   }

		   assembly += rhs;
		   assembly += '\n';
		   assembly += "SAV ";
		   assembly += variable;
		   assembly += '\n';

		   sAssembly.push(variable++); // Increment our variable name (A -> B -> C ... -> X)
	   }
   }
   assembly += '\n';
   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
