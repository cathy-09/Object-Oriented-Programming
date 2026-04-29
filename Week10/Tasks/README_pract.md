# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица десета
```
Задача 1:
Създайте клас Apartment, който описва апартамент, със следните полета и член-функции:

полета:
string address - адресът
int numberOfRooms - броят стаи
член-функции:
конструктор с параметри
сетъри и гетъри за член-данните
функция, която връща колко души живеят в съответния апартамент
Създайте клас Tennant, която описва живущ, със следните полета и член-функции:

полета:
string firstName - първото име
string lastName - второто име
shared_ptr residence - апартаментът, в който човекът живее
член-функции:
конструктор с параметри
сетъри и гетъри за член-функциите
функция, която променя местоживеенето на човека (като променя указателя)
Изтествайте класовете.
```

`Решение:`

`Apartment.h`
```h
#pragma once
#include <string>
#include <vector>

class Tennant;

class Apartment
{
    std::string address;
    int numberOfRooms;
    std::vector<Tennant*> people;

public:
    Apartment(std::string address, int numberOfRooms);
    void setAddress(std::string address);
    std::string getAddress() const;
    void setNumberOfRooms(int numberOfRooms);
    int getNumberOfRooms() const;
    void addPerson(Tennant* person);
    int getPeopleCount() const;
};
```

`Apartment.cpp`
```cpp
#include "Apartment.h"
#include <iostream>

Apartment::Apartment(std::string address, int numberOfRooms)
{
    setAddress(address);
    setNumberOfRooms(numberOfRooms);
}

void Apartment::setAddress(std::string address)
{
    if (address.empty())
    {
        std::cout << "Empty";
        return;
    }
    this->address = address;
}

std::string Apartment::getAddress() const
{
    return address;
}

void Apartment::setNumberOfRooms(int numberOfRooms)
{
    if (numberOfRooms <= 0)
    {
        std::cout << "Invalid rooms number!";
        return;
    }
    this->numberOfRooms = numberOfRooms;
}

int Apartment::getNumberOfRooms() const
{
    return numberOfRooms;
}

void Apartment::addPerson(Tennant* person)
{
    people.push_back(person);
}

int Apartment::getPeopleCount() const
{
    return people.size();
}
```

`Tennant.h`
```h
#pragma once
#include <string>
#include <memory>

class Apartment;

class Tennant
{
private:
    std::string firstName;
    std::string lastName;
    std::shared_ptr<Apartment> residence;

public:
    Tennant(std::string firstName, std::string lastName, std::shared_ptr<Apartment> residence);
    void setFirstName(std::string firstName);
    std::string getFirstName() const;
    void setLastName(std::string lastName);
    std::string getLastName() const;
    void changeResidence(std::shared_ptr<Apartment> newResidence);
};
```

`Tennant.cpp`
```cpp
#include "Tennant.h"
#include "Apartment.h"
#include <iostream>

Tennant::Tennant(std::string firstName, std::string lastName, std::shared_ptr<Apartment> residence)
{
    setFirstName(firstName);
    setLastName(lastName);
    this->residence = residence;
    if (this->residence)
    {
        this->residence->addPerson(this);
    }
}

void Tennant::setFirstName(std::string firstName)
{
    if (firstName.empty())
    {
        std::cout << "Empty";
        return;
    }
    this->firstName = firstName;
}

std::string Tennant::getFirstName() const
{
    return firstName;
}

void Tennant::setLastName(std::string lastName)
{
    if (lastName.empty())
    {
        std::cout << "Empty";
        return;
    }
    this->lastName = lastName;
}

std::string Tennant::getLastName() const
{
    return lastName;
}

void Tennant::changeResidence(std::shared_ptr<Apartment> newResidence)
{
    residence = newResidence;
    if (newResidence)
    {
        newResidence->addPerson(this);
    }
}
```

`task_1.cpp`
```cpp
#include <iostream>
#include "Apartment.h"
#include "Tennant.h"

int main()
{
    std::shared_ptr<Apartment> a1 = std::make_shared<Apartment>("Sofia Center", 3);
    Tennant t1("Ivan", "Ivanov", a1);
    Tennant t2("Maria", "Petrova", a1);
    std::cout << "People in apartment: " << a1->getPeopleCount() << std::endl;
    std::shared_ptr<Apartment> a2 = std::make_shared<Apartment>("Plovdiv", 2);
    t1.changeResidence(a2);
    std::cout << "People in new apartment: " << a2->getPeopleCount() << std::endl;
}
```

<hr style="border-width: 5px !important;">

```
Задача 2:Да се създаде клас Book, описващ книга, със следните полета и член-функции:

полета:
string title - заглавие
string author - автор
член-функции:
конструктор с параметри
сетъри и гетъри за член-функциите
Да се създаде клас Reader, описващ читател, със следните полета и член-функции:

полета:
string firstName
string lastName
vector<unique_ptr> borrowedBooks - книгите, които притежава
член-функции:
конструктор с параметри - firstName и lastName, а векторът да се инициализира без елементи
сетъри и гетъри за член-функциите
функция, която добавя книга в borrowedBooks
функция, която премахна книга от borrowedBooks
Да се създаде клас BookClub, описващ клуб за четене на книги, със следните полета и член-функции:

полета:
string name - името на клуба
vector<unique_ptr> clubBooks - книгите на клуба, които са налични в библиотеката
vector<unique_ptr<> members - членовете на клуба
член-функции:
конструктор с параметър - името на клуба, а векторите да се инициализират без елементи
функция, която добавя книга към колекцията на клуба
функция, която добавя член към клуба
функция, която премахна книга от колекцията на клуба
функция, която премахва член на клуба
функция, която заема книга на даден член на клуба - тогава книгата изчезва от библиотеката на клуба и се прехвърля в книгите на члена
функция, която връща заета книга - тогава книгата изчезва от взетите книги на члена и се прехвърля в библиотеката на клуба
Изтествайте класовете.
```

