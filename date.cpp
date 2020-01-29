#include <iostream> // cout
#include <cstdlib> // exit()
#include "date.h"

namespace { // 每月累计天数
	int BEFORE_MONTH_DAYS[] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
}

Date::Date(int year, int month, int day) :year(year), month(month), day(day) {
	if (day > getMaxDays() || day <= 0 || month <= 0 || month > 12 || year < 0 ) {
		std::cout << "Invalid date!" << std::endl;
		exit(1); // 日期无效，退出
	}
	int years = year - 1;
	totalDays = years * 365 + years / 4 - years / 100 + years / 400 +
		BEFORE_MONTH_DAYS[month - 1] + day;
	if (isLeapYear()) totalDays++;
}

int Date::getMaxDays() const { // 获取每月最大天数
	return BEFORE_MONTH_DAYS[month] - BEFORE_MONTH_DAYS[month-1];
}

bool Date::isLeapYear() const {
	return(year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
void Date::show() const{
	std::cout << year << "-" << month << "-" << day;
}