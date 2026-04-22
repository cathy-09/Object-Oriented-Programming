# Решения

<hr style="border-width: 5px !important;">

## Управление на служители във фирма

<hr style="border-width: 5px !important;">

```
Ще дефинираме следния enum class за връщане на статус на дадена операция:
```
```cpp
enum class ErrorCode {
    OK,
    NotFound,
    Duplicate,
    InvalidInput,
    Full
};
```
```
Забележка: Ако се сетите за още някой възможен edge case, добавете съответния код за грешка.
```
```
Клас Employee
Член-данни
unsigned id — генерира се автоматично и е уникално за всеки служител
char name[128] — низ с максимална дължина 127 символа
char position[128] — низ с максимална дължина 127 символа
double salary
Методи
Конструктор по подразбиране.
Конструктор с параметри.
double getSalary() const — връща заплатата.
ErrorCode updateSalary(double amount) — актуализира заплатата.
Статична функция, която връща ID-то на последно инициализирания служител.
Оператори
Служителите да могат да се извеждат на стандартния изход.
Служителите да могат да се сравняват — по заплата. При равни заплати — по ID.
Операторът ++ символизира годишно увеличение на заплатата с 10%. Да се имплементират и двете форми — prefix и postfix. Prefix връща служителя след увеличението, postfix — преди.
Клас Department
Член-данни
char* name — низ с произволна дължина
Employee* employees — динамичен масив от служители
unsigned countOfEmployees
unsigned capacity — капацитет на масива
Методи
Конструктор по подразбиране.

Конструктор с параметри — приема име и начален капацитет.

ErrorCode addEmployee(<помисли>) — добавя служител. При запълнен капацитет — удвоява масива.

ErrorCode removeEmployee(<по ид>) — премахва служител от отдела.

Оператори
Отделите да могат да се извеждат на стандартния изход.
Два отдела да могат да се сравняват — по брой служители. При равен брой — по средна заплата в отдела.
Операторът [] да позволява достъп до служител по индекс — с и без const.
Отделът да може да се използва в булев контекст — отделът е „активен" ако има поне един служител.
Операторът () приема процент и увеличава заплатата на всички служители в отдела с толкова процента. Връща референция към текущия отдел за верижно извикване.
Клас Company
Класът е имплементиран като Singleton — може да съществува най-много една инстанция на фирмата.

static Company& getInstance() — връща референция към единствената инстанция; създава я при първо извикване.
Конструкторът е private.
Copy конструкторът и operator= са изтрити.

Член-данни
Department departments[10] — масив с максимална големина 10
unsigned countOfDepartments
Методи
ErrorCode addDepartment(const char* name) — добавя отдел.
ErrorCode removeDepartment(const char* name) — премахва отдел.
ErrorCode addEmployeeToDepartment(const char* departmentName, const Employee& employee) — добавя служител към отдел.
ErrorCode removeEmployeeFromDepartment(const char* departmentName, unsigned id) — премахва служител от отдел.
Оператори
<< — извежда цялата структура на фирмата: всеки отдел с неговите служители.
Фирмата да може да се използва в булев контекст — фирмата е „активна" ако има поне един отдел с поне един служител.
Операторът [] приема име на отдел и връща указател към него. Ако отделът не съществува — връща nullptr.
Company е Singleton — copy и move конструкторите са изтрити. Помислете защо move-ът трябва да е изтрит заедно с copy-то.
```

<hr style="border-width: 5px !important;">

`Решение:`

`Employee.h`
```h
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <ostream>
#include <compare>

enum class ErrorCode 
{
    OK,
    NotFound,
    Duplicate,
    InvalidInput,
    Full,
    OutOfRange
};

class Employee
{
private:
    static const int MAX_SIZE = 128;
	unsigned id;
	char name[MAX_SIZE];
	char position[MAX_SIZE];
	double salary;

    static unsigned lastId;

public:
    Employee();
    Employee(const char* name, const char* position, double salary);
    unsigned getId() const;
    double getSalary() const;
    const char* getName() const;
    const char* getPosition() const;

    ErrorCode updateSalary(double amount);

    static unsigned getLastId();

    Employee& operator++();
    Employee operator++(int dummy);

    std::partial_ordering operator<=>(const Employee& other) const;
    bool operator==(const Employee& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Employee& e);
};
```

