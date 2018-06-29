#include "wholeNumber.h"

#include <iostream>
#include <iomanip>
#include "list.h"
//#include <list>  // for testing
#include <stack>
#include <vector>
#include <cassert>
#include <sstream>
#include <cstdlib>

namespace custom {

	/******************************************************************************
	* WHOLENUMBER() - Non Default Constructor
	******************************************************************************/
	WholeNumber::WholeNumber(unsigned int num)
	{
		std::string n2 = std::to_string(num);
		n2.insert(n2.begin(), (2 - ((n2.length() - 1) % 3)), '0');

		for (int i = 0; i < n2.length() - 1; i += 3)
		{
			int tempNum = std::stoi(n2.substr(i, 3));
			digits.push_front(tempNum);
		}
	}

	/******************************************************************************
	* WHOLENUMBER() - Copy Constructor
	******************************************************************************/
	WholeNumber::WholeNumber(const WholeNumber & rhs) throw (const char *)
	{
		//for (custom::list<int> :: const_iterator it = rhs.digits.cbegin(); it != rhs.digits.cend(); ++it)
		for (custom::list<int> ::const_iterator it = rhs.digits.cbegin(); it != rhs.digits.cend(); ++it)
		{
			this->digits.push_back(*it);
		}
	}

	WholeNumber & WholeNumber :: operator () (unsigned int num)
	{
		std::string n2 = std::to_string(num);
		n2.insert(n2.begin(), (2 - ((n2.length() - 1) % 3)), '0');

		for (int i = 0; i < n2.length() - 1; i += 3)
		{
			int tempNum = std::stoi(n2.substr(i, 3));
			this->digits.push_back(tempNum);
		}

		return *this;
	}

	/******************************************************************************
	* Assignemnt operator
	******************************************************************************/
	WholeNumber & WholeNumber :: operator = (WholeNumber & rhs) throw (const char *)
	{
		this->digits.clear();
		assert(this->digits.empty());

		this->digits = rhs.digits;

		return *this;
	}

	/******************************************************************************
	* Add-onto operator
	******************************************************************************/
	WholeNumber & WholeNumber :: operator += (WholeNumber rhs) throw (const char *)
	{
		bool carry = false;
		int carryValue = 0;

		// setup our iterators
		custom::list<int> ::iterator thisIt = this->digits.begin();
		custom::list<int> ::iterator rhsIt = rhs.digits.begin();

		// make both list's the same size:
		while (this->size() < rhs.size())
		{
			this->digits.push_back(0);
		}

		while (rhs.size() < this->size())
		{
			rhs.digits.push_back(0);
		}

		// Verify they are the same size;
		assert(this->size() == rhs.size());

		for (int i = 0; i < this->size(); i++)
		{
			if (carry)
			{
				if (i == this->size())
				{
					this->digits.push_back(carryValue);
					break;
				}

				*thisIt = *thisIt + carryValue;
				carry = false;
				carryValue = 0;
			}

			int tempNum = *thisIt + *rhsIt;

			if (tempNum > 999)
			{
				*thisIt = tempNum - 1000;

				carry = true;
				carryValue = 1;

				if (i + 1 == this->size())
				{
					this->digits.push_back(carryValue);
					carry = false;
					carryValue = 0;
					break;
				}
			}
			else
			{
				*thisIt = tempNum;
				carry = false;
			}

			++thisIt;
			++rhsIt;
		}

		return *this;
	}

	/******************************************************************************
	* Subtraction operator
	******************************************************************************/
	WholeNumber & WholeNumber :: operator - (WholeNumber rhs) throw (const char *)
	{
		//bool borrow = false;
		//int borrowValue = 0;
		WholeNumber tempNumber;
		// make both list's the same size:
		while (this->size() < rhs.size())
		{
			this->digits.push_back(0);

		}

		while (rhs.size() < this->size())
		{
			rhs.digits.push_back(0);
		}

		while (tempNumber.size() < rhs.size())
		{
			tempNumber.digits.push_back(0);
		}
		// Verify they are the same size;
		assert(this->size() == rhs.size());

		// setup our iterators
		custom::list<int> ::reverse_iterator thisIt = this->digits.rbegin();
		custom::list<int> ::reverse_iterator rhsIt = rhs.digits.rbegin();
		custom::list<int> ::reverse_iterator tempIt = tempNumber.digits.rbegin();

		if (*thisIt < *rhsIt)
			throw "ERROR: lhs must be greater than rhs";

		for (int i = 1; i <= this->size(); i++)
		{
			int tempNum = *thisIt - *rhsIt;

			if (tempNum < 0 && i != 1) // Possible negative number
			{
				// loop through previous iterations to see if where we can borrow
				custom::list<int> ::reverse_iterator placeholder = tempIt;
				if (tempNum < 0) // we need to borrow
				{
					--placeholder;
					bool barrow = false;
					do
					{
						if (*placeholder > 0) // we can borrow;
						{
							barrow = true;
							*placeholder = *placeholder - 1; // borrow 1
															 //++placeholder; // move back
							if (placeholder == tempIt)
							{
								tempNum = tempNum + 1000;
							}
							else
							{
								++placeholder;
								*placeholder = *placeholder + 1000;
							}
						}
						else
						{
							--placeholder; // keep looking
						}
					} while (tempNum < 0);
				}
				*tempIt = tempNum;
			}
			else
			{
				*tempIt = tempNum;
			}
			++thisIt;
			++rhsIt;
			++tempIt;
		}

		*this = tempNumber;

		// clean up nodes
		custom::list<int> ::iterator it = this->digits.end();
		--it;
		do
		{
			//cout << *it << endl;
			if (!*it)
				this->digits.erase(it);
			else
				break;
			--it;
		} while (it != this->digits.begin());
		return *this;
	}

