#include "Date.h"
#include <iostream>
#include<string>
using namespace std;

Date::Date(int d, int m, int y) : day(d), month(m), year(y)
{
}

void Date::setDay(int d)
{
	day = d;
}

void Date::setMonth(int m)
{
	month = m;
}

void Date::setYear(int y)
{
	year = y;
}

int Date::getDay()
{
	return day;
}

int Date::getMonth()
{
	return month;
}

int Date::getYear()
{
	return year;
}


void Date::display() {
	std::cout << getDay() << "/" << getMonth() << "/" << getYear() << std::endl;
}