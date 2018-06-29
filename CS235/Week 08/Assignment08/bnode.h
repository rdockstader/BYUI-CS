/***********************************************************************
 * Header:
 *    NODE SORT
 * Summary:
 *    This is the bnode class
 * Author
 *    Harlen Hobbs, Chris Carrick, Ryan Docstader
 ************************************************************************/

#ifndef BNODE_H
#define BNODE_H

#include "bnode.h"
#include<string>
using namespace std;

/***********************************************
 * NODE
 **********************************************/
template <class T>
class BNode
{
   public:
      T data;
      BNode * pLeft;
      BNode * pRight;
      BNode * pParent;
      BNode()        :              pLeft(NULL), pRight(NULL), pParent(NULL) {}
      BNode(T value) : data(value), pLeft(NULL), pRight(NULL), pParent(NULL) {}
};

/***********************************************
 * SIZE
 **********************************************/
template <class T>
int sizeBTree(const BNode <T> * pRoot)
{ 
  return 1 +
  (pRoot->pLeft == NULL ? 0 : sizeBTree(pRoot->pLeft)) + 
  (pRoot->pRight == NULL ? 0 : sizeBTree(pRoot->pRight));
  
}

/***********************************************
 * 
 **********************************************/
template <class T>
void addLeft (BNode <T> * pNode, BNode <T> * pAdd)
{
  
  pNode->pLeft = pAdd;
  if(!pAdd)
  {
    pAdd = new BNode <T>;
  }
  pAdd->pParent = pNode;
}

/***********************************************
 * 
 **********************************************/
template <class T>
void addRight (BNode <T> * pNode, BNode <T> * pAdd)
{
  pNode->pRight = pAdd;
  if(!pAdd)
  {
    pAdd = new BNode <T>;
  }
  pAdd->pParent = pNode;
}

/***********************************************
 * 
 **********************************************/
template <class T>
void addLeft (BNode <T> * pNode, const T & t) throw (const char*) 
{
  try
  {
    BNode <T> * pAdd = new BNode <T> (t);
    pNode->pLeft = pAdd;
    if(!pAdd)
    {
      pAdd = new BNode <T>;
    }
    pAdd->pParent = pNode;
  }
  catch (bad_alloc)
   {
      cout << "bad_alloc in addLeft const" << endl;
   }
}

/***********************************************
 * 
 **********************************************/
template <class T>
void addRight (BNode <T> * pNode, const T & t) throw (const char*) 
{
  try
  {
    BNode <T> * pAdd = new BNode <T> (t);
    pNode->pRight = pAdd;
    if(!pAdd)
    {
      pAdd = new BNode <T>;
    }
    pAdd->pParent = pNode;
  }
  catch (bad_alloc)
   {
      cout << "bad_alloc in addRight const" << endl;
   }
}

/***********************************************
 * 
 **********************************************/
template <class T>
void deleteBTree(BNode <T> * & pNode)
{
  if (pNode->pLeft != NULL)
  {
    deleteBTree(pNode->pLeft);
  }
  if (pNode->pRight != NULL)
  {
    deleteBTree(pNode->pRight);
  }
  pNode = NULL;
  delete pNode;
}

/***********************************************
 * OPERATOR <<
 * used to dispaly the contents of our list.
 **********************************************/
template <class T>
std::ostream & operator << (std::ostream & out, BNode<T> * t)
{
   displayLVR(out, t);
   
   return out;
}

/***********************************************
 * In-Order Transversal
 * used to dispaly the contents of our list.
 **********************************************/
template <class T>
void displayLVR(std::ostream & out, const BNode <T> * pHead)
{
   if (!pHead)
      return;
   
   displayLVR(out, pHead->pLeft);
   
   out << pHead->data << " ";
   
   displayLVR(out, pHead->pRight);
}

/***********************************************
 * COPY
 **********************************************/
//template <class T>
//void BNode <T> *copy(BNode <T> * head)
template <class T>
BNode <T> * copyBTree(const BNode <T> * head) throw (const char *)
{
   if(!head)
      return NULL;
   
   // Initialize new head
   try
   {
      BNode<T> * copyHead = new BNode<T>(head->data);
      
      copyHead->pLeft = copyBTree(head->pLeft);
      if (copyHead->pLeft)
         copyHead->pLeft->pParent = copyHead;
      
      copyHead->pRight = copyBTree(head->pRight);
      if (copyHead->pRight)
         copyHead->pRight->pParent = copyHead;
      
      return copyHead;
   }
   catch (...)
   {
     throw "ERROR: Unable to allocate a new BNode";
   }
}



/***********************************************
 * INSERT
 **********************************************/
template <class T>
BNode <T> * insert(BNode <T> * pBNode, const T & t, bool after = false) throw(const char *)
{
	// Create a new bnode with data assigned to t
	BNode <T> * thisBNode = new BNode<T>(t);
	// if bnode is null, put bnode in null bnode and return it.
	if (!pBNode) {
		pBNode = thisBNode;
		return pBNode;
	}
	// if insert after is true, insert the bnode after the bnode sent, and return it
	if (after) {
		// check if something is already there.
		if (pBNode->pLeft) 
		{
			//link up forward bnode
			thisBNode->pLeft = pBNode->pLeft;
			pBNode->pLeft->pRight = thisBNode;
			//link up pNOde
			pBNode->pLeft = thisBNode;
			thisBNode->pRight = pBNode;
		}
		else 
		{
			pBNode->pLeft = thisBNode;
			thisBNode->pRight = pBNode;
		}
	}
	else {
		if (pBNode->pRight)
		{
			//link up back bnode
			thisBNode->pRight = pBNode->pRight;
			pBNode->pRight->pLeft = thisBNode;
			// link up pBNode
			thisBNode->pLeft = pBNode;
			pBNode->pRight = thisBNode;

		}
		else
		{
			pBNode->pRight = thisBNode;
			thisBNode->pLeft = pBNode;
		}
	}

	return thisBNode;

  //*pBNode = t;
  //cout << *pBNode << endl;
}
 /***********************************************
 * FIND
 **********************************************/
template <class T>
BNode <T> * find(BNode <T> * pHead, const T & t)
{
	while (pHead->pLeft)
	{
		if (t == pHead->data)
		{
			return pHead;
		}

		pHead = pHead->pLeft;
	}

	if (t == pHead->data)
	{
		return pHead;
	}

	return NULL;
}


/***********************************************
 * FREEDATA
 * Used to free the memory used by each bnode of our list
 **********************************************/
template <class T>
void freeData(BNode <T> * & head)
{
   BNode<T> * pDelete;
   while (head)
   {
      pDelete = head;
      head = head->pLeft;
      delete pDelete;
   }
}

/***********************************************
 * REMOVE
 * Used to remove an element from out list.
 **********************************************/
template <class T>
BNode<T> * remove(const BNode<T> * pBNode)
{
   if (!pBNode)
      return NULL;
   
   if (pBNode->pRight)
      pBNode->pRight->pLeft = pBNode->pLeft;
   
   if (pBNode->pLeft)
      pBNode->pLeft->pRight = pBNode->pRight;
   
   BNode<T> * pReturn;
   
   if (pBNode->pRight)
      pReturn = pBNode->pRight;
   else
      pReturn = pBNode->pLeft;
   
   delete pBNode;
   return pReturn;
}
#endif // INSERTION_SORT_H
