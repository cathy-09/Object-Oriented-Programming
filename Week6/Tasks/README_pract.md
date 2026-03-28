# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица шеста
```
Задача 1: Да се създаде клас Temperature, който да има следните полета и член-функции:

полета:
int temperature - градусите
char system - да има стойности 'c' за Целзий или 'f' за Фаренхайт
член-функции:
конструктор с параметри
гетъри и сетъри и за двете полета - не забравяйте да валидирате данните!
предефинирайте операторите == и < - съобразете, че когато сравняваме Целзий и Фаренхайт, трябва да направим преобразувание!
използвайки вече предефинираните оператори == и <, дефинирайте и останалите оператори за сравнение (!=, <=, >, >=).
предефинирайте операторите + и -, като съответно събирате или изваждате градусите на съответните температури. Приемаме, че резултатът е градуси по Целзий: правете подходящи преобразувания, където е необходимо
предефинирайте операторите += и -=, като съответно събирате или изваждате градусите на съответните температури и присвоявате новата стойност на левия обект. Правете подходящи преобразувания, където е необходимо - левия обект запазва своята система.
Упътване - формули за превръщане на градуси:

От Целзий към Фаренхайт: F = C * 1.8 + 32 (приемаме, че резултатът ще е int - дробните части не ни интересуват)
От Фаренхайт към Целзий: C = (F - 32) / 1.8
```

`Решение:`

`Temperature.h`
```h
#pragma once
class Temperature
{
private:
	int temperature;
	char system;
	static int toFahrenheit(int celsius);
	static int toCelsius(int fahrenheit);
	int asCelsius() const;
public:
	Temperature(int temperature, char system);
	int getTemperature() const;
	char getSystem() const;
	void setTemperature(int temperature);
	void setSystem(char system);
	bool operator==(const Temperature& other) const;
	bool operator<(const Temperature& other) const;
	bool operator!=(const Temperature& other) const;
	bool operator<=(const Temperature& other) const;
	bool operator>(const Temperature& other) const;
	bool operator>=(const Temperature& other) const;
	Temperature operator+(const Temperature& other) const;
	Temperature operator-(const Temperature& other) const;
	Temperature& operator+=(const Temperature& other);
	Temperature& operator-=(const Temperature& other);
};
```

`Temperature.cpp`
```cpp
#include "Temperature.h"
#include <iostream>

int Temperature::toFahrenheit(int celsius)
{
    return (int)(celsius * 1.8 + 32);
}

int Temperature::toCelsius(int fahrenheit)
{
    return (int)((fahrenheit - 32) / 1.8);
}

int Temperature::asCelsius() const
{
    if (system == 'c')
    {
        return temperature;
    }
    else
    {
        return toCelsius(temperature);
    }
}

Temperature::Temperature(int temperature, char system)
{
    if (system == 'c' || system == 'f')
    {
        this->system = system;
    }
    else
    {
        this->system = 'c';
    }
    this->temperature = temperature;
}

int Temperature::getTemperature() const
{
    return temperature;
}

char Temperature::getSystem() const
{
    return system;
}

void Temperature::setTemperature(int temperature)
{
    if (system == 'c')
    {
        if (temperature < -274)
        {
            std::cout << "WTF" << std::endl;
            return;
        }
    } 
    if (system == 'f')
    {
        if (temperature < -460)
        {
            std::cout << "WTF" << std::endl;
            return;
        }
    }
    this->temperature = temperature;
}

void Temperature::setSystem(char system)
{
    if (system != 'c' && system != 'f') 
    {
        std::cout << "Invalid system!" << std::endl;
        return;
    }
    this->system = system;
}

bool Temperature::operator==(const Temperature& other) const
{
    return asCelsius() == other.asCelsius();
}

bool Temperature::operator<(const Temperature& other) const
{
    return asCelsius() < other.asCelsius();
}

bool Temperature::operator!=(const Temperature& other) const
{
    return !(*this == other);
}

bool Temperature::operator<=(const Temperature& other) const
{
    return (*this < other || *this == other);
}

bool Temperature::operator>(const Temperature& other) const
{
    return !(*this <= other);
}

bool Temperature::operator>=(const Temperature& other) const
{
    return !(*this < other);
}

Temperature Temperature::operator+(const Temperature& other) const
{
    return Temperature(asCelsius() + other.asCelsius(), 'c');
}

Temperature Temperature::operator-(const Temperature& other) const
{
    return Temperature(asCelsius() - other.asCelsius(), 'c');
}

Temperature& Temperature::operator+=(const Temperature& other)
{
    int resultCelsius = asCelsius() + other.asCelsius();
    if (system == 'c')
    {
        temperature = resultCelsius;
    }
    else
    {
        temperature = toFahrenheit(resultCelsius);
    }
    return *this;
}

Temperature& Temperature::operator-=(const Temperature& other)
{
    int resultCelsius = asCelsius() - other.asCelsius();
    if (system == 'c')
    {
        temperature = resultCelsius;
    }
    else
    {
        temperature = toFahrenheit(resultCelsius);
    }
    return *this;
}
```

