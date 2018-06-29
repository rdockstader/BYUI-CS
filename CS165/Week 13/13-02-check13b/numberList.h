/*******************
 * NumberList class
 *******************/
#ifndef NUMBER_LIST_H
#define NUMBER_LIST_H

#include <iostream>

class NumberList
{
private:
   int size;
   int *array;

public:
   NumberList()
   {
      size = 0;
      array = NULL;
   }


   // TODO: Add your constructor and destructor
   NumberList(int size) 
   { 
	   this->size = size;  
	   array = new int[size];

	   for(int i = 0; i < size; i++)
	   {
		   array[i] = 0;
	   }
   }

   NumberList(const NumberList &l2)
   {
	   this->size = l2.size;
	   array = new int[this->size];
	   for (int i = 0; i < this->size; i++)
	   {
		   this->array[i] = l2.array[i];
	   }
   }

   ~NumberList()
   {
	   delete[] array;

	   array = NULL;

	   std::cout << "Freeing memory" << std::endl;
   }

   NumberList& operator=(const NumberList &l2)
   {
	   if (array != NULL)
		   delete[] array;

	   this->size = l2.size;
	   array = new int[this->size];
	   for (int i = 0; i < this->size; i++)
	   {
		   this->array[i] = l2.array[i];
	   }

	   return *this;
   }


   int getNumber(int index) const;
   void setNumber(int index, int value);
   
   void displayList() const;

};

#endif
