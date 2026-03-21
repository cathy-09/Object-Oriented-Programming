#include "Person.h"

Person::Person(const char* cityName, long population, int age, EyeColor eyeColor) : birthplace(cityName, population) 
{
    this->age = age;
    this->eyeColor = eyeColor;
}
