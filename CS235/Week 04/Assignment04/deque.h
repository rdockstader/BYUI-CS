/***********************************************************************
 * Header:
 *    Deque
 * Summary:
 *    A templateted class that will hold a circular deque
 *
 *    This will contain the class definition of:
 *       deque             : similar to std::deque
 * Author
 *    Ryan Dockstader, Chris Carrick, Harlen Hobbs
 ************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <cassert>  // because I am paranoid
#include <vector>
#include <cstdlib> // for ABS
using namespace std;
namespace custom
{
/************************************************
 * DEQUE
 * A class that holds stuff
 ***********************************************/
template <class T>
class deque
{
   public:
      //constructors
      deque () : numCapacity(0), iFront(0), iBack(-1) {}
      deque (int capacity)                    throw (const char *);
      deque (const deque & rhs)               throw (const char *);
      deque & operator = (const deque & rhs) throw (const char *);
      //Destructor
      ~deque () { if (size() != 0) { delete[] data; data = NULL; } }  //destructor

      // Standard data structure functions
      int  size () const;
      void clear ();
      bool empty () const;

      void display () const;  // For Debugging

      // Queue specific functions
      void push_back (T value);
      void push_front (T value);

      void pop_back  ();
      void pop_front ();

            T & front ()       throw (const char *);
      const T & front () const throw (const char *);
            T & back ()        throw (const char *);
      const T & back ()  const throw (const char *);

   private:
      // Private Member variables
      T * data;
      int iFront;
      int iBack;
      int numCapacity;

      // Private member functions
      void resize (int Capacity)  throw (const char *);
      int capacity () const { return numCapacity; };
      int iFrontNormalize () const;
      int iBackNormalize ()  const;
      bool full() const;
};

using std::cerr;
/****************************************************
 * DISPLAY DEQUE
 * display the contents of a deque for debug purposes
 ****************************************************/
template <class T>
void deque <T> :: display () const
{
   // display the header info
   cerr << "\ndeque<T>::display()\n";
   cerr << "\tnumCapacity = " << numCapacity << "\n";

   // display the contents of the array
   cerr << "\tdata = ";
   if (numCapacity == 0)
      cerr << "NULL";
   else
   {
      cerr << "{ ";
      for (int i = 0; i < numCapacity; i++)
      {
         if (i != 0)
            cerr << ", " ;
         cerr << i << ":";

         // not wrapped
         //      0   1   2   3   4   5   6
         //    +---+---+---+---+---+---+---+
         //    |   |   | A | B | C |   |   |
         //    +---+---+---+---+---+---+---+
         // iFront = 9     iFrontNormalize() = 2
         // iBack  = 11    iBackNormalize()  = 4
         if (iFrontNormalize() <= iBackNormalize() &&  // not wrapped
             iFrontNormalize() <= i &&
             i <= iBackNormalize() && !empty())                        // in range
            cerr << data[i];

         // wrapped
         //      0   1   2   3   4   5   6
         //    +---+---+---+---+---+---+---+
         //    | B | C |   |   |   |   | A |
         //    +---+---+---+---+---+---+---+
         // iFront = -8    iFrontNormalize() = 6
         // iBack  = -6    iBackNormalize()  = 1
         else if (iFrontNormalize() > iBackNormalize() && // wrapped
                  size() != 0 &&                              // not empty
                  (i <= iBackNormalize() ||
                   i >= iFrontNormalize()) && !empty())                   // in range
            cerr << data[i];
         else
            cerr << "?";
      }
      cerr << " }";
   }
   cerr << "\n";

   // display the front and back with the normalized values in ()s
   if (numCapacity)
   {
      cerr << "\tiFront = " << iFront
           << " ("          << iFrontNormalize() << ") Data: ";
           try { cerr << front() << endl; } catch (const char *) { cerr << "empty\n"; }
      cerr << "\tiBack  = " << iBack
           << " ("          << iBackNormalize()  << ") Data: ";
           try { cerr << back() << endl; } catch (const char *) { cerr << "empty\n"; }
      cerr << "\tsize   = " << size() << endl
           << "\tfull   = " << (full() ? "Yes" : "No") << endl
           << "\tempty  = " << (empty() ? "Yes" : "No") << endl;
   }
}

template <class T>
int deque <T> :: iBackNormalize() const
{
   if (iBack < 0)
      return capacity() + (iBack % capacity());
   return (iBack % capacity());
}

template <class T>
int deque <T> :: iFrontNormalize() const
{
   if (iFront < 0 && (abs(iFront) != capacity()))
      return capacity() + (iFront % capacity());
   else if (empty() || (abs(iFront) == capacity()))
      return 0;
   return (iFront % capacity());
}


/**********************************************
* DEQUE : NON-DEFAULT CONSTRUCTOR
* Preallocate the deque to "capacity"
**********************************************/
template <class T>
deque <T> :: deque (int numCapacity) throw (const char *)
{
   try
   {
      data = new T[numCapacity]; //numCapacity];
      iFront = 0;
      iBack = -1;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for deque";
   }

   // copy over the stuff
   this->numCapacity = numCapacity;
}

/*******************************************
* DEQUE :: COPY CONSTRUCTOR
*******************************************/
template <class T>
deque <T> :: deque (const deque <T> & rhs) throw (const char *)
{
   assert(rhs.numCapacity >= 0);
   
   // attempt to allocate
   try
   {
      data = new T[rhs.numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer buffer for deque";
   }

   // copy over the capacity
   iFront = rhs.iFront;
   iBack  = rhs.iBack;
   numCapacity = rhs.numCapacity;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < rhs.numCapacity; i++)
      data[i] = rhs.data[i];

}