`Employee.cpp`
```cpp
#include "Employee.h"
#include "Department.h"

unsigned Employee::lastId = 0;

Employee::Employee() : id(++lastId), salary(0.0)
{
	name[0] = '\0';
	position[0] = '\0';
}

Employee::Employee(const char* name, const char* position, double salary)
	: id(++lastId)
{
	if (!name || !position)
	{
		this->name[0] = '\0';
		this->position[0] = '\0';
	}
	else
	{
		if (strlen(name) >= Employee::MAX_SIZE)
		{
			this->name[0] = '\0';
		}
		else
		{
			strcpy(this->name, name);
		}

		if (strlen(position) >= Employee::MAX_SIZE)
		{
			this->position[0] = '\0';
		}
		else
		{
			strcpy(this->position, position);
		}
	}

	if (salary < 0)
	{
		this->salary = 0;
	}
	else
	{
		this->salary = salary;
	}
}

unsigned Employee::getId() const
{
	return id;
}

double Employee::getSalary() const
{
	return salary;
}

const char* Employee::getName() const
{
	return name;
}

const char* Employee::getPosition() const
{
	return position;
}

ErrorCode Employee::updateSalary(double amount)
{
	if (salary + amount < 0)
	{
		return ErrorCode::InvalidInput;
	}
	this->salary += amount;
	return ErrorCode::OK;
}

unsigned Employee::getLastId()
{
	return lastId;
}

Employee& Employee::operator++() 
{
	const double PERCENT = 0.1;
	updateSalary(salary * PERCENT);
	return *this;
}

Employee Employee::operator++(int dummy) 
{
	const double PERCENT = 1.1;
	Employee copy = *this;
	salary *= PERCENT;
	return copy;
}

std::partial_ordering Employee::operator<=>(const Employee& other) const
{
	if (salary != other.salary)
	{
		return salary <=> other.salary;
	}
	return id <=> other.id;
}


bool Employee::operator==(const Employee& other) const
{
	bool expr = (salary == other.salary && id == other.id);
	return expr;
}

std::ostream& operator<<(std::ostream& os, const Employee& e)
{
	os << "Employee #" << e.id
		<< " " << e.name
		<< " | " << e.position
		<< " | Salary: " << e.salary;
	return os;
}
```

<hr style="border-width: 5px !important;">

`Department.h`
```h
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Employee.h"

class Department
{
private:
    char* name;
    Employee* employees;
    unsigned countOfEmployees;
    unsigned capacity;
    void copyFrom(const Department& other);
    void moveFrom(Department&& other) noexcept;
    void free();
    void resize();
    static Employee dummyEmployee;
    static const int CAP_SIZE = 4;

public:
    Department();
    Department(const char* name, unsigned initialCapacity = 4);

    Department(const Department& other);
    Department& operator=(const Department& other);
    Department(Department&& other) noexcept;
    Department& operator=(Department&& other) noexcept;
    ~Department();

    const char* getName() const;
    unsigned getCount() const;
    double averageSalary() const;

    ErrorCode addEmployee(const Employee& employee);
    ErrorCode removeEmployee(unsigned id);

    Employee& operator[](unsigned index);
    const Employee& operator[](unsigned index) const;

    Department& operator()(double percent);

    std::partial_ordering operator<=>(const Department& other) const;
    bool operator==(const Department& other) const;

    explicit operator bool() const;

    friend std::ostream& operator<<(std::ostream& os, const Department& department);
};
```

