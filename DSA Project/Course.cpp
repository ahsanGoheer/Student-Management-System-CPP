#include "Course.h"
#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
/*---------- Default Constructor ----------*/
Course::Course()
{
	strcpy_s(this->nameOfCourse, sizeof(this->nameOfCourse), "\0");
	strcpy_s(this->courseCode, sizeof(this->courseCode), "\0");
	this->creditHours = 0;
	strcpy_s(this->preRequisite, sizeof(this->preRequisite), "\0");
	strcpy_s(this->department, sizeof(this->department), "\0");
	this->semesterToBeTaughtIn = 0;
}

/*---------- Parametrized Constructor ----------*/

Course::Course(char nameOfCourse[], char courseCode[], int creditHours, char preRequisite[], char department[], int semesterToBeTaughtIn)
{
	strcpy_s(this->nameOfCourse, sizeof(this->nameOfCourse), nameOfCourse);
	strcpy_s(this->courseCode, sizeof(this->courseCode), courseCode);
	this->creditHours = creditHours;
	strcpy_s(this->preRequisite, sizeof(this->preRequisite), preRequisite);
	strcpy_s(this->department, sizeof(this->department), department);
	this->semesterToBeTaughtIn = semesterToBeTaughtIn;
}

/*---------- Setters ----------*/

void Course::setNameOfCourse(char nameOfCourse[])
{
	strcpy_s(this->nameOfCourse, sizeof(this->nameOfCourse), nameOfCourse);
}
void Course::setCourseCode(char courseCode[])
{
	strcpy_s(this->courseCode, sizeof(this->courseCode), courseCode);
}
void Course::setCreditHours(int creditHours)
{
	this->creditHours = creditHours;
}
void Course::setPreRequisite(char preRequisite[])
{
	strcpy_s(this->preRequisite, sizeof(this->preRequisite), preRequisite);
}
void Course::setSemesterToBeTaughtIn(int semesterToBeTaughtIn)
{
	this->semesterToBeTaughtIn = semesterToBeTaughtIn;
}
void Course::setDepartment(char department[])
{
	strcpy_s(this->department, sizeof(this->department), department);
}
/*----------  Getters ----------*/

std::string Course::getNameOfCourse() { return nameOfCourse; }
std::string Course::getCourseCode() { return courseCode; }
int Course::getCreditHours() { return creditHours; }
std::string Course::getPreRequisite() { return preRequisite; }
int Course::getSemesterToBeTaughtIn() { return semesterToBeTaughtIn; }
std::string Course::getDepartment() { return department; }

/*----------  Display Method ----------*/

void Course::display()
{
	std::cout << "--------------- COURSE DETAILS ---------------" << std::endl;
	std::cout << "COURSE TITLE  : " << nameOfCourse << std::endl;
	std::cout << "COURSE CODE   : " << courseCode << std::endl;
	std::cout << "CREDIT HOURS  : " << creditHours << std::endl;
	std::cout << "PREREQUISITE  : " << preRequisite << std::endl;
	std::cout << "DEPARTMENT    : " << department << std::endl;
	std::cout << "SEMESTER TO BE TAUGHT IN : " << semesterToBeTaughtIn << std::endl;
	std::cout << "--------------- -------------- ---------------" << std::endl;
}
/*---------- Write a Course to file ----------*/
void Course::writeACourseToFile()
{
	std::ofstream courseFile;			// Read, write, and update contents of any file
	courseFile.open("Courses.dat", std::ios::out | std::ios::app | std::ios::binary);
	courseFile.write(reinterpret_cast<char *>(this), sizeof(*this));
	courseFile.close();
}

/*---------- Read a Course from file ----------*/
void Course::readACourseFromFile(int courseNumber)
{
	std::ifstream courseFile;			// Read, write, and update contents of any file
	courseFile.open("Courses.dat", std::ios::in | std::ios::binary);
	courseFile.seekg(courseNumber * sizeof(Course));
	courseFile.read(reinterpret_cast<char *>(this), sizeof(*this));
	courseFile.close();
}


/*---------- Display a course that is to be found ----------*/
void Course::findACourse(char * department, int semester)
{
	std::ifstream courseFile;			// Read, write, and update contents of any file
	courseFile.open("Courses.dat", std::ios::in | std::ios::binary);
	courseFile.seekg(0, std::ios::end);

	Course courseToFind;

	int totalContentsOnFile = courseFile.tellg();
	int totalRecordsOnFile = (totalContentsOnFile / sizeof(Course));
	courseFile.seekg(0, std::ios::beg);
	for (int i = 0; i < totalRecordsOnFile; i++)
	{
		courseFile.read(reinterpret_cast<char *>(&courseToFind), sizeof(*this));

		std::cout << courseToFind;

		if (!strcmp(department, this->department) || courseToFind.semesterToBeTaughtIn == semester)
		{
			std::cout << courseToFind;
		}
	}
	courseFile.close();
}

