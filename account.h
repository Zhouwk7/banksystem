#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "accumulator.h"
#include "date.h"
#include<string>
#include<iostream>
// 银行账号基类
class Account {
private:
	std::string id;
	double balance;
	static double total;
protected:
	Account(const Date &date, const std::string &id);
	void record(const Date &date, double amount, const std::string &desc);
	void error(const std::string &msg) const {
		std::cout << "error(#" << id << "):" << msg << std::endl;
	}
public:
	std::string getId() const {
		return id;
	}
	double getBalance() const {
		return balance;
	}
	void show() const;
	static double getTotal() { return total; };
};
// 储蓄卡账号
class SavingsAccount : public Account{
private:
	double rate;
	Accumulator acc;
public:
	SavingsAccount(const Date &date, const std::string &id, const double rate);
	double getRate() const { return rate; }
	void deposit(const Date &date, double amount, const std::string &desc);
	void withdraw(const Date &date, double amount, const std::string &desc);
	void settle(const Date &date);
};
// 信用卡账号
class CreditAccount : public Account {
private:
	Accumulator acc;
	double credit;
	double rate;
	double fee;
	double getDebt() const {
		double balance = getBalance();
		return(balance < 0 ? balance : 0);
	}
public:
	CreditAccount(const Date& date, const std::string& id,
		double credit, double rate, double fee);
	double getCredit() const { return credit; }
	double getRate() const { return rate; }
	double getFee() const { return fee; }
	double getAvaliableCredit() const {
		double balance = getBalance();
		if (balance < 0) {
			return credit + balance;
		}
		return credit;
	}
	void deposit(const Date& date, double amount, const std::string& desc);
	void withdraw(const Date& date, double amount, const std::string& desc);
	void settle(const Date& date);
	void show() const;
};
#endif

