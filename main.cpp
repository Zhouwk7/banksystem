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
			try {
				controller.runCommand(cmdLine);
			}
			catch (exception & e) {
				cout << "Bad line in" << FILE_NAME << ":" << cmdLine << endl;
				cout << "Error:" << e.what() << endl;
				return 1;
			}
			
		}
		fileIn.close();
	}
	ofstream fileOut(FILE_NAME, ios_base::app); // 以追加模式打开文件
	cout << "(a)-add account (d)-deposit (w)-withdraw (s)-show (c)-change day (n)-next month (q)-query (e)-exit" << endl;
	while (!controller.isEnd()) {
		cout << controller.getDate() << "\tTotal:" << Account::getTotal() << "\tcommand>";
		string cmdLine;
		getline(cin, cmdLine);
		try {
			if (controller.runCommand(cmdLine))
				fileOut << cmdLine << endl;
		}
		catch (AccountException & e) {
			cout << "Error(#" << e.getAccount()->getId() << "):"
				<< e.what() << endl;
		}
		catch (exception & e) {
			cout << "Error:" << e.what() << endl;
		}
		
	}
	return 0;
}

