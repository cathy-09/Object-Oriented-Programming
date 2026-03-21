#pragma once
#include <string>

class UserAccount
{
private:
    std::string username;
    int id;

    static int accountsCount;

public:
    UserAccount() = default;

    UserAccount(const std::string& username, int id);

    static int getAccountsCount();

    ~UserAccount() = default;

    UserAccount(const UserAccount&) = delete;
    UserAccount& operator=(const UserAccount&) = delete;
};

