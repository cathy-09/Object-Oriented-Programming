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
