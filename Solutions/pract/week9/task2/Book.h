#pragma once
#include "Genre.h"

class Book {
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