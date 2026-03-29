#include <iostream>
#include "NumericalVector.h"

int main()
{
    NumericalVector v1(3), v2(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;

    NumericalVector v3 = v1 + v2;
    std::cout << "v1 + v2 = " << v3 << std::endl;

    int dot = v1 * v2;
    std::cout << "v1 * v2 (dot) = " << dot << std::endl;

    v1 += v2;
    std::cout << "v1 += v2: " << v1 << std::endl;

    NumericalVector va(3), vb(3);
    va[0] = 1; va[1] = 2; va[2] = 3;
    vb[0] = 1; vb[1] = 2; vb[2] = 4;
    if ((va <=> vb) < 0)
    {
        std::cout << "va <=> vb: va < vb" << std::endl;
    }
    else
    {
        std::cout << "va <=> vb: va >= vb" << std::endl;
    }

    if (va == vb)
    {
        std::cout << "va == vb: true" << std::endl;
    }
    else
    {
        std::cout << "va == vb: false" << std::endl;
    }

    v3[-1];
}
