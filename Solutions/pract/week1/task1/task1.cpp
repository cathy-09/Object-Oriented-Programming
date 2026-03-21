//Да се създаде структура, която представя тримерен вектор с целочислени координати.
//Създайте функция, която събира два вектора и връща нов вектор.
//Създайте функция, която отпечатва координатите на даден вектор.
//Създайте функция, която приема като аргументи 2 вектора и проверява дали те са линейно зависими.
#include <iostream>
#include <cmath>
struct ThreeVector
{
	int x;
	int y;
	int z;
};
ThreeVector sumOfVectors(ThreeVector first, ThreeVector second);
void newLine();
void PrintCoordinates(ThreeVector result);
bool isLZ(ThreeVector first, ThreeVector second);


int main()
{
	ThreeVector first;
	ThreeVector second;
	ThreeVector result;
	std::cin >> first.x >> first.y >> first.z;
	std::cin >> second.x >> second.y >> second.z;
	result = sumOfVectors(first, second);
	PrintCoordinates(result);
	bool isLZVectors = isLZ(first, second);
	std::cout << isLZVectors;
}
bool isLZ(ThreeVector first, ThreeVector second)
{
	if ((first.x == 0 && first.y == 0 && first.z == 0) ||
		(second.x == 0 && second.y == 0 && second.z == 0))
	{
		return true;
	}

	if (first.x * second.y != first.y * second.x)
	{
		return false;
	}
	if (first.x * second.z != first.z * second.x) 
	{
		return false;
	}
	if (first.y * second.z != first.z * second.y)
	{
		return false;
	}

	return true;
}
ThreeVector sumOfVectors(ThreeVector first, ThreeVector second)
{
	ThreeVector result;
	result.x = first.x + second.x;
	result.y = first.y + second.y;
	result.z = first.z + second.z;
	return result;
}
void PrintCoordinates(ThreeVector result)
{
	std::cout << "v = {" << result.x << " , " << result.y << " , " << result.z << " }";
	newLine();
}

void newLine()
{
	std::cout<<std::endl;
}