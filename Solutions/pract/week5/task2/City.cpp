#include "City.h"
#include <string.h>

void City::copyFrom(const City& other)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    population = other.population;
}

void City::free()
{
    delete[] name;
}

City::City()
{
    name = new char[1];
    name[0] = '\0';
    population = 0;
}

City::City(const char* name, long population)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->population = population;
}

City::City(const City& other)
{
    copyFrom(other);
}

City& City::operator=(const City& other)
{
    if (this != &other) 
    {
        free();
        copyFrom(other);
    }
    return *this;
}

City::~City()
{
    free();
}
