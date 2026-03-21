#include <iostream>

class User
{
private:
    char username[31];
    char password[16];

public:
    User(const char* name, const char* pass)
    {
        strcpy(username, name);
        username[30] = '\0';
        strcpy(password, pass);
        password[15] = '\0';
    }

    void setPassword(const char* newPassword)
    {
        int len = strlen(newPassword);
        if (len < 8 || len > 15)
        {
            std::cout << "Password length must be between 8 and 15 characters!" << std::endl;
            return;
        }

        bool hasUpper = false;
        bool hasDigit = false;

        for (int i = 0; i < len; i++)
        {
            if (isupper(newPassword[i]))
            {
                hasUpper = true;
            }
            if (isdigit(newPassword[i]))
            {
                hasDigit = true;
            }
        }

        if (!hasUpper || !hasDigit)
        {
            std::cout << "Password must contain at least one uppercase letter and one digit!" << std::endl;
            return;
        }

        strcpy(password, newPassword);
        password[15] = '\0';
    }

    bool checkPassword(const char* input) const
    {
        return strcmp(password, input) == 0;
    }
};

int main()
{
    User user("Ivan", "Test1234");

    user.setPassword("abc");
    user.setPassword("NewPass1");

    if (user.checkPassword("NewPass1"))
    {
        std::cout << "Correct password!" << std::endl;
    }
    else
    {
        std::cout << "Wrong password!" << std::endl;
    }
}