`Department.cpp`
```cpp
#include "Department.h"

Employee Department::dummyEmployee;

void Department::copyFrom(const Department& other)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    countOfEmployees = other.countOfEmployees;
    capacity = other.capacity;

    employees = new Employee[capacity];
    for (unsigned i = 0; i < countOfEmployees; i++)
    {
        employees[i] = other.employees[i];
    }
}

void Department::moveFrom(Department&& other) noexcept
{
    name = other.name;
    employees = other.employees;
    countOfEmployees = other.countOfEmployees;
    capacity = other.capacity;
    other.name = new char[1];
    other.name[0] = '\0';
    other.employees = new Employee[Department::CAP_SIZE];
    other.capacity = Department::CAP_SIZE;
    other.countOfEmployees = 0;
}

void Department::free()
{
    delete[] name;
    delete[] employees;
}

void Department::resize()
{
    unsigned newCapacity = capacity * 2;
    Employee* newArray = new Employee[newCapacity];
    for (unsigned i = 0; i < countOfEmployees; i++)
    {
        newArray[i] = employees[i];
    }
    delete[] employees;
    employees = newArray;
    capacity = newCapacity;
}

Department::Department() : countOfEmployees(0), capacity(Department::CAP_SIZE)
{
    name = new char[1];
    name[0] = '\0';

    employees = new Employee[capacity];
}

Department::Department(const char* name, unsigned initialCapacity)
{
    if (!name)
    {
        name = "";
    }

    countOfEmployees = 0;

    if (initialCapacity > 0)
    {
        capacity = initialCapacity;
    }
    else
    {
        capacity = 4;
    }

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    employees = new Employee[capacity];
}

Department::Department(const Department& other)
{
    copyFrom(other);
}

Department& Department::operator=(const Department& other) 
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

Department::Department(Department&& other) noexcept : name(other.name), employees(other.employees),
countOfEmployees(other.countOfEmployees), capacity(other.capacity)
{
    moveFrom(std::move(other));
}

Department& Department::operator=(Department&& other) noexcept
{
    if(this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Department::~Department() 
{
    free();
}

const char* Department::getName() const 
{
    return name; 
}

unsigned Department::getCount() const 
{
    return countOfEmployees; 
}

double Department::averageSalary() const
{
    if (countOfEmployees == 0)
    {
        return 0.0;
    }
    double total = 0.0;
    for (unsigned i = 0; i < countOfEmployees; i++)
    {
        total += employees[i].getSalary();
    }
    return (total / countOfEmployees);
}

ErrorCode Department::addEmployee(const Employee& employee)
{
    for (unsigned i = 0; i < countOfEmployees; i++)
    {
        if (employees[i].getId() == employee.getId())
        {
            return ErrorCode::Duplicate;
        }
    }
    if (countOfEmployees == capacity)
    {
        resize();
    }
    employees[countOfEmployees++] = employee;
    return ErrorCode::OK;
}

ErrorCode Department::removeEmployee(unsigned id)
{
    for (unsigned i = 0; i < countOfEmployees; i++) 
    {
        if (employees[i].getId() == id) 
        {
            for (unsigned j = i; j < countOfEmployees - 1; j++)
            {
                employees[j] = employees[j + 1];
            }
            countOfEmployees--;
            return ErrorCode::OK;
        }
    }
    return ErrorCode::NotFound;
}

Employee& Department::operator[](unsigned index)
{
    if (index >= countOfEmployees)
    {
        return dummyEmployee;
    }
    return employees[index];
}

const Employee& Department::operator[](unsigned index) const
{
    if (index >= countOfEmployees)
    {
        return dummyEmployee;
    }
    return employees[index];
}
Department& Department::operator()(double percent) 
{
    const int NEGATIVE_PERCENT = -100;
    if (percent <= NEGATIVE_PERCENT)
    {
        return *this;
    }

    for (unsigned i = 0; i < countOfEmployees; i++) 
    {
        employees[i].updateSalary(employees[i].getSalary() * percent / 100.0);
    }
    return *this;
}

std::partial_ordering Department::operator<=>(const Department& other) const
{
    if (countOfEmployees != other.countOfEmployees)
    {
        return countOfEmployees <=> other.countOfEmployees;
    }
    return averageSalary() <=> other.averageSalary();
}

bool Department::operator==(const Department& other) const 
{
    return ((countOfEmployees == other.countOfEmployees) && (averageSalary() == other.averageSalary()));
}

Department::operator bool() const 
{ 
    return (countOfEmployees > 0); 
}

std::ostream& operator<<(std::ostream& os, const Department& d) 
{
    os << "Department: " << d.name << " " << d.countOfEmployees << " employees" << std::endl;
    for (unsigned i = 0; i < d.countOfEmployees; i++)
    {
        os << d.employees[i] << std::endl;
    }
    return os;
}
```

<hr style="border-width: 5px !important;">

`Company.h`
```h
#pragma once
#include "Employee.h"
#include "Department.h"
class Company
{
private:
	Department departments[10];
	unsigned countOfDepartments;

	Company();

public:
	static Company& getInstance();

	Company(const Company&) = delete;
	Company& operator=(const Company&) = delete;
	Company(Company&&) = delete;
	Company& operator=(Company&&) = delete;

	ErrorCode addDepartment(const char* name);
	ErrorCode removeDepartment(const char* name);
	ErrorCode addEmployeeToDepartment(const char* departmentName, const Employee& employee);
	ErrorCode removeEmployeeFromDepartment(const char* departmentName, unsigned id);

	Department* operator[](const char* departmentName);
	const Department* operator[](const char* departmentName) const;

	explicit operator bool() const;

	friend std::ostream& operator<<(std::ostream& os, const Company& company);
};
```

