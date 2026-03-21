#include "StudentList.h"
#include <iostream>

void StudentList::copyFrom(const StudentList& other)
{
    maxCapacity = other.maxCapacity;
    studentsCount = other.studentsCount;

    studentsNames = new std::string[maxCapacity];

    for (int i = 0; i < studentsCount; i++)
    {
        studentsNames[i] = other.studentsNames[i];
    }
}

void StudentList::free()
{
    delete[] studentsNames;
}

StudentList::StudentList()
{
    maxCapacity = 10;
    studentsCount = 0;
    studentsNames = new std::string[maxCapacity];
}

StudentList::StudentList(const StudentList& other)
{
    copyFrom(other);
}

StudentList& StudentList::operator=(const StudentList& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

StudentList::~StudentList()
{
    free();
}

void StudentList::print() const
{
    for (int i = 0; i < studentsCount; i++)
    {
        std::cout << studentsNames[i] << std::endl;
    }
}

void StudentList::addStudent(const std::string& name)
{
    if (studentsCount < maxCapacity)
    {
        studentsNames[studentsCount] = name;
        studentsCount++;
    }
}

void StudentList::setStudent(int index, const std::string& name)
{
    if (index >= 0 && index < studentsCount)
    {
        studentsNames[index] = name;
    }
}
