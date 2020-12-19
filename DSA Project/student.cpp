#include "student.h"
#include <iostream>
#include <string>
#include <list>
#include <cstring>
#include <fstream>
#include <cctype>
#include<queue>
student::student(std::string nameOfStudent, date dateOfBirth, std::string enrollmentNo, std::string contactNo, std::string department, short semesterNo)
{
	this->nameOfStudent = nameOfStudent;
	this->dateOfBirth = dateOfBirth;
	this->enrollmentNo = enrollmentNo;
	this->contactNo = contactNo;
	this->department = department;
	this->semesterNo = semesterNo;
	
}

void student::initializeGpa(double gpa[],double newGpa[])
{
	for (int i = 0; i < 8; i++)
	{
		gpa[i] = newGpa[i];
	}
	return;
}
	/*---------- Setters ----------*/

void student::setNameOfStudent(std::string nameOfStudent)
{
	this->nameOfStudent = nameOfStudent;
	return;
	
}
void student::setDateOfBith(date dateOfBirth)
{
	this->dateOfBirth = dateOfBirth;
}
void student::setEnrollmentNo(std::string enrollmentNo)
{
	this->enrollmentNo = enrollmentNo;
	return;
	
}
void student::setContactNo(std::string contactNo)
{
	this->contactNo = contactNo;
	return;
	
}
void student::setDepartment(std::string department)
{
	this->department = department;
	return;
	
}

void student::setSemesterNo(short semesterNo)
{
	if (semesterNo >= 1 && semesterNo <= 8)
	{
		this->semesterNo = semesterNo;
	}
	else
	{
		std::cout << "ENTER A CORRECT SEMESTER NO : ";
		std::cin >> semesterNo;
		setSemesterNo(semesterNo);
	}
}

void student::setGpa(short location, double gpa)
{
	if (gpa >= 0.0&& gpa <= 4.0 && location >= 0 && location <= 7)
		this->gpa[location] = gpa;
	else
		std::cout << "PLEASE ENTER CORRECT GPA !" << std::endl;
}
	/*----------  Getters ----------*/

std::string student::getNameOfStudent()
{
	return nameOfStudent; 
}

std::string student::getEnrollmentNo()
{
	return enrollmentNo;
}
std::string student::getContactNo()
{
	return contactNo;
}
std::string student::getDepartment()
{
	return department;
}


short student::getSemesterNo()
{
	return semesterNo;
}
/*----------  Write student to file ----------*/
void student::writeStudentToFile()
{
	
	std::ofstream studentsFile("Students.dat",std::ios::out | std::ios::binary | std::ios::app);
	if (!studentsFile)
	{

		std::cout << "CANNOT OPEN STUDENT FILE TO SAVE THE RECORDS" << std::endl; system("pause");
	}
	else
	{
		studentsFile.write(reinterpret_cast<char*>(this), sizeof(*this));
	}
	studentsFile.close();
}



/*----------  Write student to file ----------*/
void student::readStudentFromFile(int x)
{
	std::ifstream studentsFile;
	studentsFile.open("Students.dat", std::ios::in | std::ios::binary);
	if (!studentsFile)
	{
		std::cout << "CANNOT OPEN STUDENT FILE TO READ THE RECORDS" << std::endl; 
	}
	else
	{
		studentsFile.seekg(x * (sizeof(student)));
		studentsFile.read(reinterpret_cast<char*>(this), sizeof(*this));
		studentsFile.close();
	}
}


/*---------- Search student from file ----------*/
void student::searchStudentFromFile(std::string name, student& a)
{
	std::ifstream studentsFile;
	studentsFile.open("Students.dat", std::ios::in | std::ios::binary);
	if (!studentsFile)
	{
		std::cout << "CANNOT OPEN STUDENT FILE TO READ THE RECORDS" << std::endl;
	}
	else
	{
		int totalRecords = 0;
		int lastDataByte = 0;
		studentsFile.seekg(0, std::ios::end);				// Take the file pointer to the end
		lastDataByte = studentsFile.tellg();				// Get the byte number of last data in that file
		totalRecords = (lastDataByte / sizeof(student));	// Size of each record
		studentsFile.seekg(0, std::ios::beg);
		student studentToFind;
		for (int i = 0; i < totalRecords; i++)
		{
			studentsFile.read(reinterpret_cast<char*>(&studentToFind), sizeof(studentToFind));
			if (studentToFind.nameOfStudent == name)
			{
				a = studentToFind;
			}
		}
		studentsFile.close();
	}
}

