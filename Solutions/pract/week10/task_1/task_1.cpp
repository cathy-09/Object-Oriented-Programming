#include <iostream>
#include "Apartment.h"
#include "Tennant.h"

int main()
{
    std::shared_ptr<Apartment> a1 = std::make_shared<Apartment>("Sofia Center", 3);
    Tennant t1("Ivan", "Ivanov", a1);
    Tennant t2("Maria", "Petrova", a1);
    std::cout << "People in apartment: " << a1->getPeopleCount() << std::endl;
    std::shared_ptr<Apartment> a2 = std::make_shared<Apartment>("Plovdiv", 2);
    t1.changeResidence(a2);
    std::cout << "People in new apartment: " << a2->getPeopleCount() << std::endl;
}