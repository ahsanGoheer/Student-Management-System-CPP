#pragma once
#include <string>
/*---------- Start of Class----------*/

class date
{
protected:

	/*---------- Data Members ----------*/

	int day;
	int month;
	int year;
public:
	/*---------- Parametrized Constructor ----------*/

	date(int day = 0, int month = 0, int year = 0);


	/*---------- Setters ----------*/

	void setDay(int);
	void setMonth(int);
	void setYear(int);

	/*----------  Getters ----------*/

	int getDay();
	int getMonth();
	int getYear();

	/*---------- Overloaded '<<' operator ----------*/

	friend std::ostream& operator << (std::ostream&, date);


	/*---------- Overloaded '>>' operator ----------*/

	friend std::istream& operator >> (std::istream&, date&);

	void operator=(int);
	/*---------- Display Method ----------*/

	void display();

	/* --------- Enter the Date ---------*/
	void setDate(int, int, int);
};


/*---------- End of Class ----------*/