`Company.cpp`
```cpp
#include "Company.h"

Company::Company() : countOfDepartments(0) 
{

}

Company& Company::getInstance()
{
	static Company instance;
	return instance;
}

ErrorCode Company::addDepartment(const char* name)
{
    if (!name)
    {
        return ErrorCode::InvalidInput;
    }
    if (countOfDepartments >= 10)
    {
        return ErrorCode::Full;
    }
    for (unsigned i = 0; i < countOfDepartments; i++)
    {
        if (strcmp(departments[i].getName(), name) == 0)
        {
            return ErrorCode::Duplicate;
        }
    }
    departments[countOfDepartments++] = Department(name);
    return ErrorCode::OK;
}

ErrorCode Company::removeDepartment(const char* name)
{
    if (!name)
    {
        return ErrorCode::InvalidInput;
    }
    for (unsigned i = 0; i < countOfDepartments; i++) 
    {
        if (strcmp(departments[i].getName(), name) == 0) 
        {
            for (unsigned j = i; j < countOfDepartments - 1; j++)
            {
                departments[j] = departments[j + 1];
            }
            departments[countOfDepartments - 1] = Department();
            countOfDepartments--;
            return ErrorCode::OK;
        }
    }
    return ErrorCode::NotFound;
}

ErrorCode Company::addEmployeeToDepartment(const char* departmentName, const Employee& employee)
{
    for (unsigned i = 0; i < countOfDepartments; i++)
    {
        if (strcmp(departments[i].getName(), departmentName) == 0)
        {
            return departments[i].addEmployee(employee);
        }
    }
    return ErrorCode::NotFound;
}

ErrorCode Company::removeEmployeeFromDepartment(const char* departmentName, unsigned id)
{
    for (unsigned i = 0; i < countOfDepartments; i++)
    {
        if (strcmp(departments[i].getName(), departmentName) == 0)
        {
            return departments[i].removeEmployee(id);
        }
    }
    return ErrorCode::NotFound;
}

Department* Company::operator[](const char* departmentName) 
{
    if (!departmentName)
    {
        return nullptr;
    }
    for (unsigned i = 0; i < countOfDepartments; i++)
    {
        if (strcmp(departments[i].getName(), departmentName) == 0)
        {
            return &departments[i];
        }
    }
    return nullptr;
}

const Department* Company::operator[](const char* departmentName) const 
{
    for (unsigned i = 0; i < countOfDepartments; i++)
    {
        if (strcmp(departments[i].getName(), departmentName) == 0)
        {
            return &departments[i];
        }
    }
    return nullptr;
}

Company::operator bool() const 
{
    for (unsigned i = 0; i < countOfDepartments; i++)
    {
        if (departments[i].getCount() > 0)
        {
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Company& company)
{
    os << "Company" << std::endl;
    for (unsigned i = 0; i < company.countOfDepartments; i++)
    {
        os << company.departments[i] << std::endl;
    }
    return os;
}
```

<hr style="border-width: 5px !important;">

`task1.cpp`
```cpp
#include "Employee.h"
#include <iostream>
#include "Company.h"

int main()
{
    Employee e1("Ivan Ivanov", "Developer", 3000.0);
    Employee e2("Maria Petrova", "Designer", 2500.0);
    Employee e3("Petar Georgiev", "Manager", 4000.0);

    std::cout << e1 << std::endl;

    ++e1;   // заплатата нараства с 10%: 3000 → 3300
    std::cout << e1.getSalary() << std::endl;   // 3300

    std::cout << (e1 > e2 ? "e1 is better paid" : "e2 is better paid") << std::endl;;

    Company& company = Company::getInstance();

    company.addDepartment("Engineering");
    company.addDepartment("Design");

    company.addEmployeeToDepartment("Engineering", e1);
    company.addEmployeeToDepartment("Engineering", e2);
    company.addEmployeeToDepartment("Design", e3);

    std::cout << company;

    // operator[] за достъп до отдел
    Department* eng = company["Engineering"];
    if (eng) {
        std::cout << (*eng)[0] << "\n";   // първият служител в Engineering
        (*eng)(15);                        // увеличава заплатите с 15%
        (*eng)(15)(10);                    // верижно — 15%, после още 10%
    }

    if (*eng)
    {
        std::cout << "Engineering is active\n";
    }

    if (company)
        std::cout << "The firm is active\n";

    Department* des = company["Design"];
    if (eng && des)
        std::cout << (*eng > *des ? "Engineering is bigger" : "Design is bigger") << "\n";

    company.removeEmployeeFromDepartment("Engineering", e2.getId());
    company.removeDepartment("Design");
}
```

<hr style="border-width: 5px !important;">

## Система за регистрация на превозни средства

<hr style="border-width: 5px !important;">

