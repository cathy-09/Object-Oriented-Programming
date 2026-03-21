#include <iostream>

class Car
{
private:
    char brand[41];
    double fuel;
    double fuelCapacity;

public:
    Car(const char* b, double f, double capacity)
    {
        strcpy(brand, b);
        brand[40] = '\0';

        if (capacity > 0)
        {
            fuelCapacity = capacity;
        }
        else
        {
            fuelCapacity = 0;
        }

        if (f >= 0 && f <= fuelCapacity)
        {
            fuel = f;
        }
        else
        {
            fuel = 0;
        }
    }

    void refuel(double amount)
    {
        if (amount <= 0)
        {
            std::cout << "Invalid fuel amount!" << std::endl;
        }
        else if (fuel + amount > fuelCapacity)
        {
            std::cout << "Fuel exceeds capacity!" << std::endl;
        }
        else
        {
            fuel += amount;
        }
    }

    void drive(double km)
    {
        double neededFuel = km * 0.1;

        if (neededFuel > fuel)
        {
            std::cout << "Not enough fuel!" << std::endl;
        }
        else
        {
            fuel -= neededFuel;
        }
    }

    double getFuel() const
    {
        return fuel;
    }

    const char* getBrand() const
    {
        return brand;
    }
};

int main()
{
    Car car("BMW", 10, 50);

    car.drive(50);
    car.refuel(20);

    std::cout << "Brand: " << car.getBrand() << std::endl;
    std::cout << "Fuel: " << car.getFuel() << std::endl;

    return 0;
}