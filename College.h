#pragma once
#include <iostream>
#include "Student.h"
using namespace std;

class College
{
private:
	string collegeName;
	int collegeCode;
	string collegeEmail;
	string phoneNumber;
	vector<Student> studentList;

public:

	// Constructors
	College() = default; 									 	// Default 
	College(string, int, string, string, vector<Student>);		// Parameterized
	College(const College&) = default;							// Copy

	void addStudent(const Student &);
	// Setter and Getter methods
	void setName(string);
	void setCollegeCode(int);
	void setEmail(string);
	void setPhoneNumber(string);

	string const getName();
	int const getCollegeCode();
	string const getEmail();
	string const getPhoneNumber();

	void verifyStudent();
	void viewEnrolledStudents(); // 
	void updateStudentPlacedStatus(); // Update placement status from temporary table to college database

	//Destructor
	~College() = default;
};

// coredump - size increase when shortage
// assembly code -- move push pop memory addreses
// assembly library
// static and dynamic
// debugging mode and release mode
// multithreading race condition and deadlock
// make and cmake

// Documentation
// Database diagram
// Code snippet and output
// Future scope - UI and web-based app