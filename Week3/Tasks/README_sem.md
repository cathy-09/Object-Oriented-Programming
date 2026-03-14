# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица трета
```
Да се създаде структура Jedi със следните характеристики:
Име (максимална дължина 50 символа)
- Възраст
- Сила
- LightSaber
Всеки лазер да се опише със следните полета:

Цвят - RED, YELLOW, GREEN, BLUE, PURPLE
Тип - SINGLEBLADED, DOUBLE_BLADED, CROSSGUARD
Да се напише клас JediCollection, която да може да пази в себе си най-много 100 джедая и техния брой. Да се реализира следния набор от член-функции: Където има скоби трябва да прецените какви типове трябва да приемат функциите и да връщат, къде трябва да е const къде по референция и т.н

Jedi ((НИЗ)name, (Цяло естествено число) age, (Цяло естествено число) power, (LightSaber) saber) – конструктор. Да се реализира overload, приемащ създаден цвят и тип на лазер вместо lightsaber
Функции на JediCollection

void addJedi((Джедай) jedi) – добавя джедай в колекцията
void removeJedi((НИЗ)name) – премахва джедая с подаденото име от колекцията и премества наляво елементите, които са били вдясно от него
void print() – принтира колекцията
Създайте и клас JediData, който има за цел да представя данни за джедаите и реализира следните функции:

void sortByAge((Колекция от Джедаи) collection) – сортира колекция във възходящ ред по възраст
void sortByPower((Колекция от Джедаи) collection) – сортира колекция във възходящ ред по сила
Color mostPopularSaberColor((Колекция от Джедаи) collection) – връща най-използвания цвят на лазер от джедаите в колекцията
Type mostPopularSaberType((Колекция от Джедаи) collection) – връща най-използвания тип на лазер от джедаите в колекцията
Създайте клас JediIO, който се грижи за четенето и писането на колекции от и във файлове и има следните функции:

void saveToBinary((Колекция от Джедаи) collection, (НИЗ) fileName) – запазва колекцията в подадения двоичен файл.
(Колекция от Джедаи) readFromBinary((НИЗ) fileName) – прочита колекцията от двоичен файл и я връща
void saveToTxt((Колекция от Джедаи) collection, (НИЗ) fileName) – запазва колекцията в подадения текстов файл
(Колекция от Джедаи) readFromTxt((Колекция от Джедаи) collection, (НИЗ) fileName) – прочита колекцията от текстов файл и я връща Реализирайте overload с потоци за четене/писане на горните 4 функции
```

`Решение:`

`JediUtils.h`
```h
#pragma once
#include "Jedi.h"
const char* colorToString(SaberColor color);
const char* typeToString(SaberType type);
```

`Jedi.h`
```h
#pragma once 
#include <istream>
#include <ostream>
#include <fstream>

enum class SaberColor
{
	RED,
	YELLOW,
	GREEN,
	BLUE,
	PURPLE,
};

enum class SaberType
{
	SINGLE_BLADED,
	DOUBLE_BLADED,
	CROSSGUARD,
};

struct LightSaber
{
	SaberColor color;
	SaberType  type;
	LightSaber(SaberColor color = SaberColor::BLUE, SaberType  type = SaberType::SINGLE_BLADED);
};

struct Jedi
{
	static const int MAX_NAME_LENGTH = 50;
	char name[MAX_NAME_LENGTH + 1];
	int age;
	int power;
	LightSaber saber;

	Jedi() = default;
	Jedi(const char* name, int age, int power, const LightSaber& saber);
	Jedi(const char* name, int age, int power, SaberColor color, SaberType type);
};

class JediCollection
{
private:
	static const int MAX_JEDIS = 100;
	Jedi jedis[MAX_JEDIS];
	int count = 0;

public:
	JediCollection();
	void addJedi(const Jedi& jedi);
	void removeJedi(const char* name);
	void print() const;
	int size() const;
	Jedi& getJedi(int index); 
	const Jedi& getJedi(int index) const;
	void setJedi(int index, const Jedi& jedi);
	void swapJedi(int i, int j);
};

class JediData
{
public:
	static void sortByAge(JediCollection& collection);
	static void sortByPower(JediCollection& collection);
	static SaberColor mostPopularSaberColor(const JediCollection& collection);
	static SaberType  mostPopularSaberType(const JediCollection& collection);
};

class JediIO
{
public:
	static void saveToBinary(const JediCollection& collection, const char* fileName);
	static JediCollection readFromBinary(const char* fileName);

	static void saveToBinary(std::ofstream& out, const JediCollection& collection);
	static JediCollection readFromBinary(std::ifstream& in);

	static void saveToTxt(const JediCollection& collection, const char* fileName);
	static JediCollection readFromTxt(const char* fileName);

	static void saveToTxt(std::ostream& out, const JediCollection& collection);
	static JediCollection readFromTxt(std::istream& in);
};
```

