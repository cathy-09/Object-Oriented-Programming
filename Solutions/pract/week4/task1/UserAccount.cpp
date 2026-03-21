#include "UserAccount.h"

int UserAccount::accountsCount = 0;

UserAccount::UserAccount(const std::string& username, int id)
{
	this->username = username;
	this->id = id;

	accountsCount++;
}

int UserAccount::getAccountsCount()
{
	return accountsCount;
}
