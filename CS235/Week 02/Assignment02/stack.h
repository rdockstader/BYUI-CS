/***********************************************************************
 * Header:
 *    Stack
 * Summary:
 *    This class contains the notion of an stack: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the stack, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       stack             : similar to std::stack
 *       stack :: iterator : an iterator through the stack
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef STACK_H
#define STACK_H

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
 * STACK
 * A class that holds stuff
 ***********************************************/
template <class T>
class stack
{
  public:
  stack() { numCapacity = 0; numElements = 0; } //HH default constructor
  stack(int numCapacity)                  throw (const char *); //non-default
  stack(const stack & rhs)        throw (const char *); //copy constructor
  ~stack()                         { data = NULL; delete data; } //destructor
  stack & operator = (const stack & rhs) throw (const char *); //assignment operator
  
  bool empty() const {return (numElements == 0);} 
  int  size()     const { return numElements;   } 
  int clear() {numElements = 0;} 
  int capacity() {return numCapacity;}
  
  void push(const T & t) throw (const char *); 
  void pop() throw (const char *);
  T top() throw (const char *);
  
  private:
  T * data;              // dynamically allocated stack of T
  int numElements;               // both the capacity and the number of elements
  int numCapacity;
  void resize(int newCapacity, const T & t) throw (const char *);
  void resize(int newCapacity)              throw (const char *);
};
/*******************************************
 * STACK :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
stack <T> :: stack(const stack <T> & rhs) throw (const char *)
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
 * STACK : NON-DEFAULT CONSTRUCTOR
 * Preallocate the stack to "capacity"
 **********************************************/
template <class T>
stack <T> :: stack(int numCapacity) throw (const char *)
{
   numElements = 0;
   assert(numElements >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an stack, this is kinda pointless
   /*if (numElements == 0)
   {
      this->numElements = 0;
      this->numCapacity = 0;
      this->data = NULL;
      return;
   }*/
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
   //this->numElements = numElements;
   this->numCapacity = numCapacity;
}

/*******************************************
 * STACK :: Assignment
 *******************************************/
template <class T>
stack <T> & stack <T> :: operator = (const stack <T> & rhs)
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
 * STACK :: push
 *******************************************/
template <class T>
void stack <T> :: push (const T & t) throw (const char *)
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
 * STACK :: pop
 *******************************************/
template <class T>
void stack <T> :: pop () throw (const char *)
{
  assert(numElements <= numCapacity);
  if (numElements != 0)
  {
    //data[numElements] = NULL;
    --numElements;
  }
}

/*******************************************
 * STACK :: top
 *******************************************/
template <class T>
T stack <T> :: top () throw (const char *)
{
  assert(numElements <= numCapacity);
  if (numElements != 0)
  {
    return data[numElements - 1];
  }
  throw "ERROR: Unable to reference the element from an empty Stack";
  return 0;
}

/*******************************************
 * STACK :: Resize
 *******************************************/
template <class T>
void stack <T> :: resize(int newCapacity) throw (const char *)
{
  assert(newCapacity > 0 && newCapacity > numCapacity);
  T * pNew;
  try
  {
    pNew = new T[newCapacity];
  }
  catch (std::bad_alloc)
  {
    throw "ERROR: Unable to allocate a new buffer for stack";
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

}; // namespace custom

#endif // VECTOR_H
