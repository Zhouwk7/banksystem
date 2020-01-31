#include <iostream>
#include <string>
#include "array.h"
#include "account.h"
using namespace std;
int main() {
	Date date(2008, 11, 1);
	//SavingsAccount sa1(date, "s00001", 0.015);
	//SavingsAccount sa2(date, "s00002", 0.015);
	//CreditAccount ca1(date, "c00001", 0.0005, 10000, 50);
	//Account* accounts[] = { &sa1, &sa2, &ca1 };
	//const int n = sizeof(accounts) / sizeof(Account*); // 指针类型的个数
	Array<Account*> accounts(0);
	cout << "(a)-add acount,(d)-deposit,(w)-withdraw,(s)-show,(c)-change day,(n)-next month,(e)-eixt" << endl;
	char cmd;
	do {
		date.show();
		cout << "\ttotal:\t" << Account::getTotal() << "\tcommond>";
		int index, day; // 索引账号
		double amount;	// 存取款总额
		string desc;	// 描述信息
		int i;
		char type;
		string id;
		double rate;
		double credit;
		double fee;
		Account* account;
		
		cin >> cmd;
		switch (cmd) {
		case 'a':
			cin >> type >> id;
			if (type == 's') {
				cin >> rate;
				account = new SavingsAccount(date, id, rate);
			}
			else {
				cin >> credit >> rate >> fee;
				account = new CreditAccount(date, id, rate, credit, fee);
			}
			accounts.reSize(accounts.getSize() + 1);
			accounts[accounts.getSize() - 1] = account;
			break;
		case 'd':
			cin >> index >> amount;
			getline(cin, desc);
			accounts[index]->deposit(date, amount, desc);
			break;
		case 'w':
			cin >> index >> amount;
			getline(cin, desc);
			accounts[index]->withdraw(date, amount, desc);
			break;
		case 's':
			for (i = 0; i < accounts.getSize(); ++i) {
				cout << "[" << i << "]";
				accounts[i]->show();
				cout << endl;
			}
				break;
		case 'c':
			cin >> day;
			if (day < date.getDay()) {
				cout << "You cannot specify a previous day!" << endl;
			}
			else if (day > date.getMaxDays()) {
				cout << "Invailable day!" << endl;
			}
			else {
				date = Date(date.getYear(), date.getMonth(), day);
			}
			break;
		case 'n':
			if (date.getMonth() == 12) {
				date = Date(date.getYear() + 1, 1, 1);
			}
			else {
				date = Date(date.getYear(), date.getMonth() + 1, 1);
			}
			for (i = 0; i < accounts.getSize(); i++) {
				accounts[i]->settle(date);
				cout << endl;
			}
			break;
		}
	}while (cmd != 'e');
	system("pause");
	return 0;
}

