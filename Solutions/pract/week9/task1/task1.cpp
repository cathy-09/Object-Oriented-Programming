#include <iostream>
#include "Plot.h"
#include "Farmer.h"

int main()
{
    Plot p1(100, 200, Crop::WHEAT);
    Plot p2(50, 75, Crop::CORN);
    Plot p3;

    std::cout << "p1 id=" << p1.getId() << " WHEAT" << std::endl;
    std::cout << "p2 id=" << p2.getId() << " CORN" << std::endl;
    std::cout << "p3 id=" << p3.getId() << " NOTHING" << std::endl;

    p3.sow(Crop::BARLEY);
    std::cout << std::endl;

    p2.reap();
    std::cout << std::endl;

    Plot* arr1[] = { &p1, &p2 };
    Farmer ivan("Ivan", 4, arr1, 2);

    ivan.printField();

    ivan.addPlot(&p3);
    ivan.printField();
    std::cout << std::endl;

    Plot* arr2[] = { &p1 };
    Farmer petar("Petar", 5, arr2, 1);

    petar.printField();
    std::cout << std::endl;

    p1.reap();
    std::cout << "Ivan:" << std::endl;
    ivan.printField();
    std::cout << "Petar:" << std::endl;
    petar.printField();

    Farmer ivan2 = ivan;
    ivan2.printField();

    Plot p4(30, 30, Crop::BARLEY);
    ivan2.addPlot(&p4);
    ivan2.printField();
    ivan.printField();
}