`task1.cpp`
```cpp
#include <iostream>
#include "Temperature.h"

int main()
{
	Temperature t1(100, 'c'); //212
	Temperature t2(212, 'f'); //100

	std::cout << "t1: " << t1.getTemperature() << t1.getSystem() << std::endl;
	std::cout << "t2: " << t2.getTemperature() << t2.getSystem() << std::endl;

	if (t1 == t2)
	{
		std::cout << "t1 == t2: t" << std::endl;
	}
	else
	{
		std::cout << "t1 == t2: f" << std::endl;
	}

	if (t1 != t2)
	{
		std::cout << "t1 != t2: t" << std::endl;
	}
	else
	{
		std::cout << "t1 != t2: f" << std::endl;
	}

	Temperature t3(0, 'c'); // 0
	Temperature t4(50, 'f'); //10
	if (t3 < t4)
	{
		std::cout << "t3 < t4: t" << std::endl;
	}
	else
	{
		std::cout << "t3 < t4: f" << std::endl;
	}

	if (t3 > t4)
	{
		std::cout << "t3 > t4: t" << std::endl;
	}
	else
	{
		std::cout << "t3 > t4: f" << std::endl;
	}

	Temperature sum = t1 + t3; // 100 + 0 = 100
	std::cout << "t1 + t3:  " << sum.getTemperature() << sum.getSystem() << std::endl;

	Temperature t5(32, 'f'); // 0
	Temperature t6(20, 'c'); // 20
	t5 += t6; // 20°C
	std::cout << "t5 += t6: " << t5.getTemperature() << t5.getSystem() << std::endl; // 68f

	Temperature bad(25, 'x');
	std::cout << "WTF IS THAT system? I set it to default: " << bad.getSystem() << std::endl;
}
```

<hr style="border-width: 5px !important;">

```
Задача 2: Да се създаде клас NumbericalVector, който е репрезентация на математическия вектор. Той да има следните полета и член-функции:

полета:
int size - броят на координатите във вектора
int* coordinates - координатите
член-функции:
Голяма четворка

Конструктор с параметри, приемащ size. Инициализира всички координати на 0.

setValue(index, val)

предефиниран operator[(const) size_t index] - връща координата на позиция index, като броим от 0. Не забравяйте, че трябва да предефинирате оператора с const и без const!

предефинирайте operator+, operator+=, operator*, така че те да отговарят на операциите събиране и скарално произведение на вектори.

предефинирайте operator<<, така че да изпринтирва вектора с вид "[coord0, coord1, ... coordn]". Не забравяйте, че това трябва да е приятелска функция!

предефинирайте operator<=> - обърнете внимание, че трябва да сравнявате не адресите на int* coordinates, а съдържанието!
```


`Решение:`

`NumericalVector.h`
```h
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
```

`NumericalVector.cpp`
```cpp
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
```

`task2.cpp`
```cpp
#include <iostream>
#include "NumericalVector.h"

int main()
{
    NumericalVector v1(3), v2(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;

    NumericalVector v3 = v1 + v2;
    std::cout << "v1 + v2 = " << v3 << std::endl;

    int dot = v1 * v2;
    std::cout << "v1 * v2 (dot) = " << dot << std::endl;

    v1 += v2;
    std::cout << "v1 += v2: " << v1 << std::endl;

    NumericalVector va(3), vb(3);
    va[0] = 1; va[1] = 2; va[2] = 3;
    vb[0] = 1; vb[1] = 2; vb[2] = 4;
    if ((va <=> vb) < 0)
    {
        std::cout << "va <=> vb: va < vb" << std::endl;
    }
    else
    {
        std::cout << "va <=> vb: va >= vb" << std::endl;
    }

    if (va == vb)
    {
        std::cout << "va == vb: true" << std::endl;
    }
    else
    {
        std::cout << "va == vb: false" << std::endl;
    }

    v3[-1];
}
```

<hr style="border-width: 5px !important;">

```
Задача 3: Да се създаде клас HexColourCode, който репрезентира кодиране на цвят от тип hexcode - повече информация можете да намерите тук. Класът да има следните полета и член-функции:

полета:
char* code
член-функции:
Голяма четворка
Конструктор с параметри, приемащ масив от символи
setCode(char* code) - валидирайте данните!
предефинирайте operator<<, така че да изпринтва съдържанието на code
предефинирайте operator<=>, така че да сравнява кодовете, все едно че са числа в шестнадесетична бройна система
забранете операторите за аритметични операции (operator+, operator-, operator*, operator/, operator%).
```


`Решение:`

`HexColourCode.h`
```h
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
```

`HexColourCode.cpp`
```cpp
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
```

`task3.cpp`
```cpp
#include <iostream>
#include "HexColourCode.h"

int main()
{
	HexColourCode c1("#FF0000");
	HexColourCode c2("#00FF00");
	HexColourCode c3("#FF0000");

	cout << "c1 = " << c1 << endl;
	cout << "c2 = " << c2 << endl;

	if (c1 == c3)
	{
		cout << "c1 == c3: t" << endl;
	}
	else
	{
		cout << "c1 == c3: f" << endl;
	}

	if ((c2 <=> c1) < 0)
	{
		cout << "c2 < c1: t" << endl;
	}
	else
	{
		cout << "c2 < c1: f" << endl;
	}

	HexColourCode bad2("ZZZZZZ");
	cout << "Bad code defaults to: " << bad2 << endl;

	HexColourCode bad3("#GGG000");
	bad3.setCode("not_a_code");
}
```

<hr style="border-width: 5px !important;">
