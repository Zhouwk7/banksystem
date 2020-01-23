#include<iostream>
#include "account.h"
//using namespace std;


int main() {
	Date date(2018, 11, 5);
	SavingAccount accounts[] = {
		SavingAccount(date, "s0001", 0.015),
		SavingAccount(date, "s0002", 0.015) };
	const int n = sizeof(accounts) / sizeof(SavingAccount);
	accounts[0].deposit(Date(2018, 11, 5), 5000, "salary");
	accounts[1].deposit(Date(2018, 11, 25), 10000, "sell the stock 0330");
	accounts[0].deposit(Date(2018, 12, 5), 5500, "salary");
	accounts[1].withdraw(Date(2018, 12, 20), 4000, "buy a laptop");

	for (int i = 0; i < n; i++) {
		accounts[i].settle(Date(2019, 1, 1));
		accounts[i].show();
		std::cout << std::endl;
	}
	std::cout << "totalMoney: " << SavingAccount::getTotal() << std::endl;
	system("pause");
	return 0;
}
