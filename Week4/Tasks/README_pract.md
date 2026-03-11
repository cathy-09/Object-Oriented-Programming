# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица четвърта
```
Задача 1: ДДа се създаде клас UserAccount, със следните полета и член-функции:
полета:
- username
- id
- и още нещо :)
член-функции:
- конструктор по подразбиране (генериран от компилатора)
- конструктор с параметри, приемащ потребителско име и идентификационен номер
- статичен метод, който връща броя на акаунтите, създадени с подадени параметри (в тази задача ще приемаме, че при изтриване на акаунт, броят НЕ намалява)
- деструктор (генериран от компилатора)
- да се забрани копиращият конструктор
- да се забрани оператор=
```

> [!TIP]
> Изпозвайте статична променлива за броя на създадените акаунти. (това е липсващата член-променлива :) )
> 
> За да използвате автоматичната реализация на специална член-функция от компилатора, може да използвате = default.
> 
> За да забраните използването на дадена специална член-функция (например копиращ конструктор или оператор =), използвайте = delete.

`Решение:`

`UserAccount.h`
```h
#pragma once
#include <string>

class UserAccount
{
private:
    std::string username;
    int id;

    static int accountsCount;

public:
    UserAccount() = default;

    UserAccount(const std::string& username, int id);

    static int getAccountsCount();

    ~UserAccount() = default;

    UserAccount(const UserAccount&) = delete;
    UserAccount& operator=(const UserAccount&) = delete;
};
```

`UserAccount.cpp`
```cpp
#include "UserAccount.h"

int UserAccount::accountsCount = 0;

UserAccount::UserAccount(const std::string& username, int id)
{
	this->username = username;
	this->id = id;

	accountsCount++;
}

int UserAccount::getAccountsCount()
{
	return accountsCount;
}
```

`task1.cpp`
```cpp
#include <iostream>
#include "UserAccount.h"

int main()
{
    UserAccount u1("Anna", 1);
    UserAccount u2("Ivan", 2);
    UserAccount u3("John", 3);

    std::cout << UserAccount::getAccountsCount();
}
```

<hr style="border-width: 5px !important;">

```
Задача 2: Да се създаде клас StudentList, със следните полета и член-функции:
полета:
- studentsNames (динамичен масив от имената на студентите)
- studentsCount
- maxCapacity
член-функции:
- конструктор по подразбиране, който заделя масив за точно 10 имена (в тази задача масива няма да се resize-ва)
- метод, който да принтира всички имена
- метод, който да добавя име на края на списъка (само ако има място в масива, т.е. броят на имената в списъка е по-малък от 10)
- метод, който да пренаписва име на дадена позиция в списъка (позицията трябва да бъде валидна)
- помислете в тази задача дали трябва да се пише деструктор
```

> [!TIP]
> помислете в тази задача дали трябва да се пише деструктор
>ДА. Трябва да се напише деструктор тъй като се заделя динамична памет, която трябва да бъде освободена в края на жизнения цикъл на обекта, в противен случай ще се получи оттечка на памет.

```
Продължение на задачата:
- Създайте обект sl1.
- В sl1 добавете имената Anna, Ivan, John.
- Създайте обект sl2.
- Преравнете sl2 на sl1 (т.е. sl2 = sl1).
- Принтирайте имената в sl1.
- Променете второто име в sl2 на Maria.
- Принтирайте имената в sl1 отново.
```

`Решение:`

`StudentList.h`
```h
#pragma once
#include <string>
class StudentList
{
private:
    std::string* studentsNames;
    int studentsCount;
    int maxCapacity;

    void copyFrom(const StudentList& other);
    void free();

public:
    StudentList();

    StudentList(const StudentList& other);

    StudentList& operator=(const StudentList& other);

    ~StudentList();

    void print() const;

    void addStudent(const std::string& name);

    void setStudent(int index, const std::string& name);
};
```

