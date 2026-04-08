#include <iostream>
#include "Cipher.h"

int main()
{
    Cipher c1("hello world");
    std::cout << "Original : " << c1.getText() << "\n";
    std::cout << "Encrypted: " << c1.encrypt() << "\n\n";
    Cipher c2("abc123 XYZ");
    std::cout << "Original : " << c2.getText() << "\n";
    std::cout << "Encrypted: " << c2.encrypt() << "\n\n";
    Cipher c3("one two three four");
    std::cout << "Words in " << c3.getText() << "\n";
    for (int i = 0; i < 4; ++i) 
    {
        std::cout << "  [" << i << "] = " << c3[i] << "\n";
    }
    std::cout << "\n";
    Cipher c4("good morning");
    Cipher c5("everyone");
    Cipher c6 = c4 + c5;
    std::cout << "c4 + c5  = " << c6.getText() << "\n";
    std::cout << "encrypted: " << c6.encrypt() << "\n\n";
    c4 += c5;
    std::cout << "c4 += c5 = " << c4.getText() << "\n\n";
}