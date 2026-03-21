#include <iostream>
#include <limits>

struct Student
{
    int facultyNumber;
    int year;
    double averageGrade;
};

Student initStudent()
{
    Student student;

    do
    {
        std::cout << "Enter faculty number: ";
        std::cin >> student.facultyNumber;
        if (student.facultyNumber < 10000 || student.facultyNumber > 99999)
        {
            std::cout << "Invalid faculty number! Must be 5 digits." << std::endl;
        }
    } while (student.facultyNumber < 10000 || student.facultyNumber > 99999);

    do
    {
        std::cout << "Enter year: ";
        std::cin >> student.year;
        if (student.year < 1 || student.year > 4)
        {
            std::cout << "Invalid year! Must be between 1 and 4." << std::endl;
        }
    } while (student.year < 1 || student.year > 4);

    do
    {
        std::cout << "Enter average grade: ";
        std::cin >> student.averageGrade;
        if (student.averageGrade < 0.0 || student.averageGrade > 6.0)
        {
            std::cout << "Invalid grade! Must be between 0.0 and 6.0." << std::endl;
        }
    } while (student.averageGrade < 0.0 || student.averageGrade > 6.0);

    return student;
}

void printStudent(const Student& s)
{
    std::cout << "Faculty number: " << s.facultyNumber << std::endl;
    std::cout << "Year: " << s.year << std::endl;
    std::cout << "Average grade: " << s.averageGrade << std::endl;
}

int main()
{
    Student student = initStudent();

    std::cout << std::endl << "Student info:" << std::endl;;
    printStudent(student);
}