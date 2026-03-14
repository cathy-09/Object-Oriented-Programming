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

`Изход:`
```
Wrong password!
Wrong password!
Wrong password!
Wrong password!
OOP exam task
New OOP exam task
Login fails: 4
New OOP exam task
```

<hr style="border-width: 5px !important;">

```
Задача 4.1 🎈 Да се направи клас Baloon, съдържащ полета за цена (реално число) и цвят (Цветът може да е бяло, зелено или червено). Да се реализират следните методи:

конструктор по подразбиране
конструктор с параметри
сетъри и гетъри за член-данните

Задача 4.2 😗💨 Да се направи клас Narga, съдържащ полета за цена, марка (низ с дължина максимум 1024) и вкус (Боровинка, Кралица, Манго (изберете си още 2 вкуса)).

Да се реализират следните методи:
четене от стандартния вход
отпечатване на стандартния изход
конструктор по подразбиране
подходящ конструктор с параметри
сетъри и гетъри за член-данните

Задача 4.3 Да се напише клас Alchohol, който съдържа полета за:
Име на алкохола - символен низ с максимална дължина 128
Цена на алкохола - рационално число
Създайте подходящ дефолтен конструктор
Създайте подходящ конструктор с параметри
сетъри и гетъри за член данните

3адача 4.4 Ели си пада купонджийка и след безбройните нощи в дискотеките на Студентски град тя решава да отвори собствена дискотека. Бизнесът не е лесна работа и тя решава, че ѝ е нужна програма, която да ѝ помогне. Каква случайност, че тя познава блестящи програмисти като вас, които с радост ще накодят един клас NightClub, който ще съдържа списък от предлагани балони, наргилета и алкохол, които тя предлага. Тъй като все пак не иска ченгетата да й правят проблем, Ели може да складира само 1024 балона(🎈), 512 бутилки с алкохол(🍺) и 256 наргилета. Да се реализират следните методи (при добавяне на вече съществуващ алкохол/наргиле/балон се увеличава неговата бройка и съответно при премахване тя се намалява до достигане на 0):

да се добавя балон към списъка, като характеристиките се прочитат от текстов файл. Данните (стойностите на поленцата) са разделени с "-"

green-25.6
да се добавя наргиле към списъка, като характеристиките се прочитат от текстов файл. Данните (стойностите на поленцата) са разделени с "-"

OS-queen-30
да се добавя алкохол към списъка, като характеристиките се прочитат от текстов файл. Данните (стойностите на поленцата) са разделени с "-"

black_label-60
да се премахва балон от списъка по зададен цвят
да се премахва наргиле от списъка по зададена марка и вкус
да се премахва алкохол от списъка по зададено име
проверка дали в нашата дискотека имаме:

балон с определен цвят
алкохол с определено име
наргиле с определен вкус
връщане на сметка, като параметър на метода се приема име на текстов файл, от който се прочитат консумираните алкохоли, балони и наргилета от клиента на Ели. Методът трябва да изчисли каква сума дължи клиентът на Ели и да я върне.

Данните в текстовия файл са в следния формат:

<име_на_алкохола>-<брой_поръчани_бутилки>
<цвят_на_балона>-<брой_поръчани_балони>
<име_на_марката>-<име_на_вкуса>-<брой_поръчани_наргилета>
Alchohols:
<name_of_alchohol_1>-<count_1>
<name_of_alchohol_2>-<count_2>
...
<name_of_alchohol_n>-<count_3>
Baloons:
<color_of_balloon_1>-<count_1>
<color_of_balloon_2>-<count_2>
...
<color_of_balloon_n>-<count_n>
Nargas:
<name_of_brand_1>-<name_of_taste_1>-<count_1>
<name_of_brand_2>-<name_of_taste_2>-<count_2>
...
<name_of_brand_n>-<name_of_taste_n>-<count_n>
Пример:

Alchohols:
black_lable-2
jameson-3
Baloons:
green-10
Narga:
OS-queen-2
Всеки клиент на Ели описваме чрез структура Client, която съдържа:

поле за името на клиента - низ с произволна дължина
поле за името на текстов файл, в който се съхранява сметката на клиента
печалба за деня, методът приема масив от клиенти и за всеки клиент изчислява каква сума трябва да плати на Ели, информацията за името на клиента и каква сума трябва да заплати пазим в двоичен файл с име money.dat.

Не забравяйте да създадете подходящи функции, които да се грижат за паметта. Помислите кои от методите да са private и кои public. Можете да създадете помощни методи в кой да е клас, за да си улесните работата и да повишите нивото на абстракция.
```

