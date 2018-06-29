/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother <your instructor name here>, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H
//#include "bnode.h"
#include <cassert>

namespace custom
{
	/**************************************************
	 * BST Class
	 *************************************************/
	template <class T>
	class BST
	{
	   public:
		  static class BNode
		  {
		  public:
			  T data;
			  BNode * pLeft;
			  BNode * pRight;
			  BNode * pParent;
			  BNode() : pLeft(NULL), pRight(NULL), pParent(NULL) {}
			  BNode(T value) : data(value), pLeft(NULL), pRight(NULL), pParent(NULL), isRed(true) {}
			  bool isRed;
		  };


		  // Constructors & Destructor
		  BST() : numElements(0) {}
		  BST(BST<T> & rhs) throw (const char *);
		  ~BST() {  };
   
		  // Assignment Opperator
		  BST & operator = (const BST <T> & rhs);
   
		  class iterator;
		  class const_iterator;
		  class reverse_iterator;
		  class const_reverse_iterator;
   
		  iterator begin()  { return (root == NULL ? NULL : findBegin(root)); }
		  iterator rbegin() { return (root == NULL ? NULL : findEnd(root));   }
		  iterator end()    { return NULL; }
		  iterator rend()   { return NULL; }

		  BNode * getRoot() { return root; }
   
		  BNode * findBegin(BNode * pRoot)
		  {
			 BNode * temp = pRoot;
			 while (temp->pLeft != NULL)
			 {
				temp = temp->pLeft;
			 }
			 return temp;
		  }
   
		  BNode * findEnd(BNode * pRoot)
		  {
			 BNode * temp = pRoot;
			 while (temp->pRight != NULL)
			 {
				temp = temp->pRight;
			 }
			 return temp;
		  }
   
		  int  size() const { return numElements; } ;
		  bool empty() { return (numElements == 0? true : false); }
		  void clear() { numElements = 0; deleteBTree(root); };
   
		  void      insert(T data) throw (const char *);
		  
		  void      erase(iterator & it);

		  iterator  find (T const & t)
		  {
      
			 return (finds(root, t));
      
		  };
   
		  BNode * root = NULL;
   
   
   
	   private:
		  void deleteNode(BNode deleteNode, bool right);
		  void deleteBinaryTree(BNode deleteTree){};
		  BNode* copyBinaryTree(BNode * src, BNode * dest);


		  // Red/Black Functions
		  void fixViolation(BNode *&root, BNode *&pt);
		  void rotateLeft(BNode *&root, BNode *&pt);
		  void rotateRight(BNode * &root, BNode * &pt);

		  // private insert
		  BNode * recursiveInsert(BNode * pRoot, BNode * data);

		  //Bnode Functions
		  BNode * finds(BNode * pHead, const T & t);
		  BNode * copyBTree(const BNode * head) throw (const char *);
		  void deleteBTree(BNode * & pNode);
   
		  int numElements;
   
		  BNode * head;
		  BNode * tail;
	};

	template <class T>
	class BST<T> :: iterator
	{
	   public:
		  // constructors
		  iterator()         {  pNode = NULL;            }
		  iterator(BST<T>::BNode * p) : pNode(p)  {              }
		  iterator(const iterator & rhs) { *this = rhs; }
      
		  BST<T>::BNode * pNode;
      
		  // operator=
		  iterator & operator = (const iterator & rhs)
		  {
			 this->pNode = rhs.pNode;
			 return *this;
		  }

		  // operator!=
		  bool operator != (const iterator & rhs) const { return rhs.pNode != this->pNode; }
		  // operator==
		  bool operator == (const iterator & rhs) const { return rhs.pNode == this->pNode; }

		  // operator*
		  T & operator * () throw(const char *)
		  {
			 if(pNode)
				return pNode->data;
			 else
				throw "ERROR: Trying to dereference a NULL pointer in the iterator";
		  }

