#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<iostream>
class SavingAccount {
private:
	int id;
	double balance;
	double rate;
	int lastDate;
	double accumulation;
	static double total;
	void record(int date, double amount);
	double accumulate(int date) const {
		return accumulation + (date - lastDate) * balance;
	};
public:
	SavingAccount(int date, int id, double rate);
	int getId() const {
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
	void deposit(int date, double amount);
	void withdraw(int date, double amount);
	void settle(int date);
};
#endif

