#include <iostream>
#include <limits>

const int GROUP_SIZE = 3;

struct Student
{
    int facultyNumber;
    int year;
    double averageGrade;
};

void printStudent(const Student& s)
{
    std::cout << "Faculty number: " << s.facultyNumber << std::endl;
    std::cout << "Year: " << s.year << std::endl;
    std::cout << "Average grade: " << s.averageGrade << std::endl;
    std::cout << "---------------------" << std::endl;
}

struct Group
{
    Student students[GROUP_SIZE];
    double averageSuccess;
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

Group createGroup()
{
    Group group;
    double sum = 0.0;

    for (int i = 0; i < GROUP_SIZE; i++)
    {
        std::cout << std::endl << "Enter data for student " << (i + 1) << ":" << std::endl;
        group.students[i] = initStudent();
        sum += group.students[i].averageGrade;
    }

    group.averageSuccess = sum / GROUP_SIZE;
    return group;
}

int scholarshipCount(const Group& group, double minGrade)
{
    int count = 0;
    for (int i = 0; i < GROUP_SIZE; i++)
    {
        if (group.students[i].averageGrade >= minGrade)
            count++;
    }
    return count;
}

void printGroup(const Group& g)
{
    std::cout << std::endl << "Group info (average success: " << g.averageSuccess << ")" << std::endl;
    std::cout << "------------------------" << std::endl;
    for (int i = 0; i < GROUP_SIZE; i++)
    {
        printStudent(g.students[i]);
    }
}

void printScholarshipStudents(const Group& group, double minGrade)
{
    Student acepted[GROUP_SIZE];
    int count = 0;

    for (int i = 0; i < GROUP_SIZE; i++)
    {
        if (group.students[i].averageGrade >= minGrade)
        {
            acepted[count++] = group.students[i];
        }
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (acepted[i].averageGrade < acepted[j].averageGrade)
            {
                Student temp = acepted[i];
                acepted[i] = acepted[j];
                acepted[j] = temp;
            }
        }
    }

    std::cout << std::endl << "Students eligible for scholarship (sorted descending):" << std::endl;
    for (int i = 0; i < count; i++)
    {
        printStudent(acepted[i]);
    }
}

int main()
{
    Group g;
    g.students[0] = { 12345, 1, 5.50 };
    g.students[1] = { 23456, 2, 4.80 };
    g.students[2] = { 34567, 3, 5.90 };
    g.averageSuccess = (5.50 + 4.80 + 5.90) / 3;

    double minGrade;
    std::cout << "Enter minimum grade for scholarship: ";
    std::cin >> minGrade;

    printScholarshipStudents(g, minGrade);
}