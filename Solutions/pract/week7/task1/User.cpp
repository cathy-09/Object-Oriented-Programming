#include "User.h"
#include <iostream>
int User::nextId = 1;

User::User(const std::string& username, const std::string& password) 
{
    if (username.empty()) 
    {
        std::cout << "Username cannot be empty.";
        return;
    }
    if (password.empty()) {
        std::cout << "Password cannot be empty.";
        return;
    }
    this->id = nextId++;
    this->username = username;
    this->password = password;
    this->calc = Calculator::getInstance();
}

int User::getId() const 
{
    return id;
}

std::string User::getUsername() const 
{
    return username;
}

std::string User::getPassword() const 
{
    return password;
}

Calculator* User::getCalculator() const 
{
    return calc;
}

void User::setUsername(const std::string& username) 
{
    if (username.empty()) 
    {
        std::cout << "Username cannot be empty.";
        return;
    }
    this->username = username;
}

void User::setPassword(const std::string& password) 
{
    if (password.empty())
    {
        std::cout << ("Password cannot be empty.");
        return;
    }
    this->password = password;
}