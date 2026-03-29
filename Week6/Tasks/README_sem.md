# Решения

<hr style="border-width: 5px !important;">

## Ю-Ги-О!

<hr style="border-width: 5px !important;">

```
Сето Кайба организира турнир по Ю-Ги-О!, но е съкратил бюджета в компютърния отдел и помолил нас да организираме базата данни с всички дуелисти в турнира.
Трябва да реализирате 2 класа Ю-Ги-О! карти:

Карта чудовище / Monster card

Име (низ с произволна дължина)
Атакуващи точки (неотрицателно целочислено число)
Защитни точки (неотрицателно целочислено число)
Магическа карта / Magic card

Име (низ с дължина до 25 символа).
Ефект (низ с дължина до 100 символа).
Тип (може да е един следните 3: "spell", "equip", "trap")
И двата класа трябва да имат 2 функции, като:

първата да описва типа карта (напр. "Monster cards have a name, attack points and defense points." и "Magic cards have a name, effect and a type - spell, equip or trap.")
втората да дава информация за конкретна карта (напр. "Blue-eyes white dragon is a monster with ATK: 3000 and DEF: 2500." и "Pot of greed is a spell with the following effect - "Draw 2 cards.".")
Реализирайте клас Deck.Тестето трябва да има:

Масив от карти чудовища (максимално – 20 карти).
Масив от магически карти (максимално – 20 карти).
Метод, който връща като резултат броя на магическите карти в тестето.
Метод, който връща като резултат броя на картите чудовища в тестето.
Метод, който добавя магическа карта към тестето.
Метод, който добавя карта чудовище към тестето.
Метод, който променя магическа карта от тестето, като за параметри приема индекс и нова карта.
Метод, който променя карта чудовище от тестето, като за параметри приема индекс и нова карта.
Метод, който премахва магическата карта на определена позиция от тестето
Метод, който премахва картата чудовище на определена позиция от тестето
Реализирайте клас Duelist. Той трябва трябва да има:

Име (Низ с произволна дължина).
Тесте(Deck)
Дуелистът трябва да има същите методи като в deck, с които да променяме тестето му
```

<hr style="border-width: 5px !important;">

`Решение:`

`Deck.h`
```h
#pragma once
#include "MonsterCard.h"
#include "MagicCard.h"
class Deck
{
private:
    static const int MAX_CARDS = 20;
    MonsterCard monsterCards[MAX_CARDS];
    MagicCard magicCards[MAX_CARDS];
    int monsterCount;
    int magicCount;

public:
    Deck();
    int getMonsterCardCount() const;
    int getMagicCardCount() const;
    bool addMonsterCard(const MonsterCard& card);
    bool addMagicCard(const MagicCard& card);
    bool changeMonsterCard(int index, const MonsterCard& card);
    bool changeMonsterCard(int index, const char* name, unsigned int atk, unsigned int def);
    bool changeMagicCard(int index, const MagicCard& card);
    bool changeMagicCard(int index, const char* name, const char* effect, MagicType type);
    bool removeMonsterCard(int index);
    bool removeMagicCard(int index);
    const MonsterCard& getMonsterCard(int index) const;
    const MagicCard& getMagicCard(int index) const;
};
```
<hr style="border-width: 5px !important;">

`Duelist.h`
```h
#pragma once
#include "Deck.h"
class Duelist
{
private:
    char* name;
    Deck deck;
    void copyFrom(const Duelist& other);
    void free();
public:
    Duelist(const char* name);
    Duelist(const Duelist& other);
    Duelist& operator=(const Duelist& other);
    ~Duelist();
    const char* getName() const;
    int getMonsterCardCount() const;
    int getMagicCardCount() const;
    bool addMonsterCard(const MonsterCard& card);
    bool addMagicCard(const MagicCard& card);
    bool changMonsterInDeck(int index, const MonsterCard& card);
    bool changeMagicCardInDeck(int index, const MagicCard& card);
    bool removeMonsterFromDeck(int index);
    bool removeMagicFromDeck(int index);
};
```

<hr style="border-width: 5px !important;">

`MagicCard.h`
```h
#pragma once
enum MagicType 
{
	spell,
	equip,
	trap 
};
class MagicCard
{
private:
    static const int MAX_NAME = 26;
    static const int MAX_EFFECT = 101;
    char name[MAX_NAME];
    char effect[MAX_EFFECT];
    MagicType type;

public:
    MagicCard();
    MagicCard(const char* name, const char* effect, MagicType type);
    static void describeType();
    void describeCard() const;
    const char* getName() const;
    const char* getEffect() const;
    MagicType getType() const;
};
```

