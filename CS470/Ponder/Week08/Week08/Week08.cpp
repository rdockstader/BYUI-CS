/***********************************************************************
* Program:
*    Lab 08, Vulnerabilities and Exploits
*    Brother Wilson, CS470
* Author:
*    Ryan Dockstader
* Summary: 
*    This program is designed to demonstrate memory injection vulnerabilities.
*
************************************************************************/

#include <iostream>
#include <cassert>
using namespace std;

void stackExploit();
void heapExploit();
void arrayExploit();
void intExploit();
void arcExploit();
void subterfugeExploit();
void vtableExploit();
void ansiExploit();

/******************************************************
 * MAIN
 * This function take you to the various exploits
 *****************************************************/
int main()
{
   // prompt
   cout << "  1. Array index\n"
        << "  2. Pointer subterfuge\n"
        << "  3. ARC injection\n"
        << "  4. VTable spraying\n"
        << "  5. Stack smashing\n"
        << "  6. Heap spraying\n"
        << "  7. Integer overflow\n"
        << "  8. ANSI-Unicode conversion\n"
        << "> ";
   int select;
   cin >> select;

   switch (select)
   {
      case 1:
         arrayExploit();
         break;
      case 2:
         subterfugeExploit();
         break;
      case 3:
         arcExploit();
         break;
      case 4:
         vtableExploit();
         break;
      case 5:
         stackExploit();
         break;
      case 6:
         heapExploit();
         break;
      case 7:
         intExploit();
         break;
      case 8:
         ansiExploit();
         break;
      default:
         cout << "Unknown option " << select << endl;
   }

   return 0;
}

/**************************************************************
 **************************************************************
 *******************    SUBTERFUGE    *************************
 **************************************************************
 **************************************************************/

/****************************************
 * Pointer Subterfuge Vulnerability
 * 1. There must be a pointer used in the code.
 * 2. There must be a way to overwrite the pointer
 * 3. After the pointer is overwritten, the pointer is dereferenced
 ****************************************/
void subterfugeVulnerability(long * array, int size)
{
   long int buffer[2] = {0, 1};
   const char * message = "All is safe; nothing bad happened\n";  // 1. Pointer

   for (int i = 0; i < size; i++)  // 2. Overwrite
      buffer[i] = array[i];

   cout << message;                // 3. Dereference
   
}

/****************************************
 * Pointer Subterfuge Exploitation
 * 1. The attacker must exploit a vulnerability allowing
 *    unintended access to the pointer
 * 2. The attacker must be able to provide a new pointer
 *    referring to data altering the normal flow of the program
 ****************************************/
void subterfugeExploit()
{
   // an attacker's array
   long int array[3] =             // 1. Exploit
   {
      0,
      1,
      (long int)"!!!!!!!!!!!!! You've been hacked !!!!!!!!!!!!!\n"
      // 2. Provide pointer
   };

   // exploit it
   subterfugeVulnerability(array, 3);   
}

/**************************************************************
 **************************************************************
 ********************     ARRAY      **************************
 **************************************************************
 **************************************************************/

/*************************************
 * ARRAY VULNERABILTY
 * 1. There must be an array and an array index variable
 * 2. The array index variable must be reachable through external input.
 * 3. There must not be bounds checking on the array index variable.
 ************************************/
void arrayVulnerability(long* passedArray, int size)
{
	long array[4];
	const char * authenticated = "Not Authenticated";

	for (int i = 0; i < size; i++)
	{
		array[i] = passedArray[i];
	}

	cout << authenticated << endl;

}

/**************************************
 * ARRAY EXPLOIT
 * 1. The attacker provides an array index value outside the expected range
 * 2. The attacker must be able to provide input or redirect
 *    existing input into the array at the index he provided
 * 3. The injected value must alter program state in a way
 *    that is desirable to the attacker
 *************************************/
void arrayExploit()
{
	long attackArray[5] =
	{
		0,
		0,
		0,
		0,
		(long)"Authenticated",
	};

	arrayVulnerability(attackArray, 5);
}

