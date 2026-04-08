#pragma once
#include <string>
class Cipher
{
private:
private:
    std::string text;
    int wordCount() const;
    std::string getWord(int index) const;
    static std::string reverseWord(const std::string& word);

public:
    explicit Cipher(const std::string& text);
    std::string encrypt() const;
    std::string operator[](int index) const;
    Cipher  operator+(const Cipher& other) const;
    Cipher& operator+=(const Cipher& other);

    std::string getText() const;
    void setText(const std::string& text);
};

