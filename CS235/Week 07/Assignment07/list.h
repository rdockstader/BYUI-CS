/***********************************************************************
* Header:
*    List
* Summary:
*    This class contains the notion of an list: a bucket to hold
*    data for the user.
*
*    This will contain the class definition of:
*       List             : similar to std::List
*       List :: iterator : an iterator through the List
* Author
*    Ryan Dockstader
************************************************************************/
#ifndef LIST_H
#define LIST_H

// standard libs
#include <cassert> 
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Create namespace CUSTOM
namespace custom {

	template<typename T>
	struct Node
	{
		Node(T t) :data(t), next(nullptr), prev(nullptr) {};
		T data;
		Node<T> * next;
		Node<T> * prev;
	};

	/************************************************
	* List
	* A class that holds stuff
	***********************************************/
	template<class T>
	class list 
	{
	public:
		// Constructors
		list() : head(nullptr), tail(nullptr), numElements(0) {};
		list(const list & rhs) throw (const char *);
		// Destructor
		~list();
		// Assignment
		list & operator = (const list & rhs);
		
		// Standard structure ops
		int size() const { return numElements; }
		bool empty() const { return (numElements == 0) ? true : false; }
		void clear();
		// List ops
		// - Push/pop
		void push_back(T data);
		void push_front(T data);
		void pop_back();
		void pop_front();
		// - front/back
		T & front() { return head->data; }
		const T & front() const { return head->data; }
		T & back() { return tail->data; }
		const T & back() const { return tail->data; }
		// - other
   
      // Iterators
      class iterator;
      class const_iterator;
      class reverse_iterator;
      class const_reverse_iterator;
		// Iterator begin/end
		iterator       begin()        { return iterator(head); }
		iterator       end()          { return (tail) ? iterator(tail->next) : iterator();}
		const_iterator cbegin() const { return const_iterator(head); }
      const_iterator cend()   const { return (tail) ? const_iterator(tail->next) : const_iterator(); }
   
      reverse_iterator       rbegin()        { return reverse_iterator(tail); }
		reverse_iterator       rend()          { return (head)? reverse_iterator(head->prev) : reverse_iterator(); }
		const_reverse_iterator crbegin() const { return const_reverse_iterator(tail); }
		const_reverse_iterator crend()   const { return (head) ? const_reverse_iterator(head->prev) : const_reverse_iterator();
		}
  
  
      iterator find(T data)
      {
         // If it's the tail, return it.
         if (tail->data == data)
            return iterator(tail);
         //Other wise search all other nodes.
         Node<T> * searchNode = this->head;
         while (searchNode != this->tail)
         {
            if (searchNode->data == data)
            {
               return iterator(searchNode);
            }
            searchNode = searchNode->next;
         }

         return iterator();
      }
   
      iterator erase(iterator & it)
      {
         Node<T> * eraseNode = findNode(*it);
         if(eraseNode->next)
            eraseNode->next->prev = eraseNode->prev;
         else
           tail = eraseNode->prev;
           
         if(eraseNode->prev)
            eraseNode->prev->next = eraseNode->next;
         else
           head = eraseNode->next;

         delete eraseNode;
         return it;
         // decrement num elements
         numElements--;
      }
   
      void insert(iterator it, T data);

	private:
		Node<T> * head;
		Node<T> * tail;
		int numElements;
		Node<T> * findNode(T data)
		{
			// if no head, return null
			if (!head)
				return NULL;
			// If it's the tail, return it. 
			if (tail->data == data)
				return tail;
			//Other wise search all other nodes.
			Node<T> * searchNode = this->head;
			while (searchNode != this->tail)
			{
				if (searchNode->data == data)
				{
					return searchNode;
				}
				searchNode = searchNode->next;
			}

			return NULL;
		}
		void linkNodes(Node<T> * first, Node<T> * second)
		{
     //std::cout << "B1\n";
			first->next = second;
      //std::cout << "B2\n";
			second->prev = first;
      //std::cout << "B3\n";
		}
	};
   
   
	/**************************************************
	* list ITERATOR
	* An iterator through list
	*************************************************/
	template <class T>
	class list <T> ::iterator
	{
	public:
		// constructors
		iterator() : p(NULL) {              }
		iterator(Node<T> * p) : p(p) {              }
      //iterator(const reverse_iterator & it) : p(it.p) { }
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
		T & operator * () throw(const char *) 
      {
         if(p)
            return p->data;
         else
            throw "ERROR: Trying to dereference a NULL pointer in the iterator";
      }
    
    
    // const T & operator * () const { return p->data; } 

		// prefix increment
		iterator & operator ++ () 
		{
			if (p)
        p = p->next;
      return *this;
		}

