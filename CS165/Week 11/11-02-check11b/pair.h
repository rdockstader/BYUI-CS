/*****************************************************
 * File: pair.h
 *
 * Purpose: Defines a Pair template class that can hold
 *   two items of arbitrary data types.
 ******************************************************/

#ifndef PAIR_H
#define PAIR_H

#include<iostream>
#include<string>
#include<assert.h>

template<typename T, typename F>
class Pair {
public:
	//Getters
	T getFirst();
	F getSecond();
	//Setters
	void setFirst(T value);
	void setSecond(F value);
	//Other
	void display();
private:
	T first;
	F second;
};


template<typename T, typename F>
T Pair<T, F>::getFirst()
{
	return first;
}


template<typename T, typename F>
F Pair<T, F>::getSecond()
{
	return second;
}

template<typename T, typename F>
void Pair<T, F>::setFirst(T value)
{
	first = value;
}

template<typename T, typename F>
void Pair<T, F>::setSecond(F value)
{
	second = value;
}

template<typename T, typename F>
void Pair<T, F>::display()
{
	std::cout << first << " - " << second;
}


#endif // PAIR_H
