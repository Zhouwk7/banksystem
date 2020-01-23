#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<iostream>
#include "date.h"
class SavingAccount {
private:
	std::string id;
	double balance;
	double rate;
	Date lastDate;
	double accumulation;
	static double total;
	void record(const Date& date, double amount, std::string desc);
	double accumulate(const Date& date) const {
		return accumulation + date.distance(lastDate) * balance;
	};
public:
	SavingAccount(const Date& date, const std::string id, const double rate);
	std::string getId() const {
		return id;
	}
	double getBalance() const {
		return balance;
	}
	double getRate() const {
		return rate;
	}
	static double getTotal() { // 可以使用类名调用，在没有生成对象时就可以将静态属性输出
		return total;
	}
	void show() const;
	void deposit(const Date& date, double amount, const std::string desc);
	void withdraw(const Date& date, double amount, const std::string desc);
	void settle(const Date& date);
};
#endif

