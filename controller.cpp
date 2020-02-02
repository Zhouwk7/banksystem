#include "controller.h"
#include <sstream> // istringstream、ostringstream
Controller::~Controller() {
	std::for_each(accounts.begin(),accounts.end(),deleter());
}
bool Controller::runCommand(const std::string& cmdLine) { // 返回为 true 的命令将会被保存
	std::istringstream str(cmdLine);
	char cmd, type;
	int index, day;
	double amount, credit, rate, fee;		
	std::string id, desc;
	Account* account;
	Date date1, date2;
	str >> cmd;
	switch (cmd) {	
	case 'a':
		str >> type >> id;
		if (type == 's') {
			str >> rate;
			account = new SavingsAccount(date, id, rate);
		}
		else {
			str >> credit >> rate >> fee;
			account = new CreditAccount(date, id, rate, credit, fee);
		}
		accounts.push_back(account);
		return true;
	case 'd':
		str >> index >> amount;
		getline(str, desc); // string 头文件中定义
		accounts[index]->deposit(date, amount, desc);
		return true;
	case 'w':
		str >> index >> amount;
		getline(str, desc);
		accounts[index]->withdraw(date, amount, desc);
		return true;
	case 's':
		for (size_t i = 0; i < accounts.size(); i++) {
			std::cout << "[" << i << "]";
			accounts[i]->show(std::cout);
			std::cout << std::endl;
		}
		return false;
	case 'c':
		str >> day;
		if (day < date.getDay()) {
			std::cout << "You cannot specify a previous day";
		}
		else if (day > date.getMaxDays()) {
			std::cout << "Invalid day";
		}
		else {
			date = Date(date.getYear(), date.getMonth(), day);
		}
		return true;
			
	case 'n':
		if (date.getMonth() == 12) {
			date = Date(date.getYear() + 1, 1, 1);
		}
		else {
			date = Date(date.getYear(), date.getMonth() + 1, 1);
		}
		for (std::vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); iter++) {
			(*iter)->settle(date);
		}
		return true;
	case 'q':
		str >> date1 >> date2;
		Account::query(date1, date2);
		return true;
	case 'e':
		end = true;
		return false;
	}
	return false;
}