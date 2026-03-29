#include <iostream>
#include "Temperature.h"

int main()
{
	Temperature t1(100, 'c'); //212
	Temperature t2(212, 'f'); //100

	std::cout << "t1: " << t1.getTemperature() << t1.getSystem() << std::endl;
	std::cout << "t2: " << t2.getTemperature() << t2.getSystem() << std::endl;

	if (t1 == t2)
	{
		std::cout << "t1 == t2: t" << std::endl;
	}
	else
	{
		std::cout << "t1 == t2: f" << std::endl;
	}

	if (t1 != t2)
	{
		std::cout << "t1 != t2: t" << std::endl;
	}
	else
	{
		std::cout << "t1 != t2: f" << std::endl;
	}

	Temperature t3(0, 'c'); // 0
	Temperature t4(50, 'f'); //10
	if (t3 < t4)
	{
		std::cout << "t3 < t4: t" << std::endl;
	}
	else
	{
		std::cout << "t3 < t4: f" << std::endl;
	}

	if (t3 > t4)
	{
		std::cout << "t3 > t4: t" << std::endl;
	}
	else
	{
		std::cout << "t3 > t4: f" << std::endl;
	}

	Temperature sum = t1 + t3; // 100 + 0 = 100
	std::cout << "t1 + t3:  " << sum.getTemperature() << sum.getSystem() << std::endl;

	Temperature t5(32, 'f'); // 0
	Temperature t6(20, 'c'); // 20
	t5 += t6; // 20°C
	std::cout << "t5 += t6: " << t5.getTemperature() << t5.getSystem() << std::endl; // 68f

	Temperature bad(25, 'x');
	std::cout << "WTF IS THAT system? I set it to default: " << bad.getSystem() << std::endl;
}
