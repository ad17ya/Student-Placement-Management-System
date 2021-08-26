#include <iostream>
#include <string.h>
#include <sqlite3.h>
#include "College.h"
using namespace std;

// Constructor definition
College::College(string mCollegeName, int mCollegeCode, string mCollegeEmail, string mPhoneNumber, vector<Student> mStudentList) : collegeName(mCollegeName), collegeCode(mCollegeCode), collegeEmail(mCollegeEmail), phoneNumber(mPhoneNumber), studentList(mStudentList) {}

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

static int callback(void *data, int argc, char **argv, char **azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char *)data);

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

void College::viewEnrolledStudents()
{

	sqlite3 *DB;
	int exit = 0;
	exit = sqlite3_open("db.sqlite3", &DB);
	string data("");

	string sql("SELECT id,STUDENT_NAME FROM STUDENT");
	string sql_count("SELECT COUNT(STUDENT_ID) FROM STUDENT");

	try
	{
		if (exit)
			throw exit;

		std::cout << "Opened database successfully" << std::endl;

		int rc = sqlite3_exec(DB, sql.c_str(), callback, (void *)data.c_str(), NULL);
		std::cout << std::endl;
		int rc2 = sqlite3_exec(DB, sql_count.c_str(), callback, (void *)data.c_str(), NULL);

		if (rc != SQLITE_OK || rc2 != SQLITE_OK)
		{
			throw (short) -1;
		}
		
		cout << "Operation OK!" << endl;
	}

	catch(int exit) {
			std::cout << "Exception caught" << std::endl;
			std::cerr << "Error open DB" << sqlite3_errmsg(DB) << std::endl;
	}

	catch(short rc) {
			std::cout << "Exception caught" << endl;
			std::cerr << "Error getting count " << endl;
	}

	sqlite3_close(DB);
}

void College::updateStudentPlacedStatus()
{
}