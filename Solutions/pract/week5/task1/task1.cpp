#include <iostream>
#include "Matrix.h"

int main()
{
    Matrix matrix1(2,3);
    matrix1.setValue(0, 0, 1);
    matrix1.setValue(0, 1, 2);
    matrix1.setValue(1, 2, 3);

    Matrix matrix2 = matrix1;
    Matrix matrix3(1, 1);
    matrix3 = matrix1;

    matrix1.printMatrix();
    std::cout << std::endl;
    matrix2.printMatrix();
    std::cout << std::endl;
    matrix3.printMatrix();
}
