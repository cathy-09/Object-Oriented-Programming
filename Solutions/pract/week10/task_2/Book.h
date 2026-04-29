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