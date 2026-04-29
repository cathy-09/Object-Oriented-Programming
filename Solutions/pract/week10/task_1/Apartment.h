#pragma once
#include <string>
#include <vector>

class Tennant;

class Apartment
{
    std::string address;
    int numberOfRooms;
    std::vector<Tennant*> people;

public:
    Apartment(std::string address, int numberOfRooms);
    void setAddress(std::string address);
    std::string getAddress() const;
    void setNumberOfRooms(int numberOfRooms);
    int getNumberOfRooms() const;
    void addPerson(Tennant* person);
    int getPeopleCount() const;
};