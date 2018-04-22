#include <iostream>
#include <string>
#include "Date.h"

int Date::getYear() const{
	return Year;
}
int Date::getMonth() const{
	return Month;
}
int Date::getDay() const{
	return Day;
}

void Date::setYear(int year){
	Year = year;
}
void Date::setMonth(int month){
	Month = month;
}
void Date::setDay(int day){
	Day = day;
}

std::string Date::toString() const{
	return std::to_string(Year) + "-" + std::to_string(Month) + "-" + std::to_string(Day);
}

void Date::toT(){
	int ty = 0, tm = 0, td = 0;
	ty = (Year - 2000) * 1200;
	tm = (Month * 70);
	td = Day * 2;
	t = ty + tm + td;
}
