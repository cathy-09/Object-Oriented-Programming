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
```

`Решение:`

`.h`
```h

```

`.cpp`
```cpp

```

`.cpp`
```cpp

```

<hr style="border-width: 5px !important;">
