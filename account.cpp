#include "account.h"
#include <iostream>
using namespace std;
// �����˺Ż��ඨ��
double Account::total = 0; // ����ʱ����Ҫ static ����
Account::Account(const Date &date, const std::string &id) : id(id), balance(0) {
	date.show();
	cout << "\t#" << id << "\tis created!" << endl;
}
void Account::record(const Date &date, double amount, const std::string &desc) {
	amount = floor(amount * 100 + 0.5) / 100;
	balance += amount;
	total += amount;
	date.show();
	cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}
void Account::show() const {
	cout << "#" << id << "\tBalance:" << balance;
}

// �����˺ŷ�������
SavingsAccount::SavingsAccount(const Date &date, const std::string &id, const double rate) :
	Account(date,id), acc(date, 0), rate(rate) {}
void SavingsAccount::deposit(const Date &date, double amount, const std::string &desc) {
	record(date, amount, desc);
	acc.change(date, getBalance());
}
void SavingsAccount::withdraw(const Date &date, double amount, const std::string &desc) {
	if (getBalance() < amount) {
		// cout << "Error: not enough money!" << endl;
		error("not enough money!");
	}
	else {
		record(date, -amount, desc);
		acc.change(date, getBalance());
	}
}
void SavingsAccount::settle(const Date &date) {
	// double interest = acc.getSum(date) * rate / 365;
	double interest = acc.getSum(date) * rate / 
		date.distance(Date(date.getYear()-1,1,1));
	if (interest) {
		record(date, interest, "interest");
	}
	acc.rest(date, getBalance());
}

// ���ÿ��˺ŷ�������
CreditAccount::CreditAccount(const Date& date, const std::string& id,
	double credit, double rate, double fee) : Account(date, id),
	acc(date,0), credit(credit), rate(rate), fee(fee){ }
void CreditAccount::deposit(const Date& date, double amount, const std::string& desc) {
	record(date, amount, desc);
	acc.change(date, getDebt());
}
void CreditAccount::withdraw(const Date& date, double amount, const std::string& desc) {
	if (amount - getBalance() > credit) {
		error("not enough money!");
	}
	else {
		record(date, -amount, desc);
		acc.change(date, getDebt());
	}
}
void CreditAccount::settle(const Date& date){
	double interest = acc.getSum(date) * rate;
	if(interest) record(date, interest, "interest");
	if (date.getMonth() == 1) {
		record(date, -fee, "annual fee");
	}
	acc.rest(date, getDebt());
}
void CreditAccount::show() const {
	Account::show();
	cout << "\tAvailable credit: " << getAvaliableCredit() << endl;
}

