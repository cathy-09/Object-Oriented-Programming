#define _CRT_SECURE_NO_WARNINGS
#include "Reader.h"
#include <cstring>

int Reader::genreIndex(Genre g) const
{
	return (int)g;
}

void Reader::copyFrom(const Reader& other)
{
	nameSize = other.nameSize;
	name = new char[nameSize + 1];
	strcpy(name, other.name);

	booksSize = other.booksSize;
	sizes = new size_t[GENRE_COUNT];
	books = new Book * [GENRE_COUNT];
	for (int i = 0; i < GENRE_COUNT; i++)
	{
		sizes[i] = other.sizes[i];
		if (sizes[i] > 0)
		{
			books[i] = new Book[sizes[i]];
			for (size_t j = 0; j < sizes[i]; j++)
			{
				books[i][j] = other.books[i][j];
			}
		}
		else
		{
			books[i] = nullptr;
		}
	}
}

void Reader::free()
{
	delete[] name;
	for (int i = 0; i < GENRE_COUNT; i++)
	{
		delete[] books[i];
	}
	delete[] books;
	delete[] sizes;
}

Reader::Reader(const char* n, size_t ns) : nameSize(ns), booksSize(0) 
{
	name = new char[ns + 1];
	strcpy(name, n);
	books = new Book * [GENRE_COUNT];
	sizes = new size_t[GENRE_COUNT];
	for (int i = 0; i < GENRE_COUNT; i++) 
	{
		books[i] = nullptr;
		sizes[i] = 0;
	}
}

Reader::Reader(const Reader& other)
{ 
	copyFrom(other);
}
Reader& Reader::operator=(const Reader& other)
{
	if (this != &other) 
	{
		free(); 
		copyFrom(other);
	}
	return *this;
}
Reader::~Reader() 
{
	free(); 
}

void Reader::addBook(Book book)
{
	int idx = genreIndex(book.getGenre());
	Book* newArr = new Book[sizes[idx] + 1];
	for (size_t i = 0; i < sizes[idx]; i++)
	{
		newArr[i] = books[idx][i];
	}
	newArr[sizes[idx]] = book;
	delete[] books[idx];
	books[idx] = newArr;
	sizes[idx]++;
	booksSize++;
}

Book* Reader::getBooksByGenre(Genre genre) const 
{
	int idx = genreIndex(genre);
	if (sizes[idx] > 0)
	{
		return books[idx];
	}
	else
	{
		return nullptr;
	}
}