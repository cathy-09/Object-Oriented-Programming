#include "Cipher.h"
#include <iostream>
std::string Cipher::reverseWord(const std::string& word)
{
	std::string reversed = word;
	std::reverse(reversed.begin(), reversed.end());
	return reversed;
}

int Cipher::wordCount() const
{
	int count = 0;
	std::size_t i = 0;
	while (i < text.size())
	{
		while (i < text.size() && text[i] == ' ') ++i;
		if (i < text.size())
		{
			++count;
			while (i < text.size() && text[i] != ' ')
			{
				++i;
			}
		}
	}
	return count;
}

std::string Cipher::getWord(int index) const
{
	int current = 0;
	std::size_t i = 0;
	while (i < text.size())
	{
		while (i < text.size() && text[i] == ' ')
		{
			++i;
		}
		if (i == text.size())
		{
			break;
		}
		std::size_t start = i;
		while (i < text.size() && text[i] != ' ')
		{
			++i;
		}
		if (current == index)
		{
			return text.substr(start, i - start);
		}
		++current;
	}
	return "";
}

Cipher::Cipher(const std::string& text) 
{
	for (char ch : text) 
	{
		if (!((ch >= 'a' && ch <= 'z') ||
			(ch >= 'A' && ch <= 'Z') ||
			(ch >= '0' && ch <= '9') ||
			ch == ' ')) 
		{
			std::cout << "Invalid character";
			return;
		}
	}
	this->text = text;
}

std::string Cipher::encrypt() const 
{
	if (text.empty())
	{
		return "";
	}
	std::string result;
	result.reserve(text.size());

	std::size_t i = 0;
	while (i < text.size()) 
	{
		if (text[i] == ' ')
		{
			result += ' ';
			++i;
		}
		else 
		{
			std::size_t start = i;
			while (i < text.size() && text[i] != ' ')
			{ 
				++i;
			} 
			result += reverseWord(text.substr(start, i - start));
		}
	}
	return result;
}

std::string Cipher::operator[](int index) const 
{
	if (index < 0) 
	{
		std::cout << "Index must be non-negative.";
	}
	int count = wordCount();
	if (index >= count) 
	{
		std::cout << "Index is out of range";
		return;
	}
	return getWord(index);
}

Cipher Cipher::operator+(const Cipher& other) const 
{
	std::string combined;
	if (!text.empty() && !other.text.empty()) 
	{
		combined = text + " " + other.text;
	}
	else
	{
		combined = text + other.text;
	}
	return Cipher(combined);
}

Cipher& Cipher::operator+=(const Cipher& other) 
{
	*this = *this + other;
	return *this;
}

std::string Cipher::getText() const
{
	return text;
}

void Cipher::setText(const std::string& newText) 
{
	Cipher tmp(newText);
	text = newText;
}