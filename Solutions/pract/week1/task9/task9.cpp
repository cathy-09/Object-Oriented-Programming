#include <iostream>
#include <cstring>

const int MAX_QUESTIONS = 3;
const int MAX_STR = 51;

struct Question
{
    char title[MAX_STR];
    char answers[4][MAX_STR]; 
    char correctAnswer;
    int points;
};

struct Test
{
    Question questions[MAX_QUESTIONS];
};

Question initQuestion(const char* title,
    const char* ansA,
    const char* ansB, 
    const char* ansC,
    const char* ansD,
    char correct,
    int points)
{
    Question q;
    std::strcpy(q.title, title);
    std::strcpy(q.answers[0], ansA);
    std::strcpy(q.answers[1], ansB);
    std::strcpy(q.answers[2], ansC);
    std::strcpy(q.answers[3], ansD);
    q.correctAnswer = correct;
    q.points = points;
    return q;
}

int runTest(const Test& t)
{
    int totalPoints = 0;
    char userAnswer;

    for (int i = 0; i < MAX_QUESTIONS; i++)
    {
        std::cout << std::endl << "Question " << (i + 1) << ": " << t.questions[i].title << std::endl;
        std::cout << "A) " << t.questions[i].answers[0] << std::endl;
        std::cout << "B) " << t.questions[i].answers[1] << std::endl;
        std::cout << "C) " << t.questions[i].answers[2] << std::endl;
        std::cout << "D) " << t.questions[i].answers[3] << std::endl;

        do
        {
            std::cout << "Enter your answer: ";
            std::cin >> userAnswer;
            userAnswer = toupper(userAnswer);
            if (userAnswer != 'A' && userAnswer != 'B' && userAnswer != 'C' && userAnswer != 'D')
            {
                std::cout << "Invalid answer! Try again." << std::endl;
            }
        } while (userAnswer != 'A' && userAnswer != 'B' && userAnswer != 'C' && userAnswer != 'D');

        if (userAnswer == t.questions[i].correctAnswer)
        {
            std::cout << "Correct! +" << t.questions[i].points << " points." << std::endl;
            totalPoints += t.questions[i].points;
        }
        else
        {
            std::cout << "Wrong! Correct answer: " << t.questions[i].correctAnswer << std::endl;
        }
    }

    return totalPoints;
}

int main()
{
    Test t;

    t.questions[0] = initQuestion(
        "What is the capital of France?",
        "Paris", "London", "Berlin", "Rome",
        'A', 5);

    t.questions[1] = initQuestion(
        "2 + 2 = ?",
        "3", "4", "5", "6",
        'B', 3);

    t.questions[2] = initQuestion(
        "Which language is this program written in?",
        "Python", "C#", "C++", "Java",
        'C', 4);

    std::cout << "Starting the test..." << std::endl;

    int score = runTest(t);

    std::cout << std::endl << "Test finished. Total points: " << score << std::endl;

    return 0;
}