```
Регистрационните номера на превозни средства се състоят от:

Един или два символа от латинската азбука (населено място)
Четири цифри
Два символа от латинската азбука
Примери за валидни номера: C1234AB, XY1111YX Примери за невалидни номера: 111145, ABC34DEF, ABCDEF, C11D

Класът няма конструктор по подразбиране. Невалидни регистрационни номера не трябва да могат да се създават.

Функционалности
Конструктор, който приема C-style низ и валидира съдържанието му.
Регистрационните номера да могат да се извеждат на стандартния изход.
Два регистрационни номера да могат да се сравняват.
Да може да се получи регистрационният номер като низ.
Задача 2.2: Клас Vehicle
Превозното средство се характеризира с регистрационен номер, описание с произволна дължина, година на производство и мощност на двигателя в к.с.

Класът няма конструктор по подразбиране.

Функционалности
Конструктор, който инициализира регистрационния номер, описанието, годината на производство и мощността.
Превозните средства да могат да се извеждат на стандартния изход.
Две превозни средства да могат да се сравняват — по година на производство. При равни години — по мощност на двигателя.
Задача 2.3: Клас VehicleList
Динамичен Списък от превозни средства. В списъка не могат да съществуват две превозни средства с еднакви регистрационни номера.

Функционалности
Конструктор, създаващ списък с определен капацитет. Вътрешно списъкът е масив от указатели — свободните слотове са nullptr.
+= — добавя превозно средство на първия свободен слот (nullptr). При вече съществуващ регистрационен номер операцията се игнорира. При запълнен капацитет — капацитетът се удвоява.
-= — премахва превозно средство по регистрационен номер. Освобождава слота (nullptr).
<< — извеждане на списъка на стандартния изход. Свободните слотове се представят с "*".
Два списъка да могат да се сравняват — по общия брой превозни средства. При равен брой — по лексикографски ред на регистрационния номер на първото намерено превозно средство.
() — приема код на населено място (например "C" или "XY") и връща броя превозни средства, регистрирани в това населено място.
Списъкът да може да се използва в булев контекст — списъкът се счита за валиден ако съдържа поне един елемент.
Достъп до елемент по индекс.
isFreeSlot(pos) — връща дали слотът на позиция pos е свободен.
isEmpty() — проверка дали списъкът е празен.
capacity() и size() — капацитет и текущ брой елементи.
find(reg) — търсене по регистрационен номер. Връща указател към намереното превозно средство или nullptr.
```

<hr style="border-width: 5px !important;">

`Решение:`

`Vehicle.h`
```h
#pragma once
#include "Registration.h"
class Vehicle
{
private:
    Registration registration;
    char* description;
    unsigned year;
    unsigned horsepower;

    void free();
    void copyFrom(const Vehicle& other);
    void moveFrom(Vehicle&& other) noexcept;

public:
    Vehicle() = delete;
    Vehicle(const Registration& reg, const char* description, unsigned year, unsigned hp);

    Vehicle(const Vehicle& other);
    Vehicle& operator=(const Vehicle& other);
    Vehicle(Vehicle&& other) noexcept;
    Vehicle& operator=(Vehicle&& other) noexcept;
    ~Vehicle();

    const Registration& getRegistration() const;
    const char* getDescription() const;
    unsigned getYear() const;
    unsigned getHorsepower() const;

    std::strong_ordering operator<=>(const Vehicle& other) const;
    bool operator==(const Vehicle& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Vehicle& v);
};
```

