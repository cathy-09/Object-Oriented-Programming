#pragma once
#include <ostream>
class Text
{
private:
    char* text;
    size_t size;

    void copyFrom(const char* src, size_t len);
    void free();
    public:
        Text();
        Text(const char* str, size_t len);
        Text(const Text& other);
        Text(Text&& other) noexcept;
        Text& operator=(const Text& other);
        Text& operator=(Text&& other) noexcept;
        ~Text();

        const char* getText() const;
        size_t getSize() const;
        void setText(const char* str, size_t len);

        char  operator[](size_t index) const;
        char& operator[](size_t index);

        friend std::ostream& operator<<(std::ostream& os, const Text& text);
        friend std::istream& operator>>(std::istream& is, Text& text);
};

