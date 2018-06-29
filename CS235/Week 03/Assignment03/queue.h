/***********************************************************************
 * Header:
 *    Queue
 * Summary:
 *    A templateted class that will hold a circular queue
 *
 *    This will contain the class definition of:
 *       queue             : similar to std::queue
 * Author
 *    Ryan Dockstader
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cassert>  // because I am paranoid
#include <vector>
using namespace std;
namespace custom
{
	/************************************************
	 * QUEUE
	 * A class that holds stuff
	 ***********************************************/
	template <class T>
	class queue
	{
	public:
		//constructors
		queue() : numCapacity(0), numPop(-1), numPush(-1) {}
		queue(int capacity) throw (const char *);
		queue(const queue & rhs) throw (const char *);
		queue & operator = (const queue & rhs) throw (const char *);
		//Destructor
		~queue() { if (size() != 0) { delete[] data; data = NULL; } }  //destructor

		// Standard data structure functions
		int size();
		void clear();
		bool empty();

		// Queue specific functions
		void push(T value);
		void pop();
		T & front()       throw (const char *);
		const T & front() const throw (const char *);
		T & back()        throw (const char *);
		const T & back()  const throw (const char *);


	private:
		// Private Member variables
		T * data;             
		int numPush;
		int numPop;
		int numCapacity;

		// Private member functions
		void resize(int Capacity)  throw (const char *);
		//int iHead();
		//int iTail();
		bool full();

	};

	/**********************************************
	* QUEUE : NON-DEFAULT CONSTRUCTOR
	* Preallocate the queue to "capacity"
	**********************************************/
	template <class T>
	queue <T> ::queue(int numCapacity) throw (const char *)
	{
		numPush = -1;
		numPop = -1;
		numCapacity = 0;

		try
		{
			data = new T[numCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate buffer";
		}

		// copy over the stuff
		this->numCapacity = numCapacity;
	}

	/*******************************************
	* QUEUE :: COPY CONSTRUCTOR
	*******************************************/
	template <class T>
	queue<T>::queue(const queue <T> & rhs) throw (const char *)
	{
		assert(rhs.numCapacity >= 0);
		//cout << "resize\n" << "capacity: " << rhs.numCapacity << endl;
		// attempt to allocate
		try
		{
			data = new T[rhs.numCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate buffer";
		}
		// do nothing if there is nothing to do
		if (rhs.numCapacity == 0)
		{
			numCapacity = 0;
			numPop = -1;
			numPush = -1;
			data = NULL;
			return;
		}
		//else
		{
			// copy over the capacity
			numPop = rhs.numPop;
			numPush = rhs.numPush;
			numCapacity = rhs.numCapacity;

			// copy the items over one at a time using the assignment operator
			for (int i = 0; i < rhs.numCapacity; i++)
				data[i] = rhs.data[i];
		}

	}

	/*******************************************
	* QUEUE :: Assignment
	*******************************************/
	template <class T>
	queue<T>& queue<T>::operator=(const queue <T> & rhs)
		throw (const char *)
	{
		numPop = rhs.numPop;
		numPush = rhs.numPush;
		numCapacity = rhs.numCapacity;
		data = new T[numCapacity];

		for (int i = 0; i < rhs.numCapacity; i++)
		{
			data[i] = rhs.data[i];
		}

		return *this;
	}

	/*******************************************
	* QUEUE :: Size
	*******************************************/
	template <class T>
	int queue<T>::size()
	{
		if (numPush == numPop)
			return 0;

		if(numPush > numPop)
			return numPush - numPop + 1;

		return (numCapacity - numPop) + numPush+1;
	}

	/*******************************************
	* QUEUE :: Clear
	*******************************************/
	template <class T>
	void queue<T>::clear()
	{
		numPush = -1;
		numPop = -1;
	}


	/*******************************************
	* QUEUE :: Empty
	*******************************************/
	template <class T>
	bool queue<T>::empty()
	{
		return (numPush == -1 && numPop == -1);
	}

	/*******************************************
	* QUEUE :: full
	*******************************************/
	template <class T>
	bool queue<T>::full()
	{
		if (numCapacity < 1)
			return true;
		return (((numPush + 1) % numCapacity) == numPop);
	}

	/*******************************************
	* QUEUE :: push
	*******************************************/
	template<class T>
	void queue<T>::push(T value)
	{
		

		if (full())
		{
			if (numCapacity == 0)
				resize(1);
			else
				resize(numCapacity * 2);
		}
		if (empty())
		{
			numPop = 0;
			numPush = 0;
		}
		else
		{
			numPush = (numPush + 1) % numCapacity;
		}
		data[numPush] = value;


		//if (numCapacity > 0) cout << "numpop: " << ((numPop + 1) % numCapacity) << " Num Push: " << numPush << " Num Capacity: " << numCapacity << endl;

	}

	/*******************************************
	* QUEUE :: pop
	*******************************************/
	template<class T>
	void queue<T>::pop()
	{
		if (empty())
		{

		}
		else if (numPush == numPop)
		{
			numPush = -1;
			numPop = -1;
		}
		else
		{
			numPop = (numPop + 1) % numCapacity;
		}
	}

	/*******************************************
	* QUEUE :: Resize
	*******************************************/
	template <class T>
	void queue <T> ::resize(int newCapacity) throw (const char *)
	{
		assert(newCapacity > 0 && newCapacity > numCapacity);
		std::vector<T> tempVec;
		int tempCap = numCapacity;
		//take everything off the queue and hold it in the vector
		while (!empty())
		{
			tempVec.push_back(front());
			pop();
		}
		//delete and reallocate the array
		if (NULL != data)
		{
			data = NULL;
			delete data;
		}
		try
		{
			data = new T[newCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for queue";
		}
		//reset variables
		clear();
		numCapacity = newCapacity;
		for(int i = 0; i < tempVec.size(); i++)
		{
			push(tempVec[i]);
		}

		
	}

	/*******************************************
	* QUEUE :: front
	*******************************************/
	template <class T>
	T & queue <T> ::front() throw (const char *)
	{
		assert(size() <= numCapacity);

		if(numPop == -1)
			throw "ERROR: attempting to access an element in an empty queue";

		return data[numPop];

	}

	/*******************************************
	* QUEUE :: front CONST
	*******************************************/
	template <class T>
	const T & queue <T> ::front() const throw (const char *)
	{
		assert(size() <= numCapacity);

		if (numPop == -1)
			throw "ERROR: attempting to access an element in an empty queue";

		return data[numPop];

	}

	/*******************************************
	* QUEUE :: back
	*******************************************/
	template <class T>
	T & queue <T> ::back() throw (const char *)
	{
		assert(size() <= numCapacity);

		if (numPush == -1)
			throw "ERROR: attempting to access an element in an empty queue";

		return data[numPush-1];
	}


	/*******************************************
	* QUEUE :: back CONST
	*******************************************/
	template <class T>
	const T & queue <T> ::back() const throw (const char *)
	{
		assert(size() <= numCapacity);

		if (numPush == -1)
			throw "ERROR: attempting to access an element in an empty queue";

		return data[numPush - 1];
	}

} // Namespace custom end
#endif // QUEUE_H
