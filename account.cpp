#include "account.h"
// Account �����˻�����
double Account::total = 0;

Account::Account(const Date& date, const std::string& id) :id(id), balance(0) {
	date.show();
	std::cout << "\t#" << id << "\t is created!" << std::endl;
}

void Account::record(const Date& date, double amount, const std::string& desc) {
	amount = floor(amount * 100 + 0.5) / 100;
	balance += amount;
	total += amount;
	date.show();
	std::cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << std::endl;
}
void Account::error(const std::string& msg) const {
	std::cout << "error(#" << id << "):" << msg << std::endl;
}

// SavingsAccount
SavingsAccount::SavingsAccount(const Date& date, const std::string& id, double rate) : 
	Account(date,id), acc(date,0),rate(rate){
}
void SavingsAccount::deposit(const Date& date, double amount, const std::string& desc) {	
	record(date, amount, desc);
	acc.change(date, getBalance());
}
void SavingsAccount::withdraw(const Date& date, double amount, const std::string& desc) {
	if (amount > getBalance()) {
		error("Not enough money!");
		exit(1);
	}
	record(date, -amount, desc);
	acc.change(date, getBalance());
}
void SavingsAccount::settle(const Date& date) {
	double interest = acc.getSum(date) * rate / 
		(date - Date(date.getYear() - 1, date.getMonth(), date.getDay()));
	if (interest && date.getMonth()==1) {
		record(date, interest, "interest");
		acc.rest(date, getBalance());
	}
	
}
void SavingsAccount::show() const {
	std::cout << getId() << "\tbalance: " << getBalance() << std::endl;
}

// CreditAccount

void CreditAccount::deposit(const Date& date, double amount, const std::string& desc) {
	record(date, amount, desc);
	acc.change(date, getDebt()); // ���ÿ���ϢΪ������Ӧ��ʹ��getBalance()
}
void CreditAccount::withdraw(const Date& date, double amount, const std::string& desc) {
	if (credit < amount - getBalance()) { // ���ÿ�Ϊ��ʱ�����õĽ����� credit
		error("Not enough credit!");
		exit(1);
	}
	record(date, -amount, desc);
	acc.change(date, getDebt());
}
void CreditAccount::settle(const Date& date) {// ÿ�½���һ��
	double interest = acc.getSum(date) * rate; // �����ۼ���Ϣ���Ѿ�Ϊ��
	if (date.getDay() == 1) {
		if (interest) {
			record(date, interest, "interest");
		}
		if (date.getMonth() == 1) {
			record(date, -fee, "annual fee!");
		}
		acc.rest(date, getDebt());
	}
}
void CreditAccount::show() const { // ������ֻ�ܵ��ó���������
	std::cout << getId() << "\tBalance: " << getBalance() << "\t Available credit: "<< getAvailableCredit() << std::endl;
}

