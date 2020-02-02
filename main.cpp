#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
#include<sstream>
#include "account.h"
#include "controller.h"
using namespace std;

int main() {
	Date date(2008, 11, 1);
	Controller controller(date);
	string cmdLine;
	const char* FILE_NAME = "command.txt";
	ifstream fileIn(FILE_NAME);		// 读模式打开文件
	if (fileIn) {
		while (getline(fileIn, cmdLine)) {
			controller.runCommand(cmdLine);
		}
		fileIn.close();
	}
	ofstream fileOut(FILE_NAME, ios_base::app); // 以追加模式打开文件
	cout << "(a)-add account (d)-deposit (w)-withdraw (s)-show (c)-change day (n)-next month (q)-query (e)-exit" << endl;
	while (!controller.isEnd()) {
		cout << controller.getDate() << "\tTotal:" << Account::getTotal() << "\tcommand>";
		string cmdLine;
		getline(cin, cmdLine);
		if (controller.runCommand(cmdLine))
			fileOut << cmdLine << endl;
	}
	return 0;
}