/**************************************************************
 **************************************************************
 ********************      ARC       **************************
 **************************************************************
 **************************************************************/

void DisplayFGrade()
{
	cout << "Grade: F" << endl;
}

void DisplayAGrade()
{
	cout << "Grade: A" << endl;
}

/*********************************
 * ARC VULNERABILITY
 * 1. There must be a function pointer used in the code.
 * 2. Through some vulnerability, there must be a way for user input
 *    to overwrite the function pointer. This typically happens through
 *    a stack buffer vulnerability.
 * 3. After the memory is overwritten, the function pointer must
 *    be dereferenced
 ********************************/
void arcVulnerability(long* array, int size)
{
	long int buffer[2] = { 0, 1 };
	void (*func)() = DisplayFGrade;  // 1. Pointer

	for (int i = 0; i < size; i++)  // 2. Overwrite
		buffer[i] = array[i];

	func();              // 3. Dereference
}

/*********************************
 * ARC EXPLOIT
 * 1. The attacker must exploit a vulnerability allowing
 *    unintended access to the function pointer
 * 2. The attacker must have the address to another function
 *    which is to be used to replace the existing function pointer
  ********************************/
void arcExploit()
{
	void (*func)() = DisplayAGrade;
	// an attacker's array
	long int array[3] =             // 1. Exploit
	{
	   0,
	   1,
	   (long int)func
	   // 2. Provide pointer
	};

	// exploit it
	arcVulnerability(array, 3);
}

/**************************************************************
 **************************************************************
 ********************     VTABLE     **************************
 **************************************************************
 **************************************************************/

/***********************************
 * VULNERABILITY
 * 1. The vulnerable class must be polymorphic.
 * 2. The class must have a buffer as a member variable.
 * 3. Through some vulnerability, there must be a way for user input
 *    to overwrite parts of the VTable.
 * 4. After a virtual function pointer is overwritten,
 *    the virtual function must be called.
 **********************************/
class Vulnerability
{
public:
	virtual void safe() = 0;
};

class Authenticate : public Vulnerability
{
public:
	virtual void safe()
	{
		cout << "You have been authenticated" << endl;
	}
};
class Hacker : public Vulnerability
{
public:
	virtual void safe()
	{
		cout << "Got your password!!" << endl;
	}
};

void vtableVulnerability(long* array, int size)
{
	long buffer[2] = { 0, 1 };
	Vulnerability* p = new Authenticate();

	for (int i = 0; i < size; ++i)
	{
		buffer[i] = array[i];
	}
	p->safe();
}


/************************************
 * VTABLE EXPLOIT
 * 1. Through some vulnerability, the VTable pointer
 *     or a function pointer within the VTable must be overwritten
 * 2. The attacker must have the address to another VTable pointer
 *     or a function pointer
 ***********************************/
void vtableExploit()
{
	Vulnerability* p = new Hacker();
	long array[3]{ 0, 1, (long)p };
	vtableVulnerability(array, 3);
}


/**************************************************************
 **************************************************************
 ********************    STACK       **************************
 **************************************************************
 **************************************************************/

void rightFunc()
{
	cout << "We got the right function, it's all good." << endl;
}

void wrongFunc()
{
	cout << "Oops, I stole your function address" << endl;
}


/***********************************************
 * STACK VULNERABILITY
 * 1. There must be a buffer on the stack
 * 2. the buffer must be reachable from an external input
 * 3. The mechanism to fill the buffer must not check the correct buffersize
 **********************************************/
void stackVulnerability(long* array, int size)
{
	long buffer[2] = { 0, 1 };
	void (*p)() = rightFunc;
	for (int i = 0; i < size; ++i)
	{
		buffer[i] = array[i];
	}
	p();
}

