# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица девета
```
Задача 1: Създайте енумерация Crop, представляваща различни растителни култури, които могат да бъдат засаждани. Стойностите да са: {WHEAT, BARLEY, CORN, NOTHING}.

Създайте клас Plot, описващ парче плодородна земя. Да има следните полета и член-функции:

полета:
int id - идентификационен номер. Трябва да е уникален! (Подсказва - използвайте статична член-променлива)
double width - ширина на парчето земя (в метри)
double height - височина на парчето земя (в метри)
Crop cropType - типът култура, засадена на парчето земя
член-функции:
конструктор по подразбиране - нека измеренията да са 50х50 и културата да е NOTHING
конструктор с параметри
гетъри и сетъри за член-данните, освен сетър за cropType
void sow(Crop cropType) - засажда култура на парчето земя
void reap() - събира културата на парчето земя. На парчето земя няма да има нищо ново засадено, докато не се засади със sow
Създайте клас Farmer, описващ фермер. Да има следните полета и член-функции:

полета:
char* name - името на фермера. Може да е с произволна дължина
size_t nameSize - размерът на името на фермера
Plot** plots - масив от указатели към парчета земя. Обърнете внимание, че различни фермери може да притежават една ферма и следователно едни парчета земя!
size_t plotSize - размерът на масива от указатели към парчетата земя
член-функции:
голяма шестица, без конструктор по подразбиране
конструктор с параметри, приемащ име (и размер) и масив от указатели към парчета земя (и размера му).
addPlot(Plot* plot) - добави ново парче земя. Обърнете внимание, че ще е възможно да се наложи да преоразмерите масива!
void printField() - принтира каква култура се съдържа във всички парчета земя
Изтествайте класовете. Помислете - тук трябва deep copy или shallow copy?
```

`Решение:`

`Crop.h`
```h
#pragma once

enum class Crop 
{
    WHEAT,
    BARLEY,
    CORN,
    NOTHING
};
```

`Plot.h`
```h
#pragma once
#include "Crop.h"

class Plot 
{
private:
    static int nextId;
    int id;
    double width;
    double height;
    Crop cropType;

public:
    Plot();
    Plot(double width, double height, Crop crop);

    int getId() const;
    double getWidth() const;
    double getHeight() const;
    Crop getCropType() const;

    void setWidth(double w);
    void setHeight(double h);

    void sow(Crop crop);
    void reap();
};
```

`Plot.cpp`
```cpp
#include "Plot.h"

int Plot::nextId = 1;

Plot::Plot() : id(nextId++), width(50), height(50), cropType(Crop::NOTHING)
{

}

Plot::Plot(double width, double height, Crop crop) : id(nextId++), width(this->width), height(this->height), cropType(crop)
{

}

int Plot::getId() const 
{ 
	return id; 
}
double Plot::getWidth() const 
{
	return width;
}
double Plot::getHeight() const
{
	return height;
}
Crop Plot::getCropType() const 
{
	return cropType;
}

void Plot::setWidth(double w) 
{ 
	width = w; 
}
void Plot::setHeight(double h) 
{
	height = h; 
}

void Plot::sow(Crop crop) 
{ 
	cropType = crop; 
}

void Plot::reap() 
{
	cropType = Crop::NOTHING; 
}
```

`Farmer.h`
```h
#include "Plot.h"

class Farmer 
{
private:
    char* name;
    size_t nameSize;
    Plot** plots;
    size_t plotSize;
    
    void copyFrom(const Farmer& other);
    void free();

public:
    Farmer(const char* name, size_t nameSize, Plot** plots, size_t plotSize);
    Farmer(const Farmer& other);
    Farmer& operator=(const Farmer& other);
    ~Farmer();

    void addPlot(Plot* plot);
    void printField() const;
};
```