		// postfix increment
		iterator operator ++ (int postfix) 
		{
			iterator tmp(*this);
      if(p)
			  p = p->next;
			return tmp;
		}

		// prefix decrement
		iterator & operator -- () 
		{
			if (p)
        p = p->prev;
			return *this;
		}

		// postfix decrement
		iterator operator -- (int postfix) 
		{
			iterator tmp(*this);
			if (p)
        p = p->prev;
			return tmp;
		}
    
    // two friends who need to access p directly
    //friend iterator list <T> :: insert(iterator & it, const T & data)
    //throw (const char *);
    //friend iterator list <T> :: erase(iterator it);

//private:
//typename list <T> :: Node * p;
  	private:
  		Node<T> * p;
	};

	/**************************************************
	* list CONST ITERATOR
	* An const iterator through list
	*************************************************/
	template <class T>
	class list <T> ::const_iterator
	{
	public:
		// constructors
		const_iterator()            : p(NULL) {              }
		const_iterator(Node<T> * p) : p(p)    {              }
		const_iterator(const const_iterator & rhs) { *this = rhs; }

		// operator=
		const_iterator & operator = (const const_iterator & rhs)
		{
			this->p = rhs.p; 
			return *this;
		}

		// operator!=
		bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }

		// operator==
		bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

		// operator*
		T & operator * () throw (const char*)
      {
         if(p)
            return p->data;
         else
            throw "ERROR: Trying to dereference a NULL pointer in the const_iterator";
      }
    
		const T & operator * () const { return *p; }

		// prefix increment
		const_iterator & operator ++ ()
		{
      if(p)
        p = p->next;
			return *this;
		}

		// postfix increment
		const_iterator operator ++ (int postfix)
		{
			const_iterator tmp(*this);
			if (p)
        p = p->pNext;
			return tmp;
		}

		// prefix decrement
		const_iterator & operator -- ()
		{
			if (p)
        p = p->prev;
			return *this;
		}

		// postfix increment
		const_iterator operator -- (int postfix)
		{
			iterator tmp(*this);
      if (p)
        p = p->prev;
			return tmp;
		}

