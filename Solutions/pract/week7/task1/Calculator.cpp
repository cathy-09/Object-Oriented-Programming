#include "Calculator.h"
#include <iostream>
Calculator* Calculator::instance = nullptr;

Calculator* Calculator::getInstance() 
{
    if (instance == nullptr)
    {
        instance = new Calculator();
    }
    return instance;
}

double Calculator::sum(double first, double second) 
{
    return first + second;
}

double Calculator::subtract(double first, double second) 
{
    return first - second;
}

double Calculator::multiply(double first, double second) 
{
    return first * second;
}

double Calculator::divide(double first, double second) 
{
    if (second == 0.0) 
    {
         std::cout << "Division by zero is not allowed.";
         return 0.0;
    }
    return first / second;
}
