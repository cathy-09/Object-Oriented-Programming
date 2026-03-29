#include "Temperature.h"
#include <iostream>

int Temperature::toFahrenheit(int celsius)
{
    return (int)(celsius * 1.8 + 32);
}

int Temperature::toCelsius(int fahrenheit)
{
    return (int)((fahrenheit - 32) / 1.8);
}

int Temperature::asCelsius() const
{
    if (system == 'c')
    {
        return temperature;
    }
    else
    {
        return toCelsius(temperature);
    }
}

Temperature::Temperature(int temperature, char system)
{
    if (system == 'c' || system == 'f')
    {
        this->system = system;
    }
    else
    {
        this->system = 'c';
    }
    this->temperature = temperature;
}

int Temperature::getTemperature() const
{
    return temperature;
}

char Temperature::getSystem() const
{
    return system;
}

void Temperature::setTemperature(int temperature)
{
    this->temperature = temperature;
}

void Temperature::setSystem(char system)
{
    if (system != 'c' && system != 'f') 
    {
        std::cout << "Invalid system!" << std::endl;
        return;
    }
    this->system = system;
}

bool Temperature::operator==(const Temperature& other) const
{
    return asCelsius() == other.asCelsius();
}

bool Temperature::operator<(const Temperature& other) const
{
    return asCelsius() < other.asCelsius();
}

bool Temperature::operator!=(const Temperature& other) const
{
    return !(*this == other);
}

bool Temperature::operator<=(const Temperature& other) const
{
    return (*this < other || *this == other);
}

bool Temperature::operator>(const Temperature& other) const
{
    return !(*this <= other);
}

bool Temperature::operator>=(const Temperature& other) const
{
    return !(*this < other);
}

Temperature Temperature::operator+(const Temperature& other) const
{
    return Temperature(asCelsius() + other.asCelsius(), 'c');
}

Temperature Temperature::operator-(const Temperature& other) const
{
    return Temperature(asCelsius() - other.asCelsius(), 'c');
}

Temperature& Temperature::operator+=(const Temperature& other)
{
    int resultCelsius = asCelsius() + other.asCelsius();
    if (system == 'c')
    {
        temperature = resultCelsius;
    }
    else
    {
        temperature = toFahrenheit(resultCelsius);
    }
    return *this;
}

Temperature& Temperature::operator-=(const Temperature& other)
{
    int resultCelsius = asCelsius() - other.asCelsius();
    if (system == 'c')
    {
        temperature = resultCelsius;
    }
    else
    {
        temperature = toFahrenheit(resultCelsius);
    }
    return *this;
}

