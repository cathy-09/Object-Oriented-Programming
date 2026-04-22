#include <iostream>
#include "Reader.h"

void printBooks(Book* books, size_t count, const char* label) 
{
    std::cout << label << ":" << std::endl;
    if (!books) {
        std::cout << "No book it that genre" << std::endl;
        return;
    }
    for (size_t i = 0; i < count; i++)
        std::cout << "  \"" << books[i].getTitle() << "\" - " << books[i].getAuthor() << std::endl;
}

int main() {
    Book def;
    std::cout << "Title:  " << def.getTitle() << std::endl;
    std::cout << "Author: " << def.getAuthor() << std::endl;

    Book b1("Dune", 4, "Frank Herbert", 13, Genre::SCIENCE_FICTION);
    Book b2("1984", 4, "George Orwell", 13, Genre::SCIENCE_FICTION);
    Book b3("The Hobbit", 10, "J.R.R. Tolkien", 14, Genre::FANTASY);
    Book b4("It", 2, "Stephen King", 12, Genre::HORROR);
    Book b5("Foundation", 10, "Isaac Asimov", 12, Genre::SCIENCE_FICTION);
    Book b6("The Doors of Stone", 18, "Patrick Rothfuss", 16, Genre::FANTASY);

    // --- Читател ---
    Reader maria("Maria", 5);

    maria.addBook(b1);
    maria.addBook(b2);
    maria.addBook(b3);
    maria.addBook(b4);
    maria.addBook(b5);
    maria.addBook(b6);

    Book* scifi = maria.getBooksByGenre(Genre::SCIENCE_FICTION);
    printBooks(scifi, 3, "Sci-Fi");

    Book* fantasy = maria.getBooksByGenre(Genre::FANTASY);
    printBooks(fantasy, 2, "Fantasy");

    Book* romance = maria.getBooksByGenre(Genre::ROMANCE);
    printBooks(romance, 0, "Romance");

    Reader maria2 = maria;
    Book* fantasy2 = maria2.getBooksByGenre(Genre::FANTASY);
    printBooks(fantasy2, 2, "Fantasy");

    Book b7("Mistborn", 8, "Brandon Sanderson", 17, Genre::FANTASY);
    maria.addBook(b7);

    Book* fantasy3 = maria.getBooksByGenre(Genre::FANTASY);
    printBooks(fantasy3, 3, "Fantasy");

    printBooks(fantasy2, 2, "Fantasy");

    Book b8;
    b8.setTitle("Neuromancer", 11);
    b8.setAuthor("William Gibson", 14);
    b8.setGenre(Genre::SCIENCE_FICTION);
    std::cout << "\"" << b8.getTitle() << "\" - " << b8.getAuthor() << std::endl;
}