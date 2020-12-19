#pragma once
#include <string>
#include "Date.h"
/*---------- Start of Class----------*/

class student
{
protected:
	/*---------- Data Members ----------*/
	std::string nameOfStudent;
	date dateOfBirth;
	std::string enrollmentNo;
	std::string contactNo;
	std::string department;
	short semesterNo;
	double gpa[8];
	
public:
	

	/*---------- Parametrized Constructor ----------*/
	student(std::string nameOfStudent = " ", date dateOfBirth = 0, std::string enrollmentNo = " ", std::string contactNo = " ", std::string department = " ", short semesterNo = 0);

	/*---------- Setters ----------*/

	void setNameOfStudent(std::string);
	void setDateOfBith(date);
	void setEnrollmentNo(std::string);
	void setContactNo(std::string);
	void setDepartment(std::string);
	void setSemesterNo(short);
	void setGpa(short, double);

	/*----------  Getters ----------*/

	std::string getNameOfStudent();
	std::string getEnrollmentNo();
	std::string getContactNo();
	std::string getDepartment();
	short getSemesterNo();
	
	/*---------- compute C-GPA ----------*/
	double computeCGPA();

	/*---------- Display Method ----------*/
	friend std::ostream & operator << (std::ostream &, student &);

	/*---------- Input Method ----------*/
	friend std::istream & operator>>(std::istream &, student &);

	/*---------- Write student to file ----------*/
	void writeStudentToFile();

	/*---------- Read student from file ----------*/
	void readStudentFromFile(int);

	/*---------- Search student from file ----------*/
	void searchStudentFromFile(std::string, student&);

	/*---------- Delete a student from file ----------*/
	void deleteStudentFromFile(std::string);

	//~student() {}
	/*---------- Display a Student's information ----------*/
	void displayStudentInfo();

	void initializeGpa(double gpa[],double newGpa[]);

	
};

/*---------- End of Class ----------*/