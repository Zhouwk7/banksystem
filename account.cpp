#include "account.h"
#include <iostream>
using namespace std;

double SavingAccount::total = 0;

SavingAccount::SavingAccount(int date, int id, double rate) :
	id(id), accumulation(0), lastDate(date), rate(rate), balance(0) {
	cout << date << "\t#" << id << "\tis created!" << endl;
}
void SavingAccount::record(int date, double amount) {
	accumulation += balance * (date - lastDate);
	balance += amount;
	total += amount;
	lastDate = date;
	cout << "balance " << balance << endl;
}
void SavingAccount::deposit(int date, double amount) {
	record(date, amount);
}
void SavingAccount::withdraw(int date, double amount) {
	if (balance < amount) {
		cout << "Error: not enough money!" << endl;
	}
	else {
		record(date, -amount);
	}
}
void SavingAccount::settle(int date) {
	double interest = accumulate(date) * rate / 365;
	if (interest) {
		record(date, interest);
	}
	accumulation = 0;
}
void SavingAccount::show() const {
	cout << lastDate << "\t#" << id << "\t" << balance << endl;
}