<hr style="border-width: 5px !important;">

`MonsterCard.h`
```h
#pragma once
#include <iostream>
using namespace std;

class MonsterCard
{
private:
    char* name;
    unsigned int atk;
    unsigned int def;
    void copyFrom(const MonsterCard& other);
    void free();
public:
    MonsterCard();
    MonsterCard(const char* name, unsigned int atk, unsigned int def);
    MonsterCard(const MonsterCard& other);
    MonsterCard& operator=(const MonsterCard& other);
    ~MonsterCard();
    static void describeType();
    void describeCard() const;
    const char* getName() const;
    unsigned int getATK() const;
    unsigned int getDEF() const;
};
```

<hr style="border-width: 5px !important;">

`Deck.cpp`
```cpp
#include "Deck.h"
#include <iostream>

Deck::Deck() : monsterCount(0), magicCount(0)
{

}
int Deck::getMonsterCardCount() const
{
	return monsterCount;
}
int Deck::getMagicCardCount() const
{
	return magicCount;
}
bool Deck::addMonsterCard(const MonsterCard& card)
{
	if (monsterCount >= MAX_CARDS)
	{
		std::cout << "Monster deck is full!" << std::endl;
		return false;
	}
	monsterCards[monsterCount++] = card;
	return true;
}
bool Deck::addMagicCard(const MagicCard& card)
{
	if (magicCount >= MAX_CARDS)
	{
		std::cout << "Magic deck is full!" << std::endl;
		return false;
	}
	magicCards[magicCount++] = card;
	return true;
}
bool Deck::changeMonsterCard(int index, const MonsterCard& card)
{
	if (index < 0 || index >= monsterCount)
	{
		std::cout << "Invalid monster card index!" << std::endl;
		return false;
	}
	monsterCards[index] = card;
	return true;
}
bool Deck::changeMonsterCard(int index, const char* name, unsigned int atk, unsigned int def)
{
	return changeMonsterCard(index, MonsterCard(name, atk, def));
}
bool Deck::changeMagicCard(int index, const MagicCard& card)
{
	if (index < 0 || index >= magicCount)
	{
		std::cout << "Invalid magic card index!" << std::endl;
		return false;
	}
	magicCards[index] = card;
	return true;
}
bool Deck::changeMagicCard(int index, const char* name, const char* effect, MagicType type)
{
	return changeMagicCard(index, MagicCard(name, effect, type));
}
auto removeCard = [](auto* cards, int& count, int index, const char* errorMsg, auto emptyCard)
	{
		if (index < 0 || index >= count)
		{
			std::cout << errorMsg << std::endl;
			return false;
		}
		for (int i = index; i < count - 1; i++)
		{
			cards[i] = cards[i + 1];
		}
		cards[--count] = emptyCard;
		return true;
	};
bool Deck::removeMonsterCard(int index)
{
	return removeCard(monsterCards, monsterCount, index, "Invalid monster card index!", MonsterCard());
}
bool Deck::removeMagicCard(int index)
{
	return removeCard(magicCards, magicCount, index, "Invalid magic card index!", MagicCard());
}
const MonsterCard& Deck::getMonsterCard(int index) const
{
	return monsterCards[index];
}
const MagicCard& Deck::getMagicCard(int index) const
{
	return magicCards[index];
}
```

<hr style="border-width: 5px !important;">

`Duelist.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Duelist.h"

void Duelist::copyFrom(const Duelist& other)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    deck = other.deck;
}
void Duelist::free()
{
    delete[] name;
}
Duelist::Duelist(const char* name)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}
Duelist::Duelist(const Duelist& other)
{
    copyFrom(other);
}
Duelist& Duelist::operator=(const Duelist& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
Duelist::~Duelist()
{
    free();
}
const char* Duelist::getName() const 
{
    return name;
}
int  Duelist::getMonsterCardCount() const 
{ 
    return deck.getMonsterCardCount(); 
}
int  Duelist::getMagicCardCount() const 
{
    return deck.getMagicCardCount();
}
bool Duelist::addMonsterCard(const MonsterCard& card) 
{
    return deck.addMonsterCard(card); 
}
bool Duelist::addMagicCard(const MagicCard& card) 
{
    return deck.addMagicCard(card);
}
bool Duelist::changMonsterInDeck(int index, const MonsterCard& card) 
{
    return deck.changeMonsterCard(index, card); 
}
bool Duelist::changeMagicCardInDeck(int index, const MagicCard& card)
{ 
    return deck.changeMagicCard(index, card); 
}
bool Duelist::removeMonsterFromDeck(int index) 
{
    return deck.removeMonsterCard(index); 
}
bool Duelist::removeMagicFromDeck(int index) 
{
    return deck.removeMagicCard(index); 
}
```

