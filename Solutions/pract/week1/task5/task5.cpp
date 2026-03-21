#include <iostream>
#include <cstring>

const int MAX_BOOKS = 5;
const int MAX_STR = 51;

enum class Genre
{
    ROMAN,
    HISTORICAL,
    POETRY,
    OTHER
};

struct Book
{
    char title[MAX_STR];
    char author[MAX_STR];
    Genre genre;
    bool available;
};

struct Library
{
    Book books[MAX_BOOKS];
    int count;
};

const char* genreToString(Genre genre)
{
    switch (genre)
    {
    case Genre::ROMAN: return "Roman";
    case Genre::HISTORICAL: return "Historical";
    case Genre::POETRY: return "Poetry";
    case Genre::OTHER: return "Other";
    default: return "Unknow";
    }
}

Book initBook(const char* title, const char* author, Genre genre)
{
    Book book;
    std::strcpy(book.title, title);
    std::strcpy(book.author, author);
    book.genre = genre;
    book.available = true;
    return book;
}

void addBook(Library& library, const Book& book)
{
    if (library.count >= MAX_BOOKS)
    {
        std::cout << "Library is full!" << std::endl;
        return;
    }
    library.books[library.count++] = book;
}

bool takeBook(Library& library, const char* title)
{
    for (int i = 0; i < library.count; i++)
    {
        if (strcmp(library.books[i].title, title) == 0)
        {
            if (library.books[i].available)
            {
                library.books[i].available = false;
                return true;
            }
            else
            {
                std::cout << "Книгата вече е взета!" << std::endl;
                return false;
            }
        }
    }
    std::cout << "Book with that title does not exist!";
    return false;
}

bool returnBook(Library& library, const char* title)
{
    for (int i = 0; i < library.count; i++)
    {
        if (strcmp(library.books[i].title, title) == 0)
        {
            if (!library.books[i].available)
            {
                library.books[i].available = true;
                return true;
            }
            else
            {
                std::cout << "The book is not available" << std::endl;
                return false;
            }
        }
    }
    std::cout << "Book with that title does not exist!" << std::endl;
    return false;
}

void printLibrary(const Library& library)
{
    for (int i = 0; i < library.count; i++)
    {
        std::cout << "Title: " << library.books[i].title << std::endl;
        std::cout << "Author: " << library.books[i].author << std::endl;
        std::cout << "Genre: " << genreToString(library.books[i].genre) << std::endl;
        std::cout << "Available: " << (library.books[i].available ? "Yes" : "No") << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
}

int main()
{
    Library library;
    library.count = 0;

    addBook(library, initBook("War and Peace", "Leo Tolstoy", Genre::ROMAN));
    addBook(library, initBook("Eugene Onegin", "Pushkin", Genre::POETRY));
    addBook(library, initBook("History of Bulgaria", "Ivan Vazov", Genre::HISTORICAL));
    printLibrary(library);
    takeBook(library, "War and Peace");
    printLibrary(library);
    returnBook(library, "War and Peace");
    printLibrary(library);
}