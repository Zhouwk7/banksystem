#ifndef DATE_H
#define DATE_H
#include <iostream>
class Date{
private:
	int year;
	int month; 
	int day;
	int totalDays;
public:
	Date(int year=1, int month=1, int day=1);
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
	int getTotalDays() const{ return totalDays; }
	bool isLeapYear() const{ return year % 4 == 0 && year % 100 != 0 || year % 400 == 0; }
	int getMaxDays() const;
	int operator-(const Date& date) const {
		return totalDays - date.totalDays;
	}
	
	bool operator<(const Date& date) const {
		return totalDays < date.totalDays;
	}
	//static Date read();
	void show() const;
};
std::istream& operator>>(std::istream& in, Date& date);
std::ostream& operator<<(std::ostream& out, const Date& date);

#endif