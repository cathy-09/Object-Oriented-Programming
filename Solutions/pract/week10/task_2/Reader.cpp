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