`Jedi.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Jedi.h"
#include <iostream>
using std::cout;


static void safeCopyName(char* destination, const char* source)
{
	if (!source || source[0] == '\0')
	{
		cout << "Jedi name cannot be empty.";
		return;
	}
	if (strlen(source) > Jedi::MAX_NAME_LENGTH)
	{
		cout << "Jedi name exceeds 50 characters.";
		return;
	}

	strncpy(destination, source, Jedi::MAX_NAME_LENGTH);
	destination[Jedi::MAX_NAME_LENGTH] = '\0';
}

LightSaber::LightSaber(SaberColor color, SaberType type) : color(color), type(type)
{

}

Jedi::Jedi(const char* name, int age, int power, const LightSaber& saber) : age(age), power(power), saber(saber)
{
	safeCopyName(this->name, name);
}

Jedi::Jedi(const char* name, int age, int power, SaberColor color, SaberType type) : Jedi(name, age, power, LightSaber(color, type))
{

}

JediCollection::JediCollection() : count(0)
{

}

void JediCollection::addJedi(const Jedi& jedi)
{
	if (count >= MAX_JEDIS)
	{
		return;
	}
	jedis[count++] = jedi;
}

void JediCollection::removeJedi(const char* name)
{
	for (int i = 0; i < count; i++)
	{
		if (strcmp(jedis[i].name, name) == 0)
		{
			for (int j = i; j < count - 1; j++)
			{
				jedis[j] = jedis[j + 1];
			}
			count--;
			return;
		}
	}
}

void JediCollection::print() const
{
	for (int i = 0; i < count; i++)
	{
		cout << jedis[i].name
			<< " Age:" << jedis[i].age
			<< " Power:" << jedis[i].power
			<< std::endl;
	}
}


int JediCollection::size() const { return count; }

Jedi& JediCollection::getJedi(int index)
{
	if (index < 0 || index >= count)
	{
		cout << "Index out of range";
	}
	return jedis[index];
}

const Jedi& JediCollection::getJedi(int index) const
{
	if (index < 0 || index >= count)
	{
		cout << "Index out of range";
	}
	return jedis[index];
}

void JediCollection::setJedi(int index, const Jedi& jedi)
{
	if (index < 0 || index >= count)
	{
		cout << "Index out of range";
	}
	jedis[index] = jedi;
}

void JediCollection::swapJedi(int i, int j)
{
	if (i < 0 || i >= count || j < 0 || j >= count)
	{
		cout << "Index out of range";
		return;
	}
	Jedi tmp = jedis[i];
	jedis[i] = jedis[j];
	jedis[j] = tmp;
}

void JediData::sortByAge(JediCollection& collection)
{
	int n = collection.size();
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = 0; j < n - i - 1; ++j)
		{
			Jedi& current = collection.getJedi(j);
			Jedi& next = collection.getJedi(j + 1);

			if (current.age > next.age)
			{
				collection.swapJedi(j, j + 1);
			}
		}
	}
}

void JediData::sortByPower(JediCollection& collection)
{
	int n = collection.size();
	for (unsigned int i = 0; i < n - 1; ++i)
	{
		for (unsigned int j = 0; j < n - i - 1; ++j)
		{
			if (collection.getJedi(j).power > collection.getJedi(j + 1).power)
			{
				collection.swapJedi(j, j + 1);
			}
		}
	}
}

SaberColor JediData::mostPopularSaberColor(const JediCollection& collection)
{
	int colorFrequency[5] = {};
	int totalJedis = collection.size();
	for (int jediIndex = 0; jediIndex < totalJedis; ++jediIndex)
	{
		int colorIndex = int(collection.getJedi(jediIndex).saber.color);
		colorFrequency[colorIndex]++;
	}
	int mostPopularIndex = 0;
	for (int colorIndex = 1; colorIndex < 5; ++colorIndex)
	{
		if (colorFrequency[colorIndex] > colorFrequency[mostPopularIndex])
		{
			mostPopularIndex = colorIndex;
		}
	}
	return SaberColor(mostPopularIndex);
}

SaberType JediData::mostPopularSaberType(const JediCollection& collection)
{
	int typeFrequency[3] = {};
	int totalJedis = collection.size();
	for (int jediIndex = 0; jediIndex < totalJedis; ++jediIndex)
	{
		int typeIndex = int(collection.getJedi(jediIndex).saber.type);
		typeFrequency[typeIndex]++;
	}
	int mostPopularIndex = 0;
	for (int typeIndex = 1; typeIndex < 3; ++typeIndex)
	{
		if (typeFrequency[typeIndex] > typeFrequency[mostPopularIndex])
		{
			mostPopularIndex = typeIndex;
		}
	}
	return SaberType(mostPopularIndex);
}

void JediIO::saveToBinary(const JediCollection& collection, const char* fileName)
{
	std::ofstream out(fileName, std::ios::binary);
	if (!out)
	{
		cout << "Cannot open file for writing.";
		return;
	}
	saveToBinary(out, collection);
}

JediCollection JediIO::readFromBinary(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if (!in) 
	{
		cout << "Cannot open file for reading.";
		return JediCollection();;
	}
	return readFromBinary(in);
}

void JediIO::saveToBinary(std::ofstream& out, const JediCollection& collection)
{
	int totalJedis = collection.size();
	out.write((char*)&totalJedis, sizeof(totalJedis)); 
	for (int jediIndex = 0; jediIndex < totalJedis; ++jediIndex)
	{
		const Jedi& jedi = collection.getJedi(jediIndex);
		out.write(jedi.name, sizeof(jedi.name));
		out.write((char*)&jedi.age, sizeof(jedi.age));
		out.write((char*)&jedi.power, sizeof(jedi.power));
		int color = int(jedi.saber.color);
		int type = int(jedi.saber.type);
		out.write((char*)&color, sizeof(color));
		out.write((char*)&type, sizeof(type));
	}
}

JediCollection JediIO::readFromBinary(std::ifstream& in)
{
	JediCollection collection;
	int totalJedis = 0;
	in.read((char*)&totalJedis, sizeof(totalJedis));
	for (int jediIndex = 0; jediIndex < totalJedis; ++jediIndex)
	{
		Jedi jedi;
		in.read(jedi.name, sizeof(jedi.name));
		in.read((char*)&jedi.age, sizeof(jedi.age));
		in.read((char*)&jedi.power, sizeof(jedi.power));
		int colorInt, typeInt;
		in.read((char*)&colorInt, sizeof(colorInt));
		in.read((char*)&typeInt, sizeof(typeInt));
		jedi.saber.color = SaberColor(colorInt);
		jedi.saber.type = SaberType(typeInt);
		collection.addJedi(jedi);
	}
	return collection;
}

void JediIO::saveToTxt(const JediCollection& collection, const char* fileName)
{
	std::ofstream out(fileName);
	if (!out)
	{
		cout << "Cannot open file for writing.";
		return;
	}
	saveToTxt(out, collection);
}

JediCollection JediIO::readFromTxt(const char* fileName)
{
	std::ifstream in(fileName);
	if (!in)
	{
		cout << "Cannot open file for reading.";
		return JediCollection();;
	}
	return readFromTxt(in);
}

void JediIO::saveToTxt(std::ostream& out, const JediCollection& collection)
{
	int totalJedis = collection.size();
	for (int i = 0; i < totalJedis; ++i)
	{
		const Jedi& jedi = collection.getJedi(i);
		out << jedi.name << " "
			<< jedi.age << " "
			<< jedi.power << " "
			<< int(jedi.saber.color) << " "
			<< int(jedi.saber.type) << "\n";
	}
}

JediCollection JediIO::readFromTxt(std::istream& in)
{
	JediCollection collection;
	while (!in.eof())
	{
		Jedi jedi;
		int colorInt, typeInt;
		in >> jedi.name >> jedi.age >> jedi.power >> colorInt >> typeInt;
		if (in.fail())
		{
			break;
		}
		jedi.saber.color = SaberColor(colorInt);
		jedi.saber.type = SaberType(typeInt);
		collection.addJedi(jedi);
	}
	return collection;
}
```

