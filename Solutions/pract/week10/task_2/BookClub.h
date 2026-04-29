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
