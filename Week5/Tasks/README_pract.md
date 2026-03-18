# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица четвърта
```
Задача 1: Да се създаде клас Matrix, със следните полета и член-функции:

полета:
- int** data
- int rows
- int cols

член-функции:
- Голяма четворка
- Конструктор с параметри, приемащ брой редове и брой колони
- setValue(row, col, val)
- printMatrix()
```

`Решение:`

`Matrix.h`
```h
#pragma once
class Matrix
{
private:
	int** data;
	int rows;
	int cols;

	void copyFrom(const Matrix& other);
	void free();

public:
	Matrix(int rows, int cols);
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	~Matrix();

	void setValue(int rows, int cols, int value);
	void printMatrix();
};
```

`Matrix.cpp`
```cpp
#include "Matrix.h"
#include <iostream>

void Matrix::copyFrom(const Matrix& other)
{
	this->rows = other.rows;
	this->cols = other.cols;

	data = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		data[i] = new int[cols];
		for (int j = 0; j < cols; j++)
		{
			data[i][j] = other.data[i][j];
		}
	}
}

void Matrix::free()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}

Matrix::Matrix(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;

	data = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		data[i] = new int[cols] {0};
	}
}

Matrix::Matrix(const Matrix& other)
{
	copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Matrix::~Matrix()
{
	free();
}

void Matrix::setValue(int rows, int cols, int value)
{
	if (rows > this->rows || cols > this->cols)
	{
		return;
	}
	data[rows][cols] = value;
}

void Matrix::printMatrix()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << data[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
```

`task1.cpp`
```cpp
#include <iostream>
#include "Matrix.h"

int main()
{
    Matrix matrix1(2,3);
    matrix1.setValue(0, 0, 1);
    matrix1.setValue(0, 1, 2);
    matrix1.setValue(1, 2, 3);

    Matrix matrix2 = matrix1;
    Matrix matrix3(1, 1);
    matrix3 = matrix1;

    matrix1.printMatrix();
    std::cout << std::endl;
    matrix2.printMatrix();
    std::cout << std::endl;
    matrix3.printMatrix();
}
```

<hr style="border-width: 5px !important;">

```
Задача 2: Да се създаде клас City, със следните полета и член-функции:

полета:
- char* name
- long population

член-функции:
- Голяма четворка
- Конструктор с параметри, приемащ име и брой население
- Да се създаде клас Person, със следните полета и член-функции:

полета:
- birthplace (от тип City)
- age
- eyeColor (от тип изброен(enum))

член-функции:
- Конструктор с параметри, приемащ име и брой население на родния град на Person и цвят на очите

Помислете дали трябва да се разписва Голяма четворка за клас Person
```

`Решение:`

`City.h`
```h
#pragma once
class City
{
private:
	char* name;
	long population;

	void copyFrom(const City& other);
	void free();

public:
	City();
	City(const char* name, long population);
	City(const City& other);
	City& operator=(const City& other);
	~City();
};
```

`Решение:`

`Person.h`
```h
#pragma once
#include "City.h"

enum EyeColor
{
    BLUE,
    GREEN,
    BROWN
};

class Person
{
private:
    City birthplace;
    int age;
    EyeColor eyeColor;

public:
    Person(const char* cityName, long population, int age, EyeColor eyeColor);
};
```

`City.cpp`
```cpp
#include "City.h"
#include <string.h>

void City::copyFrom(const City& other)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    population = other.population;
}

void City::free()
{
    delete[] name;
}

City::City()
{
    name = new char[1];
    name[0] = '\0';
    population = 0;
}

City::City(const char* name, long population)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->population = population;
}

City::City(const City& other)
{
    copyFrom(other);
}

City& City::operator=(const City& other)
{
    if (this != &other) 
    {
        free();
        copyFrom(other);
    }
    return *this;
}

City::~City()
{
    free();
}

```

`Person.cpp`
```cpp
#include "Person.h"

Person::Person(const char* cityName, long population, int age, EyeColor eyeColor) : birthplace(cityName, population) 
{
    this->age = age;
    this->eyeColor = eyeColor;
}
```

`task2.cpp`
```cpp
#include <iostream>
#include "City.h"
#include "Person.h"

int main()
{
    Person person("Smolqn", 27000, 20, BROWN);
    City city1("Sofia", 1000000);
    City city2 = city1;
    City city3("Plovdiv", 350000);
    city3 = city1;
}
```

<hr style="border-width: 5px !important;">