<hr style="border-width: 5px !important;">

`MagicCard.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "MagicCard.h"
#include <iostream>

MagicCard::MagicCard() : type(spell) 
{
    name[0] = '\0';
    effect[0] = '\0';
}
MagicCard::MagicCard(const char* name, const char* effect, MagicType type) : type(type) 
{
    strcpy(this->name, name);
    this->name[25] = '\0';
    strcpy(this->effect, effect);
    this->effect[100] = '\0';
}
void MagicCard::describeType() 
{
    std::cout << "Magic cards have a name, effect and a type." << std::endl;
}
void MagicCard::describeCard() const
{
    const char* typeStr;
    if (type == spell)
    {
        typeStr = "spell";
    }
    else if (type == equip)
    {
        typeStr = "equip";
    }
    else
    {
        typeStr = "trap";
    }
    std::cout << name << " is a " << typeStr << " with effect: " << effect << std::endl;
}
const char* MagicCard::getName() const 
{ 
    return name; 
}
const char* MagicCard::getEffect() const 
{ 
    return effect; 
}
MagicType   MagicCard::getType() const
{
    return type;
}
```

<hr style="border-width: 5px !important;">

`MonsterCard.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "MonsterCard.h"
MonsterCard::MonsterCard() : name(nullptr), atk(0), def(0) 
{

}
MonsterCard::MonsterCard(const char* name, unsigned int atk, unsigned int def) : atk(atk), def(def) 
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}
void MonsterCard::copyFrom(const MonsterCard& other)
{
    if (other.name)
    {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
    else
    {
        name = nullptr;
    }
    atk = other.atk;
    def = other.def;
}
void MonsterCard::free()
{
    delete[] name;
    name = nullptr;
}
MonsterCard::MonsterCard(const MonsterCard& other)
{
    copyFrom(other);
}
MonsterCard& MonsterCard::operator=(const MonsterCard& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
MonsterCard::~MonsterCard()
{
    free();
}
void MonsterCard::describeType() 
{
    cout << "Monster cards have name, attack point and defense point." << endl;
}
void MonsterCard::describeCard() const 
{
    if (name) 
    {
        std::cout << "`" << name << "` is a monster with ATK: " << atk << " and DEF: " << def << "." << std::endl;
    }
    else 
    {
        std::cout << "`Unknown` is a monster with ATK: " << atk << " and DEF: " << def << "." << std::endl;
    }
}
const char* MonsterCard::getName() const 
{
    return name;
}
unsigned int MonsterCard::getATK() const 
{
    return atk; 
}
unsigned int MonsterCard::getDEF() const
{ 
    return def;
}
```

<hr style="border-width: 5px !important;">

`sem_week5.cpp`
```cpp
#include <iostream>
#include "MonsterCard.h"
#include "MagicCard.h"
#include "Deck.h"
#include "Duelist.h"

int main()
{
	MonsterCard blueEyes("Blue-Eyes White Dragon", 3000, 2500);
	MonsterCard darkMagician("Dark Magician", 2500, 2100);
	MonsterCard kuriboh("Kuriboh", 300, 200);
	blueEyes.describeCard();
	darkMagician.describeCard();
	kuriboh.describeCard();
	MagicCard potOfGreed("Pot of Greed", "Draw 2 cards.", spell);
	MagicCard darkHole("Dark Hole", "Destroys all monsters on the field.", spell);
	MagicCard mirrorForce("Mirror Force", "Destroy all attacking monsters.", trap);
	potOfGreed.describeCard();
	darkHole.describeCard();
	mirrorForce.describeCard();
	Deck deck;
	deck.addMonsterCard(blueEyes);
	deck.addMonsterCard(darkMagician);
	deck.addMonsterCard(kuriboh);
	deck.addMagicCard(potOfGreed);
	deck.addMagicCard(darkHole);
	deck.addMagicCard(mirrorForce);
	std::cout << "Monster count: " << deck.getMonsterCardCount() << std::endl;
	std::cout << "Magic count:   " << deck.getMagicCardCount() << std::endl;
	Duelist yugi("Yugi Muto");
	Duelist kaiba("Seto Kaiba");
	yugi.addMonsterCard(darkMagician);
	yugi.addMagicCard(potOfGreed);
	kaiba.addMonsterCard(blueEyes);
	kaiba.addMagicCard(darkHole);
	std::cout << yugi.getName() << std::endl;
	std::cout << "Monsters: " << yugi.getMonsterCardCount() << std::endl;
	std::cout << "Magic: " << yugi.getMagicCardCount() << std::endl;
	std::cout << kaiba.getName() << std::endl;
	std::cout << "Monsters: " << kaiba.getMonsterCardCount() << std::endl;
	std::cout << "Magic: " << kaiba.getMagicCardCount() << std::endl;
	deck.changeMonsterCard(1, "Summoned Skull", 2500, 1200);
	deck.changeMagicCard(1, "Monster Reborn", "Revives a monster.", spell);
	deck.removeMonsterCard(0);
	deck.removeMagicCard(0);
	std::cout << "Monster count: " << deck.getMonsterCardCount() << std::endl;
	std::cout << "Magic count: " << deck.getMagicCardCount() << std::endl;
}
```

