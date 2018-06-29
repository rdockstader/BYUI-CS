/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Chris Carrick, Harlen Hobbs, Ryan Docstader
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include <cassert>         // for ASSERT
#include <string>          // for STRING: binary representation of codes
#include "bnode.h"         // for BINARY_NODE class definition
#include "vector.h"        // for VECTOR container
#include "pair.h"          // for PAIR container
#include "huffman.h"       // for HUFFMAN() prototype


using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::string;
using std::bad_alloc;
using namespace custom;


/**********************/
/******QUICK SORT******/
/**********************/

//TODO: Make Backwards...
int partition(custom::vector<huffmanCode>& A, int p, int q)
{
	huffmanCode x = A[p];
	int i = p;
	int j;

	for (j = p + 1; j<q; j++)
	{
		if (A[j] <= x)
		{
			i = i + 1;
			std::swap(A[i], A[j]);
		}

	}

	std::swap(A[i], A[p]);
	return i;
}

void quickSort(custom::vector<huffmanCode>& A, int p, int q)
{
	int r;
	if (p<q)
	{
		r = partition(A, p, q);
		quickSort(A, p, r);
		quickSort(A, r + 1, q);
	}
}

void quickSortFunc(custom::vector<huffmanCode>& v)
{
   int p = 0;
	int q = v.size();

	quickSort(v, p, q);
}



/**********************/
/*****HUFFMAN CODE*****/
/**********************/
bool operator<(huffmanCode const & first, huffmanCode const & second)
{
	return (first.frequency < second.frequency);
}
bool operator==(huffmanCode const & first, huffmanCode const & second)
{
	return (first.frequency == second.frequency);
}
bool operator!=(huffmanCode const & first, huffmanCode const & second)
{
	return !(first == second);
}
bool operator>(huffmanCode const & first, huffmanCode const & second)
{
	return second < first;
}
bool operator<=(huffmanCode const & first, huffmanCode const & second)
{
	return !(first > second);
}
bool operator>=(huffmanCode const & first, huffmanCode const & second)
{
	return !(first < second);
}
/**********************/
/*****HUFFMAN TREE*****/
/**********************/
HuffmanTree::HuffmanTree(huffmanCode left, huffmanCode right)
{
	BNode<huffmanCode> * leftNode = new BNode<huffmanCode>(left);
	BNode<huffmanCode> * rightNode = new BNode<huffmanCode>(right);
	huffmanCode headData;
	headData.frequency = left.frequency + right.frequency;
	head = new BNode<huffmanCode>(headData);
	head->pLeft = leftNode;
	head->pRight = rightNode;
}

void HuffmanTree::insert(huffmanCode newNode)
{
	BNode<huffmanCode> * temp = head;
	huffmanCode newHead;
	newHead.frequency = head->data.frequency + newNode.frequency;
	head = new BNode<huffmanCode>(newHead);
	head->pLeft = new BNode<huffmanCode>(newNode);
	head->pRight = temp;
}
void HuffmanTree::generateCodes()
{
	generateCodes(head, std::string());
}
void HuffmanTree::generateCodes(BNode<huffmanCode> * curNode, std::string code)
{
	if (curNode->pLeft == NULL && curNode->pRight == NULL)
	{
		//std::cout << "Leaf Found: " << curNode->data.data << "\t" << code << std::endl;
		huffmanCodes.push_back(custom::pair<huffmanCode, std::string>(curNode->data, code));
	}
	else if (curNode->pLeft != NULL)
	{
		code.append("0");
		generateCodes(curNode->pLeft, code);
	}
	else if (curNode->pRight != NULL)
	{
		code.append("1");
		generateCodes(curNode->pRight, code);
	}
}

std::string HuffmanTree::getCode(huffmanCode hc)
{
	if (huffmanCodes.size() < 1)
		return std::string("-1");

	for (custom::vector<custom::pair<huffmanCode, std::string> > ::iterator it = huffmanCodes.begin(); it != huffmanCodes.end(); ++it)
	{
		if ((*it).first.data == hc.data)
			return (*it).second;
	}

	return std::string("-1");
}

// Prototypes
void Huffman :: readFile(const string & fileName)
{
   ifstream fin;
   fin.open(fileName.c_str());
   
   if (fin.fail())
      return;
   
   huffmanCode code;
   
   while (fin >> code.data >> code.frequency)
      list.push_back(code); // Save our code to list, a private vector in the Huffman class
   
   fin.close();
}

void Huffman::generateTree()
{
	// copy list into new vector
	custom::vector<huffmanCode> sortedList = list;
	// sort new vector (backwards, so smallest is last)
	quickSortFunc(sortedList);
	// while vector is not empty
	while (!sortedList.empty())
	{
		// pull of last two elements, make them into a tree
		// insert tree into tree collection
		// while current element frequence < current tree head "frequency"
		// create new node
		// create new head w/ freq of newnode freq + head freq
		// add new node to new head left
		// add old head to new head right
	}
		
	// Merge tree until we only have one
	// Generate codes for final tree
}

void Huffman :: display()
{
   for (custom::vector<huffmanCode> :: iterator it = list.begin(); it != list.end(); ++it)
      cout << (*it).data << " | " << (*it).frequency << endl;
	  //cout << (*it).data << " | " << trees[0].getCode((*it)) << endl;
}

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string & fileName)
{
   Huffman newHuffman;
   newHuffman.readFile(fileName);
   newHuffman.generateTree();
   newHuffman.display();
   
   return;
}
