/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of an vector: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

//#include <iostream>
#include <cassert>  // because I am paranoid
//using namespace std;

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
   // constructors and destructors
   vector() { numCapacity = 0; numElements = 0; } //HH default constructor
   vector(int numElements)                  throw (const char *); //non-default
   vector(const vector & rhs)        throw (const char *); //copy constructor
  ~vector()                         { data = NULL; delete data; } //deconstructor
   vector & operator = (const vector & rhs) throw (const char *); //assignment operator
   
   bool empty() const {return (numElements == 0);} //HH num determines if it is empty?
   
   // standard container interfaces
   // vector treats size and max_size the same
   int  size()     const { return numElements;   } //size() JJ
   
   int capacity() {return numCapacity;} //HH capacity = num;
   
   int clear() {numElements = 0;} 
   
   // vector-specific interfaces
   // what would happen if I passed -1 or something greater than num?
   T & operator [] (int index)       throw (const char *)
   {
      return data[index];
   }
   const T & operator [] (int index) const throw (const char *)
   {
      return data[index];
   }
   
   void push_back(const T & t) throw (const char *); 
   
   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end() { return iterator (data + numElements);}

   // a debug utility to display the vector
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
   //TEST5
   // the various const_iterator interfaces
   class const_iterator;
   const_iterator cbegin() const      { return const_iterator (data); }
   const_iterator cend() const { return const_iterator (data + numElements);}
   
private:
   T * data;              // dynamically allocated vector of T
   int numElements;               // both the capacity and the number of elements
   int numCapacity;
   void resize(int newCapacity, const T & t) throw (const char *);
   void resize(int newCapacity)              throw (const char *);
};

/**************************************************
 * VECTOR ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
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
   
   //TEST5
    iterator & operator -- ()
   {
      p--;
      return *this;
   }
   
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
 * VECTOR const_ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: const_iterator
{
public:  // constructors, destructors, and assignment operator
   const_iterator()      : p(NULL)      {              }
   const_iterator(T * p) : p(p)         {              }
   const_iterator(const const_iterator & rhs) { *this = rhs; }
   const_iterator & operator = (const const_iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   const_iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   const_iterator operator ++ (int postfix)
   {
      const_iterator tmp(*this);
      p++;
      return tmp;
   }
   
   //TEST5
    const_iterator & operator -- ()
   {
      p--;
      return *this;
   }
   
      const_iterator operator -- (int postfix)
   {
      const_iterator tmp(*this);
      p--;
      return tmp;
   }
   
private:
   T * p;
};



/*******************************************
 * VECTOR :: Resize
 *******************************************/
template <class T>
void vector <T> :: resize(int newCapacity) throw (const char *)
{
  assert(newCapacity > 0 && newCapacity > numCapacity);
  T * pNew;
  try
  {
    pNew = new T[newCapacity];
  }
  catch (std::bad_alloc)
  {
    throw "ERROR: Unable to allocate a new buffer for vector";
  }
  for (int i = 0; i < numElements; i++)
  {
    pNew[i] = data[i];
  }  
  if (NULL != data)
  {
    data = NULL;
    delete data;
  }
  data = pNew;
  numCapacity = newCapacity;
}


/*******************************************
 * VECTOR :: push_back
 *******************************************/
template <class T>
void vector <T> :: push_back (const T & t) throw (const char *)
{
  assert(numElements <= numCapacity);
  if (numCapacity == 0)
  {
   resize(1);
  }
  else if (numElements == numCapacity)
  {
    resize(numCapacity * 2);
  }
  assert(numElements < numCapacity);
  data[numElements++] = t;
}

/*******************************************
 * VECTOR :: Assignment
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
          throw (const char *)
{
  numElements = 0;
  if (rhs.size() > capacity())
    {
      resize(rhs.size());
    }
  numElements = rhs.size();
  for (int i = 0; i < numElements; i++)
  {
    data[i] = rhs.data[i];
  }

   return *this;
}

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) throw (const char *)
{
   assert(rhs.numCapacity >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numCapacity == 0)
   {
      numCapacity = 0;
      numElements = 0;
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
   numCapacity = rhs.numCapacity;
   numElements = rhs.numElements;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(int numElements) throw (const char *)
{
   assert(numElements >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an vector, this is kinda pointless
   if (numElements == 0)
   {
      this->numElements = 0;
      this->numCapacity = 0;
      this->data = NULL;
      return;
   }
   // attempt to allocate
   try
   { 
      data = new T[numElements];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the stuff
   this->numElements = numElements;
   this->numCapacity = numElements;
}

/********************************************
 * VECTOR : DISPLAY
 * A debug utility to display the contents of the vector
 *******************************************/
template <class T>
void vector <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "vector<T>::display()\n";
   std::cerr << "\tnumCapacity = " << numCapacity << "\n";
   std::cerr << "\tnumElements = " << numElements << "\n";
   for (int i = 0; i < numCapacity; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // VECTOR_H

