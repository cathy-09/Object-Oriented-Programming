#pragma once
#include <iostream>
#include <compare>
using namespace std;

class HexColourCode 
{
private:
    char* code;

    static bool isValidHex(const char* code);
    static long hexToLong(const char* code);

    void free();
    void copyFrom(const HexColourCode& other);

public:
    HexColourCode();
    HexColourCode(const char* code);
    HexColourCode(const HexColourCode& other);
    HexColourCode& operator=(const HexColourCode& other);
    ~HexColourCode();
    void setCode(const char* code);
    const char* getCode() const;
    friend ostream& operator<<(ostream& os, const HexColourCode& h);
    strong_ordering operator<=>(const HexColourCode& other) const;
    bool operator==(const HexColourCode& other) const;
    HexColourCode operator+(const HexColourCode&) const = delete;
    HexColourCode operator-(const HexColourCode&) const = delete;
    HexColourCode operator*(const HexColourCode&) const = delete;
    HexColourCode operator/(const HexColourCode&) const = delete;
    HexColourCode operator%(const HexColourCode&) const = delete;
};