# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица първа
`Задача 1: Да се създаде структура, която представя тримерен вектор с целочислени координати. Създайте функция, която събира два вектора и връща нов вектор. Създайте функция, която отпечатва координатите на даден вектор. Създайте функция, която приема като аргументи 2 вектора и проверява дали те са линейно зависими.`

`Решение 1:`
```cpp
#include <iostream>
#include <cmath>
struct ThreeVector
{
	int x;
	int y;
	int z;
};
ThreeVector sumOfVectors(ThreeVector first, ThreeVector second);
void newLine();
void PrintCoordinates(ThreeVector result);
bool isLZ(ThreeVector first, ThreeVector second);


int main()
{
	ThreeVector first;
	ThreeVector second;
	ThreeVector result;
	std::cin >> first.x >> first.y >> first.z;
	std::cin >> second.x >> second.y >> second.z;
	result = sumOfVectors(first, second);
	PrintCoordinates(result);
	bool isLZVectors = isLZ(first, second);
	std::cout << isLZVectors;
}
bool isLZ(ThreeVector first, ThreeVector second)
{
	if ((first.x == 0 && first.y == 0 && first.z == 0) ||
		(second.x == 0 && second.y == 0 && second.z == 0))
	{
		return true;
	}

	if (first.x * second.y != first.y * second.x)
	{
		return false;
	}
	if (first.x * second.z != first.z * second.x) 
	{
		return false;
	}
	if (first.y * second.z != first.z * second.y)
	{
		return false;
	}

	return true;
}
ThreeVector sumOfVectors(ThreeVector first, ThreeVector second)
{
	ThreeVector result;
	result.x = first.x + second.x;
	result.y = first.y + second.y;
	result.z = first.z + second.z;
	return result;
}
void PrintCoordinates(ThreeVector result)
{
	std::cout << "v = {" << result.x << " , " << result.y << " , " << result.z << " }";
	newLine();
}

void newLine()
{
	std::cout<<std::endl;

```

<hr style="border-width: 5px !important;">

`Задача 2: Всеки преподавател във ФМИ се определя чрез идентификационен номер, образователна степен (бакалавър, магистър, доктор), брой скъсани студенти. Използвайте изброен тип за образователната степен.Идентификационните номера са винаги петцифрени цели числа. Създайте структура описваща преподавател. Създайте функция, която приема като аргументи данни, описващи преподавател. Ако данните са валидни, то функцията инициализира преподавател, в противен случай отпечатва подходящо съобщение. Да се напише функция, която принтира преподавател. Може да използвате помощни функции.`

`Решение:`
```cpp
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
```

<hr style="border-width: 5px !important;">

`Задача 3: Един университет се състои от краен брой преподаватели. Броят на преподавателите се задава от вас (НЕ се въвежда от входа). Създайте структура, която описва университет. Структурата също така трябва да пази средния брой скъсани студенти на преподавателите в университета. Направете функция, която създава университет, вземайки информация от стандартния вход. Средният брой скъсани студенти трябва да се сметне след въвеждане на информацията. Напишете функция, която приема университет и минимален брой скъсани студенти по договор, и връща колко преподаватели са изпълнили квотата си и съответно ще получат бонус. Напишете функция, която сортира преподавателите във възходящ ред спрямо броят студенти, които са скъсали.`

`Решение:`
```cpp
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
```

<hr style="border-width: 5px !important;">

`Задача 4: Един връх в граф ще описваме чрез етикета във върха, а именно символен низ с дължина максимум 10 символа. 1. Дефинирайте структура, която описва насочено ребро между два върха. 2. Граф дефинираме чрез броят на върховете му, броя на ребрата му и списък на ребрата. Дефинирайте структура, която описва граф с произволен брой ребра. 3. Създайте функция, която инициализира граф с m ребра. Броят на ребрата се прочита от стандартния вход. 4. Създайте функция, която приема два върха в граф и добавя ребро между двата върха в графа. Приемаме, че реброто е от първия връх към втория. 5. На стандартния вход ви се подават m на брой двойки етикети на върхове. Създайте функция, която обработва гореописания вход и създава граф. 6. Създайте функция, която по подаден връх от граф и граф, намира степента на върха в графа. 7. Създайте функция, която проверява дали граф е пълен. (Граф е пълен, ако всеки връх е свързан с всички останали върхове, считаме че в графа няма примки) 8. Създайте функция, която по дадено ребро и граф, изтрива реброто в графа. Ако подаденото като аргумент ребро не съществува в графа, извежда подходящо съобщение`