<hr style="border-width: 5px !important;">

## Music playlist 🎶

<hr style="border-width: 5px !important;">

```
Всички обичаме да слушаме музика - било то докато сме с приятели, докато шофираме, докато учим, докато ядем или дори докато се къпем. Разбира се, всеки от нас обича различен стил музика - някои обичат да слушат баладите на Scorpions и Rainbow, на други са им по-приятни Боро Първи и Атанас Колев, а трети се събуждат и си лягат в компанията на Азис и Галена. А някои просто си пускат най-тъжните гръцки хитове след поредното невзето теоретично тестче по Алгебра... Каквато и музика да харесвате обаче, можете да комбинирате всичко изброено в някой миш-маш плейлист и да си избухвате на макс. Именно с това ще се занимаваме днес:

Продължителност ⏳
Всяка една песен има определена дължина. Създайте структура Duration, която пази информация за продължителността на една песен - колко минути и колко секунди е дълга тя.

Песен 🎵
Време е да създадем единицата, от която ще бъдат съставени нашите плейлисти - песента. Създайте клас Song, представящ песен. В нашата програма всяка песен ще се харектеризира с име (произволна дължина), продължителност (хмм, не написахме ли вече нещо подобно?) и жанр. Помислете за подходящи начини, чрез които да конструирате песни. Реализайте гетъри и сетъри за член-данните на класа. Ще се наложи многократно копиране на обекти от този тип - помислете кое правило трябва да спазим?

Плейлист 🎧
Дойде и дългоочакваният момент - време е да създадем нашия миш-маш плейлист от песни. Напишете клас Playlist, който да съдържа списък от песни(неограничен брой). Разбира се, освен песни, нашият плейлист ще си има и име(макс 256 символа) - как иначе ще различавам плейлиста "Ne sam 4algar" от "Rock ballads of the 80s", ще взема да се изложа пред някого, пред когото не трябва... Помислете за подходящ/и конструктор/и, на кои член-данни е удачно да направим гетъри и/или сетъри и кое правило трябва да спазим.
```

<hr style="border-width: 5px !important;">

`Решение:`

`Duration.h`
```h
#pragma once
class Duration
{
private:
	unsigned int minutes;
	unsigned int seconds;
public:
	Duration();
	Duration(unsigned int minutes, unsigned int seconds);
	unsigned int totalSeconds() const;
	unsigned int getMinutes() const;
	unsigned int getSeconds() const;
	void setMinutes(unsigned int minutes);
	void setSeconds(unsigned int seconds);
	void setDuration(unsigned int minutes, unsigned int seconds);
};
```

<hr style="border-width: 5px !important;">

`Song.h`
```h
#pragma once
#include "Duration.h"

class Song
{
private:
    char* name;
    Duration duration;
    char* genre;
    void copyFrom(const Song& other);
    void free();
public:
    Song(const char* name, Duration duration, const char* genre);
    Song(const Song& other);
    Song& operator=(const Song& other);
    ~Song();
    const char* getName() const;
    Duration getDuration() const;
    const char* getGenre() const;
    void setName(const char* name);
    void setDuration(Duration duration);
    void setGenre(const char* genre);
    void print() const;
};
```

<hr style="border-width: 5px !important;">

