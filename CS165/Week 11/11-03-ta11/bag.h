#ifndef BAG_H
#define BAG_H

/***********************************************************
 * Class: Bag
 * Description: Holds ints...for now
 ***********************************************************/
template<typename T>
class Bag
{
private:
   int capacity;
   int size;
   int currentAddIndex;
   T* data;

public:
	Bag()
	{
		capacity = 5;
		size = 0;
		data = new T[capacity];
	}

	~Bag()
	{
		delete [] data;
	}
				
   // Getters
	int getCapacity() { return capacity; }
   int getCount()
   {
	   return size;
   }

   T getItem(int index)
   {
	   return data[index];
   }
   void addItem(T item)
   {
	   if (size >= capacity)
	   {
		   capacity *= 2;
		   //std::cout << "Capacity : " << capacity << std::endl;
		   T* temp = new T[capacity];
		   for (int i = 0; i < size; i++)
		   {
			   temp[i] = data[i];
		   }
		   delete data;
		   data = temp;
	   }

	   data[currentAddIndex] = item;
	   size++;
	   currentAddIndex++;
		
   }
   int find(T item)
   {
	   for (int i = 0; i < size; i++)
	   {
		   if (data[i] == item)
		   {
			   return i;
		   }
	   }

	   return -1; // Item not found, return error
   }

   void deleteItem(int index)
   {
	   for (int i = index; i < size -1; i++)
	   {
		   data[i] = data[i + 1];
	   }
	   data[size] = NULL;
	   size--; currentAddIndex--; // <-- this is the same.
   }
};

#endif

