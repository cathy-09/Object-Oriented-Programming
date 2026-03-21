#include <iostream>
#include "MyPair.h"

int main()
{
    MyPair pair1;
    MyPair pair2{ 5,10 };

    pair1.printPair();
    pair2.printPair();

    pair1.setFirst(3);
    pair1.setSecond(7);

    pair1.printPair();

    pair2.swapElements();
    pair2.printPair();

    std::cout << pair1.maxElement();
    std::cout << std::endl;
    std::cout << pair2.maxElement();
}
