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
