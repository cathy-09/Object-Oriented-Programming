#include "NumericalVector.h"

void NumericalVector::free()
{
    delete[] coordinates;
    coordinates = nullptr;
    size = 0;
}

void NumericalVector::copyFrom(const NumericalVector& other)
{
    size = other.size;
    coordinates = new int[size];
    for (int i = 0; i < size; i++)
    {
        coordinates[i] = other.coordinates[i];
    }
}

NumericalVector::NumericalVector(int size)
{
    if (size <= 0) 
    {
        std::cout << "Size must be positive!" << std::endl;
        size = 1;
    }
    this->size = size;
    coordinates = new int[size]();
}

NumericalVector::NumericalVector(const NumericalVector& other)
{
    copyFrom(other);
}

NumericalVector& NumericalVector::operator=(const NumericalVector& other)
{
    if (this != &other) 
    {
        free();
        copyFrom(other);
    }
    return *this;
}

NumericalVector::~NumericalVector()
{
    free();
}

int NumericalVector::getSize() const
{
    return size;
}

void NumericalVector::setValue(int index, int val)
{
    if (index < 0 || index >= size) 
    {
        std::cout << "Index out of range!" << std::endl;
        return;
    }
    coordinates[index] = val;
}

int& NumericalVector::operator[](size_t index)
{
    if ((int)index >= size) 
    {
        std::cout << "Index out of range!" << std::endl;
        return coordinates[0];
    }
    return coordinates[index];
}

const int& NumericalVector::operator[](size_t index) const 
{
    if ((int)index >= size) 
    {
        std::cout << "Index out of range!" << std::endl;
        return coordinates[0];
    }
    return coordinates[index];
}

NumericalVector NumericalVector::operator+(const NumericalVector& other) const
{
    if (size != other.size) 
    {
        return *this;
    }
    NumericalVector result(size);
    for (int i = 0; i < size; i++)
    {
        result.coordinates[i] = coordinates[i] + other.coordinates[i];
    }
    return result;
}

NumericalVector& NumericalVector::operator+=(const NumericalVector& other)
{
    if (size != other.size) 
    {
        return *this;
    }
    for (int i = 0; i < size; i++)
    {
        coordinates[i] += other.coordinates[i];
    }
    return *this;
}

int NumericalVector::operator*(const NumericalVector& other) const
{
    if (size != other.size) 
    {
        return 0;
    }
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += coordinates[i] * other.coordinates[i];
    }
    return sum;
}

bool NumericalVector::operator==(const NumericalVector& other) const
{
    if (size != other.size)
    {
        return false;
    }
    for (int i = 0; i < size; i++)
    {
        if (coordinates[i] != other.coordinates[i])
        {
            return false;
        }
    }
    return true;
}

std::strong_ordering NumericalVector::operator<=>(const NumericalVector& other) const
{
    int minSize;
    if (size < other.size)
    {
        minSize = size;
    }
    else
    {
        minSize = other.size;
    }
    for (int i = 0; i < minSize; i++)
    {
        if (coordinates[i] != other.coordinates[i])
        {
            return coordinates[i] <=> other.coordinates[i];
        }
    }
    return size <=> other.size;
}

std::ostream& operator<<(std::ostream& os, const NumericalVector& v)
{
    os << "[";
    for (int i = 0; i < v.size; i++) 
    {
        os << v.coordinates[i];
        if (i < v.size - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
