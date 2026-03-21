#include <iostream>

const int TEACHERS_COUNT = 3;

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

struct University
{
    FMITeacher teachers[TEACHERS_COUNT];
    double averageNotPassed;
};

void mySwap(FMITeacher& a, FMITeacher& b);
Degree readDegree(int x);
void createUniversity(University& uni);
int bonusCount(const University& uni, long long minKvota);
void sortTeachers(University& uni);

int main()
{
    University uni;

    std::cout << "Enter teachers (id degree(0-2) notPassed):" << std::endl;
    createUniversity(uni);

    std::cout << "Average not passed: "
        << uni.averageNotPassed << std::endl;

    long long minKvota;
    std::cout << "Enter minimum kvota: ";
    std::cin >> minKvota;

    int bonus = bonusCount(uni, minKvota);
    std::cout << "Teachers with bonus: " << bonus << std::endl;

    sortTeachers(uni);

    std::cout << "Sorted teachers (by not passed):" << std::endl;
    for (int i = 0; i < TEACHERS_COUNT; i++)
    {
        std::cout << uni.teachers[i].id << " "
            << uni.teachers[i].notPassedStudents
            << std::endl;
    }

    return 0;
}

Degree readDegree(int x)
{
    switch (x)
    {
    case 0: 
        return Degree::BACHELOR;
    case 1: 
        return Degree::MASTER;
    case 2: 
        return Degree::DOCTOR;
    default: 
        return Degree::BACHELOR;
    }
}

void createUniversity(University& uni)
{
    long long sum = 0;

    for (int i = 0; i < TEACHERS_COUNT; i++)
    {
        int id, degreeInput;
        long long notPassed;

        std::cin >> id >> degreeInput >> notPassed;

        uni.teachers[i].id = id;
        uni.teachers[i].degree = readDegree(degreeInput);
        uni.teachers[i].notPassedStudents = notPassed;

        sum += notPassed;
    }

    uni.averageNotPassed = (double)sum / TEACHERS_COUNT;
}

int bonusCount(const University& uni, long long minKvota)
{
    int count = 0;

    for (int i = 0; i < TEACHERS_COUNT; i++)
    {
        if (uni.teachers[i].notPassedStudents >= minKvota)
        {
            count++;
        }
    }

    return count;
}

void mySwap(FMITeacher& a, FMITeacher& b)
{
    FMITeacher temp = a;
    a = b;
    b = temp;
}

void sortTeachers(University& uni)
{
    for (int i = 0; i < TEACHERS_COUNT - 1; i++)
    {
        for (int j = i + 1; j < TEACHERS_COUNT; j++)
        {
            if (uni.teachers[i].notPassedStudents >
                uni.teachers[j].notPassedStudents)
            {
                mySwap(uni.teachers[i], uni.teachers[j]);
            }
        }
    }
}