`Решение:`

`Baloon.h`
```h
#pragma once

enum class BalloonColor
{
	WHITE,
	GREEN,
	RED,
	COUNT
};

class Baloon
{
private:
	double price;
	BalloonColor color;
	public:
		Baloon();
		Baloon(double price, BalloonColor color);
		double getPrice() const;
		BalloonColor getColor() const;
		void setPrice(double price);
		void setColor(BalloonColor color);
		static BalloonColor colorFromString(const char* s);
		static const char* colorToString(BalloonColor c);
};
```

`Narga.h`
```h
#pragma once
enum class Taste 
{ 
    BLUEBERRY,
    QUEEN,
    MANGO,
    PEACH,
    STRAWBERRY,
    COUNT
};
class Narga
{
private:
    double price;
    char   brand[1025];
    Taste taste;
public:
    Narga();
    Narga(double price, const char* brand, Taste taste);
    double getPrice() const;
    const char* getBrand() const;
    Taste  getTaste() const;
    void setPrice(double price);
    void setBrand(const char* brand);
    void setTaste(Taste taste);
    void readFromInput();
    void print() const;
    static Taste tasteFromString(const char* string);
    static const char* tasteToString(Taste taste);
};
```

`Alchohol.h`
```h
#pragma once
class Alchohol
{
private:
    char name[129];
    double price;

public:
    Alchohol();
    Alchohol(const char* name, double price);
    const char* getName()  const;
    double getPrice() const;
    void setName(const char* name);
    void setPrice(double price);
};
```

`Alchohol.h`
```h
#pragma once
#include "Baloon.h"
#include "Alchohol.h"
#include "Narga.h"

static const int MAX_BALOONS = 1024;
static const int MAX_ALCHOHOL = 512;
static const int MAX_NARGA = 256;

struct Client 
{
    char* name;
    char* billFile;

    Client();
    Client(const char* name, const char* billFile);
    Client(const Client& other);
    Client& operator=(const Client& other);
    ~Client();
};

class Nightclub
{
private:
    Baloon baloons[MAX_BALOONS]; 
    Narga nargas[MAX_NARGA];
    Alchohol alchohols[MAX_ALCHOHOL];
    int baloonCounts[MAX_BALOONS];
    int alchoholCounts[MAX_ALCHOHOL];
    int nargaCounts[MAX_NARGA];
    int baloonSize;
    int alchoholSize;  
    int nargaSize;
    int findBaloon(BalloonColor color) const;
    int findAlchohol(const char* name) const;
    int findNarga(const char* brand, Taste taste) const;
    static int  splitLine(const char* line, char tokens[][1025], int maxToken);
    static void trimInPlace(char* string);

public:
    Nightclub();
    void addBaloonFromLine(const char* line);
    void addNargaFromLine(const char* line);
    void addAlchoholFromLine(const char* line);
    void removeBaloon(BalloonColor color);
    void removeAlchohol(const char* name);
    void removeNarga(const char* brand, Taste taste);
    bool hasBaloon(BalloonColor color) const;
    bool hasAlchohol(const char* name) const;
    bool hasNarga(Taste taste) const;
    double getBill(const char* billFileName);
    void dailyProfit(Client* clients, int count);
};
```

`Baloon.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Baloon.h"
#include <iostream>
#include <string.h>

Baloon::Baloon() : price(0.0), color(BalloonColor::WHITE)
{

}

Baloon::Baloon(double price, BalloonColor color) : price(price), color(color)
{

}

double Baloon::getPrice() const
{
	return price;
}

BalloonColor Baloon::getColor() const
{
	return color;
}

void Baloon::setPrice(double price)
{
	this->price = price;
}

void Baloon::setColor(BalloonColor color)
{
	this->color = color;
}

BalloonColor Baloon::colorFromString(const char* string)
{
	if (strcmp(string, "white") == 0)
	{
		return BalloonColor::WHITE;
	}
	if (strcmp(string, "green") == 0)
	{
		return BalloonColor::GREEN;
	}
	if (strcmp(string, "red") == 0)
	{
		return BalloonColor::RED;
	}
	else
	{
		std::cout << "Unknown balloon color";
	}
	return BalloonColor::WHITE;
}

const char* Baloon::colorToString(BalloonColor color)
{
	switch (color)
	{
	case BalloonColor::WHITE: 
		return "white";
	case BalloonColor::GREEN: 
		return "green";
	case BalloonColor::RED:   
		return "red";
	default:                  
		return "unknown";
	}
}
```

