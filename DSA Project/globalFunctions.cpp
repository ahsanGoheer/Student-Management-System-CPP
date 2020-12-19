#include "globalFunctions.h"
#include <iostream>
#include "Course.h"
#include <queue>
#include <fstream>
#include <stack>

// TREE and Stack maintained during the course of the program
void initiater();
BinarySearchTree tree;
std::stack <student> changesMade;
std::stack <student> inserted;
//std::list <student> deletedStudents;

/* get date from the user*/
void dateMenu(date &dateInput)
{
	int day, month, year;
	std::cout << "ENTER DAY : ";
	std::cin >> day;
	std::cout << "ENTER MONTH : ";
	std::cin >> month;
	std::cout << "ENTER YEAR : ";
	std::cin >> year;
	
	dateInput.setDate(day,month,year);
}

/* main menu that will display first at the screen */
void displayMainMenu(char& choice)
{
	std::cout << std::endl << std::endl << "\t\t   << ----- Student Facilitation System ----- >>" << std::endl << std::endl;

	initiater();
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "\t\t To Exit                                press  \" 0 \" " << std::endl;
	std::cout << "\t\t If you are a student                   press  \" 1 \" " << std::endl;
	std::cout << "\t\t If you are a member of Administration  press  \" 2 \" " << std::endl;
	std::cout << std::endl;
	std::cout << "\t\t Please enter your choice : "; std::cin >> choice;
}

/* Error the will display on any invalid input */
void errorWrongChoice(int first, int second)
{
	std::cout << "\a ERROR : WRONG CHOICE" << std::endl << std::endl;
	std::cout << "ENTER A CORRECT CHOICE BETWEEN \'" << first << "\' and \'" << second << "\' !"  << std::endl;
}

/* Function which checks that is it an admin member or a student */
void displayStudentOrAdmin(char choice)
{
	std::cin.ignore();

	if (choice == '0')
		exit(1);
	else if (choice == '1')
		displayStudentMenu();
	else if (choice == '2')
		displayAdminMenu();
	else								// call the same function again if wrong choice
	{
		errorWrongChoice(1, 2);
		std::cout << "YOUR NEW CHOICE : ";
		std::cin >> choice;
		displayStudentOrAdmin(choice);
	}
}

/* display the admin menu */
void displayAdminMenu()
{
	system("cls");
	std::cout << "\n\t##################### ADMIN PANEL #####################" << std::endl << std::endl << std::endl;
	std::cout << "\t\tTo enroll a new student     press 1" << std::endl << std::endl;
	std::cout << "\t\tTo view a student           press 2" << std::endl << std::endl;
	std::cout << "\t\tTo view all students        press 3" << std::endl << std::endl;
	std::cout << "\t\tTo un-enroll a student      press 4" << std::endl << std::endl;
	std::cout << "\t\tTo un-enroll all students   press 5" << std::endl << std::endl;
	std::cout << "\t\tTo enter a new course       press 6" << std::endl << std::endl;
	std::cout << "\t\tTo view a course            press 7" << std::endl << std::endl;
	std::cout << "\t\tTo view all courses         press 8" << std::endl << std::endl;
	std::cout << "\t\tTo remove a course          press 9" << std::endl << std::endl;
	std::cout << "\t\tTo remove all courses       press a" << std::endl << std::endl;
	std::cout << "\t\tTo exit                     press 0" << std::endl << std::endl;

	char choice;
	std::cout << "\n\t\t\tYour choice : "; std::cin >> choice;

	char input = ' ';


	char choice2 = ' ';

	system("cls");
	switch (choice)
	{
	case'0':
		if (!changesMade.empty())
		{
			std::cout << "Do you want to restore the changes (y/n) : ";
			std::cin >> input;
			if ((input == 'y') || (input == 'Y'))
				restoreAllChanges();
		}

		system("cls");
		std::cin.get();

		displayMainMenu(choice2);

		while (1)
		{
			displayStudentOrAdmin(choice2);
			std::cin.get();
			std::cin.get();
		}


		exit(1);
		break;
	case '1':
		addANewStudent();
		tree.writeToFiles();
		break;
	case'2':
		viewAStudent();
		break;
	case'3':
		viewAllStudents();
		break;
	case'4':
		removeAStudent();
		break;
	case'5':
		removeAllStudents();
		break;
	case'6':
		addANewCourse();
		break;
	case'7':
		viewACourse();
		break;
	case'8':
		viewAllCourses();
		break;
	case'9':
		removeACourse();
		break;
	case'a':
		removeAllCourses();
		break;
	default :
		errorWrongChoice(0,8);
		std::cin.get();
		break;
	}

}

