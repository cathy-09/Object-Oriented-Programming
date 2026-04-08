#pragma once
#include <string>
#include "Calculator.h"
class User
{
private:
    int id;
    std::string username;
    std::string password;
    Calculator* calc;
    static int nextId;

public:
    User(const std::string& username, const std::string& password);
    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    Calculator* getCalculator() const;
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
};