`Решение:`

`Book.h`
```h
#pragma once
#include <string>
class Book 
{
    std::string title;
    std::string author;

public:
    Book(std::string title, std::string author);
    void setTitle(std::string title);
    std::string getTitle() const;
    void setAuthor(std::string author);
    std::string getAuthor() const;
};
```

`Book.cpp`
```cpp
#include "Book.h"
#include <iostream>

Book::Book(std::string title, std::string author)
{
	setTitle(title);
	setAuthor(author);
}

void Book::setTitle(std::string title)
{
    if (title.empty())
    {
        std::cout << "Empty";
        return;
    }
    this->title = title;
}

std::string Book::getTitle() const
{
    return title;
}

void Book::setAuthor(std::string author)
{
    if (author.empty())
    {
        std::cout << "Empty";
        return;
    }
    this->author = author;
}

std::string Book::getAuthor() const
{
    return author;
}
```

`Reader.h`
```h
#pragma once
#include <string>
#include <vector>
#include "Book.h"
#include <memory>
class Reader
{
    std::string firstName;
    std::string lastName;
    std::vector<std::unique_ptr<Book>> borrowedBooks;

public:
    Reader(std::string firstName, std::string lastName);
    void addBook(std::unique_ptr<Book> book);
    std::unique_ptr<Book> removeBook(int index);
};
```

`Reader.cpp`
```cpp
#include "Reader.h"
#include <iostream>

Reader::Reader(std::string firstName, std::string lastName) : firstName(firstName), lastName(lastName)
{

}

void Reader::addBook(std::unique_ptr<Book> book) 
{
    borrowedBooks.push_back(std::move(book));
}

std::unique_ptr<Book> Reader::removeBook(int index) 
{
    if (index < 0 || index >= borrowedBooks.size())
    {
        std::cout << ("Index was out of bounds!");
    }

    auto book = move(borrowedBooks[index]);
    borrowedBooks.erase(borrowedBooks.begin() + index);
    return book;
}
```

`BookClub.h`
```h
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Book.h"
#include "Reader.h"
class BookClub
{
    std::string name;
    std::vector<std::unique_ptr<Book>> clubBooks;
    std::vector<std::unique_ptr<Reader>> members;

public:
    BookClub(std::string name);
    void addBook(std::unique_ptr<Book> book);
    void addMember(std::unique_ptr<Reader> reader);
    std::unique_ptr<Book> removeBook(int i);
    std::unique_ptr<Reader> removeMember(int i);
    void lendBook(int bookIndex, int memberIndex);
    void returnBook(int memberIndex, int bookIndex);
};
```

`BookClub.cpp`
```cpp
#include "BookClub.h"
#include <iostream>

BookClub::BookClub(std::string name) :name(name)
{

}

void BookClub::addBook(std::unique_ptr<Book> book) 
{
    clubBooks.push_back(std::move(book));
}

void BookClub::addMember(std::unique_ptr<Reader> reader)
{
    members.push_back(std::move(reader));
}

std::unique_ptr<Book> BookClub::removeBook(int i) 
{
    if (i < 0 || i >= clubBooks.size())
    {
        std::cout << ("Index was out of bounds!");
    }
    std::unique_ptr<Book> book = std::move(clubBooks[i]);
    clubBooks.erase(clubBooks.begin() + i);
    return book;
}

std::unique_ptr<Reader> BookClub::removeMember(int i)
{
    if (i < 0 || i >= (int)members.size())
    {
        std::cout << "Index was out of bounds!";
        return nullptr;
    }
    std::unique_ptr<Reader> member = std::move(members[i]);
    members.erase(members.begin() + i);
    return member;
}

void BookClub::lendBook(int bookIndex, int memberIndex)
{
    std::unique_ptr<Book> book = removeBook(bookIndex);
    members[memberIndex]->addBook(std::move(book));
}

void BookClub::returnBook(int memberIndex, int bookIndex)
{
    std::unique_ptr<Book> book = members[memberIndex]->removeBook(bookIndex);
    addBook(std::move(book));
}
```

`task_2.cpp`
```cpp
#include <iostream>
#include "BookClub.h"

int main()
{
    BookClub club("Readers Club");
    club.addBook(std::make_unique<Book>("C++ Basics", "Bjarne"));
    club.addBook(std::make_unique<Book>("OOP", "Stroustrup"));
    club.addMember(std::make_unique<Reader>("Georgi", "Georgiev"));
    club.lendBook(0, 0);
    std::cout << "Book lent!" << std::endl;
    club.returnBook(0, 0);
    std::cout << "Book returned!" << std::endl;
}
```

<hr style="border-width: 5px !important;">