	private:
		Node<T> * p;
	};
 
 
 /**************************************************
	* list REVERSE_ITERATOR
	* A reverse iterator through list
	*************************************************/
	template <class T>
	class list <T> :: reverse_iterator
	{
	public:
		// constructors
		reverse_iterator() : p(NULL) {              }
		reverse_iterator(Node<T> * p) : p(p) {              }
		reverse_iterator(const reverse_iterator & rhs) { *this = rhs; }

		// operator=
		reverse_iterator & operator = (const reverse_iterator & rhs)
		{
			this->p = rhs.p;
			return *this;
		}

		// operator!=
		bool operator != (const reverse_iterator & rhs) const { return rhs.p != this->p; }
		// operator==
		bool operator == (const reverse_iterator & rhs) const { return rhs.p == this->p; }

		// operator*
		T & operator * () throw (const char*)
    {  
      if(p)
        return p->data; 
      else
      throw "ERROR: Trying to dereference a NULL pointer in the reverse_iterator";
    }
    
		//const T & operator * () const { return p->data; }

		// prefix increment
		reverse_iterator & operator ++ ()
		{
			if (p)
        p = p->prev;
			return *this;
		}

		// postfix increment
		reverse_iterator operator ++ (int postfix)
		{
			reverse_iterator tmp(*this);
			if (p)
        p = p->prev;
			return tmp;
		}

		// prefix decrement
		reverse_iterator & operator -- ()
		{
			if (p)
        p = p->next;
			return *this;
		}

		// postfix decrement
		reverse_iterator operator -- (int postfix)
		{
			reverse_iterator tmp(*this);
			if (p)
        p = p->next;
			return tmp;
		}

	private:
		Node<T> * p;
	};

	/**************************************************
	* list CONST REVERSE ITERATOR
	* A const reverse iterator through list
	*************************************************/
	template <class T>
	class list <T> ::const_reverse_iterator
	{
	public:
		// constructors
		const_reverse_iterator() : p(NULL) {              }
		const_reverse_iterator(Node<T> * p) : p(p) {              }
		const_reverse_iterator(const reverse_iterator & rhs) { *this = rhs; }

		// operator=
		const_reverse_iterator & operator = (const reverse_iterator & rhs)
		{
			this->p = rhs.p;
			return *this;
		}

		// operator!=
		bool operator != (const const_reverse_iterator & rhs) const { return rhs.p != this->p; }

		// operator==
		bool operator == (const const_reverse_iterator & rhs) const { return rhs.p == this->p; }

		// operator*
		T & operator * () throw (const char *)
    {
      if (p)
        return p->data;
      else
        throw "ERROR: Trying to dereference a NULL pointer in the const_reverse_iterator"; 
     }
		//const T & operator * () const { return *p; }

		// prefix increment
		const_reverse_iterator & operator ++ ()
		{
			if (p)
        p = p->prev;
			return *this;
		}

		// postfix increment
		const_reverse_iterator operator ++ (int postfix)
		{
			const_reverse_iterator tmp(*this);
			if (p)
        p = p->prev;
			return tmp;
		}

		// prefix decrement
		const_reverse_iterator & operator -- ()
		{
			if (p)
        p = p->next;
			return *this;
		}

		// postfix decrement
		const_reverse_iterator operator -- (int postfix)
		{
			reverse_iterator tmp(*this);
			if (p)
        p = p->next;
			return tmp;
		}

	private:
		Node<T> * p;
	};
 

	/**************************************************
	* list Member Functions START
	*************************************************/

   
   
	/*******************************************
	* LIST :: copy const
	*******************************************/
	template<class T>
	list<T>::list(const list & rhs) throw (const char *) 
	{
		numElements = 0;
		Node<T> * iterNode = rhs.head;
		head = new Node<T>(iterNode->data);
		tail = head;
		for (int i = 0; i < rhs.numElements; i++ )
		{
			this->push_back(iterNode->data);
			iterNode = iterNode->next;
		}

	}
   
	/*******************************************
	* LIST :: destructor
	*******************************************/
	template<class T>
	list<T>::~list()
	{
		clear();
	}
   
	/*******************************************
	* LIST :: assignment operator
	*******************************************/
	template<class T>
	list<T> & list<T>::operator = (const list & rhs)
	{
		//erase something if it exists
		clear();

		Node<T> * iterNode = rhs.head;
		for (int i = 0; i < rhs.numElements; i++)
		{
			this->push_back(iterNode->data);
			iterNode = iterNode->next;
		}

		return *this;
	}
   
	/*******************************************
	* LIST :: clear
	*******************************************/
	template<class T>
	void list<T>::clear()
	{
		// delete nodes
		if (head)
		{
			while (head != tail)
			{
				head = head->next;
				delete head->prev;
			}
			delete head;
			head = NULL;
			tail = NULL;
		}
		// reset size
		numElements = 0;
	}
   
	/*******************************************
	* LIST :: push back
	*******************************************/
	template<class T>
	void list<T>::push_back(T data)
	{
		// create node of data
		Node<T> * newNode = new Node<T>(data);
		// if no head, init head and tail
		if (head == NULL)
		{
			head = newNode;
			tail = newNode;
		}
		else // has a head and tail, add the new node at the end
		{
			linkNodes(tail, newNode);
			// Nodes are linked, reset tail to end.
			tail = newNode;
		}
		// increase size.
		numElements++;
			
	}
   
	/*******************************************
	* LIST :: push front
	*******************************************/
	template<class T>
	void list<T>::push_front(T data)
	{
		// create node of data
   //std::cout << "A1\n";
		Node<T> * newNode = new Node<T>(data);
		// if no head, init head and tail
		if (head == NULL)
		{
       //std::cout << "A2\n";
			head = newNode;
			tail = newNode;
		}
		else // has a head and tail, add the new node at the front
		{
         //std::cout << "A3\n";
			linkNodes(newNode, head);
			// Nodes are linked, reset head to beginning.
			head = newNode;
		}
   //std::cout << "A4\n";

		// increase size.
		numElements++;
   //std::cout << "numElements: " << numElements << "\n";
   //std::cout << "A5\n";
	}
   
	/*******************************************
	* LIST :: pop back
	*******************************************/
	template<class T>
	void list<T>::pop_back()
	{
		tail = tail->prev;
		delete tail->next;

		// decrease size.
		numElements--;
	}
	/*******************************************
	* LIST :: pop front
	*******************************************/
	template<class T>
	void list<T>::pop_front()
	{
		head = head->next;
		delete head->prev;

		// decrease size.
		numElements--;
	}
	/*******************************************
	* LIST :: Insert (before)
	*******************************************/
	template<class T>
	void list<T>::insert(iterator it, T data)
	{
		// Create a node
		Node<T> * newNode = new Node<T>(data);
		
		if (it != iterator())
		{
			// Get the node pointer
			Node<T> * curNode = findNode(*it);
			// Insert it before, make links.
			if (curNode->prev)
			{
				linkNodes(curNode->prev, newNode);
			}
			else
			{
				head = newNode;
			}    
			linkNodes(newNode, curNode);
		}
		else 
		{
			linkNodes(tail, newNode);
			tail = newNode;
		}
		// increase size.
		numElements++;
	}

	/**************************************************
	* list Member Functions END
	*************************************************/


} // namespace CUSTOM




#endif // LIST_H
