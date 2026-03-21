#include <iostream>

using std::cout;
class Point2D
{
private:
    double x;
    double y;

public:
    Point2D()
    {
        this->x = 0;
        this->y = 0;
    }
    Point2D(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    ~Point2D()
    {
    }
    void print() const
    {
        cout << "(" << x << ", " << y << ")";
    }
};

void newLine()
{
    cout << std::endl;
}

int main()
{
    Point2D point1;
    Point2D point2{ 1.1, 2.3 };
    point1.print();
    newLine();
    point2.print();
}