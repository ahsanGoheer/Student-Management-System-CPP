#pragma once
#include <string>
/*---------- Start of Class----------*/

class Course
{
protected:

	/*---------- Data Members ----------*/

	char nameOfCourse[50];
	char courseCode[10];
	int creditHours;
	char preRequisite[30];
	char department[5];
	int semesterToBeTaughtIn;
public:
	/*---------- Default Constructor ----------*/
	Course();

	/*---------- Parametrized Constructor ----------*/
	Course(char nameOfCourse[], char courseCode[], int creditHours, char preRequisite[], char department[], int semesterToBeTaughtIn);

	/*---------- Setters ----------*/

	void setNameOfCourse(char[]);
	void setCourseCode(char[]);
	void setCreditHours(int);
	void setPreRequisite(char[]);
	void setDepartment(char[]);
	void setSemesterToBeTaughtIn(int);

	/*----------  Getters ----------*/

	std::string getNameOfCourse();
	std::string getCourseCode();
	int getCreditHours();
	std::string getPreRequisite();
	std::string getDepartment();
	int getSemesterToBeTaughtIn();

	/*---------- Write a Course to file ----------*/
	void writeACourseToFile();

	/*---------- Read a Course from file ----------*/
	void readACourseFromFile(int);

	/*---------- Display a course that is to be found ----------*/
	void findACourse(char[], int);

	/*---------- Find a course by course code ----------*/
	void viewACourseByCode(char[]);

	/*---------- Display Method ----------*/
	void display();

	/*---------- Delete courses from file ----------*/
	void deleteCourseFromFile(std::string);

	/*---------- overloaded '<<' operator ----------*/
	friend std::ostream& operator <<(std::ostream&, Course);

	/*---------- overloaded '>>' operator ----------*/
	friend std::istream& operator >>(std::istream&, Course&);
};


/*---------- End of Class ----------*/

