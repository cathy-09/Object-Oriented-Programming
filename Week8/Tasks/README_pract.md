# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица осма
```
Задача 1: Създайте клас BinaryNumber, който представя число в двоична бройна система. Класът да има следните полета и член-функции:

полета:
int* number - числото, представено като масив от цели числа, където всеки елемент е една цифра от числото (0 или 1).
size_t size - размерът на динамичния масив

член-функции:
голяма шестица - при конструкторът по подразбиране числото да се инициализира като 0 и размерът е 1
конструктор с параметър едно число в десетична бройна система - конструкторът да превърне числото в двойно и да го запише цифра по цифра в number
сетъри и гетъри за двете член данни
предефиниран оператор <=>
предефинирани оператори + и += за сбора на две двойчни числа. Обърнете внимание, че това може да доведе до по-голямо число, и следователно преоразмеряване на масива!
```

`Решение:`

`BinaryNumber.h`
```h
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
```

`BinaryNumber.cpp`
```cpp
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
```

`task_1.cpp`
```cpp
#include <iostream>
#include "BinaryNumber.h"

int main()
{
    std::cout << "=== BinaryNumber ===";
    std::cout << std::endl;

    BinaryNumber zero;
    std::cout << "Default (0): ";
    zero.print();

    BinaryNumber a(10);
    std::cout << "10 in binary: "; 
    a.print();

    BinaryNumber b(6);
    std::cout << "6 in binary: ";
    b.print();

    BinaryNumber c = a + b;
    std::cout << "10+6=16:  "; 
    c.print();

    a += b;
    std::cout << "10+=6 = 16: ";
    a.print();

    BinaryNumber x(5), y(8);

    if (x < y)
    {
        std::cout << "5 < 8 : true";
        std::cout << std::endl;
    }
    else
    {
        std::cout << "5 < 8 : false";
        std::cout << std::endl;
    }

    if (y > x)
    {
        std::cout << "8 > 5 : true";
        std::cout << std::endl;
    }
    else
    {
        std::cout << "8 > 5 : false";
        std::cout << std::endl;
    }

    if (x == BinaryNumber(5))
    {
        std::cout << "5 == 5: true";
        std::cout << std::endl;
    }
    else
    {
        std::cout << "5 == 5: false";
        std::cout << std::endl;
    }

    BinaryNumber moved(std::move(x));
    std::cout << "Moved 5: ";
    moved.print();

    BinaryNumber copy(c);
    std::cout << "Copy of 16: ";
    copy.print();
}
```

<hr style="border-width: 5px !important;">

```
Задача 2: Да се създаде клас Text, със следните полета и член-функции:

полета:
char* text;
size_t size;
член-функции:
голяма шестица - конструкторът по подразбиране да съдържа текста "Default message"
Конструктор с параметри, приемащ символен низ и размера му
Предефинирайте оператора [], така че при подаден индекс да връща символа на съотвения индекс от съобщението, като започваме да броим от 0.

Предефинирайте операторите << и >>, така че да работят като четене и писане (cout & cin).
```

`Решение:`

`Text.h`
```h
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
```

`Text.cpp`
```cpp
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
```

`task_2.cpp`
```cpp
#include <iostream>
#include "Text.h"

int main()
{
    std::cout << "=== Text ===";
    std::cout << std::endl;

    Text t1;
    std::cout << "Default: " << t1;
    std::cout << std::endl;

    const char* msg = "Hello";
    Text t2(msg, 5);
    std::cout << "Custom: " << t2;
    std::cout << std::endl;

    std::cout << "t2[1] = " << t2[1];
    std::cout << std::endl;

    Text t3;
    t3 = t2;
    std::cout << "Copied: " << t3;
    std::cout << std::endl;

    Text t4(std::move(t3));
    std::cout << "Moved: " << t4;
    std::cout << std::endl;
}
```

<hr style="border-width: 5px !important;">
