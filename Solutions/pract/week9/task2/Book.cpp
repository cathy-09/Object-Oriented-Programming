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