`Vehicle.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Vehicle.h"
#include <cstring>

void Vehicle::free()
{
	delete[] description;
	description = nullptr;
}

void Vehicle::copyFrom(const Vehicle& other)
{
	description = new char[strlen(other.description) + 1];
	strcpy(description, other.description);
	year = other.year;
	horsepower = other.horsepower;
}

void Vehicle::moveFrom(Vehicle&& other) noexcept
{
	registration = other.registration;
	description = other.description;
	year = other.year;
	horsepower = other.horsepower;
	other.description = nullptr;
}

Vehicle::Vehicle(const Registration& reg, const char* desc, unsigned year, unsigned hp)
	: registration(reg), year(year), horsepower(hp)
{
	if (!desc)
	{
		desc = "";
	}
	if (year < 1885 || year > 2026)
	{
		this->year = 0;
	}
	if (hp == 0)
	{
		this->horsepower = 0;
	}

	description = new char[strlen(desc) + 1];
	strcpy(description, desc);
}

Vehicle::Vehicle(const Vehicle& other)
	: registration(other.registration),
	year(other.year),
	horsepower(other.horsepower)
{
	description = new char[strlen(other.description) + 1];
	strcpy(description, other.description);
}

Vehicle& Vehicle::operator=(const Vehicle& other)
{
	if (this != &other)
	{
		free();
		registration = other.registration;
		copyFrom(other);
	}
	return *this;
}

Vehicle::~Vehicle()
{
	free();
}

Vehicle::Vehicle(Vehicle&& other) noexcept : registration(other.registration), description(other.description),
year(other.year), horsepower(other.horsepower)
{
	moveFrom(std::move(other));
}

Vehicle& Vehicle::operator=(Vehicle&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

const Registration& Vehicle::getRegistration() const
{
	return registration;
}
const char* Vehicle::getDescription() const
{
	return description;
}
unsigned Vehicle::getYear() const
{
	return year;
}
unsigned Vehicle::getHorsepower() const
{
	return horsepower;
}

std::strong_ordering Vehicle::operator<=>(const Vehicle& other) const
{
	if (year != other.year)
	{
		return year <=> other.year;
	}
	return horsepower <=> other.horsepower;
}

bool Vehicle::operator==(const Vehicle& other) const
{
	return (registration == other.registration);
}

std::ostream& operator<<(std::ostream& os, const Vehicle& v)
{
	os << v.registration << " "
		<< v.description
		<< " | Year: " << v.year
		<< " | HP: " << v.horsepower;
	return os;
}
```

<hr style="border-width: 5px !important;">

`Registration.h`
```h
#pragma once
#include <ostream>

class Registration
{
private:
     static const int MAX_REG_NUMBER = 10;
    char reg[MAX_REG_NUMBER];

    static bool validate(const char* str);
    static bool checkLetters(const char* str, int start, int count);
    static bool checkDigits(const char* str, int start, int count);
    

public:
    Registration() = delete;
    explicit Registration(const char* str);

    const char* toString() const;
    bool isValid() const;

    bool operator==(const Registration& other) const;
    bool operator!=(const Registration& other) const;
    bool operator<(const Registration& other) const;
    bool operator>(const Registration& other) const;

    void getCity(char* out) const;

    friend std::ostream& operator<<(std::ostream& os, const Registration& registration);
};
```

`Registration.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Registration.h"

bool isMyAlpha(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool isMyDigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool Registration::checkLetters(const char* str, int start, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (!isMyAlpha(str[start + i]))
		{
			return false;
		}
	}
	return true;
}

bool Registration::checkDigits(const char* str, int start, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (!isMyDigit(str[start + i]))
		{
			return false;
		}
	}
	return true;
}

Registration::Registration(const char* str)
{
	if (!str || !validate(str))
	{
		reg[0] = '\0';
		return;
	}
	if (strlen(str) >= Registration::MAX_REG_NUMBER)
	{
		reg[0] = '\0';
		return;
	}

	strcpy(reg, str);
}

const char* Registration::toString() const
{
	return reg;
}

bool Registration::isValid() const
{
	return reg[0] != '\0';
}

bool Registration::operator==(const Registration& other) const
{
	return (strcmp(reg, other.reg) == 0);
}

bool Registration::operator!=(const Registration& other) const
{
	return !(*this == other);
}

bool Registration::operator<(const Registration& other) const
{
	return (strcmp(reg, other.reg) < 0);
}

bool Registration::operator>(const Registration& other) const
{
	return (other < *this);
}

void Registration::getCity(char* out) const
{ 
	int i;
	for (i = 0; reg[i] && isMyAlpha(reg[i]); i++)
	{
		out[i] = reg[i];
	}
	out[i] = '\0';
}

bool Registration::validate(const char* str)
{
	if (!str)
	{
		return false;
	}

	int len = strlen(str);
	if (len != 7 && len != 8)
	{
		return false;
	}

	int prefix = (len == 7) ? 1 : 2;

	if (!checkLetters(str, 0, prefix))
	{
		return false;
	}

	if (!checkDigits(str, prefix, 4))
	{
		return false;
	}

	if (!checkLetters(str, prefix + 4, len - (prefix + 4)))
	{
		return false;
	}

	return true;
}

std::ostream& operator<<(std::ostream& os, const Registration& registration)
{
	return os << registration.reg;
}
```

<hr style="border-width: 5px !important;">

