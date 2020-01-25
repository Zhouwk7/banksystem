#include<iostream>
#include "account.h"
//using namespace std;


int main() {
	Date date(2008, 11, 1);
	// 账号定义
	SavingsAccount s0(date, "s0001", 0.0015);
	SavingsAccount s1(date, "s0002", 0.0015);
	CreditAccount ca(date, "c0001", 10000, 0.0005, 50);
	// 11月份几笔账
	s0.deposit(Date(2008,11,5), 5000, "salary");
	ca.withdraw(Date(2008, 11, 15), 2000, "buy a cell");
	s1.deposit(Date(2008, 11, 25), 10000, "sell stock 0323");
	// 结算信用卡
	ca.settle(Date(2008, 12, 1));
	// 12 月份的几笔账
	ca.deposit(Date(2008, 12, 1), 10000 - ca.getAvaliableCredit(), "repay the credit");
	s0.deposit(Date(2008, 12, 5), 5500, "salary");
	// 结算所有账户
	s0.settle(Date(2009, 1, 1));
	s1.settle(Date(2009, 1, 1));
	ca.settle(Date(2009, 1, 1));
	// 输出各个账号信息
	std::cout << std::endl;
	s0.show(); std::cout << std::endl;
	s1.show(); std::cout << std::endl;
	ca.show(); std::cout << std::endl;
	std::cout << "Total:" << Account::getTotal() << std::endl;
	system("pause");
	return 0;
}