`Utils.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Jedi.h"
#include "JediUtils.h"

const char* colorToString(SaberColor color) 
{
    switch (color) 
    {
    case SaberColor::RED:
        return "RED";
    case SaberColor::YELLOW:
        return "YELLOW";
    case SaberColor::GREEN:
        return "GREEN";
    case SaberColor::BLUE:
        return "BLUE";
    case SaberColor::PURPLE:
        return "PURPLE";
    default:
        return "UNKNOWN";
    }
}

const char* typeToString(SaberType type) 
{
    switch (type) 
    {
    case SaberType::SINGLE_BLADED:
        return "SINGLE_BLADED";
    case SaberType::DOUBLE_BLADED:
        return "DOUBLE_BLADED";
    case SaberType::CROSSGUARD:
        return "CROSSGUARD";
    default:
        return "UNKNOWN";
    }
}
```

`taskJedi.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Jedi.h"
#include "JediUtils.h"
#include <istream>
#include <ostream>
#include <fstream>

int main()
{
    Jedi yoda("Yoda", 900, 1000, SaberColor::GREEN, SaberType::SINGLE_BLADED);
    Jedi anakin("Anakin Skywalker", 22, 850, SaberColor::BLUE, SaberType::SINGLE_BLADED);
    Jedi maul("Darth Maul", 32, 700, SaberColor::RED, SaberType::DOUBLE_BLADED);
    Jedi rey("Rey", 24, 800, SaberColor::YELLOW, SaberType::SINGLE_BLADED);
    Jedi kylo("Kylo Ren", 29, 750, LightSaber(SaberColor::RED, SaberType::CROSSGUARD));
    JediCollection council;
    council.addJedi(yoda);
    council.addJedi(anakin);
    council.addJedi(maul);
    council.addJedi(rey);
    council.addJedi(kylo);
    council.print();
    council.removeJedi("Darth Maul");
    council.print();

    JediData::sortByAge(council);
    council.print();

    JediData::sortByPower(council);
    council.print();

    SaberColor popColor = JediData::mostPopularSaberColor(council);
    SaberType  popType = JediData::mostPopularSaberType(council);
   
    switch (popColor)
    {
    case SaberColor::BLUE:   std::cout << "BLUE"<< std::endl;   break;
    case SaberColor::RED:    std::cout << "RED" << std::endl;    break;
    case SaberColor::GREEN:  std::cout << "GREEN" << std::endl;  break;
    case SaberColor::YELLOW: std::cout << "YELLOW" << std::endl; break;
    case SaberColor::PURPLE: std::cout << "PURPLE" << std::endl; break;
    default: break;
    }

    switch (popType) 
    {
    case SaberType::SINGLE_BLADED: std::cout << "SINGLE_BLADED"<< std::endl; break;
    case SaberType::DOUBLE_BLADED: std::cout << "DOUBLE_BLADED" << std::endl; break;
    case SaberType::CROSSGUARD:    std::cout << "CROSSGUARD" << std::endl;    break;
    default: break;
    }

    JediIO::saveToTxt(council, "jedis.txt");
    JediCollection fromTxt = JediIO::readFromTxt("jedis.txt");

    fromTxt.print();

    JediIO::saveToBinary(council, "jedis.bin");
    JediCollection fromBin = JediIO::readFromBinary("jedis.bin");
    fromBin.print();

    for (int i = 0; i < council.size(); ++i) {
        const Jedi& jedi = council.getJedi(i);
        std::cout << "Name: " << jedi.name
            << ", Age: " << jedi.age
            << ", Power: " << jedi.power
            << ", Saber: " << colorToString(jedi.saber.color)
            << " " << typeToString(jedi.saber.type)
            << std::endl;
    }
}
```

