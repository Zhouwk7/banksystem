#include "account.h"
#include <iostream>
using namespace std;

double SavingAccount::total = 0; // 定义时不需要 static 声明

SavingAccount::SavingAccount(const Date& date, const std::string id, const double rate) :
	id(id), accumulation(0), lastDate(date), rate(rate), balance(0) {
	date.show();
	cout << "\t#" << id << "\tis created!" << endl;
}
void SavingAccount::record(const Date& date, double amount, const std::string desc) {
	accumulation += balance * date.distance(lastDate);
	amount = floor(amount * 100 + 0.5) / 100; // floor 向下取整
	balance += amount;
	total += amount;
	lastDate = date; // 浅复制，如带有"指针变量"需要编写复制构造函数
	date.show();
	cout << "\t#"<< id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}
void SavingAccount::deposit(const Date& date, double amount, const std::string desc) {
	record(date, amount, desc);
}
void SavingAccount::withdraw(const Date& date, double amount, const std::string desc) {
	if (balance < amount) {
		cout << "Error: not enough money!" << endl;
	}
	else {
		record(date, -amount, desc);
	}
}
void SavingAccount::settle(const Date& date) {
	double interest = accumulate(date) * rate / 365;
	if (interest) {
		record(date, interest, "interest");
	}
	accumulation = 0;
}
void SavingAccount::show() const {
	cout << "#" << id << "\tbalance: " << balance;
}