#include "student.h"
#include "BinarySearchTree.h"
#include "Date.h"
#include "Node.h"
#include <queue>

// Date input menu
void dateMenu(date &);

// Main Menu 
void displayMainMenu(char&);

// Error for wrong choice
void errorWrongChoice(int,int);

// Check which menu to display student or admin
void displayStudentOrAdmin(char);

// Student Menu
void displayStudentMenu();

// Admin Menu
void displayAdminMenu();

/* ADMIN SECTION */

//Enter student details and store it in a file
void addANewStudent();

//Delete a student's records from the file
void removeAStudent();

//Delete all students' records from the file
void removeAllStudents();

// Enter course details and store it in a file
void addANewCourse();

//Delete all courses' records from the file
void removeAllCourses();

//Delete a course's records from the file
void removeACourse();

// View a student's details
void viewAStudent();

// View a course's details
void viewACourse();

// View all students' details
void viewAllStudents();

// View all courses' details
void viewAllCourses();


/* STUDENT SECTION */

// allow student to generate his timetable
void timeTabeGenerator(student);
void classesViewer(int, int&, int&, int&, int&, int&, student);

// allow student to view handbook
void handBook();

//restore changes
void restoreAllChanges();