`Изход:`
```
Yoda Age:900 Power:1000
Anakin Skywalker Age:22 Power:850
Darth Maul Age:32 Power:700
Rey Age:24 Power:800
Kylo Ren Age:29 Power:750
Yoda Age:900 Power:1000
Anakin Skywalker Age:22 Power:850
Rey Age:24 Power:800
Kylo Ren Age:29 Power:750
Anakin Skywalker Age:22 Power:850
Rey Age:24 Power:800
Kylo Ren Age:29 Power:750
Yoda Age:900 Power:1000
Kylo Ren Age:29 Power:750
Rey Age:24 Power:800
Anakin Skywalker Age:22 Power:850
Yoda Age:900 Power:1000
RED
SINGLE_BLADED
Kylo Ren Age:29 Power:750
Rey Age:24 Power:800
Anakin Skywalker Age:22 Power:850
Yoda Age:900 Power:1000
Name: Kylo Ren, Age: 29, Power: 750, Saber: RED CROSSGUARD
Name: Rey, Age: 24, Power: 800, Saber: YELLOW SINGLE_BLADED
Name: Anakin Skywalker, Age: 22, Power: 850, Saber: BLUE SINGLE_BLADED
Name: Yoda, Age: 900, Power: 1000, Saber: GREEN SINGLE_BLADED
```

