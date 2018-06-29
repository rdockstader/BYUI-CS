/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of an vector: a bucket to hold
 *    data for the user. This is similar to array, but is size aware
 *	  and can expand dynamically
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Ryan Dockstader & Br. Helfrich
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * VECTOR
 * A class that holds stuff
 ***********************************************/
template <class T>
class vector
{
public:
   // constructors
	vector() { numElements = 0; numCapacity = 0; data = new T[0]; }
	vector(int num) throw (const char *);
	vector(const vector & rhs) throw (const char *);
	// destructor
	~vector() { delete[] data; data = NULL; }
   // operator=
   vector & operator = (const vector & rhs) throw (const char *);
   // empty
   bool empty() { return (numElements == 0) ? true : false; }
   // size
   int  size()     const { return numElements; }
   int max_size() const { return numElements; }
   // capacity
   int  capacity() const { return numCapacity; }
   // clear
   void clear();
   //operator[]
   T & operator [] (int index)       throw (const char *)
   {
	  if(index >= 0 && index < numCapacity)
		return data[index];

   }
   const T & operator [] (int index) const throw (const char *)
   {
	  if (index >= 0 && index < numCapacity)
		return data[index];


	  return NULL;
   }
   void push_back(T value);

   // iterators
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();
   class const_iterator;
   const iterator cbegin() { return iterator(data); }
   const iterator cend();
   void display() const; 
   
private:
   T * data;              // dynamically allocated vector of T
   int numElements;       // number of elements
   int numCapacity;		  // curretn capacity
};

/**************************************************
 * vector ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: iterator
{
public:
   // constructors
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
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
         T & operator * ()       { return *p; }
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
* vector CONST ITERATOR
* An const iterator through vector
*************************************************/
template <class T>
class vector <T> ::const_iterator
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
 * vector :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: iterator vector <T> :: end ()
{
   return iterator (data + numElements);
}

/********************************************
* vector :: CEND
* Note that you have to use "typename" before
* the return value type
********************************************/
template <class T>
const typename vector <T> ::iterator vector <T> ::cend()
{
	return iterator(data + numElements);
}

/*******************************************
 * vector :: Assignment
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
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
 * vector :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> ::vector(const vector <T> & rhs) throw (const char *)
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
 * vector : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
vector <T> ::vector(int num) throw (const char *)
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
   for (int i = 0; i < numCapacity; i++)
   {
	   data[i] = 0;
	   numElements++;
   }
}

/********************************************
 * vector : DISPLAY
 * A debug utility to display the contents of the vector
 *******************************************/
template <class T>
void vector <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "vector<T>::display()\n";
   std::cerr << "\t numCapacity = " << numCapacity << "\n";
   std::cerr << "\t numElements = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

template <class T>
void vector <T>::clear()
{
	delete[] data;
	data = new T[numCapacity];
	numElements = 0;
}


template <class T>
void vector <T>::push_back(T value)
{
	//increment numElements, and check if it's passed numCapacity
	if (numElements + 1 > numCapacity)
	{
		//if numCapacity is 0, make it 1 otherwise double it.
		if (numCapacity == 0)
			numCapacity = 1;
		else
			numCapacity *= 2;
		// hold data in temp.
		T * temp = data;
		//allocate the new array, set it to data
		try
		{
			data = new T[numCapacity];
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
	}

	//add the new data to the array at numElements and increment
	data[numElements++] = value;



}

}; // namespace custom

#endif // VECTOR_H