`Alchohol.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Alchohol.h"

Alchohol::Alchohol() : price(0.0)
{
	name[0] = '\0';
}

Alchohol::Alchohol(const char* name, double price) : price(price) 
{
    strncpy(this->name, name, 128);
    this->name[128] = '\0';
}

const char* Alchohol::getName() const
{
    return name;
}

double Alchohol::getPrice() const 
{ 
    return price; 
}

void Alchohol::setName(const char* name)
{
    strncpy(this->name, name, 128);
    this->name[128] = '\0';
}

void Alchohol::setPrice(double price)
{
    this->price = price;
}
```

`Narga.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Narga.h"

Narga::Narga() : price(0.0), taste(Taste::QUEEN) 
{
	brand[0] = '\0'; 
}

Narga::Narga(double price, const char* brand, Taste taste) : price(price), taste(taste)
{
	strncpy(this->brand, brand, 1024);
	this->brand[1024] = '\0';
	this->price = price;
	this->taste = taste;
}

double Narga::getPrice() const
{
	return price;
}

const char* Narga::getBrand() const
{
	return brand;
}

Taste Narga::getTaste() const
{
	return taste;
}

void Narga::setPrice(double price)
{
	this->price = price;
}

void Narga::setBrand(const char* brand)
{
	strncpy(this->brand, brand, 1024);
	this->brand[1024] = '\0';
}

void Narga::setTaste(Taste taste)
{
	this->taste = taste;
}

void Narga::readFromInput()
{
	char brand[1024];
	double price;
	char taste[32];

	std::cout << "Brand: ";
	std::cin.getline(brand, 1024);

	std::cout << "Price: ";
	std::cin >> price;

	std::cout << "Taste";
	std::cin >> taste;
}
void Narga::print() const 
{
	std::cout << "Brand: " << brand
		<< " Price: " << price
		<< " Taste: " << tasteToString(taste)
		<< std::endl;
}

Taste Narga::tasteFromString(const char* string)
{
	if (strcmp(string, "blueberry") == 0)
	{
		return Taste::BLUEBERRY;
	}
	if (strcmp(string, "queen") == 0)
	{
		return Taste::QUEEN;
	}
	if (strcmp(string, "mango") == 0)
	{
		return Taste::MANGO;
	}
	if (strcmp(string, "peach") == 0)
	{
		return Taste::PEACH;
	}
	if (strcmp(string, "strawberry") == 0)
	{
		return Taste::STRAWBERRY;
	}
	else
	{
		std::cout << "Unknown narga taste";
	}
	return Taste::QUEEN;
}

const char* Narga::tasteToString(Taste taste)
{
	switch (taste)
	{
	case Taste::BLUEBERRY:
		return "blueberry";
	case Taste::QUEEN:
		return "queen";
	case Taste::MANGO:
		return "mango";
	case Taste::PEACH:
		return "peach";
	case Taste::STRAWBERRY:
		return "strawberry";
	default:
		return "unknown";
	}
}
```

