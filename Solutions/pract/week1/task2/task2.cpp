#include <iostream>

enum class Degree
{
    BACHELOR,
    MASTER,
    DOCTOR
};

struct FMITeacher
{
    int id;
    Degree degree;
    long long notPassedStudents;
};

bool createTeacher(FMITeacher& teacher, int id, Degree degree, long long notPassedStudents);
void printDegree(Degree degree);
void printTeacher(const FMITeacher& teacher);

int main()
{
    FMITeacher teacher;

    int id;
    int degreeInput;
    long long notPassed;

    std::cout << "Enter ID: ";
    std::cin >> id;

    std::cout << "Enter degree: ";
    std::cin >> degreeInput;

    std::cout << "Enter not passed students: ";
    std::cin >> notPassed;

    Degree degree;

    switch (degreeInput)
    {
    case 0: 
        degree = Degree::BACHELOR; 
        break;
    case 1: 
        degree = Degree::MASTER; 
        break;
    case 2: 
        degree = Degree::DOCTOR; 
        break;
    default:
        std::cout << "Invalid degree." << std::endl;
    }

    if (createTeacher(teacher, id, degree, notPassed))
    {
        printTeacher(teacher);
    }
}

bool createTeacher(FMITeacher& teacher, int id, Degree degree, long long notPassedStudents)
{
    if (id < 10000 || id > 99999)
    {
        std::cout << "Invalid ID." << std::endl;
        return false;
    }

    if (notPassedStudents < 0)
    {
        std::cout << "Not passed students cannot be negative." << std::endl;
        return false;
    }

    teacher.id = id;
    teacher.degree = degree;
    teacher.notPassedStudents = notPassedStudents;

    return true;
}

void printDegree(Degree degree)
{
    switch (degree)
    {
    case Degree::BACHELOR: 
        std::cout << "Bachelor"; 
        break;
    case Degree::MASTER: 
        std::cout << "Master"; 
        break;
    case Degree::DOCTOR: 
        std::cout << "Doctor"; 
        break;
    }
}

void printTeacher(const FMITeacher& teacher)
{
    std::cout << "ID: " << teacher.id << std::endl;
    std::cout << "Degree: ";
    printDegree(teacher.degree);
    std::cout << std::endl;
    std::cout << "Not passed students: " << teacher.notPassedStudents << std::endl;
}