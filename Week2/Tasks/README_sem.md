# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица втора
`Задача 1: Напишете клас teacher, който описва преподавател. Класът трябва да съдържа:
Име (фиксирана дължина)
Възраст
Години стаж като преподавател
Създайте подходящи конструктори, get и set член функции.`

`Решение:`
```cpp
#include <iostream>
static const int NAME_LENGTH = 50;

class Teacher
{
private:
    char name[NAME_LENGTH];
    int age;
    int yearsOfExperience;

public:
    Teacher() 
    {
        strcpy_s(name, (strlen("Unknown") + 1), "Unknown");
        age = 0;
        yearsOfExperience = 0;
    }
    Teacher(const char* name, int age, int yearsOfExperience) 
    {
        setName(name);
        setAge(age);
        setYearsOfExperience(yearsOfExperience);
    }

    const char* getName() const 
    {
        return name;
    }

    int getAge() const 
    {
        return age;
    }

    int getYearsOfExperience() const 
    {
        return yearsOfExperience;
    }

    void setName(const char* newName) 
    {
        if (newName == nullptr)
        {
            std::cout << "Name cannot be null." << std::endl;
            return;
        }
        if (strlen(newName) >= NAME_LENGTH)
        {
            std::cout << "Name cannot be more then 50 sybols." << std::endl;
            return;
        }
        strcpy_s(name, (strlen(newName) + 1), newName);
    }

    void setAge(int newAge) 
    {
        if (newAge < 18 || newAge > 100)
        {
            std::cout << "Invalid age." << std::endl;
            return;
        }
        age = newAge;
    }

    void setYearsOfExperience(int years) 
    {
        if (years < 0)
        {
            std::cout << "Years of experience cannot be negative." << std::endl;
            return;
        }
        if (years > age - 18)
        {
            std::cout << "Not real years of experience." << std::endl;
            return;
        }
        yearsOfExperience = years;
    }

    void print() const 
    {
        std::cout << "Teacher: " << name
            << ", Age: " << age
            << ", Years Of Experience: " << yearsOfExperience << std::endl;
    }
};

int main()
{
    Teacher t1;
    t1.print();

    Teacher t2("Ivan Ivanov", 45, 20);
    t2.print();

    Teacher t3;
    t3.setName("Maria Ivanova");
    t3.setAge(35);
    t3.setYearsOfExperience(10);
    t3.print();
}
```

<hr style="border-width: 5px !important;">