`Nightclub.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Nightclub.h"
#include "Alchohol.h"
#include "Baloon.h"
#include "Narga.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>

int Nightclub::findBaloon(BalloonColor color) const
{
	for (int i = 0; i < baloonSize; ++i)
	{
		if (baloons[i].getColor() == color)
		{
			return i;
		}
	}
	return -1;
}

int Nightclub::findAlchohol(const char* name) const
{
	for (int i = 0; i < alchoholSize; ++i)
	{
		if (strcmp(alchohols[i].getName(), name) == 0)
		{
			return i;
		}
	}
	return -1;
}

int Nightclub::findNarga(const char* brand, Taste taste) const
{
	for (int i = 0; i < nargaSize; ++i)
	{
		if (strcmp(nargas[i].getBrand(), brand) == 0 && nargas[i].getTaste() == taste)
		{
			return i;
		}
	}
	return -1;
}

int Nightclub::splitLine(const char* line, char tokens[][1025], int maxToken)
{
	int tokenCount = 0;
	const char* currPos = line;
	while (*currPos != '\0' && tokenCount < maxToken)
	{
		const char* dashPos = strchr(currPos, '-');
		int tokenLen;
		if (dashPos != nullptr)
		{
			tokenLen = dashPos - currPos;
		}
		else
		{
			tokenLen = strlen(currPos);
		}
		if (tokenLen > 1024)
		{
			tokenLen = 1024;
		}
		strncpy(tokens[tokenCount], currPos, tokenLen);
		tokens[tokenCount][tokenLen] = '\0';
		trimInPlace(tokens[tokenCount]);
		tokenCount++;
		if (dashPos == nullptr)
		{
			break;
		}
		currPos = dashPos + 1;
	}
	return tokenCount;
}

void Nightclub::trimInPlace(char* string)
{
	int start = 0;
	while (string[start] == ' ')
	{
		start++;
	}
	int i = 0;
	while (string[start] != '\0')
	{
		string[i] = string[start];
		i++;
		start++;
	}
	string[i] = '\0';
	int end = i - 1;
	while (end >= 0 && string[end] == ' ')
	{
		string[end] = '\0';
		end--;
	}
}

Nightclub::Nightclub() : baloonSize(0), alchoholSize(0), nargaSize(0)
{
	for (int i = 0; i < (int)BalloonColor::COUNT; i++)
	{
		baloonCounts[i] = 0;
	}

	for (int i = 0; i < 512; i++)
	{
		alchoholCounts[i] = 0;
	}

	for (int i = 0; i < (int)Taste::COUNT; i++)
	{
		nargaCounts[i] = 0;
	}
}

double stringToDouble(const char* string)
{
	double result = 0.0;
	int i = 0;
	bool negative = false;
	if (string[0] == '-')
	{
		negative = true;
		i++;
	}
	while (string[i] && string[i] >= '0' && string[i] <= '9')
	{
		result = result * 10 + (string[i] - '0');
		i++;
	}
	if (string[i] == '.')
	{
		i++;
		double frac = 0.0;
		double divisor = 10.0;
		while (string[i] && string[i] >= '0' && string[i] <= '9')
		{
			frac += (string[i] - '0') / divisor;
			divisor *= 10.0;
			i++;
		}
		result += frac;
	}
	if (negative)
	{
		return -result;
	}
	return result;
}

void Nightclub::addBaloonFromLine(const char* line)
{
	char tokens[2][1025];

	int tokenCount = splitLine(line, tokens, 2);

	if (tokenCount < 2)
	{
		std::cout << "Bad balloon line" << std::endl;
		return;
	}
	BalloonColor color = Baloon::colorFromString(tokens[0]);
	double price = stringToDouble(tokens[1]);
	int index = findBaloon(color);
	if (index != -1)
	{
		baloonCounts[index]++;
		return;
	}
	if (baloonSize >= 1024)
	{
		std::cout << "Balloon capacity full" << std::endl;
		return;
	}
	baloons[baloonSize] = Baloon(price, color);
	baloonCounts[baloonSize] = 1;
	baloonSize++;
}

void Nightclub::addNargaFromLine(const char* line)
{
	char tokens[3][1025];
	int tokenCount = splitLine(line, tokens, 3);
	if (tokenCount < 3)
	{
		std::cout << "Bad narga line" << std::endl;
		return;
	}
	const char* brand = tokens[0];
	Taste taste = Narga::tasteFromString(tokens[1]);
	double price = stringToDouble(tokens[2]);
	int index = findNarga(brand, taste);
	if (index != -1)
	{
		nargaCounts[index]++;
		return;
	}
	if (nargaSize >= 256)
	{
		std::cout << "Narga capacity full" << std::endl;
		return;
	}
	nargas[nargaSize] = Narga(price, brand, taste);
	nargaCounts[nargaSize] = 1;
	nargaSize++;
}

void Nightclub::addAlchoholFromLine(const char* line)
{
	const char* lastDash = strrchr(line, '-');
	if (!lastDash)
	{
		std::cout << "Bad narga line" << std::endl;
		return;
	}
	char nameBuffer[129];
	int nameLen = (int)(lastDash - line);
	if (nameLen > 128)
	{
		nameLen = 128;
	}
	strncpy(nameBuffer, line, nameLen);
	nameBuffer[nameLen] = '\0';
	trimInPlace(nameBuffer);
	char priceBuffer[64];
	strncpy(priceBuffer, lastDash + 1, 63);
	priceBuffer[63] = '\0';
	trimInPlace(priceBuffer);
	double price = stringToDouble(priceBuffer);
	int indexAlchohol = findAlchohol(nameBuffer);
	if (indexAlchohol != -1) {
		++alchoholCounts[indexAlchohol];
		return;
	}
	if (alchoholSize >= MAX_ALCHOHOL)
	{
		std::cout << "Alcohol capacity full" << std::endl;
		return;
	}
	alchohols[alchoholSize] = Alchohol(nameBuffer, price);
	alchoholCounts[alchoholSize] = 1;
	++alchoholSize;
}

void Nightclub::removeBaloon(BalloonColor color)
{
	int index = findBaloon(color);
	if (index == -1)
	{
		std::cout << "Balloon not found" << std::endl;
		return;
	}
	if (--baloonCounts[index] <= 0)
	{
		for (int i = index; i < baloonSize - 1; ++i)
		{
			baloons[i] = baloons[i + 1];
			baloonCounts[i] = baloonCounts[i + 1];
		}
		--baloonSize;
	}
}

void Nightclub::removeAlchohol(const char* name)
{
	int index = findAlchohol(name);
	if (index == -1)
	{
		std::cout << "Alchohol not found" << std::endl;
		return;
	}
	if (--alchoholCounts[index] <= 0)
	{
		for (int i = index; i < alchoholSize - 1; ++i)
		{
			alchohols[i] = alchohols[i + 1];
			alchoholCounts[i] = alchoholCounts[i + 1];
		}
		--alchoholSize;
	}
}

void Nightclub::removeNarga(const char* brand, Taste taste)
{
	int idx = findNarga(brand, taste);
	if (idx == -1)
	{
		std::cout << "Narga not found" << std::endl;
		return;
	}
	if (--nargaCounts[idx] <= 0)
	{
		for (int i = idx; i < nargaSize - 1; ++i)
		{
			nargas[i] = nargas[i + 1];
			nargaCounts[i] = nargaCounts[i + 1];
		}
		--nargaSize;
	}
}

bool Nightclub::hasBaloon(BalloonColor color) const
{
	return findBaloon(color) != -1;
}

bool Nightclub::hasAlchohol(const char* name) const
{
	return findAlchohol(name) != -1;
}

bool Nightclub::hasNarga(Taste taste) const
{
	for (int i = 0; i < nargaSize; ++i)
	{
		if (nargas[i].getTaste() == taste)
		{
			return true;
		}
	}
	return false;
}

int stringToInt(const char* s)
{
	if (!s || s[0] == '\0')
	{
		return 0;
	}
	int result = 0;
	int i = 0;
	bool negative = false;

	if (s[0] == '-')
	{
		negative = true;
		i++;
	}
	else if (s[0] == '+')
	{
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	if (negative)
	{
		result = -result;
	}
	return result;
}

double Nightclub::getBill(const char* billFileName)
{
	std::ifstream file(billFileName);
	if (!file)
	{
		return 0.0;
	}
	double total = 0.0;
	int section = 0;
	char line[2048];
	while (file)
	{
		int len = 0;
		char charche;
		while (file.get(charche) && charche != '\n')
		{
			if (len < 2047)
			{
				line[len++] = charche;
			}
		}
		line[len] = '\0';
		if (!file && len == 0)
		{
			break;
		}
		trimInPlace(line);
		if (line[0] == '\0')
		{
			continue;
		}
		if (strcmp(line, "Alchohols:") == 0)
		{
			section = 1;
			continue;
		}
		if (strcmp(line, "Baloons:") == 0)
		{
			section = 2;
			continue;
		}
		if (strcmp(line, "Nargas:") == 0 || strcmp(line, "Narga:") == 0)
		{
			section = 3;
			continue;
		}

		if (section == 1)
		{
			int lastDash = -1;
			for (int i = 0; line[i] != '\0'; ++i)
			{
				if (line[i] == '-')
				{
					lastDash = i;
				}
			}
			if (lastDash == -1)
			{
				continue;
			}
			char nameBuf[129];
			int nameLen = lastDash;
			if (nameLen > 128)
			{
				nameLen = 128;
			}
			for (int i = 0; i < nameLen; ++i)
			{
				nameBuf[i] = line[i];
			}
			nameBuf[nameLen] = '\0';
			trimInPlace(nameBuf);
			char countBuffer[64];
			int k = 0;
			for (int i = lastDash + 1; line[i] != '\0' && k < 63; ++i)
			{
				countBuffer[k++] = line[i];
			}
			countBuffer[k] = '\0';
			trimInPlace(countBuffer);
			int count = stringToInt(countBuffer);
			int index = findAlchohol(nameBuf);
			if (index != -1)
			{
				total += alchohols[index].getPrice() * count;
			}
		}
		else if (section == 2)
		{
			char tokens[2][1025];
			if (splitLine(line, tokens, 2) < 2)
			{
				continue;
			}
			int count = stringToInt(tokens[1]);
			BalloonColor color = Baloon::colorFromString(tokens[0]);
			int index = findBaloon(color);
			if (index != -1)
			{
				total += baloons[index].getPrice() * count;
			}
		}
		else if (section == 3)
		{
			char tokens[3][1025];
			if (splitLine(line, tokens, 3) < 3)
			{
				continue;
			}
			int count = stringToInt(tokens[2]);
			Taste taste = Narga::tasteFromString(tokens[1]);
			int index = findNarga(tokens[0], taste);
			if (index != -1)
			{
				total += nargas[index].getPrice() * count;
			}
		}
	}
	return total;
}

void Nightclub::dailyProfit(Client* clients, int count)
{
	std::ofstream file("money.dat", std::ios::binary);
	if (!file)
	{
		return;
	}

	for (int i = 0; i < count; ++i)
	{
		double amount = getBill(clients[i].billFile);
		size_t nameLen = 0;
		while (clients[i].name[nameLen] != '\0')
		{
			++nameLen;
		}
		file.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
		file.write(clients[i].name, nameLen);
		file.write(reinterpret_cast<const char*>(&amount), sizeof(amount));
	}
}

Client::Client() : name(nullptr), billFile(nullptr)
{
}

Client::Client(const char* name, const char* billFile)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->billFile = new char[strlen(billFile) + 1];
	strcpy(this->billFile, billFile);
}

Client::Client(const Client& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);
	this->billFile = new char[strlen(other.billFile) + 1];
	strcpy(this->billFile, other.billFile);
}

Client& Client::operator=(const Client& other)
{
	if (this != &other)
	{
		delete[] name;
		delete[] billFile;
		name = new char[strlen(other.name) + 1];
		strcpy(name, other.name);
		billFile = new char[strlen(other.billFile) + 1];
		strcpy(billFile, other.billFile);
	}
	return *this;
}

Client::~Client()
{
	delete[] name;
	delete[] billFile;
}
```

