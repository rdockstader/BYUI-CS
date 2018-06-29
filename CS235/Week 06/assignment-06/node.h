/***********************************************************************
 * Header:
 *    NODE SORT
 * Summary:
 *    This is the node class
 * Author
 *    Harlen Hobbs, Chris Carrick, Ryan Docstader
 ************************************************************************/

#ifndef NODE_H
#define NODE_H

#include "node.h"
#include<string>
using namespace std;

/***********************************************
 * NODE
 **********************************************/
template <class T>
class Node
{
   public:
      T data;
      Node * pNext;
      Node * pPrev;
      Node()        :              pNext(NULL), pPrev(NULL) {}
      Node(T value) : data(value), pNext(NULL), pPrev(NULL) {}
};

/***********************************************
 * COPY
 **********************************************/
//template <class T>
//void Node <T> *copy(Node <T> * head)
template <class T>
Node <T> * copy(const Node <T> * head) throw (const char *)
{ 
	// Initialize new head
	Node<T> * copyHead = new Node<T>(head->data);
	Node<T> * nodeIter = copyHead;
	while (head->pNext)
	{
		head = head->pNext;
		nodeIter->pNext = new Node<T>(head->data);
		nodeIter->pNext->pPrev = nodeIter;
		nodeIter = nodeIter->pNext;
	}
	
	return copyHead;
}

/*
template <class T>  
void freeData(Node <T> * head)
{
  Node <T> *h = head;
  
  while(h != NULL)
  {
    Node <T> *h2 = h;
    h = h->pNext;
    delete h2;
  }

/***********************************************
 * INSERT
 **********************************************/
template <class T>
Node <T> * insert(Node <T> * pNode, const T & t, bool after = false) throw(const char *)
{
	// Create a new node with data assigned to t
	Node <T> * thisNode = new Node<T>(t);
	// if node is null, put node in null node and return it.
	if (!pNode) {
		pNode = thisNode;
		return pNode;
	}
	// if insert after is true, insert the node after the node sent, and return it
	if (after) {
		// check if something is already there.
		if (pNode->pNext) 
		{
			//link up forward node
			thisNode->pNext = pNode->pNext;
			pNode->pNext->pPrev = thisNode;
			//link up pNOde
			pNode->pNext = thisNode;
			thisNode->pPrev = pNode;
		}
		else 
		{
			pNode->pNext = thisNode;
			thisNode->pPrev = pNode;
		}
	}
	else {
		if (pNode->pPrev)
		{
			//link up back node
			thisNode->pPrev = pNode->pPrev;
			pNode->pPrev->pNext = thisNode;
			// link up pNode
			thisNode->pNext = pNode;
			pNode->pPrev = thisNode;

		}
		else
		{
			pNode->pPrev = thisNode;
			thisNode->pNext = pNode;
		}
	}

	return thisNode;

  //*pNode = t;
  //cout << *pNode << endl;
}
 /***********************************************
 * FIND
 **********************************************/
template <class T>
Node <T> * find(Node <T> * pHead, const T & t)
{
	while (pHead->pNext)
	{
		if (t == pHead->data)
		{
			return pHead;
		}

		pHead = pHead->pNext;
	}

	if (t == pHead->data)
	{
		return pHead;
	}

	return NULL;
}
/***********************************************
 * OPERATOR <<
 * used to dispaly the contents of our list.
 **********************************************/
template <class T>
std::ostream & operator << (std::ostream & out, Node<T> * t)
{
   for (Node<T> * p = t; p; p = p->pNext)
   {
      out << p->data;
      if (p->pNext)
         out << ", ";
   }
   
   return out;
}

/***********************************************
 * FREEDATA
 * Used to free the memory used by each node of our list
 **********************************************/
template <class T>
void freeData(Node <T> * & head)
{
   Node<T> * pDelete;
   while (head)
   {
      pDelete = head;
      head = head->pNext;
      delete pDelete;
   }
}

/***********************************************
 * REMOVE
 * Used to remove an element from out list.
 **********************************************/
template <class T>
Node<T> * remove(const Node<T> * pNode)
{
   if (!pNode)
      return NULL;
   
   if (pNode->pPrev)
      pNode->pPrev->pNext = pNode->pNext;
   
   if (pNode->pNext)
      pNode->pNext->pPrev = pNode->pPrev;
   
   Node<T> * pReturn;
   
   if (pNode->pPrev)
      pReturn = pNode->pPrev;
   else
      pReturn = pNode->pNext;
   
   delete pNode;
   return pReturn;
}
#endif // INSERTION_SORT_H