`VehicleList.h`
```h
#pragma once
#include "Vehicle.h"

class VehicleList 
{
private:
    Vehicle** slots;
    unsigned cap;
    unsigned count;

    void resize();
    void copyFrom(const VehicleList& other);
    void free();
    void moveFrom(VehicleList&& other) noexcept;
    static const int CAP_SIZE = 4;

public:
    explicit VehicleList(unsigned initialCapacity = 4);

    VehicleList(const VehicleList& other);
    VehicleList& operator=(const VehicleList& other);
    VehicleList(VehicleList&& other) noexcept;
    VehicleList& operator=(VehicleList&& other) noexcept;
    ~VehicleList();

    VehicleList& operator+=(const Vehicle& v);
    VehicleList& operator-=(const Registration& reg);

    unsigned operator()(const char* cityCode) const;

    Vehicle* operator[](unsigned index);
    const Vehicle* operator[](unsigned index) const;

    std::partial_ordering operator<=>(const VehicleList& other) const;
    bool operator==(const VehicleList& other) const;

    explicit operator bool() const;

    bool isFreeSlot(unsigned pos) const;
    bool isEmpty() const;
    unsigned capacity() const;
    unsigned size() const;
    Vehicle* find(const Registration& reg) const;

    friend std::ostream& operator<<(std::ostream& os, const VehicleList& list);
};
```

`VehicleList.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "VehicleList.h"
#include <cstring>
#include <stdexcept>

void VehicleList::resize()
{
	unsigned newCap = cap * 2;
	Vehicle** newSlots = new Vehicle * [newCap];
	for (unsigned i = 0; i < cap; i++)
	{
		newSlots[i] = slots[i];
	}
	for (unsigned i = cap; i < newCap; i++)
	{
		newSlots[i] = nullptr;
	}
	delete[] slots;
	slots = newSlots;
	cap = newCap;
}

VehicleList::VehicleList(unsigned initialCapacity)
{
	count = 0;

	if (initialCapacity > 0)
	{
		cap = initialCapacity;
	}
	else
	{
		cap = VehicleList::CAP_SIZE;
	}

	slots = new Vehicle * [cap];

	for (unsigned i = 0; i < cap; i++)
	{
		slots[i] = nullptr;
	}
}

void VehicleList::moveFrom(VehicleList&& other) noexcept
{
	slots = other.slots;
	cap = other.cap;
	count = other.count;
	other.slots = new Vehicle * [1] { nullptr };
	other.cap = 1;
	other.count = 0;
}

void VehicleList::copyFrom(const VehicleList& other)
{
	cap = other.cap;
	count = other.count;

	slots = new Vehicle * [cap];

	for (unsigned i = 0; i < cap; i++)
	{
		if (other.slots[i])
		{
			slots[i] = new Vehicle(*other.slots[i]);
		}
		else
		{
			slots[i] = nullptr;
		}
	}
}

void VehicleList::free()
{
	for (unsigned i = 0; i < cap; i++)
	{
		delete slots[i];
	}
	delete[] slots;

	slots = nullptr;
	cap = 0;
	count = 0;
}

VehicleList::VehicleList(const VehicleList& other)
{
	copyFrom(other);
}

VehicleList& VehicleList::operator=(const VehicleList& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

VehicleList::~VehicleList()
{
	free();
}

VehicleList::VehicleList(VehicleList&& other) noexcept
	: slots(other.slots), cap(other.cap), count(other.count)
{
	moveFrom(std::move(other));
}

VehicleList& VehicleList::operator=(VehicleList&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

VehicleList& VehicleList::operator+=(const Vehicle& v)
{
	for (unsigned i = 0; i < cap; i++)
	{
		if (slots[i] && slots[i]->getRegistration() == v.getRegistration())
		{
			return *this;
		}
	}
	for (unsigned i = 0; i < cap; i++)
	{
		if (!slots[i])
		{
			slots[i] = new Vehicle(v);
			count++;
			return *this;
		}
	}
	resize();
	for (unsigned i = 0; i < cap; i++)
	{
		if (!slots[i])
		{
			slots[i] = new Vehicle(v);
			count++;
			return *this;
		}
	}
	return *this;
}

VehicleList& VehicleList::operator-=(const Registration& reg)
{
	for (unsigned i = 0; i < cap; i++)
	{
		if (slots[i] && slots[i]->getRegistration() == reg)
		{
			delete slots[i];
			slots[i] = nullptr;
			count--;
			return *this;
		}
	}
	return *this;
}

unsigned VehicleList::operator()(const char* cityCode) const
{
	if (!cityCode)
	{
		return 0;
	}

	unsigned result = 0;
	char city[4] = {};

	for (unsigned i = 0; i < cap; i++)
	{
		if (!slots[i])
		{
			continue;
		}
		slots[i]->getRegistration().getCity(city);
		if (strcmp(city, cityCode) == 0)
		{
			result++;
		}
	}
	return result;
}

Vehicle* VehicleList::operator[](unsigned index)
{
	if (index >= cap)
	{
		return nullptr;
	}
	return slots[index];
}

const Vehicle* VehicleList::operator[](unsigned index) const
{
	if (index >= cap)
	{
		return nullptr;
	}
	return slots[index];
}

std::partial_ordering VehicleList::operator<=>(const VehicleList& other) const
{
	if (count != other.count)
	{
		return count <=> other.count;
	}
	const char* a = nullptr;
	const char* b = nullptr;
	for (unsigned i = 0; i < cap; i++)
	{
		if (slots[i])
		{
			a = slots[i]->getRegistration().toString();
			break;
		}
	}
	for (unsigned i = 0; i < other.cap; i++)
	{
		if (other.slots[i])
		{
			b = other.slots[i]->getRegistration().toString();
			break;
		}
	}
	if (!a && !b)
	{
		return std::partial_ordering::equivalent;
	}
	if (!a)
	{
		return std::partial_ordering::less;
	}
	if (!b)
	{
		return std::partial_ordering::greater;
	}
	int compare = strcmp(a, b);
	if (compare < 0)
	{
		return std::partial_ordering::less;
	}
	if (compare > 0)
	{
		return std::partial_ordering::greater;
	}
	return std::partial_ordering::equivalent;
}

bool VehicleList::operator==(const VehicleList& other) const
{
	return (count == other.count);
}

VehicleList::operator bool() const
{
	return count > 0;
}

bool VehicleList::isFreeSlot(unsigned pos) const
{
	if (pos >= cap)
	{
		return false;
	}
	return (slots[pos] == nullptr);
}
bool VehicleList::isEmpty() const
{
	return count == 0;
}
unsigned VehicleList::capacity() const
{
	return cap;
}
unsigned VehicleList::size() const
{
	return count;
}

Vehicle* VehicleList::find(const Registration& reg) const
{
	for (unsigned i = 0; i < cap; i++)
	{
		if (slots[i] && slots[i]->getRegistration() == reg)
		{
			return slots[i];
		}
	}
	return nullptr;
}

std::ostream& operator<<(std::ostream& os, const VehicleList& list)
{
	for (unsigned i = 0; i < list.cap; i++)
	{
		if (list.slots[i])
		{
			os << list.slots[i]->getRegistration() << " ";
		}
		else
		{
			os << "[*] ";
		}
	}
	return os;
}
```

