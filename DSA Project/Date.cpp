#include "Date.h"
#include <iostream>
#include <string.h>
#include <cstring>

/*---------- Parametrized Constructor ----------*/

date::date(int day, int month, int year)
{
	setDay(day);
	setMonth(month);
	setYear(year);
}

/*---------- Setters ----------*/

void date::setDay(int day)
{
	this->day = (day > 0 && day <= 31) ? day : 0;
}
void date::setMonth(int month)
{
	this->month = (month > 0 && month <= 12) ? month : 0;
}
void date::setYear(int year)
{
	this->year = (year > 1900 && year < 2018) ? year : 0;
}
/*----------  Getters ----------*/

int date::getDay()
{
	return day;
}
int date::getMonth()
{
	return month;
}
int date::getYear()
{
	return year;
}
/*----------  Display Method ----------*/

void date::display()
{
	std::cout << day << " : " << month << " : " << year << std::endl;
}

/* --------- Enter the Date ---------*/

void date::setDate(int day, int month, int year)
{
	setDay(day);
	setMonth(month);
	setYear(year);
}

/*---------- End of Class ----------*/

/*---------- Overloaded '<<' operator ----------*/

std::ostream& operator << (std::ostream& cout, date date)
{
	cout << date.day << " / " << date.month << " / " << date.year ;
	return cout;
}

/*---------- Overloaded '>>' operator ----------*/

std::istream& operator >> (std::istream& cin, date& dateToEnter)
{
	std::cout << "DAY : ";
	cin >> dateToEnter.day;

	std::cout << "MONTH : ";
	cin >> dateToEnter.month;

	std::cout << "YEAR : ";
	cin >> dateToEnter.year;
	
	return cin;
}

void date::operator=(int value)
{
	this->day = value;
	this->month = value;
	this->year = value;
	return;
}
