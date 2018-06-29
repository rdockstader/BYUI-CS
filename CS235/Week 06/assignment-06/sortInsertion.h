/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
	// setup the pNode variable, and initialize it to the first item in the array.
	Node<T> * pNode = new Node<T>;
	pNode->data = array[0];
	// starting at the second item, go over the array
	for (int i = 1; i < num; i++)
	{
		// create a new node each loop
		Node<T> * thisNode = new Node<T>(array[i]);
				
		if (thisNode->data >= pNode->data) {
			// while thisnode is larger and we have a next node cycle pNode
			while (pNode->pNext && thisNode->data > pNode->pNext->data)
			{
				pNode = pNode->pNext;
			}
			// loop breaks we have the node we need to bump over.
			thisNode->pNext = pNode->pNext;
			thisNode->pPrev = pNode;
			if (pNode->pNext)
			{
				pNode->pNext->pPrev = thisNode;
			}
			pNode->pNext = thisNode;
		}
		else {
			// while thisnode is smaller and we have a next node cycle pNde
			while (pNode->pPrev && thisNode->data < pNode->pPrev->data)
			{
				pNode = pNode->pPrev;
			}
			// loop breaks we have the node we need to bump over.
			thisNode->pNext = pNode; // set thisNodes next to pnode
			thisNode->pPrev = pNode->pPrev; // set thisNodes prev to pNodes prev
			if (pNode->pPrev)
			{
				pNode->pPrev->pNext = thisNode;
			}
			pNode->pPrev = thisNode; // set pNode prev to thisNOde
		}
	}
	// Get back to the first node (this could probably be improved...
	while (pNode->pPrev)
	{
		pNode = pNode->pPrev;
	}
	// Copy the sorted data back in.
	int iter = 0;
	while (pNode->pNext)
	{
		array[iter] = pNode->data;
		pNode = pNode->pNext;
		iter++;
	}
	// Make sure to grab that last element.
	array[iter] = pNode->data;
}

#endif // INSERTION_SORT_H