`Farmer.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Farmer.h"
#include <iostream>

void Farmer::copyFrom(const Farmer& other) 
{
    nameSize = other.nameSize;
    name = new char[nameSize + 1];
    strcpy(name, other.name);

    plotSize = other.plotSize;
    plots = new Plot * [plotSize];
    for (size_t i = 0; i < plotSize; i++)
    {
        plots[i] = other.plots[i];
    }
}

void Farmer::free() 
{
    delete[] name;
    delete[] plots;
}

Farmer::Farmer(const char* n, size_t ns, Plot** p, size_t ps) : nameSize(ns), plotSize(ps) 
{
    name = new char[nameSize + 1];
    strcpy(name, n);
    plots = new Plot * [plotSize];
    for (size_t i = 0; i < plotSize; i++)
    {
        plots[i] = p[i];
    }
}

Farmer::Farmer(const Farmer& other) 
{ 
    copyFrom(other); 
}

Farmer& Farmer::operator=(const Farmer& other) 
{
    if (this != &other) 
    {
        free();
        copyFrom(other);
    }
    return *this;
}

Farmer::~Farmer() 
{
    free(); 
}

void Farmer::addPlot(Plot* plot) 
{
    Plot** newPlots = new Plot * [plotSize + 1];
    for (size_t i = 0; i < plotSize; i++)
    {
        newPlots[i] = plots[i];
    }
    newPlots[plotSize] = plot;
    delete[] plots;
    plots = newPlots;
    plotSize++;
}

void Farmer::printField() const 
{
    for (size_t i = 0; i < plotSize; i++) 
    {
        std::cout << "Plot " << plots[i]->getId() << ": ";
        switch (plots[i]->getCropType()) 
        {
        case Crop::WHEAT:   
            std::cout << "Wheat" << std::endl;
            break;
        case Crop::BARLEY:  
            std::cout << "Barley" << std::endl;
            break;
        case Crop::CORN:   
            std::cout << "Corn" << std::endl;
            break;
        case Crop::NOTHING: 
            std::cout << "Nothing" << std::endl;
            break;
        }
    }
}
```

`task1.cpp`
```cpp
#include <iostream>
#include "Plot.h"
#include "Farmer.h"

int main()
{
    Plot p1(100, 200, Crop::WHEAT);
    Plot p2(50, 75, Crop::CORN);
    Plot p3;

    std::cout << "p1 id=" << p1.getId() << " WHEAT" << std::endl;
    std::cout << "p2 id=" << p2.getId() << " CORN" << std::endl;
    std::cout << "p3 id=" << p3.getId() << " NOTHING" << std::endl;

    p3.sow(Crop::BARLEY);
    std::cout << std::endl;

    p2.reap();
    std::cout << std::endl;

    Plot* arr1[] = { &p1, &p2 };
    Farmer ivan("Ivan", 4, arr1, 2);

    ivan.printField();

    ivan.addPlot(&p3);
    ivan.printField();
    std::cout << std::endl;

    Plot* arr2[] = { &p1 };
    Farmer petar("Petar", 5, arr2, 1);

    petar.printField();
    std::cout << std::endl;

    p1.reap();
    std::cout << "Ivan:" << std::endl;
    ivan.printField();
    std::cout << "Petar:" << std::endl;
    petar.printField();

    Farmer ivan2 = ivan;
    ivan2.printField();

    Plot p4(30, 30, Crop::BARLEY);
    ivan2.addPlot(&p4);
    ivan2.printField();
    ivan.printField();
}
```

<hr style="border-width: 5px !important;">

```
Задача 2:Да се създаде енумерация Genre, описваща жанрове на книги. Стойностите да са: {ROMANCE, HORROR, MYSTERY, SCIENCE_FICTION, FANTASY}.

Създайте клас Book, описващ книга. Да има следните полета и член-функции:

полета:
char* title - заглавието на книгата. Може да е с произволна дължина
size_t titleSize - размерът на заглавието
char* author - името на автора. Може да е с произволна дължина
size_t authorSize - размерът на заглавието
Genre genre - жанрът
член-функции:
конструктор по подразбиране - нека заглаието да е "Default title", авторът - "Default Author", а жанрът - FANTASY
конструктор с параметри
сетъри и гетъри за всички полета
Създайте клас Reader, описващ читател. Да има следните полета и член-функции:

полета:
char* name - името на читателя. Може да е с произволна дължина
size_t nameSize - размерът на името
Book** books - масив от масиви към книги. Всеки елемент от books да сочи към масив от Book, където всички книги да са от един жанр.
size_t booksSize - размерът на books
size_t* sizes - масив от размерите на всеки масив, към който сочи books. Обърнете внимание, че ще има същия размер, като booksSizes
член-функции:
голяма шестица, без контруктор по подразбиране
конструктор с параметри, приещат име и размера му. Помислете как да инициализирате член-данните, свързани с книгите!
void addBook(Book book) - добавя книга към книгите на читателя. Обърнете внимание, че може да се наложи да оразмерявате един или повече масиви!
Book* getBooksByGenre(Genre genre) - връща масивът с книгите на читателя, които са от подадения жанр. Ако читателят няма книги от съответния жанр, да връща nullptr
Помислете - тук трябва deep copy или shallow copy?
```

