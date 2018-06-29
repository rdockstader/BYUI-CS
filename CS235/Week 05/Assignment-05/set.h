/***********************************************************************
* Header:
*    set
* Summary:
*    This class contains the notion of an set: a bucket to hold
*    data for the user. This is similar to array, but is size aware
*	  and can expand dynamically
*
*    This will contain the class definition of:
*       set             : similar to std::set
*       set :: iterator : an iterator through the set
* Author
*    Ryan Dockstader & Br. Helfrich
************************************************************************/

#ifndef set_H
#define set_H

#include <cassert>  // because I am paranoid
#include <iostream>
#include <vector>
#include <string>

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

	/************************************************
	* set
	* A class that holds stuff
	***********************************************/
	template <class T>
	class set
	{
	public:
		// constructors
		set() { numElements = 0; numCapacity = 0; data = new T[0]; }
		set(int num) throw (const char *);
		set(const set & rhs) throw (const char *);
		// destructor
		~set() { delete[] data; data = NULL; }
		// assignment
		set & operator = (const set & rhs) throw (const char *);
		// Iterators
		class iterator;
		class const_iterator;
		// Standard structure ops
		int  size()     const { return numElements; }
		bool empty() { return (numElements == 0) ? true : false; }
		void clear();
		//set ops
		iterator find(T value) const
		{
			int i = findIndex(value, 0, numElements);
			if (i == -1)
				return end();
			return iterator(&data[i]);
		}
		void insert(T value);
		void erase(iterator it)
		{
			int index = findIndex(*it, 0, numElements - 1);
			if (index >= 0 && it != end())
			{
				// Move it, move it.
				for (int i = index; i < numElements - 1; i++)
				{
					data[i] = data[i + 1];
				}
				numElements--;
			}
		}
		set operator || (const set & rhs) const throw (const char *)
		{
			set<T> returnSet(rhs);
			for (int i = 0; i < this->numElements; i++)
			{
				returnSet.insert(data[i]);
			}
			return returnSet;
		}
		set operator && (const set & rhs) const throw (const char *)
		{
			set<T> returnSet;
			for (int i = 0; i < this->numElements; i++)
			{
				if(rhs.findIndex(data[i], 0, rhs.numElements) != -1)
					returnSet.insert(data[i]);
			}
			return returnSet;
		}
		set operator - (const set & rhs) const throw (const char *)
		{
			set<T> returnSet(*this);
			for (int i = 0; i < returnSet.numElements; i++)
			{
				if (rhs.findIndex(returnSet.data[i], 0, rhs.numElements) != -1)
					returnSet.erase(returnSet.find(data[i]));
			}
			return returnSet;
		}


		// iterator functions
		iterator begin() { return iterator(data); }
		iterator end() const;
		iterator const cbegin() const { return iterator(data); }
		iterator const cend() const;

	private:
		T * data;              // dynamically allocated set of T 
		int numElements;       // number of elements
		int numCapacity;		  // curretn capacity

		int findIndex(T target, int begin, int end) const;
		void resize(int newCapacity) throw (const char *);
	};

	/**************************************************
	* set ITERATOR
	* An iterator through set
	*************************************************/
	template <class T>
	class set <T> ::iterator
	{
	public:
		// constructors
		iterator() : p(NULL) {              }
		iterator(T * p) : p(p) {              }
		iterator(const iterator & rhs) { *this = rhs; }
		// operator=
		iterator & operator = (const iterator & rhs)
		{
			this->p = rhs.p;
			return *this;
		}

		// operator!=
		bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
		// operator==
		bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

		// operator*
		T & operator * () { return *p; }
		const T & operator * () const { return *p; }

		// opeartor ++ 
		iterator & operator ++ ()
		{
			p++;
			return *this;
		}

		// postfix increment
		iterator operator ++ (int postfix)
		{
			iterator tmp(*this);
			p++;
			return tmp;
		}
		// opeartor --
		iterator & operator -- ()
		{
			p--;
			return *this;
		}

		// postfix increment
		iterator operator -- (int postfix)
		{
			iterator tmp(*this);
			p--;
			return tmp;
		}

	private:
		T * p;
	};

	/**************************************************
	* set CONST ITERATOR
	* An const iterator through set
	*************************************************/
	template <class T>
	class set <T> ::const_iterator
	{
	public:
		// constructors
		const_iterator() : p(NULL) {              }
		const_iterator(T * p) : p(p) {              }
		const_iterator(const iterator & rhs) { *this = rhs; }
		// operator=
		const_iterator & operator = (const iterator & rhs)
		{
			this->p = rhs.p;
			return *this;
		}

		// operator!=
		bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
		// operator==
		bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

		// operator*
		T & operator * () { return *p; }
		const T & operator * () const { return *p; }

		// opeartor ++ 
		iterator & operator ++ ()
		{
			p++;
			return *this;
		}


		// postfix increment
		iterator operator ++ (int postfix)
		{
			iterator tmp(*this);
			p++;
			return tmp;
		}
		// opeartor --
		iterator & operator -- ()
		{
			p--;
			return *this;
		}

		// postfix increment
		iterator operator -- (int postfix)
		{
			iterator tmp(*this);
			p--;
			return tmp;
		}

	private:
		T * p;
	};


	/********************************************
	* set :: END
	* Note that you have to use "typename" before
	* the return value type
	********************************************/
	template <class T>
	typename set <T> ::iterator set <T> ::end() const
	{
		return iterator(data + numElements);
	}

	/********************************************
	* set :: CEND
	* Note that you have to use "typename" before
	* the return value type
	********************************************/
	template <class T>
	const typename set <T> ::iterator set <T> ::cend() const
	{
		return iterator(data + numElements);
	}

	/*******************************************
	* set :: Assignment
	*******************************************/
	template <class T>
	set <T> & set <T> :: operator = (const set <T> & rhs)
		throw (const char *)
	{
		numCapacity = rhs.numCapacity;
		numElements = rhs.numElements;
		data = new T[numCapacity];

		for (int i = 0; i < numElements; i++)
			data[i] = rhs.data[i];

		return *this;
	}

	/*******************************************
	* set :: COPY CONSTRUCTOR
	*******************************************/
	template <class T>
	set <T> ::set(const set <T> & rhs) throw (const char *)
	{
		assert(rhs.numElements >= 0 && rhs.numCapacity >= 0);

		// do nothing if there is nothing to do
		if (rhs.numCapacity == 0)
		{
			numElements = 0;
			numCapacity = 0;
			data = NULL;
			return;
		}

		// attempt to allocate
		try
		{
			data = new T[rhs.numCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate buffer";
		}

		// copy over the capacity
		numElements = rhs.numElements;
		numCapacity = rhs.numCapacity;

		// copy the items over one at a time using the assignment operator
		for (int i = 0; i < numElements; i++)
			data[i] = rhs.data[i];
	}

	/**********************************************
	* set : NON-DEFAULT CONSTRUCTOR
	* Preallocate the set to "capacity"
	**********************************************/
	template <class T>
	set <T> ::set(int num) throw (const char *)
	{
		assert(num >= 0);

		// do nothing if there is nothing to do.
		if (num == 0)
		{
			this->numElements = 0;
			this->numCapacity = 0;
			this->data = NULL;
			return;
		}

		// attempt to allocate
		try
		{
			data = new T[num];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate buffer";
		}


		// copy over the stuff
		this->numCapacity = num;
		this->numElements = 0;
	}
	/**********************************************
	* set : CLEAR
	* Clears all data
	**********************************************/
	template <class T>
	void set <T>::clear()
	{
		delete[] data;
		data = new T[numCapacity];
		numElements = 0;
	}

	/**********************************************
	* set : INSERT
	* Inserts into the array
	**********************************************/
	template <class T>
	void set <T>::insert(T value)
	{
		// Check if element doesn't exist
		if (findIndex(value, 0, numElements-1) < 0)
		{
			// check if elements will be > capacity
			if (numElements + 1 > numCapacity)
			{
				//if numCapacity is 0, make it 1 otherwise double it.
				if (numCapacity == 0)
					resize(1);
				else
					resize(numCapacity * 2);

			}

			//add the new data to the array at the correct place
			if (numElements < 1 || data[numElements-1] < value) 
			{
				data[numElements++] = value;
			}
			else
			{
				for (int i = 0; i < numElements; i++)
				{
					if (data[i] > value)
					{
						// Move Over, Darling.
						for (int j = numElements; j > i; j--)
						{
							data[j] = data[j-1];
						}
						data[i] = value;
						numElements++;
						break;
					}
				}
			}

		}
		
	}
	/**********************************************
	* set : INSERT
	* Inserts into the array
	**********************************************/
	template<class T>
	void set<T>::resize(int newCapacity) throw (const char *)
	{
		T * temp = data;
		//allocate the new array, set it to data
		try
		{
			data = new T[newCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate buffer";
		}
		//copy to new data
		for (int i = 0; i < numElements; i++)
		{
			data[i] = temp[i];
		}
		// reset numCapacity
		numCapacity = newCapacity;
	}
	/**********************************************
	* set : FIND INDEX
	* Finds element in array (binary)
	**********************************************/
	template<class T>
	int set<T>::findIndex(T target, int begin, int end) const
	{
		if (end < begin || numElements < 1)
			return -1;

		int mid = (begin + end) / 2;

		if (data[mid] == target)
			return mid;

		if (data[mid] > target)
		{
			return findIndex(target, begin, mid - 1);
		}
		else
		{
			return findIndex(target, mid + 1, end);
		}
	}
}; // namespace custom

#endif // set_H