`StudentList.cpp`
```cpp
#include "StudentList.h"
#include <iostream>

void StudentList::copyFrom(const StudentList& other)
{
    maxCapacity = other.maxCapacity;
    studentsCount = other.studentsCount;

    studentsNames = new std::string[maxCapacity];

    for (int i = 0; i < studentsCount; i++)
    {
        studentsNames[i] = other.studentsNames[i];
    }
}

void StudentList::free()
{
    delete[] studentsNames;
}

StudentList::StudentList()
{
    maxCapacity = 10;
    studentsCount = 0;
    studentsNames = new std::string[maxCapacity];
}

StudentList::StudentList(const StudentList& other)
{
    copyFrom(other);
}

StudentList& StudentList::operator=(const StudentList& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

StudentList::~StudentList()
{
    free();
}

void StudentList::print() const
{
    for (int i = 0; i < studentsCount; i++)
    {
        std::cout << studentsNames[i] << std::endl;
    }
}

void StudentList::addStudent(const std::string& name)
{
    if (studentsCount < maxCapacity)
    {
        studentsNames[studentsCount] = name;
        studentsCount++;
    }
}

void StudentList::setStudent(int index, const std::string& name)
{
    if (index >= 0 && index < studentsCount)
    {
        studentsNames[index] = name;
    }
}
```

`task2.cpp`
```cpp
#include <iostream>
#include "StudentList.h"

int main()
{
    StudentList sl1;

    sl1.addStudent("Anna");
    sl1.addStudent("Ivan");
    sl1.addStudent("John");

    StudentList sl2;

    sl2 = sl1;

    std::cout << "sl1:" << std::endl;
    sl1.print();

    sl2.setStudent(1, "Maria");

    std::cout << "sl1 after change in sl2:" << std::endl;
    sl1.print();
}
```

<hr style="border-width: 5px !important;">

`Задача 3: Добавете копиращ конструктор и оператор= към класовете, които имплементирахте на Практикум 3. (DynamicArray и MyStack)`

```
Задача 3.1: Да се създаде клас DynamicArray(примитивен std::vector), със следните полета и член-функции:
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
    void copyFrom(const DynamicArray& other);
    void free();

public:
    DynamicArray(size_t initialCapacity = 2);

    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other);

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

DynamicArray::DynamicArray(const DynamicArray& other)
{
    copyFrom(other);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
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

void DynamicArray::copyFrom(const DynamicArray& other)
{
    size = other.size;
    capacity = other.capacity;

    data = new int[capacity];

    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}

void DynamicArray::free()
{
    delete[] data;
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

    cout << endl;
    cout << "TEST COPY CONSTRUCTOR" << endl;

    DynamicArray arr2 = arr;
    arr2.set(0, 999);

    cout << "arr: ";
    arr.print();

    cout << "arr2: ";
    arr2.print();

    cout << endl;
    cout << "TEST OPERATOR =" << endl;

    DynamicArray arr3;
    arr3 = arr;

    arr3.set(1, 777);

    cout << "arr: ";
    arr.print();

    cout << "arr3: ";
    arr3.print();
}
```

<hr style="border-width: 5px !important;">

```
Задача 3.2: Да се създаде клас MyStack(ваша имплементация на std::stack, реализиран с масив), със следните полета и член-функции:
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
    void copyFrom(const MyStack& other);
    void free();

public:
    MyStack(size_t initialCapacity = 2);
    MyStack(const MyStack& other);
    MyStack& operator=(const MyStack& other);
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

MyStack::MyStack(const MyStack& other)
{
    copyFrom(other);
}

MyStack& MyStack::operator=(const MyStack& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
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

void MyStack::copyFrom(const MyStack& other)
{
    currentSize = other.currentSize;
    capacity = other.capacity;

    data = new int[capacity];

    for (size_t i = 0; i < currentSize; i++)
    {
        data[i] = other.data[i];
    }
}

void MyStack::free()
{
    delete[] data;
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
}#include <iostream>
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

    cout << "Is empty: " << stack.empty() << endl;
    //1 is true

    cout << endl;
    cout << "TEST COPY CONSTRUCTOR" << endl;

    MyStack s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    MyStack s2 = s1;

    s2.pop();

    cout << "s1 top: " << s1.top() << endl;
    cout << "s2 top: " << s2.top() << endl;

    cout << endl;
    cout << "TEST OPERATOR =" << endl;

    MyStack s3;
    s3 = s1;

    s3.pop();

    cout << "s1 top: " << s1.top() << endl;
    cout << "s3 top: " << s3.top() << endl; 
}
```

<hr style="border-width: 5px !important;">
