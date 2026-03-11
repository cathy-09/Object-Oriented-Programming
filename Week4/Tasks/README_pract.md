# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица четвърта
```
Задача 1: Да се създаде клас MyPair, със следните полета и член-функции:
полета:
- int first,
- int second 
член-функции:
- конструктор по подразбиране и с параметри (написани като един конструктор)
- getFirst(),
- getSecond(),
- setFirst(int a),
- setSecond(int b),
- swapElements() – разменя first и second,
- printPair() – отпечатва (first, second),
- maxElement() – връща по-голямата стойност от двата елемента.
```

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

```
Задача 2: Да се създаде клас DynamicArray(примитивен std::vector), със следните полета и член-функции:
полета:
- int* data
- size_t size
- size_t capacity
член-функции:
- конструктор - задава начален капацитет
- деструктор
- push_back(int value) - добавя елемент накрая на масива
- pop_back() - премахва последния елемент в масива
- set(index, value) - променя стойността на елемента на даден index
- get(index) - връща стойността елемента на даден индекс
- getSize()
- getCapacity()
```

> [!TIP]
> Hint за push_back(int value)
> Напишете си private помощна функция resize(size_t newCapacity), която да увеличава размера на масива при нужда. Функцията resize трябва да задели нов масив с размер newCapacity, да копира старите елементи, да освободи старата памет и да обнови указателя data и капацитета. При извикване на push_back(int value), ако size е равно на capacity, трябва да се извика resize, например с удвояване на капацитета.

`Решение:`

`DynamicArray.h`
```h
#pragma once
#include <iostream>
using namespace std;

class DynamicArray 
{
private:
    int* data;
    size_t size;
    size_t capacity;
    void resize(size_t newCapacity);

public:
    DynamicArray(size_t initialCapacity = 2);
    ~DynamicArray();
    void push_back(int value);
    void pop_back();
    void set(size_t index, int value);
    int get(size_t index) const;
    size_t getSize() const;
    size_t getCapacity() const;
    void print() const;
};
```

`DynamicArray.cpp`
```cpp
#include "DynamicArray.h"

DynamicArray::DynamicArray(size_t initialCapacity)
{
    if (initialCapacity == 0)
    {
        initialCapacity = 2;
    }
    data = new int[initialCapacity];
    size = 0;
    capacity = initialCapacity;
}

DynamicArray::~DynamicArray() 
{
    delete[] data;
}

void DynamicArray::resize(size_t newCapacity) 
{
    int* newData = new int[newCapacity];
    for (size_t i = 0; i < size; ++i) 
    {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void DynamicArray::push_back(int value) 
{
    if (size >= capacity) 
    {
        resize(capacity * 2); 
    }
    data[size] = value;
    ++size;
}

void DynamicArray::pop_back()
{
    if (size > 0) 
    {
        --size;
    }
    else 
    {
        cout << "Empty array!" << endl;
    }
}

void DynamicArray::set(size_t index, int value) 
{
    if (index < size) 
    {
        data[index] = value;
    }
    else 
    {
        cout << "Error in index!" << endl;
    }
}

int DynamicArray::get(size_t index) const 
{
    if (index < size) 
    {
        return data[index];
    }
    else 
    {
        cout << "Error in index!" << endl;
        return -1; 
    }
}

size_t DynamicArray::getSize() const 
{
    return size;
}

size_t DynamicArray::getCapacity() const 
{
    return capacity;
}

void DynamicArray::print() const 
{
    cout << "[";
    for (size_t i = 0; i < size; ++i) 
    {
        cout << data[i];
        if (i != size - 1)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}
```

`task2.cpp`
```cpp
#include <iostream>
#include "DynamicArray.h"

int main()
{
    DynamicArray arr(2);

    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    arr.push_back(40);

    arr.print();
    cout << "Size: " << arr.getSize() << ", Capacity: " << arr.getCapacity() << endl;

    arr.set(1, 25);
    arr.print();

    cout << "Element on index 2: " << arr.get(2) << endl;

    arr.pop_back();
    arr.print();
    cout << "Size: " << arr.getSize() << ", Capacity: " << arr.getCapacity() << endl;

    arr.set(10, 100);
    cout << "Element on index 10: " << arr.get(10) << endl;
}
```

<hr style="border-width: 5px !important;">

```
Задача 3: Да се създаде клас MyStack(ваша имплементация на std::stack, реализиран с масив), със следните полета и член-функции:
Стек - абстрактна структура от данни от линеен вид при която последователността на добавяне на елементи е точно обратната на последователността на извличане на елементи от нея (FILO).

полета:
- int* data
- size_t size
- size_t capacity
член-функции:
- push(int value) - добавя нов елемент на върха на стека
- pop() - премахва елемента на върха на стека
- top() - връща елемента на върха на стека
- empty() - връща true, ако в стека няма елементи
- getSize() - връща броя елементи в стека
```

> [!TIP]
> Hint за push(int value)
> Напишете си private помощна функция resize(size_t newCapacity), която да увеличава размера на масива при нужда. Функцията resize трябва да задели нов масив с размер newCapacity, да копира старите елементи, да освободи старата памет и да обнови указателя data и капацитета. При извикване на push(int value), ако size е равно на capacity, трябва да се извика resize, например с удвояване на капацитета.

`Решение:`

`MyStack.h`
```h
#pragma once
#include <iostream>
using namespace std;

class MyStack 
{
private:
    int* data;
    size_t currentSize;
    size_t capacity;
    void resize(size_t newCapacity);

public:
    MyStack(size_t initialCapacity = 2);
    ~MyStack();
    void push(int value);
    void pop();
    int top() const;
    bool empty() const;
    size_t size() const;
};
```

`MyStack.cpp`
```cpp
#include "MyStack.h"

MyStack::MyStack(size_t initialCapacity) 
{
    if (initialCapacity == 0)
    {
        initialCapacity = 2;
    }
    data = new int[initialCapacity];
    currentSize = 0;
    capacity = initialCapacity;
}

MyStack::~MyStack() 
{
    delete[] data;
}

void MyStack::resize(size_t newCapacity) 
{
    int* newData = new int[newCapacity];
    for (size_t i = 0; i < currentSize; i++) 
    {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void MyStack::push(int value) 
{
    if (currentSize >= capacity) 
    {
        resize(capacity * 2);
    }
    data[currentSize] = value;
    currentSize++;
}

void MyStack::pop() 
{
    if (currentSize > 0) 
    {
        currentSize--;
    }
    else 
    {
        cout << "Stack is empty!" << endl;
    }
}

int MyStack::top() const
{
    if (currentSize > 0) 
    {
        return data[currentSize - 1];
    }
    else
    {
        cout << "Stack is empty!" << endl;
        return -1;
    }
}

bool MyStack::empty() const 
{
    return currentSize == 0;
}

size_t MyStack::size() const 
{
    return currentSize;
}
```

`task3.cpp`
```cpp
#include <iostream>
#include "MyStack.h"
using namespace std;

int main()
{
    MyStack stack(2);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Top element: " << stack.top() << endl;
    cout << "Size: " << stack.size() << endl;

    stack.pop();
    cout << "Top after pop: " << stack.top() << endl;

    stack.pop();
    stack.pop();
    stack.pop();

    cout << "Is empty: " << stack.empty() << endl; //1 is true
}
```

<hr style="border-width: 5px !important;">