		  // prefix increment
		  iterator & operator ++ ()
		  {
			 //cout << "increment prefix" << pNode;
			 // do nothing if we have nothing
			 if (NULL == pNode)
			 {
				//cout << "A" << endl;
				return *this;
         
			 }
      
			 // Have a right child
			 if (pNode->pRight != NULL)
			 {
				//cout << "B" << endl;
				pNode = pNode->pRight;
         
				while (pNode->pLeft != NULL)
				   pNode = pNode->pLeft;
         
				return *this;
			 }
      
			 if (pNode->pParent == NULL)
			 {
				//cout << "C" << endl;
				return * this;
			 }
			 // No right Child and we are our parents left child
			 if (pNode->pRight == NULL && pNode->pParent->pLeft == pNode)
			 {
				//cout << "D" << endl;
				pNode = pNode->pParent;
				return *this;
			 }
			 // No right childe and we are our parent's right child
			 if (pNode->pRight == NULL && pNode->pParent->pRight == pNode)
			 {
				//cout << "E" << endl;
				while (pNode->pParent && pNode->pParent->pRight == pNode)
				   pNode = pNode->pParent;
				return *this = pNode->pParent;
			 }
      
			 return * this;
      
		  };
		  // postfix increment
		  iterator operator ++ (int postfix)
		  {
			 if (NULL == pNode)
			 {
				//cout << "A" << endl;
				return *this;
         
			 }
      
			 // Have a right child
			 if (pNode->pRight != NULL)
			 {
				//cout << "B" << endl;
				pNode = pNode->pRight;
         
				while (pNode->pLeft != NULL)
				   pNode = pNode->pLeft;
         
				return *this;
			 }
      
			 if (pNode->pParent == NULL)
			 {
				//cout << "C" << endl;
				return * this;
			 }
			 // No right Child and we are our parents left child
			 if (pNode->pRight == NULL && pNode->pParent->pLeft == pNode)
			 {
				//cout << "D" << endl;
				pNode = pNode->pParent;
				return *this;
			 }
			 // No right childe and we are our parent's right child
			 if (pNode->pRight == NULL && pNode->pParent->pRight == pNode)
			 {
				//cout << "E" << endl;
				while (pNode->pParent && pNode->pParent->pRight == pNode)
				   pNode = pNode->pParent;
				return *this = pNode->pParent;
			 }
      
			 return * this;
      
		  };
      
		  // prefix decrement
		  iterator & operator -- ();
		  // postfix decrement
		  iterator operator -- (int postfix){return;};
	   private:
      
   
	};

	/**************************************************
	 * BST ITERATOR :: DECREMENT PREFIX
	 *     advance by one.
	 * Author:      Br. Helfrich
	 * Performance: O(log n) though O(1) in the common case
	 *************************************************/
 
	template <class T>
	typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
	{
	   // do nothing if we have nothing
	   if (NULL == pNode)
		  return *this;

	   // if there is a left node, take it
	   if (NULL != pNode->pLeft)
	   {
		  // go left
		  pNode = pNode->pLeft;

		  // jig right - there might be more right-most children
		  while (pNode->pRight)
			 pNode = pNode->pRight;
		  return *this;
	   }

	   // there are no left children, the right are done
	   assert(NULL == pNode->pLeft);
	   BST<T>::BNode * pSave = pNode;

	   // go up
	   pNode = pNode->pParent;

	   // if the parent is the NULL, we are done!
	   if (NULL == pNode)
		  return *this;

	   // if we are the right-child, got to the parent.
	   if (pSave == pNode->pRight)
		  return *this;

	   // we are the left-child, go up as long as we are the left child!
	   while (NULL != pNode && pSave == pNode->pLeft)
	   {
		  pSave = pNode;
		  pNode = pNode->pParent;
	   }

	   return *this;
	}

	/**************************************************
	 * BST copy constructor
	 *************************************************/
	template <class T>
	BST<T> :: BST(BST <T> & rhs) throw (const char *)
	{
	   numElements = 0;
	   numElements = rhs.numElements;
	   this->root = copyBTree(rhs.root);
	}

	/**************************************************
	 * BST assignment operator
	 *************************************************/
	template <class T>
	BST <T> & BST <T> :: operator = (const BST <T> & rhs)
	{
	   numElements = 0;
	   numElements = rhs.numElements;
	   this->root = copyBTree(rhs.root);
   
	   return * this;
	}

