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

`Задача 2: Създайте структура Car, която съдържа в себе си име на марка с произволна дължина, година на създаване, максимална скорост и масив с произволна дължина, пазещ колко километра са били пътуванията на колата (цяло число). Трябва да имплементирате:
Дефолтен конструктор
Конструктор с параметрите на колата
Деструктор (за да освободите динамичната памет, когато обектът умре)
Функция за записване на колата във файл
Функция, която прочита данни от файл
Функция, която връща колко общо са изминатите километри на автомобила
Функция, която връща големината на най-дългото пътуване`

`Решение:`
```cpp
#include <iostream>
#include <fstream>
#include <cstring>

struct Car
{
private:
    char* brand;
    int year;
    int maxSpeed;
    int* trips;
    int tripsCount;

public:
    Car() 
    {
        brand = nullptr;
        year = 0;
        maxSpeed = 0;
        trips = nullptr;
        tripsCount = 0;
    }

    Car(const char* _brand, int _year, int _maxSpeed, int* _trips, int _tripsCount) 
    {
        this->year = _year;
        this->maxSpeed = _maxSpeed;
        this->tripsCount = _tripsCount;

        this->brand = new char[strlen(_brand) + 1];
        strcpy_s(brand, (strlen(_brand) + 1), _brand);

        this->trips = new int[tripsCount];
        for (int i = 0; i < tripsCount; i++) 
        {
            trips[i] = _trips[i];
        }
    }

    ~Car() 
    {
        delete[] brand;
        delete[] trips;
    }

    void saveToFile(const char* filename) const 
    {
        std::ofstream out(filename);

        out << brand << std::endl;
        out << year << std::endl;
        out << maxSpeed << std::endl;
        out << tripsCount << std::endl;

        for (int i = 0; i < tripsCount; i++) 
        {
            out << trips[i] << " ";
        }

        out.close();
    }

    void readFromFile(const char* filename) 
    {
        std::ifstream in(filename);

        delete[] brand;
        delete[] trips;

        char buffer[256];
        in.getline(buffer, 256);

        brand = new char[strlen(buffer) + 1];
        strcpy_s(brand, (strlen(buffer) + 1), buffer);

        in >> year;
        in >> maxSpeed;
        in >> tripsCount;

        trips = new int[tripsCount];
        for (int i = 0; i < tripsCount; i++) 
        {
            in >> trips[i];
        }

        in.close();
    }

    int getTotalKilometers() const
    {
        int sum = 0;
        for (int i = 0; i < tripsCount; i++) 
        {
            sum += trips[i];
        }
        return sum;
    }

    int getLongestTrip() const
    {
        if (tripsCount == 0)
        {
            return 0;
        }

        int max = trips[0];
        for (int i = 1; i < tripsCount; i++) 
        {
            if (trips[i] > max) 
            {
                max = trips[i];
            }
        }
        return max;
    }
};

int main() 
{
    int trips[] = { 120, 340, 560, 230 };

    Car car1("Skoda", 2008, 200, trips, 4);

    car1.saveToFile("car.txt");

    Car car2;
    car2.readFromFile("car.txt");

    std::cout << "Total km: " << car2.getTotalKilometers() << std::endl;
    std::cout << "Longest trip: " << car2.getLongestTrip() << std::endl;
}
```

<hr style="border-width: 5px !important;">

`Задача 3: Серхо, подготвяйки задачите за контролното по ООП, реши, че е добра идея да внимава точно как пише задачите.
Всеки можеше да отвори лаптопа му и да открадне тази безценна информация.
Помогнете на Серхо да опази задачите от изпита - създайте клас secret.
Класът трябва да съдържа:
Условие на задачата
Парола
Брой неуспешни влизания Направете подходящи конструктори.
Да се напише функция getTask(const char*pwd), която връща условието тогава и само тогава когато сме въвели правилната парола.
Да се напише функция setPassword(const char* newPassword, const char* oldPassword), която променя паролата, но само ако сме въвели правилно старата парола.
Да се напише функция setTask(const char* newTask, const char* passwd), която променя условието на задачата ако сме въвели правилна парола.
Да се напише функция getLoginFails(), която връща броя на неуспешните влизания.Всеки път когато сме въвели неправилна парола броят на неуспешните влизания се увеличава. Трябва ли да има функция setLoginFails()?
Какво още трябва да добавим?`

`Решение:`
```cpp
#include <iostream>
#include <cstring>

class Secret
{
private:
    char* task;
    char* password;
    int loginFails;

public:
    Secret()
    {
        task = nullptr;
        password = nullptr;
        loginFails = 0;
    }

    Secret(const char* _task, const char* _password)
    {
        this->task = new char[strlen(_task) + 1];
        strcpy_s(task, (strlen(_task) + 1), _task);

        this->password = new char[strlen(_password) + 1];
        strcpy_s(password, (strlen(_password) + 1), _password);

        loginFails = 0;
    }

    ~Secret()
    {
        delete[] task;
        delete[] password;
    }

    const char* getTask(const char* pwd)
    {
        if (strcmp(pwd, password) == 0)
        {
            return task;
        }
        loginFails++;
        return "Wrong password!";
    }

    void setPassword(const char* newPassword, const char* oldPassword)
    {
        if (strcmp(oldPassword, password) == 0)
        {
            delete[] password;
            password = new char[strlen(newPassword) + 1];
            strcpy_s(password, (strlen(newPassword) + 1), newPassword);
        }
        else
        {
            loginFails++;
        }
    }

    void setTask(const char* newTask, const char* pwd)
    {
        if (strcmp(pwd, password) == 0)
        {
            delete[] task;
            task = new char[strlen(newTask) + 1];
            strcpy_s(task, (strlen(newTask) + 1), newTask);
        }
        else
        {
            loginFails++;
        }
    }

    int getLoginFails() const
    {
        return loginFails;
    }
};

int main()
{
    Secret s("OOP exam task", "1234");
    std::cout << s.getTask("1111") << std::endl;
    std::cout << s.getTask("1234") << std::endl;
    s.setPassword("abcd", "1234");
    s.setTask("New OOP task", "abcd");
    std::cout << s.getTask("abcd") << std::endl;
    std::cout << "Login fails: " << s.getLoginFails() << std::endl;

}
```

<hr style="border-width: 5px !important;">

