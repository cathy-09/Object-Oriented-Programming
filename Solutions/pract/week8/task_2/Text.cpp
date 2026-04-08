#include "Text.h"
#include <iostream>

void Text::copyFrom(const char* src, size_t len)
{
	size = len;
	text = new char[size + 1];
	std::memcpy(text, src, size);
	text[size] = '\0';
}

void Text::free()
{
	delete[] text;
	text = nullptr;
	size = 0;
}

Text::Text() : text(nullptr), size(0)
{
	const char* def = "Default message";
	copyFrom(def, std::strlen(def));
}

Text::Text(const char* str, size_t len) : text(nullptr), size(0)
{
	copyFrom(str, len);
}

Text::Text(const Text& other) : text(nullptr), size(0)
{
	copyFrom(other.text, other.size);
}

Text::Text(Text&& other) noexcept : text(other.text), size(other.size)
{
	other.text = nullptr;
	other.size = 0;
}

Text& Text::operator=(const Text& other)
{
	if (this == &other)
	{
		return *this;
	}
	free();
	copyFrom(other.text, other.size);
	return *this;
}

Text& Text::operator=(Text&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}
	free();
	text = other.text;
	size = other.size;
	other.text = nullptr;
	other.size = 0;
	return *this;
}

Text::~Text()
{
	free();
}

void Text::setText(const char* str, size_t len)
{
	free();
	copyFrom(str, len);
}

std::ostream& operator<<(std::ostream& os, const Text& t) {
	if (t.text)
	{
		os << t.text;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Text& t)
{
	char buffer[4096];
	if (is >> buffer)
	{
		delete[] t.text;
		t.copyFrom(buffer, std::strlen(buffer));
	}
	return is;
}

char Text::operator[](size_t index) const
{
	if (index >= size)
	{
		std::cout << "Index out of range";
		static char dummy = '\0';
		return dummy;
	}
	return text[index];
}

char& Text::operator[](size_t index)
{
	if (index >= size)
	{
		std::cout << "Index out of range";
		static char dummy = '\0';
		return dummy;
	}
	return text[index];
}