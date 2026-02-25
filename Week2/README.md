# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица първа
`Задача 1: Да се създаде клас BankAccount, със следните полета и член-функции: 
полета:
owner - име на собственик (максимална дължина 50 символа)
balance (максимална дължина 50 символа)
член-функции:
deposit(amount) - Увеличава balance с amount. Ако amount ≤ 0 → извежда подходящо съобщение.
withdraw(amount) - Намалява balance с amount само ако balance >= amount. Ако amount ≤ 0 или amount > balance→ извежда подходящо съобщение.
getter за balance - Връща текущия баланс.`

`Решение:`
```cpp
#include <iostream>
#include <cstring>

class BankAccount
{
private:
	char owner[51];
	double balance;

public:
	BankAccount(const char* name, double initialBalance)
	{
		strcpy(owner, name);
		owner[50] = '\0';
		balance = initialBalance;
	}
	void deposit(double amount)
	{
		if (amount <= 0) 
		{
			std::cout << "Invalid deposit amount!" << std::endl;
		}
		else 
		{
			balance += amount;
		}
	}

	void withdraw(double amount) 
	{
		if (amount <= 0) 
		{
			std::cout << "Invalid withdraw amount!" << std::endl;
		}
		else if (amount > balance) 
		{
			std::cout << "Not enough balance!" << std::endl;
		}
		else 
		{
			balance -= amount;
		}
	}

	double getBalance() const 
	{
		return balance;
	}
};

int main()
{
	BankAccount accout("Ivan Ivanov", 1000);

	accout.deposit(200);
	accout.withdraw(500);

	std::cout << "Current balance: " << accout.getBalance() << std::endl;
}
```

<hr style="border-width: 5px !important;">

`Задача 2: Да се създаде клас User, със следните полета и член-функции:
полета:
username (максимална дължина 30 символа)
password (максимална дължина 15 символа)
член-функции:
setPassword(newPassword) - Паролата трябва да е минимум 8 символа, максимум 15 символа, да съдържа поне 1 главна буква и да съдържа поне 1 цифра. Ако newPassword не отговаря на условията → password остава непроменена и се извежда подходящо съобщение.
checkPassword(input) - Връща true ако input съвпада с password и false-ако не.`

`Решение:`
```cpp
#include <iostream>

class User
{
private:
    char username[31];
    char password[16];

public:
    User(const char* name, const char* pass)
    {
        strcpy(username, name);
        username[30] = '\0';
        strcpy(password, pass);
        password[15] = '\0';
    }

    void setPassword(const char* newPassword)
    {
        int len = strlen(newPassword);
        if (len < 8 || len > 15)
        {
            std::cout << "Password length must be between 8 and 15 characters!" << std::endl;
            return;
        }

        bool hasUpper = false;
        bool hasDigit = false;

        for (int i = 0; i < len; i++)
        {
            if (isupper(newPassword[i]))
            {
                hasUpper = true;
            }
            if (isdigit(newPassword[i]))
            {
                hasDigit = true;
            }
        }

        if (!hasUpper || !hasDigit)
        {
            std::cout << "Password must contain at least one uppercase letter and one digit!" << std::endl;
            return;
        }

        strcpy(password, newPassword);
        password[15] = '\0';
    }

    bool checkPassword(const char* input) const
    {
        return strcmp(password, input) == 0;
    }
};

int main()
{
    User user("Ivan", "Test1234");

    user.setPassword("abc");
    user.setPassword("NewPass1");

    if (user.checkPassword("NewPass1"))
    {
        std::cout << "Correct password!" << std::endl;
    }
    else
    {
        std::cout << "Wrong password!" << std::endl;
    }
}
```

<hr style="border-width: 5px !important;">

`Задача 3: Да се създаде клас Car, със следните полета и член-функции:
полета:
brand (до 40 символа)
fuel (не може да бъде отрицателно число)
fuelCapacity (положително число)
член-функции:
refuel(amount) - Увеличава fuel. Ако amount ≤ 0 или fuel + amount > fuelCapacity → fuel остава непромененo и се извежда подходящо съобщение.
drive(km) - Приемаме, че 1 км = 0.1 литра. Ако няма достатъчно гориво → извежда подходящо съобщение.
getter за fuel
getter за brand`

`Решение:`
```cpp
#include <iostream>

class Car
{
private:
    char brand[41];
    double fuel;
    double fuelCapacity;

public:
    Car(const char* b, double f, double capacity)
    {
        strcpy(brand, b);
        brand[40] = '\0';

        if (capacity > 0)
        {
            fuelCapacity = capacity;
        }
        else
        {
            fuelCapacity = 0;
        }

        if (f >= 0 && f <= fuelCapacity)
        {
            fuel = f;
        }
        else
        {
            fuel = 0;
        }
    }

    void refuel(double amount)
    {
        if (amount <= 0)
        {
            std::cout << "Invalid fuel amount!" << std::endl;
        }
        else if (fuel + amount > fuelCapacity)
        {
            std::cout << "Fuel exceeds capacity!" << std::endl;
        }
        else
        {
            fuel += amount;
        }
    }

    void drive(double km)
    {
        double neededFuel = km * 0.1;

        if (neededFuel > fuel)
        {
            std::cout << "Not enough fuel!" << std::endl;
        }
        else
        {
            fuel -= neededFuel;
        }
    }

    double getFuel() const
    {
        return fuel;
    }

    const char* getBrand() const
    {
        return brand;
    }
};

int main()
{
    Car car("BMW", 10, 50);

    car.drive(50);
    car.refuel(20);

    std::cout << "Brand: " << car.getBrand() << std::endl;
    std::cout << "Fuel: " << car.getFuel() << std::endl;

    return 0;
}
```