/* display the student menu */
void displayStudentMenu()
{
	system("cls");

	char name[32];
	std::cin.ignore();
	std::cout << "ENTER YOUR NAME : ";
	std::cin.getline(name, 32, '\n');
	student anyStudent;
	//anyStudent.searchStudentFromFile(name, anyStudent);

	Course anyCourses;
	do{
		system("cls");
		std::cout << "\n\t##################### STUDENT PANEL #####################" << std::endl << std::endl;
		std::cout << "\t\tTO VIEW PERSONAL DETAILS      PRESS 1" << std::endl;
		std::cout << "\t\t TO VIEW COURSES' DEAILS      PRESS 2" << std::endl;
		//std::cout << "\t\t   TO GENERATE TIMETABLE      PRESS 3" << std::endl;
		std::cout << "\t\t        TO VIEW HANDBOOK      PRESS 3" << std::endl;
		std::cout << "\t\t            TO VIEW CGPA      PRESS 4" << std::endl;
		std::cout << "\t\t                 TO EXIT      PRESS 0" << std::endl;

		char department[] = "CS";

		char choice;
		std::cout << "\n\t\t\tYour choice : "; std::cin >> choice;
		switch (choice)
		{
		case'0':
			exit(1);
			break;
		case'1':
			tree.SearchTree(tree.get_root(), name);/*->data.displayStudentInfo()*/;
			//std::cout << anyStudent << std::endl;
			break;
		case'2':
			anyCourses.findACourse(department, anyStudent.getSemesterNo());
			break;
		//case'3':
			//timeTableGenerator(anyStudent);
			//break;
		case'3':
			handBook();
			break;
		case'4':
			std::cout << "YOUR CGPA IS : " << anyStudent.computeCGPA() << " CONGRATULATIONS !" << std::endl;
			break;
		default:
			errorWrongChoice(0, 5);
			break;
		}
		system("pause");
	} while (1);
}
/*---------- Input Student Details and update it on the students file ----------*/
void addANewStudent()
{
	char choice;
	student newStudent;
	std::cin >> newStudent;

	tree.InsertStudent(newStudent);
	newStudent.writeStudentToFile();
	inserted.push(newStudent);

	std::cout << "Are you sure about this change ? (y/n) ";
	std::cin >> choice;
	if (choice != 'y')
	{
		tree.deleteNode(inserted.top().getNameOfStudent());
		inserted.pop();
	}
}

/*---------- Delete the details of a student from the students file ----------*/
void removeAStudent()
{
	student studentToDelete;
	std::string name;
	std::cout << "ENTER THE NAME OF THE STUDENT YOU WANT TO REMOVE : ";
	std::cin >> name;


	
	studentToDelete=tree.deleteNode(name);
	changesMade.push(studentToDelete);

}

//Delete all students' records from the file
void removeAllStudents()
{
	std::ofstream file("Students.dat");
	file << "";
	file.close();

	tree.setRoot(nullptr);
}

bool ran = false;
/*---------- Input Course Details and update it on the courses file ----------*/
void addANewCourse()
{
	Course courseToBeAdded;
	std::cin >> courseToBeAdded;
}

/*---------- Delete the details of a course from the courses file ----------*/ 
void removeACourse()
{
	std::string courseCodeOfCourseToRemove;
	std::cout << "ENTER THE COURSE CODE TO REMOVE A COURSE : ";
	std::cin >> courseCodeOfCourseToRemove;

	Course removeACourse;
	removeACourse.deleteCourseFromFile(courseCodeOfCourseToRemove);
}

//Delete all courses' records from the file
void removeAllCourses()
{
	std::ofstream file("Courses.dat");
	file << "";
	file.close();
}

// View a student's details
void viewAStudent()
{
	std::cin.ignore();
	char name[30];
	std::cout << "ENTER THE NAME OF STUDENT : ";
	std::cin.getline(name, 30 , '\n');

	tree.SearchForNode(tree.get_root(), name)->data.displayStudentInfo();

	//student anyStudent;
	//anyStudent.searchStudentFromFile(name, anyStudent);
	//std::cout << anyStudent;
}

// View a course's details
void viewACourse()
{
	std::cin.ignore();

	char code[30];
	std::cout << "ENTER THE COURSE CODE : ";
	std::cin.getline(code, 30, '\n');

	Course anyCourseToFind;
	anyCourseToFind.viewACourseByCode(code);
}

