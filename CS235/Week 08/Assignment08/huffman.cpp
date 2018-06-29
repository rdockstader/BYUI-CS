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
#include <list>

#include "sortInsertion.h"

using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::string;
using std::bad_alloc;
using namespace custom;



///////////////////


template <class T>
bool compNodes(BNode <T> * first, BNode <T> * second)
{
  if(first->data == second->data) 
  {
    return first->data.second < second->data.second;
  }
  return first->data < second->data;
}

template <class T, class U>
bool compPairs (custom::pair<T, U> p1, custom:: pair<T, U> p2)
{
  return p1 < p2;
}

BNode <custom::pair <float, std::string> > * createHuffTree(list <BNode < custom::pair <float, std::string> > * > readInto)
{
  while (readInto.size() > 1)
  {
    BNode <custom::pair <float, std::string> > * left = readInto.front();
    readInto.pop_front();
    
    BNode <custom::pair <float, std::string> > * right = readInto.front();
    readInto.pop_front();
    
    custom:: pair <float, std::string> newPair;
    newPair.first = left->data.first + right->data.first;
    newPair.second = '{';
    
    BNode <custom::pair <float, std::string> > * newNode = new BNode <custom::pair <float, std::string> > (newPair);
    
    addLeft(newNode, left);
    
    addRight(newNode, right);
    
    readInto.push_front(newNode);
    
    sortInsertion(readInto, compNodes);
  }
  
  return readInto.front();
}

void encodeHuff(BNode <custom::pair <float, std::string> > * root, string code, list <custom::pair <std::string, string> > & codeTable)
{
  if ((root->pLeft == NULL) && (root->pRight == NULL))
  {
    custom::pair <std::string, string> newCode(root->data.second, code);
    codeTable.push_back(newCode);
  }
  else
  {
    encodeHuff(root->pLeft, code + "0", codeTable);
    encodeHuff(root->pRight, code + "1", codeTable);
  }
}

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string & fileName)
{
  vector <BNode <custom::pair <float, std::string> > *> sortedPairs;
   ifstream fin;
   fin.open(fileName.c_str());
   
   if (fin.fail())
      return;
   
   
   
   
  list <BNode <custom::pair <float, std::string> > * > readInto;  
  std::string letter;
  float number;

  while (fin >> letter >> number)
    {
        custom::pair <float, std::string> temp(number, letter);
        BNode <custom::pair <float, std::string> > * tempNode;
        tempNode = new BNode <custom::pair <float, std::string> > (temp);
        readInto.push_back(tempNode);
    }
   fin.close();
   
   
   
   sortInsertion(readInto, compNodes);
   
   BNode <custom::pair <float, std::string> > * root = createHuffTree(readInto);
   list <custom::pair <std::string, string> > codeTable;
   string nothing = "";
   
   encodeHuff(root, nothing, codeTable);
   typename list <custom::pair <std::string, string> > :: iterator tableA;
   sortInsertion(codeTable, compPairs);
   tableA = codeTable.begin();
   
   for(; tableA != codeTable.end(); tableA++)
   {
     custom::pair <std::string, string> pairTemp = *tableA;
     cout << pairTemp.first << " = " << pairTemp.second << endl;
   }
   
   return;
}
