#include<iostream>
#include "account.h"
using namespace std;


int main() {
	SavingAccount s0(1, 10001, 0.015);
	SavingAccount s1(1, 10002, 0.015);

	s0.deposit(5, 5000);
	s1.deposit(25, 10000);
	s0.deposit(45, 5500);
	s1.withdraw(60, 4000);
	s0.settle(90);
	s1.settle(90);
	s0.show();
	s1.show();
	double totalMoney = SavingAccount::getTotal();
	cout << "totalMoney: " << totalMoney << endl;
	system("pause");
	return 0;
}