/*******************************************
* DEQUE :: Assignment
*******************************************/
template <class T>
deque <T> & deque <T> :: operator = (const deque <T> & rhs) throw (const char *)
{
   iFront = rhs.iFront;
   iBack  = rhs.iBack;
   numCapacity = rhs.numCapacity;
   
   try
   {
      data = new T[rhs.numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer buffer for deque";
   }

   for (int i = 0; i < rhs.numCapacity; i++)
      data[i] = rhs.data[i];

   return *this;
}

/*******************************************
* DEQUE :: Size
*******************************************/
template <class T>
int deque <T> :: size () const 
{
   return iBack - iFront + 1;
}

/*******************************************
* DEQUE :: Clear
*******************************************/
template <class T>
void deque <T> :: clear ()
{
   iFront = 0;
   iBack = -1;
}


/*******************************************
* DEQUE :: Empty
*******************************************/
template <class T>
bool deque <T> :: empty () const
{
   //if (iFront > iBack)
   //   return true;
   return (!size());//iFront == -1 && iBack == -1);
}

/*******************************************
* DEQUE :: full
*******************************************/
template <class T>
bool deque <T> :: full () const
{
   if (numCapacity < 1)
      return true;
   return (size() == capacity());
}

/*******************************************
* DEQUE :: push_front
*******************************************/
template<class T>
void deque <T> :: push_front (T value)
{
   if (numCapacity == 0)
      resize(1);
   else if (full())
      resize(numCapacity * 2);
   
   if (empty())
   {
      iFront = 1;
      iBack = 0;
   }
   
   iFront--;
   data[iFrontNormalize()] = value;
}

/*******************************************
* DEQUE :: pop_front
*******************************************/
template<class T>
void deque <T> :: pop_front ()
{
   if (iFront > iBack)
   {
      iFront = -1;
      iBack = -1;
   }
   else if (size() == 1)
   {
      iFront = 0;
      iBack = -1;
   }
   else
      iFront++;

}

/*******************************************
* DEQUE :: push_back
*******************************************/
template<class T>
void deque <T> :: push_back (T value)
{
   //cout << "numCapacity: " << numCapacity << endl;
   if (numCapacity == 0)
      resize(1);
   else if (full())
      resize(numCapacity * 2);
   //cout << "numCapacity: " << numCapacity << endl;
   if (empty())
      iFront = 0;
   
   iBack++;
   data[iBackNormalize()] = value;
   
}

/*******************************************
* DEQUE :: pop_back
*******************************************/
template<class T>
void deque <T> :: pop_back ()
{
   if (empty())
   {
      iBack = -1;
      iFront = -1;
   }
   else if (size() == 1)
   {
      iFront = 0;
      iBack = -1;
   }
   else
   {
      iBack--;
   }
   
}

/*******************************************
* DEQUE :: Resize
*******************************************/
template <class T>
void deque <T> :: resize (int newCapacity) throw (const char *)
{
   assert(newCapacity > 0 && newCapacity > numCapacity);
   int oldcapcity = capacity();
   int tempNum = iFrontNormalize();
   int oldSize = size();
   
   T * tempData;
   try
   {
      tempData = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
      throw ("ERROR: unable to allocate new buffer for deque 1");
   }
   
   for (int i = 0 ; i < capacity(); i++)
   {
      tempData[i] = data[i];
   }
   
   if (size() != 0)
   {
      delete [] data;
      data = NULL;
   }
   
   try
   {
      data = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
      throw ("ERROR: unable to allocate new buffer for deque 2");
   }
   
   //cout << "tempNum: " << tempNum << endl;
   //cout << "oldsize: " << oldSize << endl;
   //cout << "oldcapa: " << oldcapcity << endl;
   for (int i = 0; i < oldSize; i++)
   {
   
      if (tempNum < oldcapcity)
      {
         //cout << "tempNum: " << tempNum << endl;
         data[i] = tempData[tempNum++];
      }
      else
      {
         //cout << "tempNum: " << tempNum - oldcapcity << " : " << tempData[tempNum - oldcapcity] << endl;
         data[i] = tempData[tempNum - oldcapcity];
         tempNum++;
      }
   }
   iFront = 0;
   iBack = oldSize - 1;
   
   if (tempData != NULL)
   {
      delete [] tempData;
      tempData = NULL;
   }
   numCapacity = newCapacity;
   
}

/*******************************************
* DEQUE :: front
*******************************************/
template <class T>
T & deque <T> :: front() throw (const char *)
{
   assert(size() <= numCapacity);

   if(empty())//iFront == -1)
      throw "ERROR: unable to access data from an empty deque";

   return data[iFrontNormalize()];
}

/*******************************************
* DEQUE :: front CONST
*******************************************/
template <class T>
const T & deque <T> ::front() const throw (const char *)
{
   assert(size() <= numCapacity);

   if (empty())//iFront == -1)
      throw "ERROR: unable to access data from an empty deque";

   return data[iFrontNormalize()];
}

/*******************************************
* DEQUE :: back
*******************************************/
template <class T>
T & deque <T> :: back() throw (const char *)
{
   assert(size() <= numCapacity);

   if (iBack == -1 && empty())
      throw "ERROR: unable to access data from an empty deque";
   
   //cout << "back() : " << iBackNormalize() - 1 << endl;
   return data[iBackNormalize()];
}


/*******************************************
* DEQUE :: back CONST
*******************************************/
template <class T>
const T & deque <T> ::back() const throw (const char *)
{
   assert(size() <= numCapacity);

   if (iBack == -1 && empty())
      throw "ERROR: unable to access data from an empty deque";
   //cout << "back() : " << iBackNormalize() - 1 << endl;
   return data[iBackNormalize()];
}

} // Namespace custom end
#endif // DEQUE_H
