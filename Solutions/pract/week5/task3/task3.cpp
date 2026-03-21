#include <iostream>
#include "MyString.h"
using namespace std;

int main() {
    MyString myString("hello");
    myString.print();

    myString.toUpper();
    cout << "Upper: "; 
    myString.print();

    myString.toLower();
    cout << "Lower: "; 
    myString.print();

    myString.setAt(0, 'H');
    cout << "setAt: ";
    myString.print();

    cout << "Find 'e': " << myString.find('e') << endl;

    myString.insert(1, 'X');
    cout << "Insert: ";
    myString.print();

    myString.erase(1);
    cout << "Erase: ";
    myString.print();

    myString.append("!!!");
    cout << "Append: "; 
    myString.print();

    myString.clear();
    cout << "Clear: "; 
    myString.print();

    MyString string2("test");
    MyString string3 = string2;
    string3.print();
    MyString string4("abc");
    string4 = string2;
    cout << "Assign: "; 
    string4.print();
}