	/**************************************************
	 * BST insert()
	 *************************************************/
	template <class T>
	void BST<T> :: insert(T data) throw (const char *)
	{
		BST<T>::BNode * newNode = new BST<T>::BNode(data);
  
		root = recursiveInsert(root, newNode);
		numElements++;

	   fixViolation(root, newNode);
	}

	/**************************************************
	 * BST insert()
	 *************************************************/
	template <class T>
	BST<T>::BNode * BST<T> :: recursiveInsert(BST<T>::BNode  * root, BST<T>::BNode * pt)
	{
		/* If the tree is empty, return the new node */
		if (root == NULL)
			return pt;

		/* Otherwise, recur down the tree */
		if (pt->data < root->data)
		{
			root->pLeft = recursiveInsert(root->pLeft, pt);
			root->pLeft->pParent = root;
		}
		else if (pt->data > root->data)
		{
			root->pRight = recursiveInsert(root->pRight, pt);
			root->pRight->pParent = root;
		}

		/* return the (unchanged) node pointer */
		return root;
	}

	/**************************************************
	* BST erase()
	*************************************************/
	template <class T>
	void BST<T> ::erase(iterator & it)
	{
		BST<T>::BNode * node = it.pNode;
		// Check if node exists
		if (node != NULL)
		{
			BST<T>::BNode * left = node->pLeft;
			BST<T>::BNode * right = node->pRight;
			BST<T>::BNode * parent = node->pParent;
			bool hasRight = (right != NULL) ? true : false;
			bool hasLeft = (left != NULL) ? true : false;
			// If leaf node
			if (!(hasRight && hasLeft))
			{
				// Node is left child
				if (parent->pLeft == node)
				{
					parent->pLeft = NULL;
				}
				else
				{
					parent->pRight = NULL;
				}
				delete node;
				node = NULL;
			}
			// Has only right child
			else if (hasRight && !hasLeft)
			{
				// Node is left child
				if (parent->pLeft == node)
				{
					parent->pLeft = right;
				}
				else
				{
					parent->pRight = right;
				}
				delete node;
				node = NULL;
			}
			// Has only left child
			else if (hasLeft && !hasRight)
			{
				// Node is left child
				if (parent->pLeft == node)
				{
					parent->pLeft = left;
				}
				else
				{
					parent->pRight = left;
				}
				delete node;
				node = NULL;
			}
			// Has both children
			else
			{
				// find min value in right tree
				BST<T>::BNode * minVal = right;
				while (minVal->pLeft)
				{
					minVal = minVal->pLeft;
				}
				// Setup these if there is a value in left.
				BST<T>::BNode * rightOfMin = minVal->pRight;
				BST<T>::BNode * parentOfMin = minVal->pParent;
				// Replace node data with min value data.
				node->data = minVal->data;
				node->isRed = minVal->isRed;
				// Remove min val from parent
				if (minVal == parentOfMin->pLeft)
				{
					parentOfMin->pLeft = rightOfMin;
				}
				else
				{
					parentOfMin->pRight = rightOfMin;
				}
				if (rightOfMin)
				{
					rightOfMin->pParent = parentOfMin;
				}
				// Remove minVal
				delete minVal;
				minVal = NULL;
			}

		}
	}


	template <class T>
	void BST<T> :: rotateLeft(BST<T>::BNode * &root, BST<T>::BNode * &pt)
	{
		BST<T>::BNode *pt_right = pt->pRight;

		pt->pRight = pt_right->pLeft;

		if (pt->pRight != NULL)
			pt->pRight->pParent = pt;

		pt_right->pParent = pt->pParent;

		if (pt->pParent == NULL)
			root = pt_right;

		else if (pt == pt->pParent->pLeft)
			pt->pParent->pLeft = pt_right;

		else
			pt->pParent->pRight = pt_right;

		pt_right->pLeft = pt;
		pt->pParent = pt_right;
	}
	template <class T>
	void BST<T> ::rotateRight(BST<T>::BNode * &root, BST<T>::BNode * &pt)
	{
		BST<T>::BNode * pt_left = pt->pLeft;

		pt->pLeft = pt_left->pRight;

		if (pt->pLeft != NULL)
			pt->pLeft->pParent = pt;

		pt_left->pParent = pt->pParent;

		if (pt->pParent == NULL)
			root = pt_left;

		else if (pt == pt->pParent->pLeft)
			pt->pParent->pLeft = pt_left;

		else
			pt->pParent->pRight = pt_left;

		pt_left->pRight = pt;
		pt->pParent = pt_left;
	}

