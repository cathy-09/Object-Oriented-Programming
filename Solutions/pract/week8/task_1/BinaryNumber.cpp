#include "Text.h"
#include "BinaryNumber.h"
#include <iostream>

void BinaryNumber::free()
{
    delete[] number;
    number = nullptr;
    size = 0;
}

void BinaryNumber::fromDecimal(unsigned long long decimal)
{
    if (decimal == 0) 
    {
        size = 1;
        number = new int[1] {0};
        return;
    }

    size_t digits = 0;
    unsigned long long tmp = decimal;
    while (tmp > 0) 
    {
        ++digits;
        tmp = tmp / 2;
    }

    size = digits;
    number = new int[digits];

    for (size_t i = 0; i < digits; ++i) 
    {
        number[digits - 1 - i] = decimal % 2;
        decimal = decimal / 2;
    }
}

void BinaryNumber::copyFrom(const BinaryNumber& other)
{
    size = other.size;
    number = new int[size];
    for (size_t i = 0; i < size; ++i)
    {
        number[i] = other.number[i];
    }
}

void BinaryNumber::addArrays(const int* a, size_t sizeA, const int* b, size_t sizeB)
{
    size_t maxLen;
    if (sizeA > sizeB)
    {
        maxLen = sizeA;
    }
    else
    {
        maxLen = sizeB;
    }

    size_t newSize = maxLen + 1;

    int* result = new int[newSize]();

    int carry = 0;
    for (size_t i = 0; i < maxLen || carry != 0; ++i)
    {
        int digitA = 0;
        if (i < sizeA)
        {
            digitA = a[sizeA - 1 - i];
        }

        int digitB = 0;
        if (i < sizeB)
        {
            digitB = b[sizeB - 1 - i];
        }

        int sum = digitA + digitB + carry;
        result[newSize - 1 - i] = sum % 2;
        carry = sum / 2;
    }

    size_t start = 0;
    while (start < newSize - 1 && result[start] == 0)
    {
        ++start;
    }

    free();
    size = newSize - start;
    number = new int[size];

    for (size_t i = 0; i < size; ++i)
    {
        number[i] = result[start + i];
    }

    delete[] result;
}

BinaryNumber::BinaryNumber() : number(new int[1] {0}), size(1) 
{

}

BinaryNumber::BinaryNumber(unsigned long long decimal) : number(nullptr), size(0) 
{
    fromDecimal(decimal);
}

BinaryNumber::BinaryNumber(const BinaryNumber& other) : number(nullptr), size(0) 
{
    copyFrom(other);
}

BinaryNumber::BinaryNumber(BinaryNumber&& other) noexcept : number(other.number), size(other.size) 
{
    other.number = nullptr;
    other.size = 0;
}

BinaryNumber& BinaryNumber::operator=(const BinaryNumber& other)
{
    if (this == &other)
    {
        return *this;
    }
    free();
    copyFrom(other);
    return *this;
}

BinaryNumber& BinaryNumber::operator=(BinaryNumber&& other) noexcept
{
    if (this == &other) return *this;
    free();
    number = other.number;
    size = other.size;
    other.number = nullptr;
    other.size = 0;
    return *this;
}

BinaryNumber::~BinaryNumber()
{
    free();
}

const int* BinaryNumber::getNumber() const
{
    return number;
}

size_t BinaryNumber::getSize() const
{
    return size;
}

void BinaryNumber::setNumber(const int* arr, size_t newSize)
{
    free();
    size = newSize;
    number = new int[size];
    for (size_t i = 0; i < size; ++i)
    {
        number[i] = arr[i];
    }
}

void BinaryNumber::setSize(size_t newSize)
{
    int* newArr = new int[newSize]();

    size_t minSize;
    if (newSize < size)
    {
        minSize = newSize;
    }
    else
    {
        minSize = size;
    }

    for (size_t i = 0; i < minSize; ++i)
    {
        newArr[newSize - 1 - i] = number[size - 1 - i];
    }

    delete[] number;
    number = newArr;
    size = newSize;
}

bool BinaryNumber::operator==(const BinaryNumber& rhs) const
{
    return (*this <=> rhs) == std::strong_ordering::equal;
}

BinaryNumber BinaryNumber::operator+(const BinaryNumber& rhs) const
{
    BinaryNumber result(*this);
    result.addArrays(number, size, rhs.number, rhs.size);
    return result;
}

BinaryNumber& BinaryNumber::operator+=(const BinaryNumber& rhs)
{
    addArrays(number, size, rhs.number, rhs.size);
    return *this;
}

void BinaryNumber::print() const
{
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << number[i];
    }
    std::cout << std::endl;
}

std::strong_ordering BinaryNumber::operator<=>(const BinaryNumber& rhs) const
{
    if (size != rhs.size)
    {
        return size <=> rhs.size;
    }
    for (size_t i = 0; i < size; ++i) 
    {
        if (number[i] != rhs.number[i])
        {
            return number[i] <=> rhs.number[i];
        }      
    }
    return std::strong_ordering::equal;
}