`Решение:`
```cpp
#include <iostream>
#include <cstring>

const int MAX_LABEL = 11;

struct Edge
{
    char from[MAX_LABEL];
    char to[MAX_LABEL];
};

struct Graph
{
    int verticesCount;
    int edgesCount;
    int capacity;
    Edge* edges;
};

void initGraph(Graph& g, int m)
{
    g.edgesCount = 0;
    g.capacity = m;
    g.verticesCount = 0;
    g.edges = new Edge[m];
}

bool edgeExists(const Graph& g, const char* from, const char* to)
{
    for (int i = 0; i < g.edgesCount; i++)
    {
        if (strcmp(g.edges[i].from, from) == 0 &&
            strcmp(g.edges[i].to, to) == 0)
            return true;
    }
    return false;
}

void addEdge(Graph& g, const char* from, const char* to)
{
    if (g.edgesCount >= g.capacity)
        return;

    strcpy(g.edges[g.edgesCount].from, from);
    strcpy(g.edges[g.edgesCount].to, to);
    g.edgesCount++;
}

void createGraph(Graph& g, int m)
{
    initGraph(g, m);

    char from[MAX_LABEL];
    char to[MAX_LABEL];

    for (int i = 0; i < m; i++)
    {
        std::cin >> from >> to;
        addEdge(g, from, to);
    }
}

int degree(const Graph& g, const char* vertex)
{
    int count = 0;

    for (int i = 0; i < g.edgesCount; i++)
    {
        if (strcmp(g.edges[i].from, vertex) == 0)
            count++;
    }

    return count;
}

bool isComplete(const Graph& g)
{
    for (int i = 0; i < g.edgesCount; i++)
    {
        for (int j = 0; j < g.edgesCount; j++)
        {
            if (strcmp(g.edges[i].from, g.edges[j].to) != 0 &&
                !edgeExists(g, g.edges[i].from, g.edges[j].to))
                return false;
        }
    }
    return true;
}

void removeEdge(Graph& g, const char* from, const char* to)
{
    for (int i = 0; i < g.edgesCount; i++)
    {
        if (strcmp(g.edges[i].from, from) == 0 &&
            strcmp(g.edges[i].to, to) == 0)
        {
            for (int j = i; j < g.edgesCount - 1; j++)
            {
                g.edges[j] = g.edges[j + 1];
            }
            g.edgesCount--;
            std::cout << "Edge removed.\n";
            return;
        }
    }

    std::cout << "Edge does not exist.\n";
}

int main()
{
    int m;
    std::cout << "Enter number of edges: ";
    std::cin >> m;

    Graph g;
    createGraph(g, m);

    char vertex[MAX_LABEL];
    std::cout << "Enter vertex to check degree: ";
    std::cin >> vertex;

    std::cout << "Degree: " << degree(g, vertex) << std::endl;

    std::cout << "Is complete: "
        << (isComplete(g) ? "Yes" : "No")
        << std::endl;

    char from[MAX_LABEL], to[MAX_LABEL];
    std::cout << "Enter edge to remove (from to): ";
    std::cin >> from >> to;

    removeEdge(g, from, to);

    delete[] g.edges;

    return 0;
}
```

<hr style="border-width: 5px !important;">

`Задача 5: Да се създаде структура Book със следните характеристики: заглавие (до 50 символа) , автор (до 50 символа), жанр и наличност. Жанровете са ограничени и могат да бъдат "Роман", "Исторически", "Поезия" и "Друг". Да се създаде структура Libary, която се описва с константен брой книги (вие изберете този брой). Реализирайте функции за : инициализиране на книга; добавяне на нова книга в библиотеката (ако капацитетът е запълнен, да се изведе съобщение); вземане на книга по подадено заглавие; връщане на книга по подадено заглавие; извеждане на информация за всички книги в библиотеката.`