<hr style="border-width: 5px !important;">

```
Задача 3 Серхо, подготвяйки задачите за контролното по ООП, реши, че е добра идея да внимава точно как пише задачите.
Всеки можеше да отвори лаптопа му и да открадне тази безценна информация.
Помогнете на Серхо да опази задачите от изпита - създайте клас secret.
Класът трябва да съдържа:
- Условие на задачата
- Парола
- Брой неуспешни влизания 
Направете подходящи конструктори.
Да се напише функция getTask(const char*pwd), която връща условието тогава и само тогава когато сме въвели правилната парола.
Да се напише функция setPassword(const char* newPassword, const char* oldPassword), която променя паролата, но само ако сме въвели правилно старата парола.
Да се напише функция setTask(const char* newTask, const char* passwd), която променя условието на задачата ако сме въвели правилна парола.
Да се напише функция getLoginFails(), която връща броя на неуспешните влизания.Всеки път когато сме въвели неправилна парола броят на неуспешните влизания се увеличава. 
```

`Решение:`

`Secret.h`
```h
#pragma once
class Secret
{
	private:
		char* task;
		char* password;
		int loginFails;
public:
	Secret();
	Secret(const char* _task, const char* _password);
	Secret(const Secret& other);
	Secret& operator=(const Secret& other);
	~Secret();
	const char* getTask(const char* pwd);
	void setPassword(const char* newPassword, const char* oldPassword);
	void setTask(const char* newTask, const char* pwd);
	int getLoginFails() const;
};
```

`Secret.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Secret.h"
#include <string.h>

static char* copyString(const char* src)
{
    if (!src)
    {
        return nullptr;
    }
    char* copy = new char[strlen(src) + 1];
    strcpy(copy, src);
    return copy;
}

Secret::Secret() : task(nullptr),
password(nullptr), loginFails(0)
{

}

Secret::Secret(const char* _task, const char* _password) : 
    task(copyString(_task)),
    password(copyString(_password)),
    loginFails(0)
{

}

Secret::Secret(const Secret& other) :
    task(copyString(other.task)), 
    password(copyString(other.password)), 
    loginFails(other.loginFails)
{

}

Secret& Secret::operator=(const Secret& other)
{
    if (this != &other)
    {
        delete[] task;
        delete[] password;
        task = copyString(other.task);
        password = copyString(other.password);
        loginFails = other.loginFails;
    }
    return *this;
}

Secret::~Secret()
{
    delete[] task;
    delete[] password;
}

const char* Secret::getTask(const char* passwd)
{
    if (password && passwd && strcmp(passwd, password) == 0)
    {
        return task;
    }
    loginFails++;
    return "Wrong password!";
}

void Secret::setPassword(const char* newPassword, const char* oldPassword)
{
    if (password && oldPassword && strcmp(oldPassword, password) == 0)
    {
        delete[] password;
        password = copyString(newPassword);
    }
    else
    {
        loginFails++;
    }
}

void Secret::setTask(const char* newTask, const char* pwd)
{
    if (password && pwd && strcmp(pwd, password) == 0)
    {
        delete[] task;
        task = copyString(newTask);
    }
    else
    {
        loginFails++;
    }
}

int Secret::getLoginFails() const
{
    return loginFails;
}
```

`taskSecret.h`
```cpp
#include <iostream>
#include "Secret.h"

int main()
{
    Secret s("OOP exam task", "1234");

    std::cout << s.getTask("1111") << std::endl;
    std::cout << s.getTask("1211") << std::endl;
    std::cout << s.getTask("1141") << std::endl;
    std::cout << s.getTask("1219") << std::endl;
    std::cout << s.getTask("1234") << std::endl;
    s.setPassword("asd", "1234");
    s.setTask("New OOP exam task", "asd");
    std::cout << s.getTask("asd") << std::endl;
    std::cout << "Login fails: " << s.getLoginFails() << std::endl;

    Secret s2 = s;
    std::cout << s2.getTask("asd") << std::endl;
}
```

<hr style="border-width: 5px !important;">