/*---------- Delete a student from file ----------*/
void student::deleteStudentFromFile(std::string name)
{
	std::ifstream oldFile("Students.dat", std::ios::in | std::ios::binary);
	std::ofstream newFile("temp.dat", std::ios::out | std::ios::ate | std::ios::app | std::ios::binary);

	student studentToDelete;

	oldFile.seekg(0, std::ios::end);				// Take the file pointer to the end
	int lastDataByte = oldFile.tellg();				// Get the byte number of last data in that file
	int totalRecords = (lastDataByte / sizeof(student));	// Size of each record
	oldFile.seekg(0, std::ios::beg);

	for (int i = 0; i < totalRecords; i++)
	{
		oldFile.read(reinterpret_cast<char*>(&studentToDelete), sizeof(studentToDelete));
		if (studentToDelete.getNameOfStudent() != name)
		{
			newFile.write(reinterpret_cast<char*>(&studentToDelete), sizeof(studentToDelete));
		}
	}
	oldFile.close();
	newFile.close();
	std::remove("Students.dat");
	std::rename("temp.dat", "Students.dat");
}

/*---------- compute C-GPA ----------*/
double student::computeCGPA()
{
	double total = 0;
	for (int i = 0; i < (semesterNo - 1); i++)	// CANT GET THE GPA OF CURRENT SEMESTER
	{
		if (this->gpa[i] != 0)
		{
			total += gpa[i];					// ADD THE GPA OF ALL SEMESTERS
		}
	}
	return (total / (semesterNo-1));				// RETURN THEIR AVERAGE
}

/*---------- End of Class ----------*/


/*----------  Overloaded '<<' operator to diplay student details ----------*/

std::ostream & operator << (std::ostream & cout, student &anyStudent)
{
	cout << "NAME          : " << anyStudent.nameOfStudent << std::endl;
	cout << "DATE OF BIRTH : " << anyStudent.dateOfBirth << std::endl;
	cout << "ENROLLMENT NO : " << anyStudent.enrollmentNo << std::endl;
	cout << "CONTACT NO    : " << anyStudent.contactNo << std::endl;
	cout << "DEPARTMENT    : " << anyStudent.department << std::endl;
	cout << "SEMESTER NO   : " << anyStudent.semesterNo << std::endl;
	cout << "CGPA IS       : " << anyStudent.computeCGPA() << std::endl;

	return cout;
}

/*---------- Overloaded '<<' operator to input student details ----------*/
std::istream& operator >> (std::istream& cin, student& studentToEnter)
{
	std::string nameOfStudent;
	date dateOfBirth;
	std::string enrollmentNo;
	std::string contactNo;
	std::string department;

	short semesterNo;
	double gpaEntered;

	cin.ignore();
	std::cout << "NAME OF THE STUDENT : ";
	getline(std::cin,nameOfStudent, '\n');

	std::cout << "DATE OF BIRTH " << std::endl;
	cin >> dateOfBirth;
	cin.ignore();
	std::cout << std::endl;
	
	std::cout << "ENROLLMENT NUMBER (WITH DASHES) : ";
	getline(std::cin,enrollmentNo, '\n');

	std::cout << "CONTACT NUMBER (WITH DASHES) : ";
	getline(std::cin,contactNo, '\n');
	

	std::cout << "DEPARTMENT : ";
	getline(std::cin,department, '\n');
	
	std::cout << "CURRENT SEMESTER NO : ";
	cin >> semesterNo;

	studentToEnter.setNameOfStudent(nameOfStudent);
	studentToEnter.setDateOfBith(dateOfBirth);
	studentToEnter.setEnrollmentNo(enrollmentNo);
	studentToEnter.setContactNo(contactNo);
	studentToEnter.setDepartment(department);
	studentToEnter.setSemesterNo(semesterNo);
	studentToEnter.writeStudentToFile();
	cin.ignore();

	for (short i = 0; i < studentToEnter.semesterNo - 1; i++)
	{
		std::cout << "ENTER GPA FOR SEMESTER NO " << i+1 << " : ";
		std::cin >> gpaEntered;
		studentToEnter.setGpa(i, gpaEntered);
	}
	return cin;
}

void student::displayStudentInfo()
{
	std::cout << "NAME OF THE STUDENT :  " <<this->nameOfStudent << std::endl;
	std::cout << "ENROLLMENT NUMBER   :  " << this->enrollmentNo << std::endl;
	std::cout << "CONTACT NUMBER      :  " << this->contactNo << std::endl;
	std::cout << "DEPARTMENT          :  " << this->department << std::endl;
	std::cout << "-------------------------------" << std::endl;
}