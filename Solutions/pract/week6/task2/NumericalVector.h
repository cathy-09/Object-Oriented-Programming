#pragma once
#include <iostream>
#include <ostream>
#include <compare>
class NumericalVector
{
private:
    int  size;
    int* coordinates;
    void free();
    void copyFrom(const NumericalVector& other);
    public:
        NumericalVector(int size);
        NumericalVector(const NumericalVector& other);
        NumericalVector& operator=(const NumericalVector& other);
        ~NumericalVector();
        int getSize() const;
        void setValue(int index, int val);
        int& operator[](size_t index);
        const int& operator[](size_t index) const;
        NumericalVector  operator+ (const NumericalVector& other) const;
        NumericalVector& operator+=(const NumericalVector& other);
        int operator* (const NumericalVector& other) const; 
        std::strong_ordering operator<=>(const NumericalVector& other) const;
        bool operator==(const NumericalVector& other) const;
        friend std::ostream& operator<<(std::ostream& os, const NumericalVector& v);
};

