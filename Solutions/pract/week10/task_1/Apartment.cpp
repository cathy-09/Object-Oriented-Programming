#include "Apartment.h"
#include <iostream>

Apartment::Apartment(std::string address, int numberOfRooms)
{
    setAddress(address);
    setNumberOfRooms(numberOfRooms);
}

void Apartment::setAddress(std::string address)
{
    if (address.empty())
    {
        std::cout << "Empty";
        return;
    }
    this->address = address;
}

std::string Apartment::getAddress() const
{
    return address;
}

void Apartment::setNumberOfRooms(int numberOfRooms)
{
    if (numberOfRooms <= 0)
    {
        std::cout << "Invalid rooms number!";
        return;
    }
    this->numberOfRooms = numberOfRooms;
}

int Apartment::getNumberOfRooms() const
{
    return numberOfRooms;
}

void Apartment::addPerson(Tennant* person)
{
    people.push_back(person);
}

int Apartment::getPeopleCount() const
{
    return people.size();
}