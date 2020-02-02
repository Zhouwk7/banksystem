#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<iostream>
#include <vector>
#include <algorithm>
#include"account.h"
// ���ڴ洢�˻��б�ʹ�������
struct deleter {
	template<class T>
	void operator() (T* p) {
		delete p;
	}
};
class Controller {
private:
	Date date;
	std::vector<Account*> accounts;
	bool end;
public:
	Controller(const Date& date) :date(date), end(false) {
	}
	~Controller();
	const Date& getDate() const { return date; }
	bool isEnd() const { return end; }
	bool runCommand(const std::string& cmdLine);
};

#endif