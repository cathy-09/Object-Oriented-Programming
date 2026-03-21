#include <iostream>

class ExamResult
{
private:
    int score;
    mutable int timesChecked;
    mutable int lastReturnedGrade;

public:
    ExamResult()
    {
        score = 0;
        timesChecked = 0;
        lastReturnedGrade = 2;
    }

    void setScore(int newScore)
    {
        if (newScore < 0 || newScore > 100)
        {
            std::cout << "Invalid score!" << std::endl;
        }
        else
        {
            score = newScore;
        }
    }

    int getGrade() const
    {
        int grade;

        if (score <= 49)
        {
            grade = 2;
        }
        else if (score <= 59)
        {
            grade = 3;
        }
        else if (score <= 69)
        {
            grade = 4;
        }
        else if (score <= 84)
        {
            grade = 5;
        }
        else
        {
            grade = 6;
        }

        timesChecked++;
        lastReturnedGrade = grade;

        return grade;
    }

    int getTimesChecked() const
    {
        return timesChecked;
    }

    int getLastReturnedGrade() const
    {
        return lastReturnedGrade;
    }
};

int main()
{
    ExamResult exam;

    exam.setScore(78);

    std::cout << "Grade: " << exam.getGrade() << std::endl;
    std::cout << "Grade: " << exam.getGrade() << std::endl;

    std::cout << "Times checked: " << exam.getTimesChecked() << std::endl;
    std::cout << "Last grade: " << exam.getLastReturnedGrade() << std::endl;

    return 0;
}