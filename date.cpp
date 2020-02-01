#include<iostream>
#include "date.h"
const int BEFROE_MONTH_DAYS[] = { 0,31,59,90,120,151,181,212,143,273,304,334,365 };
Date::Date(int year, int month, int day) :year(year), month(month), day(day) {
	int years = year - 1;
	if (day > getMaxDays()) {
		std::cout << "Invalid date!" << std::endl;
		exit(1);
	}
	totalDays = years * 365 + years / 4 - years / 100 + years / 400 + BEFROE_MONTH_DAYS[month - 1] + day;
	if (isLeapYear()) totalDays++;
}
int Date::getMaxDays() const {
	return BEFROE_MONTH_DAYS[month] - BEFROE_MONTH_DAYS[month - 1];
}

Date Date::read() {
	char c;
	int year, month, day;
	std::cin >> year >> c >> month >> c >> day;
	return Date(year, month, day);
}

void Date::show() const {
	std::cout << year << "-" << month << "-" << day;
}
