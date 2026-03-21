#include <iostream>
#include "City.h"
#include "Person.h"

int main()
{
    Person person("Smolqn", 27000, 20, BROWN);
    City city1("Sofia", 1000000);
    City city2 = city1;
    City city3("Plovdiv", 350000);
    city3 = city1;
}
