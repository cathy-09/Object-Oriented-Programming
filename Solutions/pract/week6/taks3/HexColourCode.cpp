#include "HexColourCode.h"
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iostream>
using namespace std;

void HexColourCode::copyFrom(const HexColourCode& other) 
{
    code = new char[strlen(other.code) + 1];
    strcpy(code, other.code);
}

void HexColourCode::free() 
{
    delete[] code;
    code = nullptr; 
}

bool HexColourCode::isValidHex(const char* code) 
{
    if (!code) 
    {
        return false;
    }
    if (strlen(code) != 7)
    {
        return false;
    }
    if (code[0] != '#') 
    {
        return false;
    }
    for (int i = 1; i <= 6; i++) 
    {
        char c = code[i];
        if (!((c >= '0' && c <= '9') ||
            (c >= 'a' && c <= 'f') ||
            (c >= 'A' && c <= 'F')))
        {
            return false;
        }
    }
    return true;
}

long HexColourCode::hexToLong(const char* code) 
{
    long result = 0;

    for (int i = 1; i <= 6; i++) 
    { 
        char c = code[i];
        int value = 0;

        if (c >= '0' && c <= '9')
        {
            value = c - '0';
        }
        else if (c >= 'A' && c <= 'F')
        {
            value = c - 'A' + 10;
        }
        else if (c >= 'a' && c <= 'f')
        {
            value = c - 'a' + 10;
        }
        else
        {
            value = 0;
        }
        result = result * 16 + value;
    }

    return result;
}

HexColourCode::HexColourCode() 
{
    code = new char[8];
    strcpy(code, "#000000");
}

HexColourCode::HexColourCode(const char* code) 
{
    if (!isValidHex(code)) 
    {
        std::cout << "Invalid hex colour code!" << std::endl;
        this->code = new char[8];
        strcpy(this->code, "#000000");
        return;
    }
    this->code = new char[strlen(code) + 1];
    this->code[0] = '#';
    for (int i = 1; i <= 6; i++) 
    {
        char c = code[i];
        if (c >= 'a' && c <= 'f')
        {
            c = c - 'a' + 'A';
        }
        this->code[i] = c;
    }
    this->code[7] = '\0';
}

HexColourCode::HexColourCode(const HexColourCode& other) 
{
    copyFrom(other);
}

HexColourCode& HexColourCode::operator=(const HexColourCode& other)
{
    if (this != &other) 
    {
        free();
        copyFrom(other);
    }
    return *this;
}

HexColourCode::~HexColourCode() 
{
    free();
}

void HexColourCode::setCode(const char* code) 
{
    if (!isValidHex(code))
    {
        cout << "Invalid hex colour code!" << endl;
        return;
    }
    delete[] this->code;
    this->code = new char[strlen(code) + 1];
    strcpy(this->code, code);
    for (int i = 1; i <= 6; i++)
    {
        this->code[i] = (char)toupper(this->code[i]);
    }
}

const char* HexColourCode::getCode() const
{
    return code; 
}

ostream& operator<<(ostream& os, const HexColourCode& h) 
{
    os << h.code;
    return os;
}

strong_ordering HexColourCode::operator<=>(const HexColourCode& other) const 
{
    long a = hexToLong(code);
    long b = hexToLong(other.code);
    return a <=> b;
}

bool HexColourCode::operator==(const HexColourCode& other) const 
{
    return hexToLong(code) == hexToLong(other.code);
}