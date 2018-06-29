/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include "vector.h"
#include "pair.h"
using custom::vector;


void huffman(const std::string & fileName);

struct huffmanCode
{
   string data;
   float  frequency;
};

bool operator<(huffmanCode const &, huffmanCode const &);
bool operator==(huffmanCode const &, huffmanCode const &);
bool operator!=(huffmanCode const &, huffmanCode const &);
bool operator>(huffmanCode const &, huffmanCode const &);
bool operator<=(huffmanCode const &, huffmanCode const &);
bool operator>=(huffmanCode const &, huffmanCode const &);

class HuffmanTree
{
public:
	HuffmanTree(huffmanCode left, huffmanCode right);
	void insert(huffmanCode newNode);
	void generateCodes();
	std::string getCode(huffmanCode);
private:
	void generateCodes(BNode<huffmanCode> * curNode, std::string code);

	BNode<huffmanCode> * head;
	custom::vector<custom::pair<huffmanCode, std::string> > huffmanCodes;
};

class Huffman
{
   public:
      void readFile(const string & fileName);
      void display();
	  void generateTree();
   private:
      custom::vector<huffmanCode> list;
	  custom::vector<HuffmanTree> trees;
};

#endif // HUFFMAN_h
