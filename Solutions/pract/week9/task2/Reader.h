#pragma once
#include "Book.h"

class Reader {
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