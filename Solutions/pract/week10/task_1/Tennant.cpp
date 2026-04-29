#include "Tennant.h"
#include "Apartment.h"
#include <iostream>

Tennant::Tennant(std::string firstName, std::string lastName, std::shared_ptr<Apartment> residence)
{
    setFirstName(firstName);
    setLastName(lastName);
    this->residence = residence;
    if (this->residence)
    {
        this->residence->addPerson(this);
    }
}

void Tennant::setFirstName(std::string firstName)
{
    if (firstName.empty())
    {
        std::cout << "Empty";
        return;
    }
    this->firstName = firstName;
}

std::string Tennant::getFirstName() const
{
    return firstName;
}

void Tennant::setLastName(std::string lastName)
{
    if (lastName.empty())
    {
        std::cout << "Empty";
        return;
    }
    this->lastName = lastName;
}

std::string Tennant::getLastName() const
{
    return lastName;
}

void Tennant::changeResidence(std::shared_ptr<Apartment> newResidence)
{
    residence = newResidence;
    if (newResidence)
    {
        newResidence->addPerson(this);
    }
}