// View all students' details
void viewAllStudents()
{
	// if (tree.isEmpty())
	std::cout << "Displaying all the students LEXICOGRAPHICALLY" << std::endl << std::endl;
	// else
	//	std::cout << "No students available to display" << std::endl;
	tree.InOrderTraveral();

	/*student allStudents;

	std::ifstream studentsFile("Students.dat", std::ios::out | std::ios::binary);

	if (!studentsFile)
	{
		std::cout << "NO STUDENT FILE EXISTS" << std::endl;
	}
	else
	{
		studentsFile.seekg(0, std::ios::end);
		int totalSizeOfFile = studentsFile.tellg();
		studentsFile.seekg(0, std::ios::beg);
		int totalRecords = (totalSizeOfFile / sizeof(student));
		for (int i = 0; i < totalRecords; i++)
		{
			allStudents.readStudentFromFile(i);
			std::cout << allStudents << std::endl;
		
		}
		studentsFile.close();
	}*/
}

// View all courses' details
void viewAllCourses()
{
	Course Courses;
	std::ifstream coursesFile("Courses.dat", std::ios::out | std::ios::binary);

	if (!coursesFile)
	{
		std::cout << "NO COURSE FILE EXISTS" << std::endl;
	}
	else
	{
		coursesFile.seekg(0, std::ios::end);
		int totalSizeOfFile = coursesFile.tellg();
		coursesFile.seekg(0, std::ios::beg);
		int totalRecords = (totalSizeOfFile / sizeof(Course));

		for (int i = 0; i < totalRecords; i++)
		{
			Courses.readACourseFromFile(i);
			std::cout << Courses << std::endl;
		}

		coursesFile.close();
	}
}


// allow student to generate his timetable

void timeTableGenerator(student a)
{
	int creditHours = 0;
	int mon, tues, wed, thurs, fri;

	switch (a.getSemesterNo())
	{
	case 1:
		creditHours = 17;
		system("cls");
		std::cout << "YOUR HAVE " << creditHours << " CREDIT HOURS THIS SEMESTER !" << std::endl;
		classesViewer(creditHours, mon, tues, wed, thurs, fri, a);
		std::cout << "TIMETABLE GENERATED " << std::endl; 
		break;
	case 2:
		system("cls");
		creditHours = 18;
		std::cout << "YOUR HAVE " << creditHours << " CREDIT HOURS THIS SEMESTER !" << std::endl;
		classesViewer(creditHours, mon, tues, wed, thurs, fri, a);
		std::cout << "TIMETABLE GENERATED " << std::endl;
		break;
	case 3:
		system("cls");
		creditHours = 19;
		std::cout << "YOUR HAVE " << creditHours << " CREDIT HOURS THIS SEMESTER !" << std::endl;
		classesViewer(creditHours, mon, tues, wed, thurs, fri, a);
		std::cout << "TIMETABLE GENERATED " << std::endl;
		break;
	case 4:
		system("cls");
		creditHours = 18;
		std::cout << "YOUR HAVE " << creditHours << " CREDIT HOURS THIS SEMESTER !" << std::endl;
		classesViewer(creditHours, mon, tues, wed, thurs, fri, a);
		std::cout << "TIMETABLE GENERATED " << std::endl;
		break;
	case 5:
		system("cls");
		creditHours = 15;
		std::cout << "YOUR HAVE " << creditHours << " CREDIT HOURS THIS SEMESTER !" << std::endl;
		classesViewer(creditHours, mon, tues, wed, thurs, fri, a);
		std::cout << "TIMETABLE GENERATED " << std::endl;
		break;
	case 6:
		system("cls");
		creditHours = 16;
		std::cout << "YOUR HAVE " << creditHours << " CREDIT HOURS THIS SEMESTER !" << std::endl;
		classesViewer(creditHours, mon, tues, wed, thurs, fri, a);
		std::cout << "TIMETABLE GENERATED " << std::endl;
		break;
	case 7:
		creditHours = 17;
		std::cout << "YOUR HAVE " << creditHours << " CREDIT HOURS THIS SEMESTER !" << std::endl;
		classesViewer(creditHours, mon, tues, wed, thurs, fri, a);
		std::cout << "TIMETABLE GENERATED " << std::endl;
		break;
	case 8:
		system("cls");
		creditHours = 12;
		std::cout << "YOUR HAVE " << creditHours << " CREDIT HOURS THIS SEMESTER !" << std::endl;
		classesViewer(creditHours, mon, tues, wed, thurs, fri, a);
		std::cout << "TIMETABLE GENERATED " << std::endl;
		break;
	}
}