`Playlist.h`
```h
#pragma once
#include "Song.h"

class Playlist 
{
private:
    static const int MAX_NAME = 257;
    char name[MAX_NAME];
    Song** songs;
    int count;
    int capacity;
    void resize();
    void copyFrom(const Playlist& other);
    void free();

public:
    Playlist(const char* name);
    Playlist(const Playlist& other);
    Playlist& operator=(const Playlist& other);
    ~Playlist();
    const char* getName() const;
    void setName(const char* name);
    int getSongCount() const;
    int  getSongIndex(const char* songName);
    void addSong(const Song& songToAdd);
    bool removeSong(const char* songName);
    void printPlaylistInfo();
};
```

<hr style="border-width: 5px !important;">

`Duration.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Duration.h"
#include <iostream>

Duration::Duration() : minutes(0), seconds(0) 
{

}
Duration::Duration(unsigned int minutes, unsigned int seconds) 
{
    this->minutes = minutes;
    if (seconds >= 60) 
    {
        this->minutes += seconds / 60;
        this->seconds = seconds % 60;
    }
    else 
    {
        this->seconds = seconds;
    }
}
unsigned int Duration::totalSeconds() const
{
    return minutes * 60 + seconds;
}
unsigned int Duration::getMinutes() const 
{ 
    return minutes;
}
unsigned int Duration::getSeconds() const
{
    return seconds;
}
void Duration::setMinutes(unsigned int minutes)
{
    this->minutes = minutes;
}
void Duration::setSeconds(unsigned int seconds)
{ 
    this->seconds = seconds;
}
void Duration::setDuration(unsigned int minutes, unsigned int seconds) 
{ 
    this->minutes = minutes;
    this->seconds = seconds; 
}
```

<hr style="border-width: 5px !important;">

`Song.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Song.h"
#include <cstring>
#include <iostream>

void Song::copyFrom(const Song& other)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    genre = new char[strlen(other.genre) + 1];
    strcpy(genre, other.genre);

    duration = other.duration;
}
void Song::free()
{
    delete[] name;
    delete[] genre;
}
Song::Song(const char* name, Duration duration, const char* genre)
    : duration(duration)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    this->genre = new char[strlen(genre) + 1];
    strcpy(this->genre, genre);
}
Song::Song(const Song& other)
{
    copyFrom(other);
}
Song& Song::operator=(const Song& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
Song::~Song()
{
    free();
}
const char* Song::getName() const 
{ 
    return name;
}
const char* Song::getGenre() const 
{
    return genre;
}
Duration Song::getDuration() const
{ 
    return duration;
}
void Song::setName(const char* newName)
{
    if (!newName)
    {
        return;
    }
    delete[] name;
    name = new char[strlen(newName) + 1];
    strcpy(name, newName);
}
void Song::setGenre(const char* newGenre)
{
    if (!newGenre)
    {
        return;
    }
    delete[] genre;
    genre = new char[strlen(newGenre) + 1];
    strcpy(genre, newGenre);
}
void Song::setDuration(Duration newDuration)
{
    duration = newDuration;
}
void Song::print() const
{
    std::cout << name << " (" << genre << ") " << duration.getMinutes() << ":";
    if (duration.getSeconds() < 10)
    {
        std::cout << "0";
    }
    std::cout << duration.getSeconds() << std::endl;
}
```

<hr style="border-width: 5px !important;">

