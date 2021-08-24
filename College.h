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
	College(College&) = default;								// Copy

	// Setter and Getter methods
	void setName(string);
	void setCollegeCode(int);
	void setEmail(string);
	void setPhoneNumber(string);
	string getName();
	int getCollegeCode();
	string getEmail();
	string getPhoneNumber();
	void verify();
	void viewEnrolledStudents();
	void updateStudentPlacedStatus();

	//Destructor
	~College() = default;
};