`Задача 3: `
```
Да се създаде клас MyString, със следните полета и член-функции:

полета:
- char* data
- size_t length
- size_t capacity

член-функции:
- Голяма четворка
- Конструктор с параметри, приемащ текст
- гетър за length
- clear() - "зачиства" стринга
- setAt(size_t index, char ch) - замества символа на позиция index със символа ch (приемаме, че позициите се броят от 0)
- find(char ch) - връща индекса на първото срещане на символа или -1, ако ch не се среща в стринга
- toUpper() - преобразува всички букви в главни
- toLower() - преобразува всички букви в малки
- erase(size_t index) - "изтрива" символа на позиция index(приемаме, че позициите се броят от 0)
- insert(size_t index, char ch) - "вмъква" символа на позиция index(приемаме, че позициите се броят от 0)
- append(char* str) - "долепва" str в края на data
```

`Решение:`

`MyString.h`
```h
#pragma once
class MyString
{
private:
	char* data;
	size_t length;
	size_t capacity;

	void copyFrom(const MyString& other);
	void free();

public:
	MyString();
	MyString(const char* string);
	MyString(const MyString& other);
	MyString& operator =(const MyString& other);
	~MyString();

	size_t getLength() const;
	void clear();
	void setAt(size_t index, char ch);
	int find(char ch);
	void toUpper();
	void toLower();
	void erase(size_t index);
	void insert(size_t index, char ch);
	void append(const char* str);
	void print();
};
```

`MyString.cpp`
```cpp
#include "MyString.h"
#include <string.h>
#include <iostream>

void MyString::copyFrom(const MyString& other)
{
	this->data = new char[other.capacity];
	strcpy(this->data, other.data);
	this->length = other.length;
	this->capacity = other.capacity;
}
void MyString::free()
{
	delete[] data;
}

MyString::MyString()
{
	this->capacity = 8;
	this->length = 0;
	this->data = new char[capacity];
	this->data[0] = '\0';
}

MyString::MyString(const char* string)
{
	this->length = strlen(string);
	this->capacity = length + 1;
	this->data = new char[capacity];
	strcpy(this->data, string);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MyString::~MyString()
{
	free();
}

size_t MyString::getLength() const
{
	return length;
}

void MyString::clear()
{
	this->data[0] = '\0';
	this->length = 0;
}

void MyString::setAt(size_t index, char ch)
{
	if (index < length)
	{
		data[index] = ch;
	}
}

int MyString::find(char ch)
{
	for (size_t i = 0; i < length; i++)
	{
		if (data[i] == ch)
		{
			return i;
		}
	}
	return -1;
}

void MyString::toUpper()
{
	for (size_t i = 0; i < length; i++)
	{
		if (data[i] >= 'a' && data[i] <= 'z')
		{
			data[i] = data[i] - ('a' - 'A');
		}
	}
}

void MyString::toLower()
{
	for (size_t i = 0; i < length; i++)
	{
		if (data[i] >= 'A' && data[i] <= 'Z')
		{
			data[i] = data[i] - ('a' - 'A');
		}
	}
}

void MyString::erase(size_t index)
{
	for (int i = index; i < length - 1; i++)
	{
		data[i] = data[i + 1];
		length--;
		data[length] = '\0';
	}
}

void MyString::insert(size_t index, char ch)
{
	if (length + 1 >= capacity)
	{
		return;
	}
	for (size_t i = length; i > index; i--)
	{
		data[i] = data[i - 1];
	}
	data[index] = ch;
	length++;
}

void MyString::append(const char* str)
{
	size_t len = strlen(str);
	if (len + length >= capacity)
	{
		return;
	}
	strcat(data, str);
	length = length + len;
}

void MyString::print()
{
	std::cout << data << std::endl;
}
```

`task3.cpp`
```cpp
#include <iostream>
#include "MyString.h"
using namespace std;

int main() {
    MyString myString("hello");
    myString.print();

    myString.toUpper();
    cout << "Upper: "; 
    myString.print();

    myString.toLower();
    cout << "Lower: "; 
    myString.print();

    myString.setAt(0, 'H');
    cout << "setAt: ";
    myString.print();

    cout << "Find 'e': " << myString.find('e') << endl;

    myString.insert(1, 'X');
    cout << "Insert: ";
    myString.print();

    myString.erase(1);
    cout << "Erase: ";
    myString.print();

    myString.append("!!!");
    cout << "Append: "; 
    myString.print();

    myString.clear();
    cout << "Clear: "; 
    myString.print();

    MyString string2("test");
    MyString string3 = string2;
    string3.print();
    MyString string4("abc");
    string4 = string2;
    cout << "Assign: "; 
    string4.print();
}
```

<hr style="border-width: 5px !important;">
