#include <iostream>

class Counter
{
private:
    int value;
    mutable int accessCount;

public:
    Counter()
    {
        value = 0;
        accessCount = 0;
    }

    void increment()
    {
        value++;
    }

    int getValue() const
    {
        accessCount++;
        return value;
    }

    int getAccessCount() const
    {
        return accessCount;
    }
};

int main()
{
    Counter c;

    c.increment();
    c.increment();

    std::cout << c.getValue() << std::endl;
    std::cout << c.getValue() << std::endl;

    std::cout << "Access count: " << c.getAccessCount() << std::endl;

    return 0;
}