//Input function for timetable
void classesViewer(int creditHours, int& Mon, int& Tues, int& Wed, int& Thurs, int& Fri, student a)
{
	std::string timeMonday;
	std::string timeTuesday;
	std::string timeWednesday;
	std::string timeThursday;
	std::string timeFriday;
	std::cout << "ENTER THE CLASSES YOU WANT ON MONDAY    : ";
	std::cin >> Mon;

	std::cout << std::endl << "ENTER THE TIME FOR DURING WHICH YOU WANT THE CLASSES : ";
	std::cin >> timeMonday;

	std::cout << std::endl << "ENTER THE CLASSES YOU WANT ON TUESDAY   : ";
	std::cin >> Tues;

	std::cout << std::endl << "ENTER THE TIME FOR DURING WHICH YOU WANT THE CLASSES : ";
	std::cin >> timeTuesday;

	std::cout << std::endl << "ENTER THE CLASSES YOU WANT ON WEDNESDAY : ";
	std::cin >> Wed;

	std::cout << std::endl << "ENTER THE TIME FOR DURING WHICH YOU WANT THE CLASSES : ";
	std::cin >> timeWednesday;

	std::cout << std::endl << "ENTER THE CLASSES YOU WANT ON THURSDAY  : ";
	std::cin >> Thurs;

	std::cout << std::endl << "ENTER THE TIME FOR DURING WHICH YOU WANT THE CLASSES : ";
	std::cin >> timeThursday;

	std::cout << std::endl << "ENTER THE CLASSES YOU WANT ON MONDAY    : ";
	std::cin >> Fri;

	std::cout << std::endl << "ENTER THE TIME FOR DURING WHICH YOU WANT THE CLASSES : ";
	std::cin >> timeFriday;
	if ((Mon + Tues + Wed + Thurs + Fri) != creditHours)
	{
		std::cout << "ENTER THE CREDIT HOURS THAT ARE EQUAL TO " << creditHours << " !" << std::endl;
		classesViewer(creditHours, Mon, Tues, Wed, Thurs, Fri, a);
	}
	std::fstream timeTable(a.getNameOfStudent() + "'s TIMETABLE.txt", std::ios::out);

	timeTable << "DEAR " << a.getNameOfStudent() << " Enrollment NO " << a.getEnrollmentNo() << std::endl << std::endl;
	timeTable << "YOUR TIMETABLE FOR SEMESTER " << a.getSemesterNo() << " WOULD BE LIKE !" << std::endl;
	timeTable << "CLASSES ON MONDAY ARE FOR\t\t: " << Mon << " HOURS!\t" << " DURING :\t" << timeMonday << std::endl;
	timeTable << "CLASSES ON TUESDAY ARE FOR\t\t: " << Tues << " HOURS!\t" << " DURING :\t" << timeTuesday << std::endl;
	timeTable << "CLASSES ON WEDNESDAY ARE FOR\t\t: " << Wed << " HOURS!\t" << " DURING :\t" << timeWednesday << std::endl;
	timeTable << "CLASSES ON THURSDAY ARE FOR\t\t: " << Thurs << " HOURS!\t" << " DURING :\t" << timeThursday << std::endl;
	timeTable << "CLASSES ON FRIDAY ARE FOR\t\t\t: " << Fri << " HOURS!\t" << " DURING :\t" << timeFriday << std::endl;
	timeTable.close();
}


// allow student to view handbook
void handBook()
{
	std::string eachLine;
	std::ifstream handBookFile("Student HandBook.txt", std::ios::in);
	system("cls");
	while (!handBookFile.eof())
	{
		getline(handBookFile, eachLine, '\n');
		std::cout << eachLine << std::endl;
	}
	handBookFile.close();
}

//
void restoreAllChanges()
{
	std::cout << "Restroring all the changes " << std::endl << std::endl;

	while (!changesMade.empty())
	{
		std::cout << "Restoring : " << changesMade.top().getNameOfStudent() << std::endl ;
		tree.InsertStudent(changesMade.top());
		changesMade.pop();
	}

	std::cin.get();
	std::cin.get();
}

void initiater()
{
	if (!ran)
	{
		tree.addStudentToTree();
		tree.InsertStudent(student("Ali", date(12, 10, 1995), "01-12345-67", "0333-12345", "CS", 1));
		tree.InsertStudent(student("Umair", date(1, 1, 2000), "01-23456-46", "0333-1234567", "CS", 1));
		tree.InsertStudent(student("Farhan", date(6, 5, 2005), "01-23421-56", "0333-2345678", "CS", 1));
		ran = true;
	}
}