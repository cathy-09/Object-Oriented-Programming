#include <iostream>
#include "BinaryNumber.h"

int main()
{
    std::cout << "=== BinaryNumber ===";
    std::cout << std::endl;

    BinaryNumber zero;
    std::cout << "Default (0): ";
    zero.print();

    BinaryNumber a(10);
    std::cout << "10 in binary: "; 
    a.print();

    BinaryNumber b(6);
    std::cout << "6 in binary: ";
    b.print();

    BinaryNumber c = a + b;
    std::cout << "10+6=16:  "; 
    c.print();

    a += b;
    std::cout << "10+=6 = 16: ";
    a.print();

    BinaryNumber x(5), y(8);

    if (x < y)
    {
        std::cout << "5 < 8 : true";
        std::cout << std::endl;
    }
    else
    {
        std::cout << "5 < 8 : false";
        std::cout << std::endl;
    }

    if (y > x)
    {
        std::cout << "8 > 5 : true";
        std::cout << std::endl;
    }
    else
    {
        std::cout << "8 > 5 : false";
        std::cout << std::endl;
    }

    if (x == BinaryNumber(5))
    {
        std::cout << "5 == 5: true";
        std::cout << std::endl;
    }
    else
    {
        std::cout << "5 == 5: false";
        std::cout << std::endl;
    }

    BinaryNumber moved(std::move(x));
    std::cout << "Moved 5: ";
    moved.print();

    BinaryNumber copy(c);
    std::cout << "Copy of 16: ";
    copy.print();
}