# Решения

<hr style="border-width: 5px !important;">

## Задачи от седмица първа
`Да се създаде клас BankAccount, със следните полета и член-функции: 
полета:
owner - име на собственик (максимална дължина 50 символа)
balance (максимална дължина 50 символа)
член-функции:
deposit(amount) - Увеличава balance с amount. Ако amount ≤ 0 → извежда подходящо съобщение.
withdraw(amount) - Намалява balance с amount само ако balance >= amount. Ако amount ≤ 0 или amount > balance→ извежда подходящо съобщение.
getter за balance - Връща текущия баланс.`

`Решение:`
```cpp
#include <iostream>
#include <cstring>

class BankAccount
{
private:
	char owner[51];
	double balance;

public:
	BankAccount(const char* name, double initialBalance)
	{
		strcpy(owner, name);
		owner[50] = '\0';
		balance = initialBalance;
	}
	void deposit(double amount)
	{
		if (amount <= 0) 
		{
			std::cout << "Invalid deposit amount!" << std::endl;
		}
		else 
		{
			balance += amount;
		}
	}

	void withdraw(double amount) 
	{
		if (amount <= 0) 
		{
			std::cout << "Invalid withdraw amount!" << std::endl;
		}
		else if (amount > balance) 
		{
			std::cout << "Not enough balance!" << std::endl;
		}
		else 
		{
			balance -= amount;
		}
	}

	double getBalance() const 
	{
		return balance;
	}
};

int main()
{
	BankAccount accout("Ivan Ivanov", 1000);

	accout.deposit(200);
	accout.withdraw(500);

	std::cout << "Current balance: " << accout.getBalance() << std::endl;
}
```

<hr style="border-width: 5px !important;">
