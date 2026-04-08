#pragma once
#include <compare>
class BinaryNumber
{
private:
    int* number;
    size_t size;

    void free();
    void fromDecimal(unsigned long long decimal);
    void copyFrom(const BinaryNumber& other);
    void addArrays(const int* a, size_t sizeA, const int* b, size_t sizeB);

public:
    BinaryNumber();
    explicit BinaryNumber(unsigned long long decimal);
    BinaryNumber(const BinaryNumber& other);
    BinaryNumber(BinaryNumber&& other) noexcept;
    BinaryNumber& operator=(const BinaryNumber& other);
    BinaryNumber& operator=(BinaryNumber&& other) noexcept;
    ~BinaryNumber();

    const int* getNumber() const;
    size_t getSize() const;
    void setNumber(const int* arr, size_t newSize);
    void setSize(size_t newSize);

    std::strong_ordering operator<=>(const BinaryNumber& rhs) const;
    bool operator==(const BinaryNumber& rhs) const;

    BinaryNumber operator+(const BinaryNumber& rhs) const;
    BinaryNumber& operator+=(const BinaryNumber& rhs);

    void print() const;
};