`Playlist.cpp`
```cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Playlist.h"
#include <cstring>
#include <iostream>

void Playlist::resize() 
{
    capacity = capacity * 2;
    Song** newSongs = new Song* [capacity];
    for (int i = 0; i < count; i++)
    {
        newSongs[i] = songs[i];
    }
    delete[] songs;
    songs = newSongs;
}
void Playlist::copyFrom(const Playlist& other) 
{
    strcpy(name, other.name);
    name[256] = '\0';
    count = other.count;
    capacity = other.capacity;
    songs = new Song * [capacity];
    for (int i = 0; i < count; i++)
    {
        songs[i] = new Song(*other.songs[i]);
    }
}
void Playlist::free() 
{
    for (int i = 0; i < count; i++)
    {
        delete songs[i];
    }
    delete[] songs;
}
Playlist::Playlist(const char* name) : count(0), capacity(4) 
{
    strcpy(this->name, name);
    this->name[256] = '\0';
    songs = new Song* [capacity];
}

Playlist::Playlist(const Playlist& other)
{
    copyFrom(other);
}

Playlist& Playlist::operator=(const Playlist& other) 
{
    if (this != &other) 
    {
        free();
        copyFrom(other);
    }
    return *this;
}

Playlist::~Playlist() 
{
    free();
}

const char* Playlist::getName() const 
{
    return name;
}
int Playlist::getSongCount() const 
{
    return count;
}
void Playlist::setName(const char* name) 
{
    if (!name)
    {
        std::cout << "Invalid name!" << std::endl;
        return;
    }
    strcpy(this->name, name);
    this->name[256] = '\0';
}
int Playlist::getSongIndex(const char* songName) 
{
    for (int i = 0; i < count; i++) 
    {
        if (strcmp(songs[i]->getName(), songName) == 0)
        {
            return i;
        }
    }
    return -1;
}

void Playlist::addSong(const Song& songToAdd) 
{
    if (getSongIndex(songToAdd.getName()) != -1) 
    {
        std::cout << "Song " << songToAdd.getName() << " already exists in the playlist. Skipping." << std::endl;
        return;
    }
    if (count == capacity)
    {
        resize();
    }
    songs[count++] = new Song(songToAdd);
}

bool Playlist::removeSong(const char* songName) 
{
    int index = getSongIndex(songName);
    if (index == -1) 
    {
        std::cout << "Song " << songName << " not found in playlist." << std::endl;
        return false;
    }
    delete songs[index];
    for (int i = index; i < count - 1; i++)
    {
        songs[i] = songs[i + 1];
    }
    songs[--count] = nullptr;
    return true;
}
void Playlist::printPlaylistInfo() 
{
    unsigned int total = 0;
    for (int i = 0; i < count; i++)
    {
        total += songs[i]->getDuration().totalSeconds();
    }
    unsigned int totalMin = total / 60;
    unsigned int totalSec = total % 60;
    std::cout << "Playlist: " << name << std::endl;
    std::cout << "Songs (" << count << "):" << std::endl;
    for (int i = 0; i < count; i++) 
    {
        std::cout << "  " << (i + 1) << ". ";
        songs[i]->print();
    }
    std::cout << "Total duration: " << totalMin << ":";
    if (totalSec < 10)
    {
        std::cout << "0";
    }
    std::cout << totalSec << std::endl;
}
```

<hr style="border-width: 5px !important;">

`sem_music_task.cpp`
```cpp
#include <iostream>
#include "Duration.h"
#include "Song.h"
#include "Playlist.h"

int main()
{
    Song s1("Arctic Monkeys - Arabella", Duration(3, 27), "CathyMusic");
    Song s2("Artemas - myself", Duration(4, 10), "CathyMusic");
    Song s3("Arctic Monkeys - Knee Socks", Duration(4, 15), "CathyMusic");
    Song s4("The Neighbourhood - A Little Death", Duration(3, 45), "CathyMusic");
    std::cout << "Songs" << std::endl;
    s1.print();
    s2.print();
    s3.print();
    s4.print();
    std::cout << std::endl;
    Playlist myPlaylist("My Favorite Tracks");
    myPlaylist.addSong(s1);
    myPlaylist.addSong(s2);
    myPlaylist.addSong(s3);
    myPlaylist.addSong(s4);

    myPlaylist.addSong(s1);
    std::cout << std::endl;

    std::cout << "Playlist Info" << std::endl;
    myPlaylist.printPlaylistInfo();
    std::cout << std::endl;
    int index1 = myPlaylist.getSongIndex("Artemas - myself (official lyric video)");
    std::cout << "Index of " << s2.getName() <<": " << index1 << std::endl;
    int index2 = myPlaylist.getSongIndex("Non existent Song");
    std::cout << "Index of that song: " << index2 << std::endl;
    std::cout << std::endl;
    bool removed1 = myPlaylist.removeSong("Arctic Monkeys - Knee Socks");
    std::cout << "Removed: " << s3.getName() << ": ";
    if (removed1)
    {
        std::cout << "true";
    }
    else
    {
        std::cout << "false";
    }
    std::cout << std::endl;
    bool removed2 = myPlaylist.removeSong("Song That Is Not In Playlist");
    std::cout << "Removed: ";
    if (removed2)
    {
        std::cout << "true";
    }
    else
    {
        std::cout << "false";
    }
    std::cout << std::endl;
    std::cout << "Updated Playlist" << std::endl;
    myPlaylist.printPlaylistInfo();
    Playlist copiedPlaylist = myPlaylist;
    copiedPlaylist.setName("Copied Playlist");
    copiedPlaylist.addSong(Song("Extra Song", Duration(3, 30), "CathyMusic"));
    std::cout << std::endl;
    std::cout << "Copied Playlist" << std::endl;
    copiedPlaylist.printPlaylistInfo();
}
```

<hr style="border-width: 5px !important;">
