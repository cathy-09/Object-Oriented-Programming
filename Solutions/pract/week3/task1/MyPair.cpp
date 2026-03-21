#include <iostream>
#include "MyPair.h"

MyPair::MyPair(int _first, int _second)
{
	this->first = _first;
	this->second = _second;
}

int MyPair::getFirst() const
{
	return this->first;
}

int MyPair::getSecond() const
{
	return this->second;
}

void MyPair::setFirst(int a)
{
	this->first = a;
}

void MyPair::setSecond(int b)
{
	this->second = b;
}

void MyPair::swapElements()
{
	int temp = this->first;
	this->first = this->second;
	this->second = temp;
}

void MyPair::printPair() const
{
	std::cout << "(" << first << ", " << second << ")" << std::endl;
}

int MyPair::maxElement() const
{
	if (this->first > this->second)
	{
		return this->first;
	}
	else
	{
		return this->second;
	}
}