`taskNightClub.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "Nightclub.h"

static void createBillFile(const char* filename, const char* content)
{
    std::ofstream f(filename);
    f << content;
}

int main()
{
    createBillFile("ivan_bill.txt",
        "Alchohols:\n"
        "black_label-2\n"
        "jameson-3\n"
        "Baloons:\n"
        "green-10\n"
        "Nargas:\n"
        "OS-queen-2\n");
    createBillFile("maria_bill.txt",
        "Alchohols:\n"
        "jameson-1\n"
        "Baloons:\n"
        "red-5\n"
        "Nargas:\n"
        "Alfa-mango-1\n");
    Nightclub club;
    club.addBaloonFromLine("green-25.6");
    club.addBaloonFromLine("red-15.0");
    club.addBaloonFromLine("white-10.0");
    club.addNargaFromLine("OS-queen-30");
    club.addNargaFromLine("Alfa-mango-35");
    club.addAlchoholFromLine("black_label-60");
    club.addAlchoholFromLine("jameson-50");
    std::cout << "Green baloon: " << (club.hasBaloon(BalloonColor::GREEN) ? "yes" : "no") << "\n";
    std::cout << "White baloon: " << (club.hasBaloon(BalloonColor::WHITE) ? "yes" : "no") << "\n";
    std::cout << "jameson: " << (club.hasAlchohol("jameson") ? "yes" : "no") << "\n";
    std::cout << "Mango narga: " << (club.hasNarga(Taste::MANGO) ? "yes" : "no") << "\n";
    club.removeBaloon(BalloonColor::WHITE);
    std::cout << "White baloon: " << (club.hasBaloon(BalloonColor::WHITE) ? "yes" : "no") << "\n";
    std::cout << "\nBills for Ivan:  " << club.getBill("ivan_bill.txt") << " lv.\n";
    std::cout << "Bills for Maria: " << club.getBill("maria_bill.txt") << " lv.\n";
    Client clients[2] = 
    {
        Client("Ivan",  "ivan_bill.txt"),
        Client("Maria", "maria_bill.txt")
    };
    club.dailyProfit(clients, 2);
}
```

`Изход:`
```
Green baloon: yes
White baloon: yes
jameson: yes
Mango narga: yes
White baloon: no

Bills for Ivan:  586 lv.
Bills for Maria: 160 lv.
```

<hr style="border-width: 5px !important;">