`Решение:`

`Genre.h`
```h
#pragma once
#pragma once

enum class Genre 
{
    ROMANCE,
    HORROR,
    MYSTERY,
    SCIENCE_FICTION,
    FANTASY
};
```

`Book.h`
```h
#pragma once
#include "Genre.h"

class Book
{
private:
    char* title;
    size_t titleSize;
    char* author;
    size_t authorSize;
    Genre genre;
    void copyFrom(const Book& other);
    void free();

public:
    Book();
    Book(const char* title, size_t ts, const char* author, size_t as, Genre genre);
    Book(const Book& other);
    Book& operator=(const Book& other);
    ~Book();

    const char* getTitle() const;
    const char* getAuthor() const;
    Genre getGenre() const;
    void setTitle(const char* t, size_t ts);
    void setAuthor(const char* a, size_t as);
    void setGenre(Genre g);
};
```

`Book.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <iostream>

void Book::copyFrom(const Book& other) 
{
    titleSize = other.titleSize;
    title = new char[titleSize + 1];
    strcpy(title, other.title);

    authorSize = other.authorSize;
    author = new char[authorSize + 1];
    strcpy(author, other.author);

    genre = other.genre;
}

void Book::free() 
{
    delete[] title; 
    delete[] author; 
}

Book::Book() : titleSize(13), authorSize(14), genre(Genre::FANTASY) 
{
    title = new char[14]; 
    strcpy(title, "Default title");
    author = new char[15];
    strcpy(author, "Default Author");
}

Book::Book(const char* t, size_t ts, const char* a, size_t as, Genre g) : titleSize(ts), authorSize(as), genre(g)
{
    title = new char[ts + 1]; strcpy(title, t);
    author = new char[as + 1]; strcpy(author, a);
}

Book::Book(const Book& other) 
{
    copyFrom(other);
}

Book& Book::operator=(const Book& other) 
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

Book::~Book() 
{
    free();
}

const char* Book::getTitle() const 
{ 
    return title;
}
const char* Book::getAuthor() const 
{
    return author;
}
Genre Book::getGenre() const 
{
    return genre;
}
void Book::setTitle(const char* t, size_t ts) 
{
    delete[] title; titleSize = ts;
    title = new char[ts + 1]; strcpy(title, t);
}
void Book::setAuthor(const char* a, size_t as) 
{
    delete[] author; authorSize = as;
    author = new char[as + 1]; strcpy(author, a);
}
void Book::setGenre(Genre g) 
{
    genre = g;
}
```

`Reader.h`
```h
#pragma once
#include "Book.h"

class Reader
{
private:
    char* name;
    size_t nameSize;
    Book** books;
    size_t booksSize;
    size_t* sizes;
    void copyFrom(const Reader& other);
    void free();
    int genreIndex(Genre g) const;
    static const int GENRE_COUNT = 5;

public:
    Reader(const char* name, size_t nameSize);
    Reader(const Reader& other);
    Reader& operator=(const Reader& other);
    ~Reader();

    void addBook(Book book);
    Book* getBooksByGenre(Genre genre) const;
};
```

