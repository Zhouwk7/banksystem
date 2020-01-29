#ifndef DATE_H
#define DATE_H
class Date {
private:
	int year;
	int month;
	int day;
	int totalDays;
public:
	Date(int year, int month, int day);
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
	bool isLeapYear() const;
	int getMaxDays() const;
	int getTotalDays() const { return totalDays; }
	int operator-(const Date& date) const{
		return totalDays - date.totalDays;
	}
	void show() const;
};
#endif