/*---------- Find a course by course code ----------*/
void Course::viewACourseByCode(char codeToFind[])
{
	std::ifstream courseFile;			// Read, write, and update contents of any file
	courseFile.open("Courses.dat", std::ios::in | std::ios::binary);
	courseFile.seekg(0, std::ios::end);

	Course courseToFind;

	int totalContentsOnFile = courseFile.tellg();
	courseFile.seekg(0, std::ios::beg);
	int totalRecordsOnFile = (totalContentsOnFile / sizeof(Course));

	bool found = false;

	for (int i = 0; i < totalRecordsOnFile; i++)
	{
		courseFile.read(reinterpret_cast<char *>(&courseToFind), sizeof(*this));

		if (!(_strcmpi(courseToFind.courseCode, codeToFind)))
		{
			std::cout << courseToFind;
			found = true;
			break;
		}
	}
	if (!found)
	{
		std::cout << "COURSE NOT FOUND !" << std::endl;
	}
	courseFile.close();
}
/*---------- Delete courses from file ----------*/
void Course::deleteCourseFromFile(std::string courseCode)
{
	std::ifstream oldFile("Courses.dat", std::ios::in | std::ios::binary);
	std::ofstream newFile("temp.dat", std::ios::out | std::ios::ate | std::ios::app | std::ios::binary);

	Course courseToDelete;

	oldFile.seekg(0, std::ios::end);				// Take the file pointer to the end
	int lastDataByte = oldFile.tellg();				// Get the byte number of last data in that file
	int totalRecords = (lastDataByte / sizeof(Course));	// Size of each record
	oldFile.seekg(0, std::ios::beg);

	for (int i = 0; i < totalRecords; i++)
	{
		oldFile.read(reinterpret_cast<char*>(&courseToDelete), sizeof(courseToDelete));
		if (courseToDelete.getCourseCode() == courseCode)
		{
		}
		else
		{
			newFile.write(reinterpret_cast<char*>(&courseToDelete), sizeof(courseToDelete));
		}
	}
	oldFile.close();
	newFile.close();
	std::remove("Courses.dat");
	std::rename("temp.dat", "Courses.dat");
}


/*---------- End of Class ----------*/

/*---------- overloaded '<<' operator ----------*/
std::ostream& operator <<(std::ostream& cout, Course anyCourse)
{
	cout << "--------------- COURSE DETAILS ---------------" << std::endl;
	cout << "COURSE TITLE  : " << anyCourse.nameOfCourse << std::endl;
	cout << "COURSE CODE   : " << anyCourse.courseCode << std::endl;
	cout << "CREDIT HOURS  : " << anyCourse.creditHours << std::endl;
	cout << "PREREQUISITE  : " << anyCourse.preRequisite << std::endl;
	cout << "DEPARTMENT    : " << anyCourse.department << std::endl;
	cout << "SEMESTER TO BE TAUGHT IN : " << anyCourse.semesterToBeTaughtIn << std::endl;
	cout << "--------------- -------------- ---------------" << std::endl;
	return cout;
}

/*---------- overloaded '>>' operator ----------*/
std::istream& operator >>(std::istream& cin, Course& anyCourse)
{
	char nameOfCourse[50];
	char courseCode[10];
	int creditHours;
	char preRequisite[30];
	char department[5];
	int semesterToBeTaughtIn;

	std::cin.ignore();
	std::cout << "COURSE TITLE  : ";
	cin.getline(nameOfCourse, 50, '\n');

	std::cin.ignore();
	std::cout << "COURSE CODE   : ";
	cin.getline(courseCode, 10, '\n');

	std::cin.ignore();
	std::cout << std::endl;
	std::cout << "CREDIT HOURS  : ";
	std::cin >> creditHours;

	std::cin.ignore();
	std::cout << "PREREQUISITE  : ";
	cin.getline(preRequisite, 30, '\n');

	std::cin.ignore();
	std::cout << "DEPARTMENT : ";
	cin.getline(department, 5, '\n');

	std::cin.ignore();
	std::cout << std::endl;
	std::cout << "SEMESTER TO BE TAUGHT IN : ";
	std::cin >> semesterToBeTaughtIn;


	anyCourse.setNameOfCourse(nameOfCourse);
	anyCourse.setCourseCode(courseCode);
	anyCourse.setCreditHours(creditHours);
	anyCourse.setPreRequisite(preRequisite);
	anyCourse.setDepartment(department);
	anyCourse.setSemesterToBeTaughtIn(semesterToBeTaughtIn);

	anyCourse.writeACourseToFile();

	return cin;
}
