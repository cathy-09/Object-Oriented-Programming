#include <iostream>
#include "Text.h"

int main()
{
    std::cout << "=== Text ===";
    std::cout << std::endl;

    Text t1;
    std::cout << "Default: " << t1;
    std::cout << std::endl;

    const char* msg = "Hello";
    Text t2(msg, 5);
    std::cout << "Custom: " << t2;
    std::cout << std::endl;

    std::cout << "t2[1] = " << t2[1];
    std::cout << std::endl;

    Text t3;
    t3 = t2;
    std::cout << "Copied: " << t3;
    std::cout << std::endl;

    Text t4(std::move(t3));
    std::cout << "Moved: " << t4;
    std::cout << std::endl;
}