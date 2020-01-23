#include <iostream>
#include <cstdlib>
#include "date.h"
using namespace std;
namespace {
	const int DAYS_BEFORE_MONTH[] = {
		0,31,59,90,120,151,181,212,243,273,304,334,365 };
}
int Date::getMaxDay() const {
	return DAYS_BEFORE_MONTH[month] - DAYS_BEFORE_MONTH[month - 1];
}
Date::Date(int year, int month, int day):
	year(year),month(month),day(day){
	if (day <= 0 || day > getMaxDay()) { // 排除日期不正确的 date
		cout << "Invalid date:";
		show();
		cout << endl;
		exit(1);
	}
	else {
		int years = year - 1;
		totalDays = years * 365 + years / 4 - years / 100 + years / 400 +
			DAYS_BEFORE_MONTH[month] + day;
		if (isLeapYear() || month > 2) totalDays++;
	}
}

void Date::show() const {
	cout << getYear() << "-" << getMonth() << "-" << getDay();
}