<hr style="border-width: 5px !important;">

`Задача 4: Да се създаде клас Counter, със следните полета и член-функции:
полета:
value
accessCount
член-функции:
increment() - Увеличава value с 1.
getValue() const - Връща стойността на value и увеличава стойността на accessCount.
getAccessCount() const - Връща стойността на accessCount.`

`Решение:`
```cpp
#include <iostream>

class Counter
{
private:
    int value;
    mutable int accessCount;

public:
    Counter()
    {
        value = 0;
        accessCount = 0;
    }

    void increment()
    {
        value++;
    }

    int getValue() const
    {
        accessCount++;
        return value;
    }

    int getAccessCount() const
    {
        return accessCount;
    }
};

int main()
{
    Counter c;

    c.increment();
    c.increment();

    std::cout << c.getValue() << std::endl;
    std::cout << c.getValue() << std::endl;

    std::cout << "Access count: " << c.getAccessCount() << std::endl;

    return 0;
}
```

<hr style="border-width: 5px !important;">

`Да се създаде клас ExamResult, със следните полета и член-функции:
полета:
score – цяло число в интервала [0 – 100]
timesChecked – брои колко пъти е извикана функцията getGrade()
lastReturnedGrade – пази последната изчислена оценка
член-функции:
setScore(newScore) - Задава стойност на score. Ако newScore < 0 или newScore > 100 → извежда подходящо съобщение и не променя стойността.
getGrade() const - Преобразува score в оценка по следната скала:.`

| Точки&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; | Оценка&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|-------------------------------------------------------------|-------------------------------------------------------------|
| 0–49                                                          | 2                                                           |
| 50–59                                                          | 3                                                           |
| 60–69	                                                          | 4                                                           |
| 70–84	                                                          | 5                                                           |
| 85–100	                                                          | 6                                                           |

`Увеличава timesChecked, записва получената оценка в lastReturnedGrade и връща оценката.
getTimesChecked() const - Връща стойността на timesChecked.
getLastReturnedGrade() const - Връща стойността на lastReturnedGrade.`

`Решение:`
```cpp
#include <iostream>

class ExamResult
{
private:
    int score;
    mutable int timesChecked;
    mutable int lastReturnedGrade;

public:
    ExamResult()
    {
        score = 0;
        timesChecked = 0;
        lastReturnedGrade = 2;
    }

    void setScore(int newScore)
    {
        if (newScore < 0 || newScore > 100)
        {
            std::cout << "Invalid score!" << std::endl;
        }
        else
        {
            score = newScore;
        }
    }

    int getGrade() const
    {
        int grade;

        if (score <= 49)
        {
            grade = 2;
        }
        else if (score <= 59)
        {
            grade = 3;
        }
        else if (score <= 69)
        {
            grade = 4;
        }
        else if (score <= 84)
        {
            grade = 5;
        }
        else
        {
            grade = 6;
        }

        timesChecked++;
        lastReturnedGrade = grade;

        return grade;
    }

    int getTimesChecked() const
    {
        return timesChecked;
    }

    int getLastReturnedGrade() const
    {
        return lastReturnedGrade;
    }
};

int main()
{
    ExamResult exam;

    exam.setScore(78);

    std::cout << "Grade: " << exam.getGrade() << std::endl;
    std::cout << "Grade: " << exam.getGrade() << std::endl;

    std::cout << "Times checked: " << exam.getTimesChecked() << std::endl;
    std::cout << "Last grade: " << exam.getLastReturnedGrade() << std::endl;

    return 0;
}
```

<hr style="border-width: 5px !important;">

`Задача 6: Да се създаде клас Point2D, със следните полета:
полета:
double x
double y
и да се реализират:
default конструктор
конструктор с параметри
деструктор
print() const - извежда координатите на точката във формат (x, y)`

`Решение:`
```cpp
#include <iostream>

using std::cout;
class Point2D
{
private:
    double x;
    double y;

public:
    Point2D()
    {
        this->x = 0;
        this->y = 0;
    }
    Point2D(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    ~Point2D()
    {
    }
    void print() const
    {
        cout << "(" << x << ", " << y << ")";
    }
};

void newLine()
{
    cout << std::endl;
}

int main()
{
    Point2D point1;
    Point2D point2{ 1.1, 2.3 };
    point1.print();
    newLine();
    point2.print();
}
```

<hr style="border-width: 5px !important;">

`Задача 7: Да се създаде клас Message, със следните полета:
полета:
char* text
и да се реализират:
default конструктор - задава text да е "no_text"
конструктор с параметри
деструктор
print() const - извежда text`

`Решение:`
```cpp
#include <iostream>

void newLine();
class Message
{
private:
    char* text;

public:
    Message()
    {
        text = new char[8];
        strcpy_s(text, 8, "no_text");
    }
    Message(const char* newText)
    {
        text = new char[strlen(newText) + 1];
        strcpy_s(text, (strlen(newText) + 1), newText);
    }
    ~Message()
    {
        delete[] text;
    }
    void print() const
    {
        std::cout << text;
        newLine();
    }
};
void newLine()
{
    std::cout << std::endl;
}
int main()
{
    Message message1;
    Message message2{ "Hello" };
    message1.print();
    message2.print();
}
```

<hr style="border-width: 5px !important;">