/*********************************************
 * STACK EXPLOIT
 * 1. The attacker must provide more data into the
 *    outwardly facing buffer than the buffer is designed to hold
 * 2. The attacker must know where the the stack pointer resides
 *    on the stack. This should be just beyond the end of the buffer
 * 3. The attacker must insert machine language instructions in the buffer.
 *    This may occur before, after, or even around the stack pointer. The
 *    machine language could be already compiled code in the program
 * 4. The attacker must overwrite the stack pointer. The old value,
 *    directing the flow of the program after the function is returned,
 *    must be changed from the calling function to the provided
 *    machine language in step 3.
 *********************************************/
void stackExploit()
{
	void (*p)() = wrongFunc;
	long array[3] = { 1, 2, (long int)p };
	stackVulnerability(array, 3);
}

/**************************************************************
 **************************************************************
 ********************      HEAP      **************************
 **************************************************************
 **************************************************************/


/*************************************
 * HEAP VULNERABILITY
 * 1. There must be two adjacent heap buffers.
 * 2. The first buffer must be reachable through external input.
 * 3. The mechanism to fill the buffer from the external input must
 *    not correctly check for the buffer size.
 * 4. The second buffer must be released before the first.
 *************************************/
void heapVulnerability(char * input)
{
	char* buffer1 = new char[4]; // requires two buffers on the heap 
	char * buffer2 = new char[4]; 
	buffer1 = input;
	delete [] buffer2; // need to delete second buffer first 
	delete [] buffer1;
}

/*************************************
 * HEAP EXPLOIT
 * 1. The attacker must provide more data into the outwardly facing
 *    heap buffer than the buffer is designed to hold
 * 2. The attacker must know the layout of the Memory Control Block (MCB)
 *    (essentially a linked list) residing just after the buffer
 * 3. The attacker must provide a new MCB containing both the location
 *    of the memory overwrite and the new data to be overwritten
 ***********************************/
void heapExploit()
{
	char str[] = "goodBAD";
	heapVulnerability(str);
}


/**************************************************************
 **************************************************************
 *******************    INTEGER      **************************
 **************************************************************
 **************************************************************/

/********************************************
 * INTEGER VULNERABILITY
 * 1. There must be a security check represented by an expression.
 * 2. The expression must have the potential for overflow.
 * 3. At least one of the numbers used to compute the sentinel
 *    must be reachable through external input.
 *********************************************/
void intVulnerability(int offset, int input)
{
	int buffer[256];
	int* sentinel = buffer + 256;

	if (offset + buffer < sentinel)
	{	
		buffer[offset] = input;
		cout << "buffer at offset is set" << endl;
	}
	else
		cout << "Invalid offset" << endl;

}

/**********************************************
 * INTEGER EXPLOIT
 * 1. Provide input, either a buffer size or a single value,
 *    that is directly or indirectly used in the vulnerable expression
 * 2. The input must exceed the valid bounds of the data-type,
 *    resulting in an overflow or underflow condition
 **********************************************/
void intExploit()
{
	// doesn't work
	// intVulnerability(515, 1);
	// works
	intVulnerability(2147483648, 1);
}


/**************************************************************
 **************************************************************
 ******************    ANSI-Unicode    ************************
 **************************************************************
 **************************************************************/

/*********************************************************
 * ANSI - UNICODE VULNERABILITY
 * 1. There must be a buffer where the basetype is greater than one.
 * 2. Validation of the buffer must check the size of the buffer
 *    rather than the number of elements in the buffer.
 ********************************************************/
void ansiVulnerability(long*text)
{
	long unicodeText[4];
	const char* message = "You can always trust user input.";

	for (int i = 0; i < sizeof(text); i++)
	{
		unicodeText[i] = text[i];
	}

	cout << message << endl;
}

/***********************************************
 * ASCI - UNICODE EXPLOIT
 * 1. The attacker must provide more than half as much data
 *    into the outwardly facing buffer as it is designed to hold
 **********************************************/
void ansiExploit()
{
	long unicodeText1[5] = { 44, 79, 78, 45, (long) & "You're living in a dream world..." };

	ansiVulnerability(unicodeText1);
}
