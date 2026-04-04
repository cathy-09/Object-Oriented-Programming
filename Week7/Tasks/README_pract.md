# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица седма
```
Задача 1: Създайте клас Calculator, който няма член-данни и има следните член-функции:

член-функции:
double sum (double first, double second) - връща сумата на двата аргумента
double substeact(double first, double second) - връща разликата на двата аргумента
double multiply(double first, double second) - връща произведението на двата аргумента
double divide(double first, double second) - връща частното на двата аргумента. Внимавайте с деленето на 0!
Нека класът Calculator да е Singleton.

Създайте клас User, със следните полета и член-функции:

полета:
int id
string username
string password
Calculator* calc;
член-функции:
Конструктор с параметри - потребителско име и парола

гетъри и сетъри за потребителското име и за паролата

Полето id да се инкрементира за всеки потребител, като първият потребител трябва да е с номер 1, следващият - с номер 2 и т.н. Указание: използвайте статична член-данна, която да брои инстанциите на класа.

Инстанцирайте множество потребители и изтествайте калкулатора чрез тях.
```

`Решение:`

`Calculator.h`
```h
#pragma once
class Calculator
{
private:
    Calculator() = default;
    Calculator(const Calculator&) = delete;
    Calculator& operator=(const Calculator&) = delete;
    static Calculator* instance;

public:
    static Calculator* getInstance();
    double sum(double first, double second);
    double subtract(double first, double second);
    double multiply(double first, double second);
    double divide(double first, double second); 
};
```

`Calculator.cpp`
```cpp
#include "Calculator.h"
#include <iostream>
Calculator* Calculator::instance = nullptr;

Calculator* Calculator::getInstance() 
{
    if (instance == nullptr)
    {
        instance = new Calculator();
    }
    return instance;
}

double Calculator::sum(double first, double second) 
{
    return first + second;
}

double Calculator::subtract(double first, double second) 
{
    return first - second;
}

double Calculator::multiply(double first, double second) 
{
    return first * second;
}

double Calculator::divide(double first, double second) 
{
    if (second == 0.0) 
    {
         std::cout << "Division by zero is not allowed.";
         return 0.0;
    }
    return first / second;
}
```

`User.h`
```h
#pragma once
#include <string>
#include "Calculator.h"
class User
{
private:
    int id;
    std::string username;
    std::string password;
    Calculator* calc;
    static int nextId;

public:
    User(const std::string& username, const std::string& password);
    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    Calculator* getCalculator() const;
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
};
```

`User.cpp`
```cpp
#include "User.h"
#include <iostream>
int User::nextId = 1;

User::User(const std::string& username, const std::string& password) 
{
    if (username.empty()) 
    {
        std::cout << "Username cannot be empty.";
        return;
    }
    if (password.empty()) {
        std::cout << "Password cannot be empty.";
        return;
    }
    this->id = nextId++;
    this->username = username;
    this->password = password;
    this->calc = Calculator::getInstance();
}

int User::getId() const 
{
    return id;
}

std::string User::getUsername() const 
{
    return username;
}

std::string User::getPassword() const 
{
    return password;
}

Calculator* User::getCalculator() const 
{
    return calc;
}

void User::setUsername(const std::string& username) 
{
    if (username.empty()) 
    {
        std::cout << "Username cannot be empty.";
        return;
    }
    this->username = username;
}

void User::setPassword(const std::string& password) 
{
    if (password.empty())
    {
        std::cout << ("Password cannot be empty.");
        return;
    }
    this->password = password;
}
```

`task1.cpp`
```cpp
#include <iostream>
#include "User.h"

int main()
{
    User az("az", "pass123");
    User didi("didi", "qwerty");
    User kiki("kiki", "abc456");

    std::cout << "az id=" << az.getId() << " didi id=" << didi.getId() << " kiki id=" << kiki.getId() << "\n\n";

    Calculator* c = az.getCalculator();
    std::cout << "Calculator instance same for all users? " << (c == didi.getCalculator() && c == kiki.getCalculator() ? "YES" : "NO") << "\n\n";

    double a = 10, b = 3;
    std::cout << a << " + " << b << " = " << c->sum(a, b) << "\n";
    std::cout << a << " - " << b << " = " << c->subtract(a, b) << "\n";
    std::cout << a << " * " << b << " = " << c->multiply(a, b) << "\n";
    std::cout << a << " / " << b << " = " << c->divide(a, b) << "\n\n";
}
```

<hr style="border-width: 5px !important;">

