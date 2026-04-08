#pragma once
class Calculator
{
private:
    Calculator() = default;
    Calculator(const Calculator&) = delete;
    Calculator& operator=(const Calculator&) = delete;
    static Calculator* instance;

public:
    static Calculator* getInstance();
    double sum(double first, double second);
    double subtract(double first, double second);
    double multiply(double first, double second);
    double divide(double first, double second); 
};

