#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <map>
#include <string>
#include "accumulator.h"
#include "date.h"
using namespace std::rel_ops; // >= ==模板函数生成
class Account;
//class AccountRecord;
//typedef std::multimap<Date, AccountRecord> RecordMap;


class AccountRecord {
private:
	const Account* account;
	Date date;
	double amount;
	double balance;
	std::string desc;
public:
	AccountRecord(const Date& date, const Account* account, double amount, double balance, const std::string desc);
	void show() const;
};
typedef std::multimap<Date, AccountRecord> RecordMap;

class Account {
private:
	std::string id;
	double balance;
	static double total;
	static RecordMap recordMap;
protected:
	Account(const Date& date, const std::string& id);
	void record(const Date& date, double amount, const std::string& desc);
	void error(const std::string& msg) const;
public:
	const std::string& getId() const {
		return id;
	}
	double getBalance() const {
		return balance;
	}
	static double getTotal() {
		return total;
	}
	virtual void deposit(const Date& date, double amount, const std::string& desc) = 0;
	virtual void withdraw(const Date& date, double amount, const std::string& desc) = 0;
	virtual void settle(const Date& date) = 0;
	virtual void show(std::ostream& out) const; // 不是纯虚函数
	static void query(const Date& begin, const Date& end);
};
inline std::ostream& operator<<(std::ostream& out, const Account& account) {
	account.show(out);
	return out;
}


class SavingsAccount : public Account{
private:
	Accumulator acc;
	double rate; // 年利率
public:
	SavingsAccount(const Date& date, const std::string& id, double rate);
	double getRate() const {
		return rate;
	}
	void deposit(const Date& date, double amount, const std::string& desc);
	void withdraw(const Date& date, double amount, const std::string& desc);
	void settle(const Date& date);
	//void show() const;
};

// 信用卡账号类


class CreditAccount : public Account {
private:
	Accumulator acc;
	double rate;
	double credit;
	double fee;
public:
	CreditAccount(const Date& date, const std::string& id, double rate, double credit, double fee) :
		Account(date, id), acc(date, 0), rate(rate), credit(credit), fee(fee) {}
	double getRate() const { return rate; }
	double getCredit() const { return credit; }
	double getFee() const { return fee; }
	double getDebt() const { return getBalance() < 0 ? getBalance() : 0; }
	double getAvailableCredit() const{ return credit + getDebt(); }
	void deposit(const Date& date, double amount, const std::string& desc);
	void withdraw(const Date& date, double amount, const std::string& desc);
	void settle(const Date& date);
	void show(std::ostream& out) const;
};

#endif