#pragma once
#include <iostream>
#include <string>

class Date {

private:
	int Year, Month, Day;
	int t;

public:
	Date() : Year(0), Month(0), Day(0){}
	Date(int year, int month, int day) : Year(year), Month(month), Day(day) { toT();} /// Maybe Wrong 
	Date(const Date& date) : Year(date.Year), Month(date.Month), Day(date.Day) {}
	~Date() {}
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	std::string toString() const;
	void toT();
};