```
Задача 2: Да се създаде клас Cipher, със следните полета и член-функции:

полета:
string text;
член-функции:
Конструктор с параметри, приемащ текст, който да бъде криптиран
string encrypt() - връща съобщението, съдържащо се в полето text, преобразувано, като за всяка дума първият символ е разменен с последния, вторият - с предпоследния, и т.н., докато символите по средата не се разменят. Под "дума" разбираме всяка поредица от символи, заобиколени от произволен брой интервали. Приемете, че в съобщението има само латински букви, цифри, и интервали.
Предефинирайте оператора [], така че при подаден индекс да връща думата на съотвения индекс от оригиналното съобщение, като започваме да броим от 0.

Предефинирайте операторите + и +=, така че да конкатенират съобщенията.
```

`Решение:`

`Cipher.h`
```h
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
```

`Cipher.cpp`
```cpp
#include "Cipher.h"
#include <iostream>
std::string Cipher::reverseWord(const std::string& word)
{
	std::string reversed = word;
	std::reverse(reversed.begin(), reversed.end());
	return reversed;
}

int Cipher::wordCount() const
{
	int count = 0;
	std::size_t i = 0;
	while (i < text.size())
	{
		while (i < text.size() && text[i] == ' ') ++i;
		if (i < text.size())
		{
			++count;
			while (i < text.size() && text[i] != ' ')
			{
				++i;
			}
		}
	}
	return count;
}

std::string Cipher::getWord(int index) const
{
	int current = 0;
	std::size_t i = 0;
	while (i < text.size())
	{
		while (i < text.size() && text[i] == ' ')
		{
			++i;
		}
		if (i == text.size())
		{
			break;
		}
		std::size_t start = i;
		while (i < text.size() && text[i] != ' ')
		{
			++i;
		}
		if (current == index)
		{
			return text.substr(start, i - start);
		}
		++current;
	}
	return "";
}

Cipher::Cipher(const std::string& text) 
{
	for (char ch : text) 
	{
		if (!((ch >= 'a' && ch <= 'z') ||
			(ch >= 'A' && ch <= 'Z') ||
			(ch >= '0' && ch <= '9') ||
			ch == ' ')) 
		{
			std::cout << "Invalid character";
			return;
		}
	}
	this->text = text;
}

std::string Cipher::encrypt() const 
{
	if (text.empty())
	{
		return "";
	}
	std::string result;
	result.reserve(text.size());

	std::size_t i = 0;
	while (i < text.size()) 
	{
		if (text[i] == ' ')
		{
			result += ' ';
			++i;
		}
		else 
		{
			std::size_t start = i;
			while (i < text.size() && text[i] != ' ')
			{ 
				++i;
			} 
			result += reverseWord(text.substr(start, i - start));
		}
	}
	return result;
}

std::string Cipher::operator[](int index) const 
{
	if (index < 0) 
	{
		std::cout << "Index must be non-negative.";
	}
	int count = wordCount();
	if (index >= count) 
	{
		std::cout << "Index is out of range";
		return;
	}
	return getWord(index);
}

Cipher Cipher::operator+(const Cipher& other) const 
{
	std::string combined;
	if (!text.empty() && !other.text.empty()) 
	{
		combined = text + " " + other.text;
	}
	else
	{
		combined = text + other.text;
	}
	return Cipher(combined);
}

Cipher& Cipher::operator+=(const Cipher& other) 
{
	*this = *this + other;
	return *this;
}

std::string Cipher::getText() const
{
	return text;
}

void Cipher::setText(const std::string& newText) 
{
	Cipher tmp(newText);
	text = newText;
}
```

`task2.cpp`
```cpp
#include <iostream>
#include "Cipher.h"

int main()
{
    Cipher c1("hello world");
    std::cout << "Original : " << c1.getText() << "\n";
    std::cout << "Encrypted: " << c1.encrypt() << "\n\n";
    Cipher c2("abc123 XYZ");
    std::cout << "Original : " << c2.getText() << "\n";
    std::cout << "Encrypted: " << c2.encrypt() << "\n\n";
    Cipher c3("one two three four");
    std::cout << "Words in " << c3.getText() << "\n";
    for (int i = 0; i < 4; ++i) 
    {
        std::cout << "  [" << i << "] = " << c3[i] << "\n";
    }
    std::cout << "\n";
    Cipher c4("good morning");
    Cipher c5("everyone");
    Cipher c6 = c4 + c5;
    std::cout << "c4 + c5  = " << c6.getText() << "\n";
    std::cout << "encrypted: " << c6.encrypt() << "\n\n";
    c4 += c5;
    std::cout << "c4 += c5 = " << c4.getText() << "\n\n";
}
```

<hr style="border-width: 5px !important;">


<hr style="border-width: 5px !important;">