<hr style="border-width: 5px !important;">

`tsk2.cpp`
```cpp
#include "Registration.h"
#include "Vehicle.h"
#include <iostream>
#include "VehicleList.h"
int main() 
{
    Registration r1("C1234AB");
    Registration r2("C5678XY");
    Registration r3("XY1111AB");

    std::cout << r1 << "\n";   // C1234AB

    Vehicle v1(r1, "Honda Civic", 2019, 150);
    Vehicle v2(r2, "Toyota Yaris", 2021, 120);
    Vehicle v3(r3, "BMW X5", 2019, 250);

    std::cout << v1 << "\n";
    // Сравнение по година: 2019 < 2021
    std::cout << (v1 < v2 ? "v1 is older" : "v2 is older") << "\n";  // v1
    // При равни години — по мощност: 150 < 250
    std::cout << (v1 < v3 ? "v1 is weaker" : "v3 is weaker") << "\n";  // v1

    VehicleList list(10);

    list += v1;   // слот 0
    list += v2;   // слот 1
    list += v3;   // слот 2
    list += v1;   // игнорира се — дублиран номер

    std::cout << list.size() << "\n";   // 3
    std::cout << list.capacity() << "\n";   // 10
    std::cout << list.isEmpty() << "\n";   // false
    std::cout << list.isFreeSlot(3) << "\n"; // true

    if (list)
        std::cout << "The list is valid\n";

    std::cout << list << "\n";
    // [C1234AB] [C5678XY] [XY1111AB] [*] [*] ...

    std::cout << list("C") << "\n";   // 2 — v1 и v2
    std::cout << list("XY") << "\n";   // 1 — v3

    list -= r2;   // премахва v2 ? слот 1 става nullptr

    std::cout << list.size() << "\n";   // 2
    std::cout << list << "\n";
    // [C1234AB] [*] [XY1111AB] [*] ...

    list += v2;   // добавя на първия свободен слот ? слот 1

    Vehicle* found = list.find(r1);
    if (found)
        std::cout << "Found: " << *found << "\n";

    VehicleList list2(5);
    list2 += v1;
    list2 += v2;

    // Сравнение: list има 3 коли, list2 има 2 ? list > list2
    std::cout << (list > list2 ? "list is bigger" : "list2 is bigger") << "\n";
}
```
