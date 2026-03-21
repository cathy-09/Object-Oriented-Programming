#pragma once
#include "City.h"

enum EyeColor
{
    BLUE,
    GREEN,
    BROWN
};

class Person
{
private:
    City birthplace;
    int age;
    EyeColor eyeColor;

public:
    Person(const char* cityName, long population, int age, EyeColor eyeColor);
};

