#pragma once
#include <string>
#include <memory>

class Apartment;

class Tennant
{
private:
    std::string firstName;
    std::string lastName;
    std::shared_ptr<Apartment> residence;

public:
    Tennant(std::string firstName, std::string lastName, std::shared_ptr<Apartment> residence);
    void setFirstName(std::string firstName);
    std::string getFirstName() const;
    void setLastName(std::string lastName);
    std::string getLastName() const;
    void changeResidence(std::shared_ptr<Apartment> newResidence);
};