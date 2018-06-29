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
#include <list>

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(list <T> & x, bool (*compare)(T, T))
{
	// setup the pNode variable, and initialize it to the first item in the array.
	Node<T> * thisNode = new Node<T> (x.front());
	typename list <T> :: iterator it = x.begin();
	it++;
   
	// starting at the second item, go over the array
	for (; it != x.end(); it++)
	{
		// create a new node each loop
		Node<T> * temp = NULL;
				
		for (Node <T> *p = thisNode; p; p = p->pNext)
		{
			if (compare(p->data, *it))
			temp = p;
		}
		if(temp)
		{
			insert(temp, *it, true);
		}
		else
		{
			thisNode = insert(thisNode, *it);
		}
	}
	int i = 0;
	x.clear();
   
	for (Node <T> *p = thisNode; p; p = p->pNext, i++)
	{
		x.push_back(p->data);
	}
   
	freeData(thisNode);
}

#endif // INSERTION_SORT_H


