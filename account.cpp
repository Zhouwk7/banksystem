#include <iostream>
#include <utility> // pair
#include "account.h"
//using namespace std;
// AccountRecord 类

AccountRecord::AccountRecord(const Date& date, const Account* account, double amount, double balance, const std::string desc):
	date(date), account(account), amount(amount),balance(balance),desc(desc){ }
void AccountRecord::show() const {
	std::cout << date << "\t#" << account->getId() << "\t" << amount << "\t" << balance << "\t" << desc << std::endl;
}


// Account 银行账户基类
double Account::total = 0;		// 静态属性定义
RecordMap Account::recordMap;	

Account::Account(const Date& date, const std::string& id) :id(id), balance(0) {
	std::cout << date << "\t#" << id << "\t is created!" << std::endl;
}

void Account::record(const Date& date, double amount, const std::string& desc) {
	amount = floor(amount * 100 + 0.5) / 100;
	balance += amount;
	total += amount;
	/*date.show();*/
	std::cout << date << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << std::endl;
	recordMap.insert(recordMap.end(), std::pair<Date, AccountRecord>(date, AccountRecord(date,this,amount,getBalance(),desc)));
}
void Account::error(const std::string& msg) const {
	std::cout << "error(#" << id << "):" << msg << std::endl;
}

void Account::show(std::ostream& out) const {
	out << getId() << "\tbalance: " << getBalance() << std::endl;
}

void Account::query(const Date& begin, const Date& end) {
	if (begin <= end) {
		RecordMap::iterator iter1 = recordMap.lower_bound(begin);
		RecordMap::iterator iter2 = recordMap.upper_bound(end);
		for (RecordMap::iterator iter = iter1; iter != iter2; iter++) {
			iter->second.show();
		}
	}
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
//void SavingsAccount::show() const {
//	std::cout << getId() << "\tbalance: " << getBalance() << std::endl;
//}

// CreditAccount

void CreditAccount::deposit(const Date& date, double amount, const std::string& desc) {
	record(date, amount, desc);
	acc.change(date, getDebt()); // 信用卡利息为负，不应该使用getBalance()
}
void CreditAccount::withdraw(const Date& date, double amount, const std::string& desc) {
	//	std::cout << "credit" << credit << ",amount" << amount << ",balance" << getBalance() << std::endl;
	if (credit < amount - getBalance()) { // 信用卡为正时，可用的金额大于 credit
		error("Not enough credit!");
		exit(1);
	}
	record(date, -amount, desc);
	acc.change(date, getDebt());
}
void CreditAccount::settle(const Date& date) {// 每月结算一次
	double interest = acc.getSum(date) * rate; // 按日累计利息，已经为负
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
void CreditAccount::show(std::ostream& out) const { // 常函数只能调用常函数方法
	Account::show(out);
	out << "\t Available credit: "<< getAvailableCredit();
}

