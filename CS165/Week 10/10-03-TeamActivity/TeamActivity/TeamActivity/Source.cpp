#include <iostream>
#include "LinkedList.h"

using namespace std;

void promptNumbers(LinkedList<int> &numbers)
{
	int i = 1;
	while (i != 0)
	{
		cout << "Enter number: ";
		cin >> i;
		if (i != 0)
			numbers.insert(i);
	}
}

void displayNumbers(const LinkedList<int> numbers)
{
	numbers.forEach([](int i) { cout << i << endl; })
}

void removeOdds(LinkedList<int> &numbers)
{
	list <int> ::const_iterator it = numbers.begin();
	while (it != numbers.end())
	{
		if (*it % 2 == 0)
			it = numbers.erase(it);
		else
			it++;
	}
}

int main()
{
	LinkedList<int> numbers;
	promptNumbers(numbers);
	displayNumbers(numbers);
	removeOdds(numbers);
	displayNumbers(numbers);
	return 0;
}