	/******************************************************************************
	* Multiplication operator
	******************************************************************************/
	WholeNumber & WholeNumber :: operator *  (WholeNumber rhs) throw (const char *)
	{
		//WholeNumber tempNumber;

		custom::list<int> ::iterator thisIt = this->digits.begin();
		custom::list<int> ::iterator rhsIt = rhs.digits.begin();

		std::vector<WholeNumber> tempNumbers;
		WholeNumber storage;

		// Loop through the bottom row
		for (int rhsI = 0; rhsI < rhs.size(); rhsI++)
		{
			// Loop through the top row
			for (int thisI = 0; thisI < this->size(); thisI++)
			{
				// Calculate leading zeros
				storage.digits.clear();
				for (int i = 0; i < rhsI + thisI; i++)
					storage.digits.push_front(0);

				// Multiply our two nodes
				int tempNum = *thisIt * *rhsIt;

				// Convert our int to a whole number
				WholeNumber temp(tempNum);

				// Loop through our whole number one node at a time and push that to our storage
				for (custom::list<int> ::iterator it = temp.digits.begin(); it != temp.digits.end(); it++)
					storage.digits.push_back(*it);

				// Save our storage to a vector to be added later
				tempNumbers.push_back(storage);

				// Clear our storage
				storage.digits.clear();

				// Increment the top row iterator
				++thisIt;
			}

			// Set the top row iterator back to the beginning of the row
			thisIt = this->digits.begin();

			// Increment our bottom row
			++rhsIt;
		}

		// A whole number to add up our final value into
		WholeNumber finalValue;

		// Save the size of our vector to be used in a loop
		unsigned long loopValue = tempNumbers.size();

		// Loop through our vector and += each value in the vector
		for (int i = 0; i < loopValue; i++)
		{
			finalValue += tempNumbers.back();
			tempNumbers.pop_back();
		}

		// Save our final value to this
		*this = finalValue;

		// clean up nodes used to erase empty nodes before the number starts
		custom::list<int> ::iterator it = this->digits.end();
		--it;
		do
		{
			//cout << *it << endl;
			if (!*it)
				this->digits.erase(it);
			else
				break;
			--it;
		} while (it != this->digits.begin());

		return *this;
	}

	/******************************************************************************
	* OPERATOR : <<
	******************************************************************************/
	std::ostream & operator << (std::ostream & out, WholeNumber & t)
	{
		int count = 0;
		//custom::cout << (t.sign ? "-" : "");
		for (custom::list<int> ::reverse_iterator it = t.digits.rbegin(); it != t.digits.rend(); ++it)
		{
			if (count != 0)
				out << std::setfill('0') << std::setw(3) << *it;
			else
				out << *it;

			if (t.size() != count + 1)
				out << ",";
			count++;
		}
		return out;
	}

	/******************************************************************************
	* OPERATOR : >>
	******************************************************************************/
	std::istream & operator >> (std::istream & in, WholeNumber & t)
	{
		unsigned int num;
		in >> num;
		WholeNumber n2(num);
		t = n2;
		return in;
	}

	/******************************************************************************
	* DISPLAY()
	*    Used for debugging
	******************************************************************************/
	void WholeNumber::display()
	{
		std::cout << "Size     : " << size() << std::endl;
		std::cout << "Data     : ";
		for (custom::list<int> ::iterator it = digits.begin(); it != digits.end(); ++it)
		{
			std::cout << "[" << *it << "]";
		}
		std::cout << std::endl;
	}
}