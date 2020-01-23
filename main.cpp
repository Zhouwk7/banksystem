#include<iostream>
#include<cmath>
using namespace std;
class SavingAccount {
private:
	int id;
	double balance;
	double rate;
	int lastDate;
	double accumulation;
	void record(int date, double amount);
	double accumulate(int date) const;
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
	void show() const {
		cout << "#" << id << "\tbalance\t" << balance << endl;
	}
	void deposit(int date, double amount);
	void withdraw(int date, double amount);
	void settle(int date);
};
SavingAccount::SavingAccount(int date, int id, double rate):
	id(id), accumulation(0), lastDate(date), rate(rate),balance(0) {
	cout << date << "\t#" << id << "\tis created!" << endl;
}
double SavingAccount::accumulate(int date) const{
	return accumulation + balance * (date - lastDate);
}
void SavingAccount::record(int date, double amount) {
	accumulation += balance * (date - lastDate);
	balance += amount;
	lastDate = date;
	cout << "balance " << balance << endl;
}
void SavingAccount::deposit(int date, double amount) {
	record(date, amount);
}
void SavingAccount::withdraw(int date, double amount) {
	if (balance < amount) {
		cout << "Error: not enough money!" << endl;
	}
	else {
		record(date, -amount);
	}
}
void SavingAccount::settle(int date) {
	double interest = accumulate(date) * rate / 365;
	if (interest) {
		record(date, interest);
	}	
	accumulation = 0;
}
int main() {
	SavingAccount s0(1, 10001, 0.015);
	SavingAccount s1(1, 10002, 0.015);

	s0.deposit(5, 5000);
	s1.deposit(25, 10000);
	s0.deposit(45, 5500);
	s1.withdraw(60, 4000);
	s0.settle(90);
	s1.settle(90);
	s0.show();
	s1.show();
	system("pause");
	return 0;
}
