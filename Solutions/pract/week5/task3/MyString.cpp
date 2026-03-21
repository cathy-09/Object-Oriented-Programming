#include "MyString.h"
#include <string.h>
#include <iostream>

void MyString::copyFrom(const MyString& other)
{
	this->data = new char[other.capacity];
	strcpy(this->data, other.data);
	this->length = other.length;
	this->capacity = other.capacity;
}
void MyString::free()
{
	delete[] data;
}

MyString::MyString()
{
	this->capacity = 8;
	this->length = 0;
	this->data = new char[capacity];
	this->data[0] = '\0';
}

MyString::MyString(const char* string)
{
	this->length = strlen(string);
	this->capacity = length + 1;
	this->data = new char[capacity];
	strcpy(this->data, string);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MyString::~MyString()
{
	free();
}

size_t MyString::getLength() const
{
	return length;
}

void MyString::clear()
{
	this->data[0] = '\0';
	this->length = 0;
}

void MyString::setAt(size_t index, char ch)
{
	if (index < length)
	{
		data[index] = ch;
	}
}

int MyString::find(char ch)
{
	for (size_t i = 0; i < length; i++)
	{
		if (data[i] == ch)
		{
			return i;
		}
	}
	return -1;
}

void MyString::toUpper()
{
	for (size_t i = 0; i < length; i++)
	{
		if (data[i] >= 'a' && data[i] <= 'z')
		{
			data[i] = data[i] - ('a' - 'A');
		}
	}
}

void MyString::toLower()
{
	for (size_t i = 0; i < length; i++)
	{
		if (data[i] >= 'A' && data[i] <= 'Z')
		{
			data[i] = data[i] - ('a' - 'A');
		}
	}
}

void MyString::erase(size_t index)
{
	for (int i = index; i < length - 1; i++)
	{
		data[i] = data[i + 1];
		length--;
		data[length] = '\0';
	}
}

void MyString::insert(size_t index, char ch)
{
	if (length + 1 >= capacity)
	{
		return;
	}
	for (size_t i = length; i > index; i--)
	{
		data[i] = data[i - 1];
	}
	data[index] = ch;
	length++;
}

void MyString::append(const char* str)
{
	size_t len = strlen(str);
	if (len + length >= capacity)
	{
		return;
	}
	strcat(data, str);
	length = length + len;
}

void MyString::print()
{
	std::cout << data << std::endl;
}