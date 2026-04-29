#include <iostream>
#include "BookClub.h"

int main()
{
    BookClub club("Readers Club");
    club.addBook(std::make_unique<Book>("C++ Basics", "Bjarne"));
    club.addBook(std::make_unique<Book>("OOP", "Stroustrup"));
    club.addMember(std::make_unique<Reader>("Georgi", "Georgiev"));
    club.lendBook(0, 0);
    std::cout << "Book lent!" << std::endl;
    club.returnBook(0, 0);
    std::cout << "Book returned!" << std::endl;
}