`Reader.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Reader.h"
#include <cstring>

int Reader::genreIndex(Genre g) const
{
	return (int)g;
}

void Reader::copyFrom(const Reader& other)
{
	nameSize = other.nameSize;
	name = new char[nameSize + 1];
	strcpy(name, other.name);

	booksSize = other.booksSize;
	sizes = new size_t[GENRE_COUNT];
	books = new Book * [GENRE_COUNT];
	for (int i = 0; i < GENRE_COUNT; i++)
	{
		sizes[i] = other.sizes[i];
		if (sizes[i] > 0)
		{
			books[i] = new Book[sizes[i]];
			for (size_t j = 0; j < sizes[i]; j++)
			{
				books[i][j] = other.books[i][j];
			}
		}
		else
		{
			books[i] = nullptr;
		}
	}
}

void Reader::free()
{
	delete[] name;
	for (int i = 0; i < GENRE_COUNT; i++)
	{
		delete[] books[i];
	}
	delete[] books;
	delete[] sizes;
}

Reader::Reader(const char* n, size_t ns) : nameSize(ns), booksSize(0) 
{
	name = new char[ns + 1];
	strcpy(name, n);
	books = new Book * [GENRE_COUNT];
	sizes = new size_t[GENRE_COUNT];
	for (int i = 0; i < GENRE_COUNT; i++) 
	{
		books[i] = nullptr;
		sizes[i] = 0;
	}
}

Reader::Reader(const Reader& other)
{ 
	copyFrom(other);
}
Reader& Reader::operator=(const Reader& other)
{
	if (this != &other) 
	{
		free(); 
		copyFrom(other);
	}
	return *this;
}
Reader::~Reader() 
{
	free(); 
}

void Reader::addBook(Book book)
{
	int idx = genreIndex(book.getGenre());
	Book* newArr = new Book[sizes[idx] + 1];
	for (size_t i = 0; i < sizes[idx]; i++)
	{
		newArr[i] = books[idx][i];
	}
	newArr[sizes[idx]] = book;
	delete[] books[idx];
	books[idx] = newArr;
	sizes[idx]++;
	booksSize++;
}

Book* Reader::getBooksByGenre(Genre genre) const 
{
	int idx = genreIndex(genre);
	if (sizes[idx] > 0)
	{
		return books[idx];
	}
	else
	{
		return nullptr;
	}
}
```

`task2.cpp`
```cpp
#include <iostream>
#include "Reader.h"

void printBooks(Book* books, size_t count, const char* label) 
{
    std::cout << label << ":" << std::endl;
    if (!books) {
        std::cout << "No book it that genre" << std::endl;
        return;
    }
    for (size_t i = 0; i < count; i++)
        std::cout << "  \"" << books[i].getTitle() << "\" - " << books[i].getAuthor() << std::endl;
}

int main() {
    Book def;
    std::cout << "Title:  " << def.getTitle() << std::endl;
    std::cout << "Author: " << def.getAuthor() << std::endl;

    Book b1("Dune", 4, "Frank Herbert", 13, Genre::SCIENCE_FICTION);
    Book b2("1984", 4, "George Orwell", 13, Genre::SCIENCE_FICTION);
    Book b3("The Hobbit", 10, "J.R.R. Tolkien", 14, Genre::FANTASY);
    Book b4("It", 2, "Stephen King", 12, Genre::HORROR);
    Book b5("Foundation", 10, "Isaac Asimov", 12, Genre::SCIENCE_FICTION);
    Book b6("The Doors of Stone", 18, "Patrick Rothfuss", 16, Genre::FANTASY);

    // --- Читател ---
    Reader maria("Maria", 5);

    maria.addBook(b1);
    maria.addBook(b2);
    maria.addBook(b3);
    maria.addBook(b4);
    maria.addBook(b5);
    maria.addBook(b6);

    Book* scifi = maria.getBooksByGenre(Genre::SCIENCE_FICTION);
    printBooks(scifi, 3, "Sci-Fi");

    Book* fantasy = maria.getBooksByGenre(Genre::FANTASY);
    printBooks(fantasy, 2, "Fantasy");

    Book* romance = maria.getBooksByGenre(Genre::ROMANCE);
    printBooks(romance, 0, "Romance");

    Reader maria2 = maria;
    Book* fantasy2 = maria2.getBooksByGenre(Genre::FANTASY);
    printBooks(fantasy2, 2, "Fantasy");

    Book b7("Mistborn", 8, "Brandon Sanderson", 17, Genre::FANTASY);
    maria.addBook(b7);

    Book* fantasy3 = maria.getBooksByGenre(Genre::FANTASY);
    printBooks(fantasy3, 3, "Fantasy");

    printBooks(fantasy2, 2, "Fantasy");

    Book b8;
    b8.setTitle("Neuromancer", 11);
    b8.setAuthor("William Gibson", 14);
    b8.setGenre(Genre::SCIENCE_FICTION);
    std::cout << "\"" << b8.getTitle() << "\" - " << b8.getAuthor() << std::endl;
}
```

<hr style="border-width: 5px !important;">

