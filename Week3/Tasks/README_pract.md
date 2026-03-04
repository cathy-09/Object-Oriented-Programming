# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица трета
`Задача 1: Да се създаде клас MyPair, със следните полета и член-функции:
полета: 
int first,  
int second
член-функции:
конструктор по подразбиране и с параметри (написани като един конструктор)
getFirst(), 
getSecond(), 
setFirst(int a), 
setSecond(int b), 
swapElements() – разменя first и second, 
printPair() – отпечатва (first, second), 
maxElement() – връща по-голямата стойност от двата елемента.`

`Решение:`

`MyPair.h`
```h
#pragma once
#include <iostream>

class MyPair
{
private:
	int first;
	int second;
public:
	MyPair(int _first = 0, int _second = 0);
	int getFirst() const;
	int getSecond() const;
	void setFirst(int a);
	void setSecond(int b);
	void swapElements();
	void printPair() const;
	int maxElement() const;
};
```

`MyPair.cpp`
```cpp
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
```

`task1.cpp`
```cpp
#include <iostream>
#include "MyPair.h"

int main()
{
    MyPair pair1;
    MyPair pair2{ 5,10 };

    pair1.printPair();
    pair2.printPair();

    pair1.setFirst(3);
    pair1.setSecond(7);

    pair1.printPair();

    pair2.swapElements();
    pair2.printPair();

    std::cout << pair1.maxElement();
    std::cout << std::endl;
    std::cout << pair2.maxElement();
}

```

<hr style="border-width: 5px !important;">