	// This function fixes violations caused by BST insertion
	template <class T>
	void BST<T> ::fixViolation(BST<T>::BNode * &root, BST<T>::BNode * &pt)
	{
		BST<T>::BNode *parent_pt = NULL;
		BST<T>::BNode *grand_parent_pt = NULL;

		while ((pt != root) && (pt->isRed) && (pt->pParent->isRed))
		{

			parent_pt = pt->pParent;
			grand_parent_pt = pt->pParent->pParent;

			/*  Case : A
			Parent of pt is left child of Grand-parent of pt */
			if (parent_pt == grand_parent_pt->pLeft)
			{

				BST<T>::BNode *uncle_pt = grand_parent_pt->pRight;

				/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
				if (uncle_pt != NULL && uncle_pt->isRed)
				{
					grand_parent_pt->isRed = true;
					parent_pt->isRed = false;
					uncle_pt->isRed = false;
					pt = grand_parent_pt;
				}

				else
				{
					/* Case : 2
					pt is right child of its parent
					Left-rotation required */
					if (pt == parent_pt->pRight)
					{
						rotateLeft(root, parent_pt);
						pt = parent_pt;
						parent_pt = pt->pParent;
					}

					/* Case : 3
					pt is left child of its parent
					Right-rotation required */
					rotateRight(root, grand_parent_pt);
					swap(parent_pt->isRed, grand_parent_pt->isRed);
					pt = parent_pt;
				}
			}

			/* Case : B
			Parent of pt is right child of Grand-parent of pt */
			else
			{
				BST<T>::BNode * uncle_pt = grand_parent_pt->pLeft;

				/*  Case : 1
				The uncle of pt is also red
				Only Recoloring required */
				if ((uncle_pt != NULL) && (uncle_pt->isRed))
				{
					grand_parent_pt->isRed = true;
					parent_pt->isRed = false;
					uncle_pt->isRed = false;
					pt = grand_parent_pt;
				}
				else
				{
					/* Case : 2
					pt is left child of its parent
					Right-rotation required */
					if (pt == parent_pt->pLeft)
					{
						rotateRight(root, parent_pt);
						pt = parent_pt;
						parent_pt = pt->pParent;
					}

					/* Case : 3
					pt is right child of its parent
					Left-rotation required */
					rotateLeft(root, grand_parent_pt);
					swap(parent_pt->isRed, grand_parent_pt->isRed);
					pt = parent_pt;
				}
			}
		}

		root->isRed = false;
	}

	/***********************************************
	* DELETEBTREE
	**********************************************/
	template <class T>
	void BST<T>::deleteBTree(BST<T>::BNode * & pNode)
	{
		if (pNode->pLeft != NULL)
		{
			deleteBTree(pNode->pLeft);
		}
		if (pNode->pRight != NULL)
		{
			deleteBTree(pNode->pRight);
		}
		delete pNode;
		pNode = NULL;
	}

	/***********************************************
	* COPY
	**********************************************/
	template <class T>
	BST<T> ::BNode * BST<T>::copyBTree(const BST<T>::BNode * head) throw (const char *)
	{
		if (!head)
			return NULL;

		// Initialize new head
		try
		{
			BST<T>::BNode * copyHead = new BST<T>::BNode(head->data);

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
	* FIND
	**********************************************/
	template <class T>
	BST<T>::BNode * BST<T>::finds(BNode * pHead, const T & t)
	{
		while (pHead != NULL)
		{
			if (pHead->data == t)
				break;

			if (pHead->data > t)
				pHead = pHead->pLeft;
			else if (pHead->data < t)
				pHead = pHead->pRight;
		}

		if (pHead == NULL)
			return NULL;

		if (pHead->data == t)
			return pHead;

		return NULL;
	}

} // namespace custom

#endif // BST_H
