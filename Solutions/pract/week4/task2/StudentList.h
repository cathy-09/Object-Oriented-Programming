#pragma once
#include <string>
class StudentList
{
private:
    std::string* studentsNames;
    int studentsCount;
    int maxCapacity;

    void copyFrom(const StudentList& other);
    void free();

public:
    StudentList();

    StudentList(const StudentList& other);

    StudentList& operator=(const StudentList& other);

    ~StudentList();

    void print() const;

    void addStudent(const std::string& name);

    void setStudent(int index, const std::string& name);
};

