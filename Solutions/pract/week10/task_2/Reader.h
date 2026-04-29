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