`Решение:`
```cpp
#include <iostream>
#include <cstring>

const int MAX_BOOKS = 5;
const int MAX_STR = 51;

enum class Genre
{
    ROMAN,
    HISTORICAL,
    POETRY,
    OTHER
};

struct Book
{
    char title[MAX_STR];
    char author[MAX_STR];
    Genre genre;
    bool available;
};

struct Library
{
    Book books[MAX_BOOKS];
    int count;
};

const char* genreToString(Genre genre)
{
    switch (genre)
    {
    case Genre::ROMAN: return "Roman";
    case Genre::HISTORICAL: return "Historical";
    case Genre::POETRY: return "Poetry";
    case Genre::OTHER: return "Other";
    default: return "Unknow";
    }
}

Book initBook(const char* title, const char* author, Genre genre)
{
    Book book;
    std::strcpy(book.title, title);
    std::strcpy(book.author, author);
    book.genre = genre;
    book.available = true;
    return book;
}

void addBook(Library& library, const Book& book)
{
    if (library.count >= MAX_BOOKS)
    {
        std::cout << "Library is full!" << std::endl;
        return;
    }
    library.books[library.count++] = book;
}

bool takeBook(Library& library, const char* title)
{
    for (int i = 0; i < library.count; i++)
    {
        if (strcmp(library.books[i].title, title) == 0)
        {
            if (library.books[i].available)
            {
                library.books[i].available = false;
                return true;
            }
            else
            {
                std::cout << "Книгата вече е взета!" << std::endl;
                return false;
            }
        }
    }
    std::cout << "Book with that title does not exist!";
    return false;
}

bool returnBook(Library& library, const char* title)
{
    for (int i = 0; i < library.count; i++)
    {
        if (strcmp(library.books[i].title, title) == 0)
        {
            if (!library.books[i].available)
            {
                library.books[i].available = true;
                return true;
            }
            else
            {
                std::cout << "The book is not available" << std::endl;
                return false;
            }
        }
    }
    std::cout << "Book with that title does not exist!" << std::endl;
    return false;
}

void printLibrary(const Library& library)
{
    for (int i = 0; i < library.count; i++)
    {
        std::cout << "Title: " << library.books[i].title << std::endl;
        std::cout << "Author: " << library.books[i].author << std::endl;
        std::cout << "Genre: " << genreToString(library.books[i].genre) << std::endl;
        std::cout << "Available: " << (library.books[i].available ? "Yes" : "No") << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
}

int main()
{
    Library library;
    library.count = 0;

    addBook(library, initBook("War and Peace", "Leo Tolstoy", Genre::ROMAN));
    addBook(library, initBook("Eugene Onegin", "Pushkin", Genre::POETRY));
    addBook(library, initBook("History of Bulgaria", "Ivan Vazov", Genre::HISTORICAL));
    printLibrary(library);
    takeBook(library, "War and Peace");
    printLibrary(library);
    returnBook(library, "War and Peace");
    printLibrary(library);
}
```

<hr style="border-width: 5px !important;">

`Задача 6: Създайте структура, описваща студент. Всеки студент се определя чрез: факултетен номер(петцифрени цели числа); курс (∀студент е в първи, втори, трети или четвърти курс); средна оценка за курса. Създайте подходящо параметризирана функция initStudent(...); която въвежда коректни данни за студент. Да се напише функция, която принтира студент. Може да използвате помощни функции.`

`Решение:`
```cpp
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
```

<hr style="border-width: 5px !important;">

`Задача 7: Една група се състои от краен брой студенти, като броят на студентите се задава от вас. Създайте структура, която описва група. Структурата също така трябва да пази средния успех на групата. Направете функция, която създава група, вземайки информация от стандартния вход. Средният успех трябва да се сметне след въвеждане на информацията. Напишете функция, която приема група и минимален успех за стипендия, и връща колко студента ще получават стипендия.`

`Решение:`
```cpp
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
    std::cout << std::endl <<"Group info (average success: " << g.averageSuccess << ")" << std::endl;
    std::cout << "------------------------" << std::endl;
    for (int i = 0; i < GROUP_SIZE; i++)
    {
        printStudent(g.students[i]);
    }
}

int main()
{
    Group group = createGroup();

    printGroup(group);

    double minGrade;
    std::cout << std::endl << "Enter minimum grade for scholarship: ";
    std::cin >> minGrade;

    int scholarship = scholarshipCount(group, minGrade);
    std::cout << "Number of students are approved for scholarship: " << scholarship << std::endl;
}
```

<hr style="border-width: 5px !important;">

`Задача 8:Създайте функция, която приема група и минимален успех за стипендия, и извежда сортирани низходящо по успех всички студенти, които ще получават стипендия идния семестър `

`Решение:`
```cpp
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
```

<hr style="border-width: 5px !important;">

`Да се напише програма, която симулира изпълнение на тест. Всеки тест представлява структура, съдържаща константен брой въпроси (вие изберете този брой). Всеки въпрос има заглавие (до 50 символа), четири възможни отговора, верен отговор (може да е A, B, C или D), и точки, които се дават за правилно отговорен въпрос. Всеки отговор съдържа символен низ с до 50 символа. Потребителят трябва да може да отговаря на въпросите, като избира една от четирите възможности. След като потребителят отговори на всички въпроси, програмата да извежда общия брой точки, които е спечелил потребителят. `

`Решение:`
```cpp
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
```

<hr style="border-width: 5px !important;">
