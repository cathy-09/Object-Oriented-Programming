#include <iostream>

//strcry_s
void newLine();
class Message
{
private:
    char* text;

public:
    Message()
    {
        text = new char[8];
        strcpy_s(text, 8, "no_text");
    }
    Message(const char* newText)
    {
        text = new char[strlen(newText) + 1];
        strcpy_s(text, (strlen(newText) + 1), newText);
    }
    ~Message()
    {
        delete[] text;
    }
    void print() const
    {
        std::cout << text;
        newLine();
    }
};
void newLine()
{
    std::cout << std::endl;
}
int main()
{
    Message message1;
    Message message2{ "Hello" };
    message1.print();
    message2.print();
}
