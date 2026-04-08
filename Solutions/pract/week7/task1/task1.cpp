#include <iostream>
#include "User.h"

int main()
{
    User az("az", "pass123");
    User didi("didi", "qwerty");
    User kiki("kiki", "abc456");

    std::cout << "az id=" << az.getId() << " didi id=" << didi.getId() << " kiki id=" << kiki.getId() << "\n\n";

    Calculator* c = az.getCalculator();
    std::cout << "Calculator instance same for all users? " << (c == didi.getCalculator() && c == kiki.getCalculator() ? "YES" : "NO") << "\n\n";

    double a = 10, b = 3;
    std::cout << a << " + " << b << " = " << c->sum(a, b) << "\n";
    std::cout << a << " - " << b << " = " << c->subtract(a, b) << "\n";
    std::cout << a << " * " << b << " = " << c->multiply(a, b) << "\n";
    std::cout << a << " / " << b << " = " << c->divide(a, b) << "\n\n";
}
