#include <iostream>
#include <string>
#include "account.h"
using namespace std;
int main() {
	Date date(2008, 11, 1);
	SavingsAccount sa1(date, "s00001", 0.015);
	SavingsAccount sa2(date, "s00002", 0.015);
	CreditAccount ca1(date, "c00001", 0.0005, 10000, 50);
	Account* accounts[] = { &sa1, &sa2, &ca1 };
	const int n = sizeof(accounts) / sizeof(Account*); // ָ�����͵ĸ���
	cout << "(d)-deposit,(w)-withdraw,(s)-show,(c)-change day,(n)-next month,(e)-eixt" << endl;
	char cmd;
	do {
		date.show();
		cout << "\ttotal:\t" << Account::getTotal() << "\tcommond>";
		int index, day; // �����˺�
		double amount;	// ��ȡ���ܶ�
		string desc;	// ������Ϣ
		int i;
		cin >> cmd;
		switch (cmd) {
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
			for (i = 0; i < n; ++i) {
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
			for (i = 0; i < n; i++) {
				accounts[i]->settle(date);
				cout << endl;
			}
			break;
		}
	}while (cmd != 'e');
	system("pause");
	return 0;
}

