#include<iostream>
#include<string.h>
#include"College.h"
using namespace std;

// Constructor definition
College::College(string mCollegeName, int mCollegeCode, string mCollegeEmail, string mPhoneNumber, vector<Student> mStudentList) : collegeName(mCollegeName), collegeCode(mCollegeCode), collegeEmail(mCollegeEmail), phoneNumber(mPhoneNumber) , studentList(mStudentList)  {}

// Copy Constructor
// College(const College &collegeObject) : collegeName(collegeObject.collegeName), collegeCode(collegeObject.collegeCode), collegeEmail(collegeObject.collegeEmail), phoneNumber(collegeObject.phoneNumber) , studentList(collegeObject.studentList)  {}

void College::setName(string s)
{
	collegeName = s;
}

void College::setCollegeCode(int code)
{
	collegeCode = code;
}

void College::setEmail(string e)
{
	collegeEmail = e;
}

void College::setPhoneNumber(string pn)
{
	phoneNumber = pn;
}

string College::getName()
{
	return collegeName;
}

int College::getCollegeCode()
{
	return collegeCode;
}

string College::getEmail()
{
	return collegeEmail;
}

string College::getPhoneNumber()
{
	return phoneNumber;
}
